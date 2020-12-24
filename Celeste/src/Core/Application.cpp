/**
 * Application implementation
 */
#include <Utilities/Timer.hpp>
#include <Core/Application.hpp>
#include <Utilities/Assertion.hpp>

namespace Celeste::Core {
    Application* Application::s_Instance = nullptr;
    ApplicationEngineConfig ApplicationEngineConfig::defaultConfig = {};


    Application::Application(const char* name, const ApplicationEngineConfig& config) : m_Name(name) {
        CS_CORE_ASSERT(!s_Instance, "Instance already exists!")
        s_Instance = this;
        m_Running = true;

        //TODO: Platform Init
    }

    Application::~Application() {
        //TODO: Platform Shutdown
    }

    void Application::Close() {
        m_Running = false;
    }

    void Application::Run() {
        Utilities::Timer timer;
        while(m_Running) {
            m_LastFrameTime = static_cast<float>(timer.getDeltaTime());

            //TODO: Update stuff
            //TODO: Render stuff
        }
    }
}