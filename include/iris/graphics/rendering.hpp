#pragma once

#include "glm/fwd.hpp"
#include "iris/types.hpp"
#include "windowing.hpp"

namespace iris {
    class renderer {
    public:
        struct config {
            glm::vec2 viewport_size_override;
            glm::vec2 viewport_offset_override;
            u32 fps;
            bool depth : 1;
            bool gles : 1;

            config() noexcept
                : viewport_size_override(-1, -1)
                , viewport_offset_override(-1, -1)
                , fps(60)
                , depth(false)
                , gles(false)
            {};

            ~config() noexcept {}
        };
    private:
        config config;
        void *resources;
    public:
        /// @brief Clear the screen
        void clear(rgba_color color = { 162, 32, 240, 255 }) noexcept;

        /// @brief Begin Frame
        /// @note Call this before doing anything graphical with the renderer
        void begin_frame() noexcept;

        /// @brief End Frame
        /// @note Call this to avoid crashing lol
        /// @note Also call this AFTER begin_frame... yeah.
        void end_frame() noexcept;

#ifdef Iris_Debug
        void debug() noexcept;
#endif

        renderer(const window &window, struct config cfg = {}) noexcept;

        ~renderer();
    };
}
