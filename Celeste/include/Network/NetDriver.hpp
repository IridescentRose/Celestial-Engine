/**
 * Network driver for all platforms
 */
#pragma once
#include "cpch.hpp"

namespace Celeste::Network {

    class NetDriver : public Singleton {
    public:

        static bool init();
        static void cleanup();

        inline auto isInit() -> bool {
            return isInitialized;
        }

        static NetDriver& Get() {
            static NetDriver instance;
            return instance;
        }

    private:
        bool isInitialized = false;
    };
}