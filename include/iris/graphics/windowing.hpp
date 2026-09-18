#pragma once

#include <string>
#include <glm/glm.hpp>
#include "../io/io.hpp"

namespace iris {
    class window {
        friend class renderer;
    private:
        io::key_state keys[io::keys];
        struct {
            bool vsync : 1 = false;
            u32 msaa_samples : 4 = 0; // upto 15 but 2,4,8 only
        } config;

        void *handle = nullptr; 

        void create(const std::string &title, glm::ivec2 size) noexcept;
        void make_gl_context_current() const noexcept;
    public:
        /// @brief Get the key state for any key
        [[nodiscard]] io::key_state key_state(io::key key) const noexcept;

        // @brief Get the touch point(s) on a single-touch or multi-touch
        //        surface
        [[nodiscard]] std::vector<glm::vec2> touch_points() noexcept;

        /// @brief Swaps buffers (calls underlying swap function)
        void swap_buffers() const noexcept;

        /// @brief Returns if the window is still running
        [[nodiscard]] bool running() const noexcept;

        /// @brief Returns if the window surface is visible to the user
        /// @note Use this to know if you should render or not
        [[nodiscard]] bool visible_surface() const noexcept;

        /// @brief Poll events
        /// @note Call every frame or your window will appear unresponsive
        void poll_events() noexcept;

        window() noexcept;
        window(const std::string &title, glm::ivec2 size) noexcept;

        ~window();
    };
}
