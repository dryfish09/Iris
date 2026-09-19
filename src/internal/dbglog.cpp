#include "spdlog/spdlog.h"
#include <dbglog.hpp>

namespace iris::internal {
    void debug_log(const std::string &message) noexcept {
        spdlog::debug("{}", message);
    }
}
