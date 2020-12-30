/**
 * Implement the AudioListener
 */
#include <Audio/Listener.hpp>
#if BUILD_PLAT == BUILD_WINDOWS || BUILD_PLAT == BUILD_POSIX
#include <SFML/Audio.hpp>
#endif

namespace Celeste::Audio {

    void AudioListener::init() {
        px = py = pz;
        dx = dy = dz;

        #if BUILD_PLAT == BUILD_WINDOWS || BUILD_PLAT == BUILD_POSIX
        sf::Listener::setPosition(px, py, pz);
        sf::Listener::setDirection(dx, dy, dz);
        #endif
    }

    void AudioListener::cleanup() {
        px = py = pz;
        dx = dy = dz;

        #if BUILD_PLAT == BUILD_WINDOWS || BUILD_PLAT == BUILD_POSIX
        sf::Listener::setPosition(px, py, pz);
        sf::Listener::setDirection(dx, dy, dz);
        #endif
    }

    void AudioListener::setPos(const float &x, const float &y, const float &z) {
        px = x;
        py = y;
        pz = z;

        #if BUILD_PLAT == BUILD_WINDOWS || BUILD_PLAT == BUILD_POSIX
        sf::Listener::setPosition(px, py, pz);
        #endif
    }

    void AudioListener::setDirection(const float &x, const float &y, const float &z) {
        dx = x;
        dy = y;
        dz = z;

        #if BUILD_PLAT == BUILD_WINDOWS || BUILD_PLAT == BUILD_POSIX
        sf::Listener::setDirection(dx, dy, dz);
        #endif

    }
}
