#include "iris/types.hpp"
#include <iris/graphics/rendering.hpp>
#include "gl_render_layer.hpp"

namespace iris {
    renderer::renderer(const window &window, struct config cfg) noexcept {
        window.make_gl_context_current();
        gl::init({
            .viewport_size = cfg.viewport_size_override != glm::vec2 { -1, -1 } 
                            ? cfg.viewport_size_override 
                            : glm::vec2 { 0, 0 },

            .viewport_offset = cfg.viewport_offset_override != glm::vec2 { -1, -1 } 
                            ? cfg.viewport_offset_override 
                            : glm::vec2 { 0, 0 },

            .depth_func = this->config.depth 
                            ? gl::depth_func::less
                            : gl::depth_func::none,
        });
    }

    void renderer::begin_frame() noexcept {
    }

    void renderer::end_frame() noexcept {
    }

    void renderer::clear(rgba_color color) noexcept {
        glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
        i32 clear_flags = GL_COLOR_BUFFER_BIT;
        if (this->config.depth) {
            clear_flags |= GL_DEPTH_BUFFER_BIT;
        }
        glClear(clear_flags);
    }

#ifdef Iris_Debug
    void renderer::debug() noexcept {
    }
#endif

    renderer::~renderer() {}
}
