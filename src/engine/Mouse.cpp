#include "Mouse.h"

using namespace engine;

auto Mouse::operator[](int key) -> MouseButtonState& {
    return button_states_[key];
}

auto Mouse::operator[](int key) const -> const MouseButtonState& {
    return button_states_[key];
}

auto Mouse::position() const -> Point2DL {
    return current_;
}

void Mouse::set_position(Point2DL point) {
    current_.x = point.x;
    current_.y = point.y;
}
