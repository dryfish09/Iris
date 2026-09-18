#pragma once

#include "nutils/types.hpp"
namespace iris::internal::bitutil {
    template<typename T>
    [[nodiscard]] constexpr T set(u8 index, T target) noexcept {
        return target | 1 << index;
    }

    template<typename T>
    [[nodiscard]] constexpr T clear(u8 index, T target) noexcept {
        return target & ~(1 << index);
    }

    template<typename T>
    [[nodiscard]] constexpr T toggle(u8 index, T target) noexcept {
        return target ^ 1 << index;
    }

    template<typename T>
    constexpr void setr(u8 index, T &target) noexcept {
        target |= 1 << index;
    }

    template<typename T>
    constexpr void clearr(u8 index, T &target) noexcept {
        target &= ~(1 << index);
    }

    template<typename T>
    constexpr void toggler(u8 index, T &target) noexcept {
        target ^= 1 << index;
    }

    template<typename T>
    [[nodiscard]] constexpr bool check(u8 index, T target) noexcept {
        return target & (1 << index);
    }
}
