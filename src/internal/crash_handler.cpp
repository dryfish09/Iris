#include "dbglog.hpp"
#include <crash_handler.hpp>

namespace iris::internal {
    void dump(std::span<char> buffer) noexcept {
        std::snprintf(buffer.data(), buffer.size(), R"(--- Crash Dump ---
Generated on %s

Iris Version: %s
other detials coming soon ok
The uhh thing of the thing has crashed go fuck yourself
)", "today vro", "1.0.0:dev");
    }

    void crash(const std::string &message) noexcept {
        internal::debug_log(message);
    }
}
