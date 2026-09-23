#pragma once

#include "iris/platform_macros.hpp"

#ifdef Iris_Platform_Desktop
#include <GL/glew.h>
#elifdef Iris_Platform_Android
#include <GLES3/gl3.h>
#endif

namespace iris::gl {
    void gl_init() noexcept;
}
