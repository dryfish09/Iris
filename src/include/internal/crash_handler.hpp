#pragma once

#include <span>
#include <string>
namespace iris::internal {
    void dump(std::span<char> buffer) noexcept; 
    void crash(const std::string &message) noexcept;
}
