#pragma once

#include <glm/glm.hpp>
#include "nutils/types.hpp"
#include <string_view>

namespace iris::native {
    [[noreturn]] void terminate() noexcept;
    [[nodiscard]] bool keyboard_connected() noexcept;
    [[nodiscard]] bool mouse_connected() noexcept;
    [[nodiscard]] bool touch_connected() noexcept;
    [[nodiscard]] std::string device_name() noexcept;
    [[nodiscard]] std::string processor_name() noexcept;
    [[nodiscard]] glm::ivec2 screen_resolution() noexcept;
}
