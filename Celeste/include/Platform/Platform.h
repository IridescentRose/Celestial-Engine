//
// Created by Iride on 12/7/2020.
//

#pragma once

namespace Celeste::Platform{
    enum class PlatformType {
        Windows [[maybe_unused]],
        Darwin [[maybe_unused]],
        Linux [[maybe_unused]],
        Playstation_Portable [[maybe_unused]],
        Playstation_Vita [[maybe_unused]],
        Playstation_2 [[maybe_unused]],
        Playstation_3 [[maybe_unused]],
        Nintendo_GameCube [[maybe_unused]],
        Nintendo_O3DS [[maybe_unused]],
        Nintendo_N3DS [[maybe_unused]],
        Nintendo_Switch [[maybe_unused]]
    };

    constexpr auto getPlatform() -> PlatformType {
        return BUILD_PLATFORM;
    }

    constexpr auto isPlatform(PlatformType pType) -> bool {
        return getPlatform() == pType;
    }
}