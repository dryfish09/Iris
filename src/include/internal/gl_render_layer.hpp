#pragma once

#include "nutils/types.hpp"
#include <glm/glm.hpp>
#include <GL/glew.h>

namespace iris::gl {
    enum class depth_func : u32 {
        none = 0,
        less,
        equal,
        greater,
    };

    struct init_config {
        glm::vec2 viewport_size;
        glm::vec2 viewport_offset;
        depth_func depth_func = depth_func::none;
    };

    struct scoped_texture_unit {
    private:
        u32 unit = 0;
    public:
        scoped_texture_unit() noexcept;
        u32 operator()() const noexcept;
        ~scoped_texture_unit();
    };

    void init(const init_config &cfg) noexcept;
}
