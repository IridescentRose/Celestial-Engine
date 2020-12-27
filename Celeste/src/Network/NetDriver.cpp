/*
 * Network Driver
 */
#include <Network/NetDriver.hpp>

#if BUILD_PLAT == BUILD_WINDOWS
#include <winsock2.h>
#endif

namespace Celeste::Network {

    bool NetDriver::init() {

#if BUILD_PLAT == BUILD_WINDOWS
            WSAData data;
            int res = WSAStartup(MAKEWORD(2, 2), &data);
            if (res != 0) {
                return false;
            }
#endif
        return true;
    }

    void NetDriver::cleanup() {
#if BUILD_PLAT == BUILD_WINDOWS
            WSACleanup();
#endif
    }
}