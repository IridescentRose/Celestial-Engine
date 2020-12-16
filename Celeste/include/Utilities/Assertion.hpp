/**
 * Assert functionality
 */
#pragma once

#include "Logger.hpp"
#include "../Platform/Platform.h"
#include <Windows.h>

inline auto CS_DEBUG_BREAK() {
    using namespace Celeste::Platform;

    if constexpr (isPlatform(PlatformType::Windows)) {
        __debugbreak();
    }
}

#define CS_ASSERT(check, msg, ...) { if(!(check)) { CS_APP_ERROR(msg, __VA_ARGS__); CS_DEBUG_BREAK(); } }
#define CS_CORE_ASSERT(check, msg, ...) {if(!(check)) { CS_CORE_ERROR(msg, __VA_ARGS__); CS_DEBUG_BREAK(); }}
