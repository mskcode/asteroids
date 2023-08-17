#pragma once

#include "GameObjectFactory.h"
#include "Renderer.h"
#include "engine/Camera.h"
#include "engine/CameraDirector.h"
#include "engine/FontBitmapCache.h"
#include "engine/Window.h"
#include <memory>

namespace game {

class Game final {
public:
    Game(engine::Window& window);
    ~Game() = default;

    void initialize();
    void loop();

private:
    engine::Window& window_;
    std::unique_ptr<GameObjectFactory> game_object_factory_;
    std::unique_ptr<Renderer> renderer_;
    std::unique_ptr<engine::FontBitmapCache> font_bitmap_cache_;
    std::unique_ptr<engine::TextRenderer> renderable_text_;
    std::unique_ptr<engine::Camera> camera_;
    std::unique_ptr<engine::CameraDirector> camera_director_;
    bool stop_requested_ = false;
};

} // namespace game
