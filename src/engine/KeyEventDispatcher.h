#ifndef ENGINE_KEYEVENTDISPATCHER_H
#define ENGINE_KEYEVENTDISPATCHER_H

#include "Keyboard.h"
#include "Window.h"

namespace engine {

class KeyEventDispatcher final {
public:
    KeyEventDispatcher(const Window& window);
    KeyEventDispatcher(const KeyEventDispatcher&) = delete;
    KeyEventDispatcher(KeyEventDispatcher&&) = delete;
    ~KeyEventDispatcher() = default;

    auto operator=(const KeyEventDispatcher&) -> KeyEventDispatcher& = delete;
    auto operator=(KeyEventDispatcher&&) noexcept -> KeyEventDispatcher& = delete;

    [[nodiscard]] auto keyboard() const -> const Keyboard&;

    void register_listener(const std::function<void(const KeyEvent&)>& listener);
    void dispatch_event(const KeyEvent& event);

private:
    Keyboard keyboard_;
    std::vector<std::function<void(const KeyEvent&)>> listeners_;
};

} // namespace engine

#endif // ENGINE_KEYEVENTDISPATCHER_H
