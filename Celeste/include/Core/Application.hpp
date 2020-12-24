/**
 * Defines a Celeste App
 */
#pragma once

int main(int argc, char** argv);

namespace Celeste::Core {

    struct ApplicationEngineConfig {
        bool headless = false;

        //Platform specifics

        static ApplicationEngineConfig defaultConfig;
    };


    class Application {
    public:
        Application() = delete;
        Application(const char* name = "Stardust Celeste Application", const ApplicationEngineConfig& config = ApplicationEngineConfig::defaultConfig);
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