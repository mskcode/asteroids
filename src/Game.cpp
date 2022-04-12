#include "Game.h"
#include "ServiceLocator.h"
#include "TickLimiter.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace game;

static auto load_shaders() -> std::unique_ptr<engine::ShaderProgramRegistry> {
    using namespace engine;
    dbgln("Loading shaders");

    ShaderProgram shader1{
        {GL_VERTEX_SHADER,
         "./resources/shaders/vertex.vert",
         {{"position", 3, GL_FLOAT, false, 0}, {"color", 3, GL_FLOAT, false, sizeof(float) * 3}}},
        {GL_FRAGMENT_SHADER, "./resources/shaders/fragment.frag"},
    };

    ShaderProgram shader2{
        {GL_VERTEX_SHADER, "./resources/shaders/glyph.vert", {{"vertex", 4, GL_FLOAT, false, 0}}},
        {GL_FRAGMENT_SHADER, "./resources/shaders/glyph.frag"},
    };
    shader2.customize([](auto& shader) -> void {
        const auto screen_width = 1024;
        const auto screen_height = 768;
        auto location = shader.query_uniform_location("projection");
        glm::mat4 projection =
            glm::ortho(0.0f, static_cast<float>(screen_width), 0.0f, static_cast<float>(screen_height));
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));
    });

    auto registry = std::make_unique<engine::ShaderProgramRegistry>();
    registry->set(0, std::move(shader1));
    registry->set(1, std::move(shader2));
    return registry;
}

static auto load_fonts() -> std::unique_ptr<engine::FontBitmapCache> {
    using namespace engine;
    FontManager font_manager;
    font_manager.load_font("default", "./resources/fonts/arcadeclassic.ttf");
    auto& font = font_manager.get_font("default");
    font.set_pixel_sizes(24);
    auto font_bitmap_cache = FontBitmapCache::from(font);
    return font_bitmap_cache;
}

Game::Game(engine::Window& window) :
    window_(window),
    key_event_dispatcher_({window}) {}

void Game::initialize() {
    key_event_dispatcher_.register_listener([this](auto event) {
        if (event.is_keypress(GLFW_KEY_ESCAPE)) {
            this->window_.close();
        }
    });

    shader_program_registry_ = load_shaders();
    font_bitmap_cache_ = load_fonts();
    renderable_text_ = std::make_unique<engine::RenderableText>(*font_bitmap_cache_, shader_program_registry_->get(1));

    game_object_factory_ =
        std::make_unique<GameObjectFactory>(key_event_dispatcher_.keyboard(), *shader_program_registry_);
    game_object_factory_->create_spaceship();

    renderer_ = std::make_unique<Renderer>(window_, *game_object_factory_, *renderable_text_);
    key_event_dispatcher_.register_listener([this](auto event) {
        if (event.is_keypress(GLFW_KEY_F12)) {
            this->renderer_->toggle_wireframe_rendering();
        }
    });
}

void Game::loop() {
    TickLimiter update_tick_limiter{30};
    TickLimiter render_tick_limiter{60};

    while (!stop_requested_ && !window_.should_close()) {
        if (update_tick_limiter.should_tick()) {
            for (auto* updateable : game_object_factory_->updateables()) {
                updateable->update();
            }
            update_tick_limiter.tick();
        }

        if (render_tick_limiter.should_tick()) {
            renderer_->render();
            glfwSwapBuffers(window_.window_pointer());
            render_tick_limiter.tick();
        }

        glfwPollEvents();
    }
}
