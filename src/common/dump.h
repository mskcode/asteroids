#pragma once

#include "typealiases.h"
#include <array>
#include <cstddef>

namespace common {

auto dump_memory(const u8* ptr, size_t size) -> void;

template <typename TType, size_t TSize>
auto dump_memory(std::array<TType, TSize> array) -> void {
    dump_memory(reinterpret_cast<const u8*>(array.data()), sizeof(array));
}

template <typename TType>
auto dump_memory(TType obj) -> void {
    dump_memory(reinterpret_cast<const u8*>(&obj), sizeof(obj));
}

} // namespace common
