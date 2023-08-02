#pragma once

#include <cassert>
#include <memory>
#include <optional>
#include <utility>

namespace common::result {

struct EmptyResultValue {};
struct EmptyResultError {};

template <typename, typename>
class Result;

template <typename T>
auto make_success_result(T value) -> Result<T, EmptyResultError> {
    std::optional<T> tmp_value{value};
    std::optional<EmptyResultError> tmp_error{std::nullopt};
    return {std::move(tmp_value), std::move(tmp_error)};
}

template <typename E>
auto make_error_result(E error) -> Result<EmptyResultValue, E> {
    std::optional<EmptyResultValue> tmp_value{std::nullopt};
    std::optional<E> tmp_error{error};
    return {std::move(tmp_value), std::move(tmp_error)};
}

template <typename T, typename E>
class [[nodiscard]] Result final {
    using ValueType = T;
    using ErrorType = E;

    template <typename T1>
    friend auto make_success_result(T1 value) -> Result<T1, EmptyResultError>;

    template <typename E1>
    friend auto make_error_result(E1 error) -> Result<EmptyResultValue, E1>;

public:
    Result() = delete;
    Result(const Result&) = default;
    Result(Result&&) noexcept = default;
    ~Result() noexcept = default;

    auto operator=(const Result&) -> Result& = default;
    auto operator=(Result&&) noexcept -> Result& = default;

    [[nodiscard]] auto is_ok() const -> bool { return !is_error_; }
    [[nodiscard]] auto is_error() const -> bool { return is_error_; }

    [[nodiscard]] auto value() const -> const ValueType& {
        assert(!is_error_);
        assert(!is_released_);
        return value_.value();
    }

    [[nodiscard]] auto error() const -> const ErrorType& {
        assert(is_error_);
        assert(!is_released_);
        return error_.value();
    }

    [[nodiscard]] auto release_value() -> ValueType {
        assert(!is_error_);
        assert(!is_released_);

        std::optional<ValueType> tmp;
        value_.swap(tmp);

        auto unboxed_value = std::move(tmp.value());
        // value_.value().~ValueType();
        is_released_ = true;
        return unboxed_value;
    }

    [[nodiscard]] auto release_error() -> ErrorType {
        assert(is_error_);
        assert(!is_released_);

        std::optional<ErrorType> tmp;
        error_.swap(tmp);

        auto unboxed_error = std::move(tmp.value());
        error_.value().~ErrorType();
        is_released_ = true;
        return unboxed_error;
    }

private:
    Result(std::optional<ValueType>&& value, std::optional<ErrorType>&& error) :
        value_(std::exchange(value, {})),
        error_(std::exchange(error, {})),
        is_error_(error_.has_value()),
        is_released_(false) {
        // both variables cannot be set at the same time
        assert(!(value_.has_value() && error_.has_value()));
        // both variables cannot be empty at the same time
        assert(!(!value_.has_value() && !error_.has_value()));
    }

    std::optional<ValueType> value_;
    std::optional<ErrorType> error_;
    const bool is_error_;
    bool is_released_;
};

// TODO implement partial specialization for void value type

} // namespace common::result
