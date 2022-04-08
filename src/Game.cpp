#include "Game.h"
#include "ServiceLocator.h"
#include "TickLimiter.h"

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

    auto registry = std::make_unique<engine::ShaderProgramRegistry>();
    registry->set(0, std::move(shader1));

    return registry;
}

static auto load_fonts() -> std::unique_ptr<engine::FontBitmapMap> {
    using namespace engine;
    FontManager font_manager;
    font_manager.load_font("default", "./resources/fonts/arcadeclassic.ttf");
    auto font = font_manager.get_font("default");
    auto font_bitmap_map = FontBitmapMap::from(font);
    return font_bitmap_map;
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
    font_bitmap_map_ = load_fonts();

    game_object_factory_ =
        std::make_unique<GameObjectFactory>(key_event_dispatcher_.keyboard(), *shader_program_registry_);
    game_object_factory_->create_spaceship();

    renderer_ = std::make_unique<Renderer>(window_, *game_object_factory_);
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
