//
// Created by Iride on 12/7/2020.
//

#pragma once

#include <Utilities/Types.hpp>

#ifndef BUILD_PLAT
#error No platform selected!
#endif

#define BUILD_WINDOWS 0
#define BUILD_POSIX 1
#define BUILD_PSP 2
#define BUILD_VITA 3

namespace Celeste::Platform{
    enum class PlatformType {
        Windows [[maybe_unused]],
        Posix [[maybe_unused]],
        Playstation_Portable [[maybe_unused]],
        Playstation_Vita [[maybe_unused]],
        Playstation_2 [[maybe_unused]],
        Playstation_3 [[maybe_unused]],
        Nintendo_GameCube [[maybe_unused]],
        Nintendo_O3DS [[maybe_unused]],
        Nintendo_N3DS [[maybe_unused]],
        Nintendo_Switch [[maybe_unused]]
    };


#if BUILD_PLAT == BUILD_WINDOWS
    constexpr auto BUILD_PLATFORM = Celeste::Platform::PlatformType::Windows;
#elif BUILD_PLAT == BUILD_POSIX
    constexpr auto BUILD_PLATFORM = Celeste::Platform::PlatformType::Posix;
    #else
#error Invalid Platform!
#endif

    constexpr auto isPlatform(PlatformType pType) -> bool {
        return BUILD_PLATFORM == pType;
    }

    inline auto delayForMS(u32 millis) -> void {
        std::this_thread::sleep_for(std::chrono::milliseconds(millis));
    }
}
