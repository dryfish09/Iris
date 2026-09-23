#include <exception>
#include <native.hpp>
#include <string>
#include <gl.h>

namespace iris::gl {
    void gl_init() noexcept {
        glewExperimental = true;
        glewInit();
    }
}

namespace iris::native {
    void init() noexcept {}
    void terminate() noexcept {
        std::terminate();
    }

    bool keyboard_connected() noexcept {
        return false;
    }

    bool mouse_connected() noexcept {
        return false;
    }

    bool touch_connected() noexcept {
        return false;
    }

    std::string device_name() noexcept {
        return "Unknown";
    }

    std::string processor_name() noexcept {
        return "Unknown";
    }

    glm::ivec2 screen_resolution() noexcept {
        return { 0, 0 };
    }
}
