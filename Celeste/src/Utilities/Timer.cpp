/**
 * Timer class
 */
#include <Utilities/Timer.hpp>

namespace Celeste::Utilities {

    RefPtr <Timer> Timer::s_Time;

    Timer::Timer() {
        last = std::chrono::high_resolution_clock::now();
        total = 0;
        dt = 0;
    }

    Timer::Timer(Timer &&other) noexcept {
        last = other.last;
        dt = other.dt;
        total = other.total;

        other.last = std::chrono::high_resolution_clock::now();
        other.total = 0;
        other.dt = 0;
    }

    Timer &Timer::operator=(Timer &&other) noexcept {
        last = other.last;
        dt = other.dt;
        total = other.total;

        other.last = std::chrono::high_resolution_clock::now();
        other.total = 0;
        other.dt = 0;

        return *this;
    }

    Timer::~Timer() {
        total = 0;
        dt = 0;
    }

    auto Timer::init() -> void {
        s_Time = createRefPtr<Timer>();
    }

    auto Timer::getDeltaTime() -> double {
        std::chrono::time_point<std::chrono::high_resolution_clock> current = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>(current - last).count();
        last = current;

        total += dt;
        return dt;
    }

    auto Timer::reset() -> void {
        total = 0;
    }

    auto Timer::elapsed() const -> double {
        return total;
    }
}