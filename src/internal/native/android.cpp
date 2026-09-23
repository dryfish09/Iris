#include "android_native_app_glue.h"
#include "spdlog/common.h"
#include <android/native_window.h>
#include <exception>
#include <format>
#include <native.hpp>
#include <string>
#include <gl.h>
#include <sys/system_properties.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/android_sink.h>

namespace iris::gl {
    void gl_init() noexcept {}
}

extern android_app *g_android_app;

namespace iris::native {
    void init() noexcept {
        auto sink = std::make_shared<spdlog::sinks::android_sink_mt>("Iris");
        auto logger = std::make_shared<spdlog::logger>("Iris", sink);
        spdlog::set_default_logger(logger);
    }

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
        return true; // which android device doesn't have a damn touchscreen bro
    }

    std::string device_name() noexcept {
        char buf[PROP_VALUE_MAX + 1] = {};
        __system_property_get("ro.product.model", buf);
        return buf;
    }

    std::string processor_name() noexcept {
        char buf[PROP_VALUE_MAX + 1] = {};
        __system_property_get("ro.soc.manufacturer", buf);
        std::string manufacturer = buf;
        memset(buf, 0, PROP_VALUE_MAX + 1);
        __system_property_get("ro.soc.model", buf);
        std::string model = buf;
        
        return std::format("{} {}", manufacturer, model);
    }

    glm::ivec2 screen_resolution() noexcept {
        ANativeWindow *window = g_android_app->window;
        if (window == nullptr) {
            return { 0, 0 };
        } else {
            return { ANativeWindow_getWidth(window), ANativeWindow_getHeight(window) };
        }
    }
}
