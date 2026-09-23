#include <cstddef>
#include <exception>
#include <fstream>
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
        std::ifstream file("/sys/devices/virtual/dmi/id/product_name");
        file.seekg(0, std::ios::end);
        size_t sz = file.tellg();
        file.seekg(0, std::ios::beg);
        std::string name;
        name.resize(sz + 1);
        file.read(name.data(), sz);
        name[sz] = '\0';
        name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
        return name;
    }

    std::string processor_name() noexcept {
        const char *cmd = "cat /proc/cpuinfo | grep 'model name' | sed 's/^model name[[:space:]]*:[[:space:]]*//'";
        FILE *pipe = popen(cmd, "r");
        char buf[512];
        fgets(buf, 512, pipe);
        pclose(pipe);
        std::string result = buf;
        result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
        return result;
    }

    glm::ivec2 screen_resolution() noexcept {
        return { 0, 0 };
    }
}
