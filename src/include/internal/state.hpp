#pragma once

#include <iris/runtime.hpp>
#include <limits>
#include <spdlog/spdlog.h>
#include <gl_render_layer.hpp>

namespace iris::internal {
    struct global_state {
        struct {
            u32 bound_framebuffer = 0;
            u32 bound_texture = 0;
            u32 texture_unit_freelist = 0;
            i32 max_texture_units = 0;
        } gl_state;
        log_hook log_hook = nullptr;
    };

    extern global_state g_state;
}
