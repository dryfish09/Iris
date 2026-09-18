#include "iris/io/io.hpp"
#include "iris/runtime.hpp"
#include <iris/graphics/windowing.hpp>
#include <GLFW/glfw3.h>

namespace {
    static u32 glfw_inits = 0;

    namespace callback {
        void glfw_error(int code, const char *description) {
            spdlog::critical("GLFW has encountered an error ({}): {}", code, description);
        }
    }

    void glfw_init() {
        if (glfw_inits == 0) {
            glfwInit();
            glfwSetErrorCallback(callback::glfw_error);
            ++glfw_inits;
        }
    }

    void glfw_terminate() {
        if (glfw_inits == 0) {
            glfwTerminate();
        } else {
            --glfw_inits;
        }
    }
}

namespace iris {
    void window::create(const std::string &title, glm::ivec2 size) noexcept {
        glfw_init();
        if (this->config.msaa_samples > 0) {
            glfwWindowHint(GLFW_SAMPLES, this->config.msaa_samples);
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        this->handle = glfwCreateWindow(
            size.x,
            size.y,
            title.c_str(),
            nullptr,
            nullptr
        );

        if (this->handle == nullptr) {
            crash("Window creation failed: glfwCreateWindow returned nullptr");
        }

        glfwSetWindowUserPointer(reinterpret_cast<GLFWwindow*>(this->handle), this);

        // whatever i'll keep this?
        glfwShowWindow(reinterpret_cast<GLFWwindow*>(this->handle));
    }

    bool window::running() const noexcept {
        return !glfwWindowShouldClose(reinterpret_cast<GLFWwindow*>(this->handle));
    }

    void window::swap_buffers() const noexcept {
        glfwSwapBuffers(reinterpret_cast<GLFWwindow*>(this->handle));
    }

    void window::make_gl_context_current() const noexcept {
        glfwMakeContextCurrent(reinterpret_cast<GLFWwindow*>(this->handle));
    }

    static io::key glfw_to_iris(i32 k) noexcept {
        switch (k) {
            case GLFW_KEY_A: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_B: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_C: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_D: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_E: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_F: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_G: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_H: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_I: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_J: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_K: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_L: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_M: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_N: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_O: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_P: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_Q: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_R: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_S: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_T: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_U: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_V: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_W: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_X: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_Y: return io::key(k - GLFW_KEY_A);
            case GLFW_KEY_Z: return io::key(k - GLFW_KEY_A);

            case GLFW_KEY_0: return io::key::num_0;
            case GLFW_KEY_1: return io::key::num_1;
            case GLFW_KEY_2: return io::key::num_2;
            case GLFW_KEY_3: return io::key::num_3;
            case GLFW_KEY_4: return io::key::num_4;
            case GLFW_KEY_5: return io::key::num_5;
            case GLFW_KEY_6: return io::key::num_6;
            case GLFW_KEY_7: return io::key::num_7;
            case GLFW_KEY_8: return io::key::num_8;
            case GLFW_KEY_9: return io::key::num_9;

            case GLFW_KEY_SPACE: return io::key::space;
            case GLFW_KEY_APOSTROPHE: return io::key::apostrophe;
            case GLFW_KEY_COMMA: return io::key::comma;
            case GLFW_KEY_MINUS: return io::key::minus;
            case GLFW_KEY_PERIOD: return io::key::period;
            case GLFW_KEY_SLASH: return io::key::slash;
            case GLFW_KEY_SEMICOLON: return io::key::semicolon;
            case GLFW_KEY_EQUAL: return io::key::equal;
            case GLFW_KEY_LEFT_BRACKET: return io::key::left_bracket;
            case GLFW_KEY_BACKSLASH: return io::key::backslash;
            case GLFW_KEY_RIGHT_BRACKET: return io::key::right_bracket;
            case GLFW_KEY_GRAVE_ACCENT: return io::key::grave;

            case GLFW_KEY_ESCAPE: return io::key::escape;
            case GLFW_KEY_ENTER: return io::key::enter;
            case GLFW_KEY_TAB: return io::key::tab;
            case GLFW_KEY_BACKSPACE: return io::key::backspace;
            case GLFW_KEY_INSERT: return io::key::insert;
            case GLFW_KEY_DELETE: return io::key::delete_;

            case GLFW_KEY_RIGHT: return io::key::right;
            case GLFW_KEY_LEFT: return io::key::left;
            case GLFW_KEY_DOWN: return io::key::down;
            case GLFW_KEY_UP: return io::key::up;

            case GLFW_KEY_PAGE_UP: return io::key::page_up;
            case GLFW_KEY_PAGE_DOWN: return io::key::page_down;
            case GLFW_KEY_HOME: return io::key::home;
            case GLFW_KEY_END: return io::key::end;

            case GLFW_KEY_CAPS_LOCK: return io::key::caps_lock;
            case GLFW_KEY_SCROLL_LOCK: return io::key::scroll_lock;
            case GLFW_KEY_NUM_LOCK: return io::key::num_lock;
            case GLFW_KEY_PRINT_SCREEN: return io::key::print_screen;
            case GLFW_KEY_PAUSE: return io::key::pause;

            case GLFW_KEY_F1: return io::key::f1;
            case GLFW_KEY_F2: return io::key::f2;
            case GLFW_KEY_F3: return io::key::f3;
            case GLFW_KEY_F4: return io::key::f4;
            case GLFW_KEY_F5: return io::key::f5;
            case GLFW_KEY_F6: return io::key::f6;
            case GLFW_KEY_F7: return io::key::f7;
            case GLFW_KEY_F8: return io::key::f8;
            case GLFW_KEY_F9: return io::key::f9;
            case GLFW_KEY_F10: return io::key::f10;
            case GLFW_KEY_F11: return io::key::f11;
            case GLFW_KEY_F12: return io::key::f12;
            case GLFW_KEY_F13: return io::key::f13;
            case GLFW_KEY_F14: return io::key::f14;
            case GLFW_KEY_F15: return io::key::f15;
            case GLFW_KEY_F16: return io::key::f16;
            case GLFW_KEY_F17: return io::key::f17;
            case GLFW_KEY_F18: return io::key::f18;
            case GLFW_KEY_F19: return io::key::f19;
            case GLFW_KEY_F20: return io::key::f20;
            case GLFW_KEY_F21: return io::key::f21;
            case GLFW_KEY_F22: return io::key::f22;
            case GLFW_KEY_F23: return io::key::f23;
            case GLFW_KEY_F24: return io::key::f24;

            case GLFW_KEY_KP_0: return io::key::keypad_0;
            case GLFW_KEY_KP_1: return io::key::keypad_1;
            case GLFW_KEY_KP_2: return io::key::keypad_2;
            case GLFW_KEY_KP_3: return io::key::keypad_3;
            case GLFW_KEY_KP_4: return io::key::keypad_4;
            case GLFW_KEY_KP_5: return io::key::keypad_5;
            case GLFW_KEY_KP_6: return io::key::keypad_6;
            case GLFW_KEY_KP_7: return io::key::keypad_7;
            case GLFW_KEY_KP_8: return io::key::keypad_8;
            case GLFW_KEY_KP_9: return io::key::keypad_9;
            case GLFW_KEY_KP_DECIMAL: return io::key::keypad_decimal;
            case GLFW_KEY_KP_DIVIDE: return io::key::keypad_divide;
            case GLFW_KEY_KP_MULTIPLY: return io::key::keypad_multiply;
            case GLFW_KEY_KP_SUBTRACT: return io::key::keypad_subtract;
            case GLFW_KEY_KP_ADD: return io::key::keypad_add;
            case GLFW_KEY_KP_ENTER: return io::key::keypad_enter;
            case GLFW_KEY_KP_EQUAL: return io::key::keypad_equal;

            case GLFW_KEY_LEFT_SHIFT: return io::key::left_shift;
            case GLFW_KEY_LEFT_CONTROL: return io::key::left_control;
            case GLFW_KEY_LEFT_ALT: return io::key::left_alt;
            case GLFW_KEY_LEFT_SUPER: return io::key::left_super;

            case GLFW_KEY_RIGHT_SHIFT: return io::key::right_shift;
            case GLFW_KEY_RIGHT_CONTROL: return io::key::right_control;
            case GLFW_KEY_RIGHT_ALT: return io::key::right_alt;
            case GLFW_KEY_RIGHT_SUPER: return io::key::right_super;

            case GLFW_KEY_MENU: return io::key::menu;
        }

        return io::key::none;
                // {
                //     int state = glfwGetKey(reinterpret_cast<GLFWwindow*>(this->handle), i);
                //     size_t idx = static_cast<u32>(io::key::a) + (i - GLFW_KEY_A);
                //     if (state == GLFW_PRESS) {
                //         this->keys[idx].make_down();
                //         spdlog::info("Key Press: {}", static_cast<char>(65 + (i - GLFW_KEY_A)));
                //     } else if (state == GLFW_RELEASE) {
                //         this->keys[idx].make_released();
                //     }
                //     break;
                // }
    }

    void window::poll_events() noexcept {
        glfwPollEvents();
        for (int i = GLFW_KEY_SPACE; i <= GLFW_KEY_LAST; ++i) {
            const io::key key = glfw_to_iris(i);
            int state = glfwGetKey(reinterpret_cast<GLFWwindow*>(this->handle), i);
            size_t idx = static_cast<u32>(key);
            if (state == GLFW_PRESS) {
                this->keys[idx].make_down();
            } else if (state == GLFW_RELEASE) {
                this->keys[idx].make_released();
            }
        }
    }

    window::window() noexcept {
        this->create("Iris — Unnamed Window", { 800, 600 });
    }

    window::window(const std::string &title, glm::ivec2 sz) noexcept {
        this->create(title, sz);
    }

    window::~window() {
        glfwDestroyWindow(reinterpret_cast<GLFWwindow*>(this->handle));
        glfw_terminate();
    }
}
