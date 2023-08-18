#include "Game.h"
#include "ResourceId.h"
#include "TickLimiter.h"
#include "engine/Keyboard.h"
#include "engine/Mouse.h"
#include "engine/MouseKeyboardCameraDirector.h"
#include "engine/Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace game;

static auto load_shaders() -> void {
    using namespace engine;
    dbgln("Loading shaders");

    auto shader1 = ShaderProgram::create("default",
                                         Shader::create(GL_VERTEX_SHADER,
                                                        "./resources/shaders/default_vert.glsl",
                                                        {{.location = 0,
                                                          .name = "in_position",
                                                          .size = 3,
                                                          .type = GL_FLOAT,
                                                          .normalized = false,
                                                          .relative_offset = 0},
                                                         {.location = 1,
                                                          .name = "in_vertex_color",
                                                          .size = 4,
                                                          .type = GL_FLOAT,
                                                          .normalized = false,
                                                          .relative_offset = sizeof(float) * 3},
                                                         {.location = 2,
                                                          .name = "in_texture_coordinates",
                                                          .size = 2,
                                                          .type = GL_FLOAT,
                                                          .normalized = false,
                                                          .relative_offset = sizeof(float) * 7}}),
                                         Shader::create(GL_FRAGMENT_SHADER, "./resources/shaders/default_frag.glsl"));

    auto shader2 = ShaderProgram::create("glyph",
                                         Shader::create(GL_VERTEX_SHADER,
                                                        "./resources/shaders/glyph_vert.glsl",
                                                        {{.location = 0,
                                                          .name = "in_vertex",
                                                          .size = 4,
                                                          .type = GL_FLOAT,
                                                          .normalized = false,
                                                          .relative_offset = 0}}),
                                         Shader::create(GL_FRAGMENT_SHADER, "./resources/shaders/glyph_frag.glsl"));

    shader2.customize([](auto& shader) -> void {
        const auto screen_width = 1024;
        const auto screen_height = 768;
        auto location = shader.query_uniform_location("projection");
        glm::mat4 projection = glm::ortho(0.0f,
                                          static_cast<float>(screen_width),
                                          0.0f,
                                          static_cast<float>(screen_height));
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));
    });

    ShaderProgramRegistry::instance().set(ShaderProgramResources::DEFAULT, shader1);
    ShaderProgramRegistry::instance().set(ShaderProgramResources::GLYPH, shader2);
}

static auto load_fonts() -> void {
    using namespace engine;
    auto& font_manager = FontManager::instance();
    auto& font_bitmap_cache_registry = FontBitmapCacheRegistry::instance();

    auto font = font_manager.load(FontResources::ARCADE, "./resources/fonts/arcadeclassic.ttf");
    font_bitmap_cache_registry.create(FontBitmapCacheResources::ARCADE_48, font, {48, 0});
}

static auto load_textures() -> void {
    using namespace engine;
    auto& texture_registry = TextureRegistry::instance();
    texture_registry.load_texture(TextureResources::SMILEY, "./resources/images/smiley-256x256.png");
}

Game::Game(engine::Window& window) :
    window_(window) {}

void Game::initialize() {
    auto& keyboard = engine::Keyboard::instance();
    keyboard.attach(window_);
    keyboard.register_listener([this](auto event) {
        if (event.is_keypress(GLFW_KEY_ESCAPE)) {
            this->window_.close();
        }
    });

    auto& mouse = engine::Mouse::instance();
    mouse.attach(window_);

    load_shaders();
    load_fonts();
    load_textures();

    renderable_text_ = std::make_unique<engine::TextRenderer>(ShaderProgramResources::GLYPH);

    game_object_factory_ = std::make_unique<GameObjectFactory>();

    game_object_factory_->create_spaceship();

    camera_director_ = std::make_unique<engine::MouseKeyboardCameraDirector>();
    camera_ = std::make_unique<engine::Camera>(*camera_director_, ShaderProgramResources::DEFAULT, "camera_matrix");
    camera_->set_window_dimensions(window_.window_size());

    renderer_ = std::make_unique<Renderer>(window_, *camera_, *game_object_factory_, *renderable_text_);
    keyboard.register_listener([this](auto event) {
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
            camera_director_->update();
            for (auto* updateable : game_object_factory_->updateables()) {
                updateable->update();
            }
            update_tick_limiter.tick();
        }

        if (render_tick_limiter.should_tick()) {
            renderer_->render();
            render_tick_limiter.tick();
        }

        glfwPollEvents();
    }
}
