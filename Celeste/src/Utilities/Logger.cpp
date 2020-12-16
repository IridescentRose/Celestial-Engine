/**
 * Logger
 */
#include <Utilities/Logger.hpp>

namespace Celeste::Utilities {

    RefPtr <Logger> Logger::s_Core;
    RefPtr <Logger> Logger::s_Application;

    /**
     * Create the static members
     */
    auto Utilities::Logger::init(bool color) -> void {
        s_Core = createRefPtr<Logger>("CORE", "core_log.log");
        s_Core->setUseColor(color);
        s_Application = createRefPtr<Logger>("APP", "app_log.log");
        s_Core->setUseColor(color);
    }

    /**
     * Creates a Logger Instances
     * @param name - Name of the Logger
     * @param path - Path to file output
     */
    Logger::Logger(const char *name, const char *path)
            : m_FileOut(nullptr), m_CutoffLevel(LogLevel::Trace),
              m_LogName(name), m_UseColor(false) {
        fopen_s(&m_FileOut, path, "w");
    }

    /**
     * Closes and flushes the file.
     */
    Logger::~Logger() {
        fclose(m_FileOut);
    }

    /**
     * Cleans up the static loggers.
     */
    auto Logger::cleanup() -> void {
        s_Core.reset();
        s_Application.reset();
    }
}