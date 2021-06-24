/**
 * Implement an AudioClip for this platform
 */
#include <Audio/AudioClip.hpp>
#include <SFML/Audio.hpp>

namespace Celeste::Audio{


    #if BUILD_PLAT == BUILD_WINDOWS || BUILD_PLAT == BUILD_POSIX
    struct Sound {
        sf::SoundBuffer sb;
        sf::Sound snd;
    };
    #endif

    /**
    * Creates a brand new audio clip.
    * @param path - Path to file to use
    * @param streaming - Whether or not to stream (does not necessarily have to be respected)
    */
    AudioClip::AudioClip(const char *path, const bool &streaming) :
    pan(0), vol(0), stream(streaming), px(0), py(0), pz(0) {

        #if BUILD_PLAT == BUILD_WINDOWS || BUILD_PLAT == BUILD_POSIX

        if(streaming) {
            auto music = new sf::Music();
            if (!music->openFromFile(path)) {
                throw std::runtime_error("Couldn't open audio file: " + std::string(path));
            }
            handle = reinterpret_cast<void*>(music);
        }else {
            auto sound = new Sound();
            sound->sb.loadFromFile(path);
            sound->snd.setBuffer(sound->sb);

            handle = reinterpret_cast<void*>(sound);
        }
        #endif
    }

    /**
    * Audio Clip Move Constructor
    * @param other - AudioClip to be moved.
    */
    AudioClip::AudioClip(AudioClip &&other) noexcept {
        this->handle = other.handle;
        //We do not need to clear `other` as it's in a valid state
        this->pan = other.pan;
        this->vol = other.vol;
        this->stream = other.stream;

        other.handle = nullptr;
    }

    /**
    * AudioClip Move Assignment Operator
    * @param other - AudioClip to be moved.
    * @return - new AudioClip
    */
    AudioClip &AudioClip::operator=(AudioClip &&other) noexcept {
        this->handle = other.handle;
        //We do not need to clear `other` as it's in a valid state
        this->pan = other.pan;
        this->vol = other.vol;
        this->stream = other.stream;

        other.handle = nullptr;
        return *this;
    }

    /**
    * Play a sound on a channel
    * @param channel - The channel to play on (PSP 0-7, PC none)
    */
    void AudioClip::Play(u8 channel) {
#if BUILD_PLAT == BUILD_WINDOWS || BUILD_PLAT == BUILD_POSIX

        if(stream) {
            auto music = reinterpret_cast<sf::Music *>(handle);
            music->play();
        } else {
            auto music = reinterpret_cast<Sound*>(handle);
            music->snd.play();
        }
#endif
    }

    /**
    * Set the volume of this clip
    * @param volume - Clip Volume from 0.0 - 1.0
    */
    void AudioClip::SetVol(const float &volume) {
        vol = volume;
#if BUILD_PLAT == BUILD_WINDOWS || BUILD_PLAT == BUILD_POSIX
        if(stream) {
            auto music = reinterpret_cast<sf::Music *>(handle);
            music->setVolume(volume * 100.0f);
        } else {
            auto music = reinterpret_cast<Sound*>(handle);
            music->snd.setVolume(volume * 100.0f);
        }
#endif
    }

    /**
     * Set the pan of this clip
     * @param panning - Clip pan from -1.0 (left) - 1.0 (right)
     */
    void AudioClip::SetPan(const float &panning) {
        pan = panning;
#if BUILD_PLAT == BUILD_WINDOWS || BUILD_PLAT == BUILD_POSIX
        if(stream) {
            auto music = reinterpret_cast<sf::Music *>(handle);
            music->setPosition({panning, 0, 0});
        } else {
            auto music = reinterpret_cast<Sound*>(handle);
            music->snd.setPosition({panning, 0, 0});
        }
#endif
    }

    AudioClip::~AudioClip() {
        #if BUILD_PLAT == BUILD_WINDOWS || BUILD_PLAT == BUILD_POSIX

        if(stream) {
            auto music = reinterpret_cast<sf::Music *>(handle);
            delete music;
        }else{
            auto music = reinterpret_cast<Sound*>(handle);
            delete music;
        }
        #endif
    }

    void AudioClip::SetPosition(const float &x, const float &y, const float &z) {
        px = x;
        py = y;
        pz = z;

        #if BUILD_PLAT == BUILD_WINDOWS || BUILD_PLAT == BUILD_POSIX

        if(stream) {
            auto music = reinterpret_cast<sf::Music *>(handle);
            music->setPosition(px, py, pz);
        }else{
            auto music = reinterpret_cast<Sound*>(handle);
            music->snd.setPosition(px, py, pz);
        }
        #endif
    }
}