#pragma once

#include "iris/runtime.hpp"
namespace iris {
    void error(iris::error_code ec, const std::string &msg = "") noexcept;
}
