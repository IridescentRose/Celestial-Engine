/**
 * This is the CORE Stardust Celeste Event system
 * This is not to be used in user applications.
 *
 */
#pragma once

#include "cpch.hpp"
#include <bus.hpp>
#include <event.hpp>

namespace Celeste::Utilities {
    namespace CelesteEvents{
        struct EventA: public eventpp::Event<EventA> {

        };


        struct Listener {
            auto receive(const EventA&) -> void;
        };

        using Bus = eventpp::Bus<EventA>;
    }

    /**
     * This class defines a very limited internal event bus
     */
    class EventBus : public Singleton {
    public:
        /**
         * Initializes the listener and bus and registers listener functions.
         */
        inline static auto init() -> void {
            s_Listener = createRefPtr<CelesteEvents::Listener>();
            s_Bus = createRefPtr<CelesteEvents::Bus>();

            s_Bus->reg(s_Listener);
        }

        /**
         * Gets the event bus itself
         * @return - Static Event Bus
         */
        inline static auto get() -> RefPtr<CelesteEvents::Bus> {
            return s_Bus;
        }

        /**
         * Cleans up the state
         */
        inline static auto cleanup() -> void {
            s_Bus.reset();
            s_Listener.reset();
        }

    private:
        static RefPtr<CelesteEvents::Listener> s_Listener;
        static RefPtr<CelesteEvents::Bus> s_Bus;
    };

}