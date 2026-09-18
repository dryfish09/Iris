#include "iris/graphics/rendering.hpp"
#include "iris/graphics/windowing.hpp"
#include <iris/runtime.hpp>

void iris_main(const iris_main_arguments &) {
    auto init_data = iris::init();
    iris::window window;
    iris::renderer renderer(window);

    while (window.running()) {
        renderer.begin_frame();
        renderer.clear();
        renderer.end_frame();
        window.poll_events();
        window.swap_buffers();
    }
}

IrisPlatformGlue
