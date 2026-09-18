#include "state.hpp"
#include <error.hpp>
#include <string>

namespace iris {
    void error(iris::error_code ec, const std::string &msg) noexcept {
        spdlog::error("An error occurred: {}", detail::error_code_to_string(ec));
        if (!msg.empty()) {
            spdlog::error("{}", msg);
        }
    }
}
