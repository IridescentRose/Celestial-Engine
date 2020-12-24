/**
 * Assert functionality
 */
#pragma once

#include <cpch.hpp>
#include <Windows.h>

inline auto CS_DEBUG_BREAK() {
    using namespace Celeste::Platform;

    if constexpr (isPlatform(PlatformType::Windows)) {
        __debugbreak();
    }
}

#define CS_ASSERT(check, ...) if(!(check)) { CS_APP_ERROR(__VA_ARGS__); CS_DEBUG_BREAK(); }
#define CS_CORE_ASSERT(check, ...) if(!(check)) { CS_CORE_ERROR(__VA_ARGS__); CS_DEBUG_BREAK(); }
