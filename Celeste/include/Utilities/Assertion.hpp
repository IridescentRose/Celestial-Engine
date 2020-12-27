/**
 * Assert functionality
 */
#pragma once
#include <cpch.hpp>

#if BUILD_PLAT == BUILD_POSIX
#include <signal.h>
#endif

inline auto CS_DEBUG_BREAK() {
    using namespace Celeste::Platform;

#if BUILD_PLAT == BUILD_WINDOWS
    __debugbreak();
#elif BUILD_PLAT == BUILD_POSIX
    raise(SIGTRAP);
#else
#error No Debug Break!
#endif
}

#define CS_ASSERT(check, ...) if(!(check)) { CS_APP_ERROR(__VA_ARGS__); CS_DEBUG_BREAK(); }
#define CS_CORE_ASSERT(check, ...) if(!(check)) { CS_CORE_ERROR(__VA_ARGS__); CS_DEBUG_BREAK(); }
