w/**
 * Audio Clip interface (implementation based on platform)
 */
#pragma once

#include "cpch.hpp"

namespace Celeste::Audio{

    /**
     * Platform-independent audio file handle
     */
     typedef void* IAudioHandle;

     /**
      * An audio clip
      */
    class IAudioClip : public NonCopyable {
    public:
        virtual ~IAudioClip() = default;

        /**
         * Play a sound on a channel
         *
         * @param channel - The channel to play on (PSP 0-7, PC none)
         */
        virtual void Play(u8 channel) = 0;

        /**
         * Set the volume of this clip
         * @param volume - Clip Volume from 0.0 - 1.0
         */
        virtual void SetVol(const float& volume) = 0;

        /**
         * Set the pan of this clip
         * @param panning - Clip pan from -1.0 (left) - 1.0 (right)
         */
        virtual void SetPan(const float& panning) = 0;

        /**
         * Set the 3D Position of a sound (disables panning)
         * @param x - X Pos
         * @param y - Y Pos
         * @param z - Z Fos
         */
        virtual void SetPosition(const float& x, const float& y, const float& z) = 0;

    protected:
        IAudioHandle handle;
    };
}