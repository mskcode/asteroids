#ifndef OPENGL_KEYEVENTDISPATCHER_H
#define OPENGL_KEYEVENTDISPATCHER_H

#include "Window.h"

namespace opengl {

class KeyEventDispatcher final {
public:
    KeyEventDispatcher(const Window& window);
    KeyEventDispatcher(const KeyEventDispatcher&) = delete;
    KeyEventDispatcher(KeyEventDispatcher&&) = delete;
    ~KeyEventDispatcher() = default;

    auto operator=(const KeyEventDispatcher&) -> KeyEventDispatcher& = delete;
    auto operator=(KeyEventDispatcher&&) noexcept -> KeyEventDispatcher& = delete;
    
    void register_listener(const std::function<void(const KeyEvent&)>& listener);
    void dispatch_event(const KeyEvent& event);

private:
    std::vector<std::function<void(const KeyEvent&)>> listeners_;
};

} // namespace opengl

#endif // OPENGL_KEYEVENTDISPATCHER_H
