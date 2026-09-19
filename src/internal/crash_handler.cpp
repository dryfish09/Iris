#include "dbglog.hpp"
#include <crash_handler.hpp>

#include <cstdio>
#include <ctime>
#include <span>
#include <string>

namespace iris::internal {

    namespace {
        constexpr const char* kIrisVersion = "1.0.0-dev";
        constexpr std::size_t kTimestampBufferSize = 32;

        std::string current_timestamp() noexcept {
            try {
                const std::time_t now = std::time(nullptr);
                if (now == static_cast<std::time_t>(-1)) {
                    return "<unknown>";
                }

                std::tm local_tm{};
#if defined(_WIN32)
                if (localtime_s(&local_tm, &now) != 0) {
                    return "<unknown>";
                }
#else
                if (localtime_r(&now, &local_tm) == nullptr) {
                    return "<unknown>";
                }
#endif

                char buffer[kTimestampBufferSize]{};
                if (std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local_tm) == 0) {
                    return "<unknown>";
                }
                return buffer;
            } catch (...) {
                return "<unknown>";
            }
        }
    } // namespace

    void dump(std::span<char> buffer) noexcept {
        if (buffer.empty()) {
            return;
        }

        const std::string timestamp = current_timestamp();

        std::snprintf(
            buffer.data(),
            buffer.size(),
            "--- Crash Report ---\n"
            "Timestamp:    %s\n"
            "Iris Version: %s\n"
            "Status:       An unexpected error has occurred.\n"
            "Details:      Additional diagnostic information is not yet available.\n",
            timestamp.c_str(),
            kIrisVersion);

        buffer.back() = '\0';
    }
    void crash(const std::string& message) noexcept {
        try {
            debug_log(message);
        } catch (...) {
            // A crash handler must never propagate exceptions.
        }
    }

} // namespace iris::internal
