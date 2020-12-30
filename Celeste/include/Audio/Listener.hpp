/**
 * Defines a Listener to Audio in 3D space
 */
#pragma once

namespace Celeste::Audio {

    /**
     * AudioListener Class
     */
    class AudioListener : public Singleton{
    public:

        /**
         * Initialize the listener
         */
        void init();

        /**
         * Cleanup the listener
         */
        void cleanup();

        /**
         * Set the Position
         * @param x - X Pos
         * @param y - Y Pos
         * @param z - Z Pos
         */
        void setPos(const float& x, const float& y, const float& z);

        /**
         * Set the Direction
         * @param x - X Dir
         * @param y - Y Dir
         * @param z - Z Dir
         */
        void setDirection(const float& x, const float& y, const float& z);

        /**
         * Get the instance
         * @return - An instance of AudioListener
         */
        inline static auto Get() -> AudioListener& {
            static AudioListener listener;
            return listener;
        }

    private:
        float px, py, pz;
        float dx, dy, dz;

    };
}