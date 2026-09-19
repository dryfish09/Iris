#include "glm/fwd.hpp"
#include "iris/types.hpp"
#include <iris/graphics/rendering.hpp>
#include "gl_render_layer.hpp"
#include "spdlog/spdlog.h"
#include <assert.hpp>

namespace iris {
    namespace {
        struct gl_resources {
            gl::object obj_quad;
        };
    }

    struct renderer::drawcall {
        gl::object &object;
        glm::vec2 pos;
        glm::vec2 size;
    };

    renderer::renderer(const class window &window, struct config cfg) noexcept
        : window(window) 
    {
        this->resources = new gl_resources();
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
        gl::shader shader = gl::compile_debug_shader();
        shader.uniforms["p_color"] = glm::vec4(1, 0, 0, 1);
        shader.update_uniforms();
        reinterpret_cast<gl_resources*>(this->resources)->obj_quad = gl::create_object({ 0, 0, 1, 0, 1, 1, 0, 1 }, { 0, 1, 2, 2, 3, 0, }, shader);
    }

    void renderer::begin_frame() noexcept {
        this->begin_frame_called = true;
    }

    void renderer::end_frame() noexcept {
        this->viewport_size_ = this->window.framebuffer_size();
        this->viewport_offset_ = { 0, 0 };
        glm::ivec2 vp_offset = this->config.viewport_offset_override != glm::vec2 { -1, -1 } ? this->config.viewport_offset_override : this->viewport_offset_;
        glm::ivec2 vp_size = this->config.viewport_size_override != glm::vec2 { -1, -1 } ? this->config.viewport_size_override : this->viewport_size_;
        glViewport(vp_offset.x, vp_offset.y, vp_size.x, vp_size.y);

        this->flush_drawcalls(); // actually draw

        this->begin_frame_called = !this->begin_frame_called;
        IrisAssert(this->begin_frame_called == false);
    }

    void renderer::pre_draw_check() const noexcept {
        IrisAssert(this->begin_frame_called);
    }

    void renderer::flush_drawcalls() noexcept {
        for (auto &dc : this->drawcalls) {
            glUseProgram(dc.object.shader.gl_program);

            dc.object.shader.uniforms.try_emplace("iris_pos", glm::vec2{});
            if (auto &val = std::get<glm::vec2>(dc.object.shader.uniforms.at("iris_pos"));
                dc.pos != val)
            {
                val = dc.pos;
                dc.object.shader.update_uniforms();
            }

            dc.object.shader.uniforms.try_emplace("iris_size", glm::vec2{});
            if (auto &val = std::get<glm::vec2>(dc.object.shader.uniforms.at("iris_size"));
                dc.size != val)
            {
                val = dc.size;
                dc.object.shader.update_uniforms();
            }

            glBindVertexArray(dc.object.vao);
            glDrawElements(GL_TRIANGLES, dc.object.indices, GL_UNSIGNED_INT, nullptr);
        }
        this->drawcalls.clear();
    }

    void renderer::clear(rgba_color color) noexcept {
        pre_draw_check();
        glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
        i32 clear_flags = GL_COLOR_BUFFER_BIT;
        if (this->config.depth) {
            clear_flags |= GL_DEPTH_BUFFER_BIT;
        }
        glClear(clear_flags);
    }

    glm::vec2 renderer::viewport_size() const noexcept {
        return this->viewport_size_;
    }

    glm::vec2 renderer::viewport_offset() const noexcept {
        return this->viewport_offset_;
    }

#ifdef Iris_Debug
    void renderer::debug() noexcept {
        pre_draw_check();
        gl_resources *res = reinterpret_cast<gl_resources*>(this->resources); 
        this->drawcalls.emplace_back(res->obj_quad, glm::vec2 { 50, 50 } / this->viewport_size_, glm::vec2 { 200, 200 } / this->viewport_size_);
    }
#endif

    renderer::~renderer() {
        delete reinterpret_cast<gl_resources*>(this->resources);
    }
}
