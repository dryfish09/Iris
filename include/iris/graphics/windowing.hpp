#pragma once

#include <string>
#include <glm/glm.hpp>
#include <unordered_map>
#include "iris/io/io.hpp"

namespace iris {
    class window {
        friend class renderer;
    public:
        struct config {
            bool vsync : 1;
            /// @brief OpenGL ES mode
            /// @note Does not actually create an OpenGL ES window
            ///       on desktop platforms, only signals to the renderer
            ///       to use OpenGL ES mode i.e. a standards-compliant mode
            ///       so it can work across a variety of OpenGL ES devices
            ///       and disables Desktop-OpenGL only features.
            bool gles : 1;
            u32 msaa_samples : 4; // upto 15 but 2,4,8 only

            config() noexcept 
                : vsync(false)
                , gles(false)
                , msaa_samples(0)
            {}
        };
    private:
        io::key_state keys[io::keys];
        config config;

        void *handle = nullptr; 

        void create(const std::string &title, glm::ivec2 size) noexcept;
        void make_gl_context_current() const noexcept;
    public:
        /// @brief Get the key state for any key
        [[nodiscard]] io::key_state key_state(io::key key) const noexcept;

        // @brief Get the touch point(s) on a single-touch or multi-touch
        //        surface
        [[nodiscard]] std::unordered_map<i32, glm::vec2> touch_points() noexcept;

        /// @brief Swaps buffers (calls underlying swap function)
        void swap_buffers() const noexcept;

        /// @brief Query window running status
        [[nodiscard]] bool running() const noexcept;

        /// @brief Returns if the window surface is visible to the user
        /// @note Use this to know if you should render or not
        [[nodiscard]] bool visible_surface() const noexcept;

        /// @brief Poll events
        /// @note Call every frame or your window will appear unresponsive
        void poll_events() noexcept;

        /// @brief Query framebuffer size
        [[nodiscard]] glm::ivec2 framebuffer_size() const noexcept;

        window() noexcept;
        window(const std::string &title, glm::ivec2 size, const struct config &config = {}) noexcept;

        ~window();
    };
}
