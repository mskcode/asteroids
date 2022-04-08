#ifndef COMMON_SIGNAL_H
#define COMMON_SIGNAL_H

#include <functional>
#include <vector>

namespace common {

class Signal final {
public:
    Signal(int number) :
        number_(number) {}

    [[nodiscard]] auto number() const -> int { return number_; }
    [[nodiscard]] auto is(int number) const -> bool { return number_ == number; }

private:
    int number_;
};

using SignalListenerList = std::vector<std::function<void(const Signal&)>>;

class SignalHandler final {
public:
    SignalHandler();

    void register_listener(const std::function<void(const Signal&)>& listener, int signal_number);
    void register_listener(const std::function<void(const Signal&)>& listener, const std::vector<int>& signal_numbers);
    void handle_signal(int signal_number);

private:
    std::unordered_map<int, SignalListenerList> listeners_;
};

} // namespace common

#endif //  COMMON_SIGNAL_H
