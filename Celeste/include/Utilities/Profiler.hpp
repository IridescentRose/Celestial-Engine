/**
 * Profiler
 */
#pragma once

#include <cpch.hpp>

namespace Celeste::Utilities {

    class Profiler : public Singleton{
    public:

        void BeginSession(const std::string& name, const std::string& filepath = "results.json") {
            m_FsOut.open(filepath);

            if (m_FsOut.is_open()){
                m_FsOut << "{events:[";
                m_FsOut.flush();
            }
        }

        void BeginProfile(const std::string& name, int line, const char* file) {
            profName = name;
            ln = line;
            sfile = file;
            t.reset();
        }

        void EndProfile() {

            auto dt = t.getDeltaTime();

            std::stringstream json;

            json << std::setprecision(6) << std::fixed;
            json << ",{";
            json << R"("cat":"function",)";
            json << R"("duration":)" << (dt) << ',';
            json << R"("name":")" << profName << "\",";
            json << R"("line":)" << ln << ',';
            json << R"("file":")" << sfile << "\",";
            json << "}";
            m_FsOut << json.str();
            m_FsOut.flush();
        }

        void EndSession() {
            m_FsOut << "]}";
            m_FsOut.close();
        }

        static Profiler& Get() {
            static Profiler instance;
            return instance;
        }

    private:
        Utilities::Timer t;
        std::ofstream m_FsOut;
        std::string profName;
        int ln{};
        std::string sfile;
    };
}

#define CS_PROFILE_BEGIN_SESSION(name, filepath) ::Celeste::Utilities::Profiler::Get().BeginSession(name, filepath)
#define CS_PROFILE_END_SESSION() ::Celeste::Utilities::Profiler::Get().EndSession()
#define CS_PROFILE_FUNCTION(fname, line, file, ...) ::Celeste::Utilities::Profiler::Get().BeginProfile(#fname, line, file); fname(__VA_ARGS__); ::Celeste::Utilities::Profiler::Get().EndProfile();