#pragma once

#include <glm/glm.hpp>
#include "iris/types.hpp"
#include "iris/graphics/windowing.hpp"

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
        struct drawcall;

        std::vector<drawcall> drawcalls;
        config config;
        const window &window;
        glm::vec2 viewport_size_;
        glm::vec2 viewport_offset_;
        void *resources = nullptr;
        bool begin_frame_called = false;

        void pre_draw_check() const noexcept;
        void flush_drawcalls() noexcept;
    public:
        /// @brief Clear the screen
        void clear(rgba_color color = { 14, 14, 14, 255 }) noexcept;

        /// @brief Begin Frame
        /// @note Call this before doing anything graphical with the renderer
        void begin_frame() noexcept;

        /// @brief End Frame
        /// @note Call this to avoid crashing lol
        /// @note Also call this AFTER begin_frame... yeah.
        void end_frame() noexcept;

        /// @brief Query viewport size
        [[nodiscard]] glm::vec2 viewport_size() const noexcept;

        /// @brief Query viewport offset
        [[nodiscard]] glm::vec2 viewport_offset() const noexcept;

        void debug() noexcept;

        renderer(const class window &window, struct config cfg = {}) noexcept;

        ~renderer();
    };
}
