/**
 * Events implementation for listeners and whatnot
 */

#include <Utilities/Events.hpp>
#include <Utilities/Logger.hpp>

namespace Celeste::Utilities{

    namespace CelesteEvents {
        auto Listener::receive(const CelesteEvents::EventA &) -> void {
            CS_APP_INFO("RECEIVED EVENT A!");
        }
    }

    RefPtr<CelesteEvents::Listener> EventBus::s_Listener = nullptr;
    RefPtr<CelesteEvents::Bus> EventBus::s_Bus = nullptr;
}