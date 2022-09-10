#include "Mouse.h"

using namespace engine;

auto Mouse::operator[](int key) -> MouseButtonState& {
    return button_states_[key];
}

auto Mouse::operator[](int key) const -> const MouseButtonState& {
    return button_states_[key];
}

auto Mouse::position() const -> Point2DD {
    return current_;
}

void Mouse::set_initial_position(Point2DD point) {
    initial_ = point;
}

void Mouse::set_position(Point2DD point) {
    // compute the normalized position
    // the origin point is { 0, 0 }
    current_.x = -(initial_.x - point.x);
    current_.y = -(initial_.y - point.y);
}
