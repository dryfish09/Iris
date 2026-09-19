#include "iris/graphics/rendering.hpp"
#include "iris/graphics/windowing.hpp"
#include <iris/runtime.hpp>

void iris_main(const iris_main_arguments &) {
    auto init_data = iris::init();
    struct iris::window::config config;
    config.msaa_samples = 15;
    iris::window window = { "AS", { 800, 600 }, config };
    iris::renderer renderer(window);

    while (window.running()) {
        renderer.begin_frame();
        renderer.clear();
        renderer.debug();
        renderer.end_frame();
        window.poll_events();
        window.swap_buffers();
    }
}

IrisPlatformGlue
