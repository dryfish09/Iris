#pragma once

#include "../types.hpp"
#include "glm/fwd.hpp"
#include <cstddef>
#include <vector>

namespace iris::io {
    enum class key : u32 {
        none = 0,

        escape, 
        f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12,
        f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24,

        grave,

        num_1,
        num_2,
        num_3,
        num_4,
        num_5,
        num_6,
        num_7,
        num_8,
        num_9,
        num_0,

        minus,
        equal,
        
        backspace,
        tab,
        
        left_bracket,
        right_bracket,
        backslash,

        caps_lock,

        semicolon,
        apostrophe,
        enter,

        left_shift,
        comma,
        period,
        slash,
        right_shift,
        
        left_control,
        left_alt,
        left_super,

        space,

        right_control,
        right_alt,
        right_super,

        a, b, c, d, e, f, g, h, i, j, k, l, m,
        n, o, p, q, r, s, t, u, v, w, x, y, z,

        insert,
        delete_,

        right,
        left,
        down,
        up,

        page_up,
        page_down,
        home,
        end,

        scroll_lock,
        num_lock,
        print_screen,
        pause,

        keypad_0,
        keypad_1,
        keypad_2,
        keypad_3,
        keypad_4,
        keypad_5,
        keypad_6,
        keypad_7,
        keypad_8,
        keypad_9,

        keypad_decimal,
        keypad_divide,
        keypad_multiply,
        keypad_subtract,
        keypad_add,
        keypad_enter,
        keypad_equal,

        menu,

        // Mouse Buttons
        lmb, rmb,

        // Touch
        finger,

        last = finger,
    };

    constexpr size_t keys = static_cast<u32>(key::finger) + 1;
    static_assert(keys == 121);

    struct key_state {
        bool now = false;
        bool previous = false;

        constexpr bool down() const noexcept {
            return this->now;
        }

        constexpr bool press() const noexcept {
            return !this->now && this->previous;
        }

        constexpr bool released() const noexcept {
            return !this->now;
        }

        void make_down() noexcept {
            this->now = true;
        }

        void make_press() noexcept {
            this->now = false;
            this->previous = true;
        }

        void make_released() noexcept {
            this->now = false;
        }
    };

    // TODO: Touch API
}
