/*
 * Network Driver
 */
#include <Network/NetDriver.hpp>
#include <winsock2.h>

namespace Celeste::Network {

    bool NetDriver::init() {
        using namespace Platform;

        if constexpr (isPlatform(PlatformType::Windows)) {
            WSAData data;
            int res = WSAStartup(MAKEWORD(2, 2), &data);
            if (res != 0) {
                return false;
            }
        } else {
            return false;
        }

        return true;
    }

    void NetDriver::cleanup() {
        using namespace Platform;

        if constexpr (isPlatform(PlatformType::Windows)) {
            WSACleanup();
        }
    }
}