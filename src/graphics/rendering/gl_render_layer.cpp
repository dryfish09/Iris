#include "gl_render_layer.hpp"
#include "error.hpp"
#include "spdlog/spdlog.h"
#include "state.hpp"
#include "bitutil.hpp"

#include <GL/glew.h>

using namespace iris::internal;

namespace iris::gl {
    u32 compile_debug_shader() noexcept {
        const char *vertex = "", *fragment = "";
        u32 vert, frag;
        i32 success;
        char log[512];

        vert = glCreateShader(GL_VERTEX_SHADER);
        frag = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(vert, 1, &vertex, nullptr);
        glShaderSource(frag, 1, &fragment, nullptr);

        glCompileShader(vert);
        glCompileShader(frag);

        u32 prog = glCreateProgram();
        glAttachShader(prog, vert);
        glAttachShader(prog, frag);

        glLinkProgram(prog);

        glDeleteShader(vert);
        glDeleteShader(frag);

        return prog;
    }

    void init(const init_config &cfg) noexcept {
        glViewport(
            static_cast<i32>(cfg.viewport_size.x),
            static_cast<i32>(cfg.viewport_size.y),
            static_cast<i32>(cfg.viewport_offset.x),
            static_cast<i32>(cfg.viewport_offset.y)
        );

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &g_state.gl_state.max_texture_units);

        for (i32 i = 0; i < g_state.gl_state.max_texture_units; ++i) {
            bitutil::setr(i, g_state.gl_state.texture_unit_freelist);
        }

        spdlog::info("OpenGL initialized with driver \"{}\"", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    }

    void glew_init() noexcept {
        [[maybe_unused]] static i32 _ = []() -> i32 {
            glewExperimental = true;
            glewInit();
            return 0;
        } ();
    }

    scoped_texture_unit::scoped_texture_unit() noexcept {
        for (i32 i = 0; i < g_state.gl_state.max_texture_units; ++i) {
            if (bitutil::check(i, g_state.gl_state.texture_unit_freelist)) {
                bitutil::clearr(i, g_state.gl_state.texture_unit_freelist); 
                this->unit = i;
                return;
            }
        }

        iris::error(error_code::texture_units_exhausted);
    }

    scoped_texture_unit::~scoped_texture_unit() {
        bitutil::setr(this->unit, g_state.gl_state.texture_unit_freelist);
    }
}
