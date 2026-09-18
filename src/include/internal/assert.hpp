#pragma once

#define NAssert_Log ::iris::internal::debug_log
#define NAssert_Terminate ::iris::native::terminate

#include <dbglog.hpp>
#include <native.hpp>
#include <nutils/assert.hpp>

#define IrisAssert NAssert
