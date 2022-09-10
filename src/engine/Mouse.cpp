#include "Mouse.h"

using namespace engine;

auto Mouse::operator[](int key) -> MouseButtonState& {
    return button_states_[key];
}

auto Mouse::operator[](int key) const -> const MouseButtonState& {
    return button_states_[key];
}

auto Mouse::position() const -> Point2DD {
    return {x_position_, y_position_};
}

auto Mouse::x_position() const -> double {
    return x_position_;
}

auto Mouse::y_position() const -> double {
    return y_position_;
}

void Mouse::set_position(double x, double y) {
    x_position_ = x;
    y_position_ = y;
}
