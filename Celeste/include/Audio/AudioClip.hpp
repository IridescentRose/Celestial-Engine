/**
 * Implementation of Abstract IAudioClip
 */
#pragma once
#include "IAudioClip.hpp"

namespace Celeste::Audio{

    class AudioClip : public IAudioClip {
    public:
        /**
         * Creates a brand new audio clip.
         * @param path - Path to file to use
         * @param streaming - Whether or not to stream (does not necessarily have to be respected)
         */
        AudioClip(const char* path, const bool& streaming = false);

        /**
         * Audio Clip Move Constructor
         * @param other - AudioClip to be moved.
         */
        AudioClip(AudioClip&& other) noexcept;

        /**
         * AudioClip Move Assignment Operator
         * @param other - AudioClip to be moved.
         * @return - new AudioClip
         */
        AudioClip& operator=(AudioClip&& other) noexcept;

        ~AudioClip() override;

        /**
         * Play a sound on a channel
         *
         * @param channel - The channel to play on (PSP 0-7, PC none)
         */
        void Play(u8 channel) override;

        /**
         * Set the volume of this clip
         * @param volume - Clip Volume from 0.0 - 1.0
         */
        void SetVol(const float& volume) override;

        /**
         * Set the pan of this clip
         * @param panning - Clip pan from -1.0 (left) - 1.0 (right)
         */
        void SetPan(const float& panning) override;

        /**
         * Set the 3D Position of a sound (disables panning)
         * @param x - X Pos
         * @param y - Y Pos
         * @param z - Z Fos
         */
        void SetPosition(const float& x, const float& y, const float& z);

    private:
        float vol;
        float pan;
        bool stream;
        float px, py, pz;
    };
}