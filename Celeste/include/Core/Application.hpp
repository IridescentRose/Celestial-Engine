/**
 * Defines a Celeste App
 */
#pragma once

int main(int argc, char** argv);

namespace Celeste::Core {

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
        Application() = delete;
        Application(const char* name = "Stardust Celeste Application");
        virtual ~Application();

        static Application& Get() { return *s_Instance; }

        void Close();

        [[nodiscard]] inline auto getName() const -> const char* {
            return m_Name;
        }
    private:
        auto Run() -> void;

        static Application* s_Instance;
        friend int ::main(int argc, char** argv);
        const char* m_Name;
        bool m_Running = true;
        float m_LastFrameTime = 0.0f;
    };
}