/**
 * A simple timer
 */
#pragma once

namespace Celeste::Utilities {

    /**
     * A flexible timer object.
     */
    class Timer: public NonCopyable{
    public:

        /**
         * Timer Construction
         */
        Timer();

        /**
         * Timer Move Constructor
         * @param other - Timer to be moved.
         */
        Timer(Timer&& other) noexcept;

        /**
         * Timer Move Assignment Operator
         * @param other - Timer to be moved.
         * @return - new Timer
         */
        Timer& operator=(Timer&& other) noexcept;

        /**
         * Destructor
         */
        ~Timer();

        /**
         * Initializes an application timer to time things.
         */
        static auto init() -> void;

        /**
         * Gets our main application timer
         * @return - Application Timer RefPtr
         */
        static RefPtr<Timer>& GetAppTimer() {return s_Time;}

        /**
         * Gets the deltaTime
         * @return - Time since last call (Should not be discarded as it is an explicit call)
         */
        [[nodiscard]] auto getDeltaTime() -> double;

        /**
         * Resets the timer to zero elapsed time and no deltaTime
         */
        auto reset() -> void;

        /**
         * Elapsed time since object creation or last reset.
         * @return - Total elapsed time (Should not be discarded as it is an explicit call)
         */
        [[nodiscard]] auto elapsed() const -> double;

    private:
        double dt;
        double total;
        std::chrono::time_point<std::chrono::high_resolution_clock> last;

        static RefPtr<Timer> s_Time;
    };
}