#pragma once

#include "nutils/types.hpp"
#include <gl.h>

namespace iris::internal {
    enum class shader_type {
        rectangle
    };

    [[nodiscard]] u32 get_shader_program(shader_type type) noexcept;
}
