/**
 * Application implementation
 */
#include <Utilities/Timer.hpp>
#include <Core/Application.hpp>
#include <Utilities/Assertion.hpp>

namespace Celeste::Core {
    Application* Application::s_Instance = nullptr;
    ApplicationEngineConfig ApplicationEngineConfig::defaultConfig = {};


    Application::Application() {
        CS_CORE_ASSERT(!s_Instance, "Instance already exists!")
        s_Instance = this;
        m_Running = true;
    }

    Application::~Application() = default;

    void Application::Close() {
        m_Running = false;
    }

    void Application::Run() {
        Utilities::Timer timer;
        while(m_Running) {
            m_LastFrameTime = static_cast<float>(timer.getDeltaTime());

            if(!m_StateStack.empty()){
                m_StateStack.back()->onUpdate(this, m_LastFrameTime);
                m_StateStack.back()->onDraw(this, m_LastFrameTime);
            }
        }
    }

    void Application::PushState(RefPtr <ApplicationState> state) {
        m_StateStack.emplace_back(state);
    }

    void Application::PopState() {
        m_StateStack.pop_back();
    }

    void Application::SetState(RefPtr <ApplicationState> state) {
        m_StateStack.clear();
        m_StateStack.emplace_back(state);
        m_StateStack.shrink_to_fit();
    }
}