/**
 * Network driver for all platforms
 */
#pragma once

namespace Celeste::Network {

    /**
     * Main driver
     */
    class NetDriver : public Singleton {
    public:

        /**
         * Starts up your networking code
         * @return - successful?
         */
        static bool init();

        /**
         * Cleans up the network code
         */
        static void cleanup();

        /**
         * Checks if the network driver is already set up
         * @return - If the network driver has been set up
         */
        inline auto isInit() const -> bool {
            return isInitialized;
        }

        /**
         * Gets the instance of the net driver
         * @return - Instance of this
         */
        static NetDriver& Get() {
            static NetDriver instance;
            return instance;
        }

    private:
        bool isInitialized = false;
    };
}