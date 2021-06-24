/**
 * Defines a Celeste App
 */
#pragma once

#include "State.hpp"

[[maybe_unused]] int main(int argc, char** argv);

namespace Celeste::Core {

    class ApplicationState;

    struct ApplicationEngineConfig {
        bool headless = false;

        //Each individual submodule

        //Platform specifics

        static ApplicationEngineConfig defaultConfig;
    };

    class PlatformLayer {
    public:
        inline static void initializeWithSettings(const ApplicationEngineConfig& app) {
            auto inst = Get();
            inst.config = app;

            //TODO: Initialize Engine
        }

        inline static void terminateLayer() {
            //TODO: Terminate Engine
        }

        inline static PlatformLayer& Get() {
            static PlatformLayer ply;
            return ply;
        }
    private:
        ApplicationEngineConfig config;
    };

    class Application {
    public:
        Application();
        virtual ~Application();

        static Application& Get() { return *s_Instance; }

        void SetState(RefPtr<ApplicationState> state);
        void PushState(RefPtr<ApplicationState> state);
        void PopState();

        void Close();
    private:
        auto Run() -> void;

        static Application* s_Instance;

        friend int ::main(int argc, char** argv);
        bool m_Running = true;
        float m_LastFrameTime = 0.0f;
        std::vector<RefPtr<ApplicationState>> m_StateStack;
    };
}