/**
 * Assert functionality
 */
#pragma once

#include "Logger.hpp"
#include "../Platform/Platform.h"
#include <Windows.h>

inline auto SD_DEBUG_BREAK() {
    using namespace Celeste::Platform;

    if constexpr (isPlatform(PlatformType::Windows)) {
        __debugbreak();
    }
}

#define SD_ASSERT(check, msg, ...) {if(!(check)) { SD_APP_ERROR(msg, __VA_ARGS__); SD_DEBUG_BREAK(); }}
#define SD_CORE_ASSERT(check, msg, ...) {if(!(check)) { SD_CORE_ERROR(msg, __VA_ARGS__); SD_DEBUG_BREAK(); }}
