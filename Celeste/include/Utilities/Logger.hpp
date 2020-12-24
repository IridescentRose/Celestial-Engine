/**
 * A generic logger with threadsafety.
 */
#pragma once

#include <fmt/color.h>
#include "../cpch.hpp"

#ifndef SINGLE_THREADED
#include <mutex>
#endif

namespace Celeste::Utilities {

    /**
     * Defines basic Levels of logging
     */
    enum class LogLevel {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
    };


    /**
     * A Logger class which defines singleton-like objects.
     * It can still be instantiated for your own use, but recommended that you use the Core and App loggers provided.
     */
    class Logger final : public Singleton {
    public:

        /**
         * A basic logger object
         * @param name - Name of logger
         * @param path - Output file path
         */
        Logger(const char *name, const char *path);

        /**
         * Destructor.
         */
        ~Logger();

        /**
         * Initializes the core and app loggers
         */
        static auto init(bool color = false) -> void;

        /**
         * Cleans up the core and app loggers (calls delete)
         */
        static auto cleanup() -> void;

        /**
         * Gets the Core Logger
         * @return - RefPtr to the Core Logger
         */
        static RefPtr<Logger> &GetCoreLogger() { return s_Core; }

        /**
         * Gets the App Logger
         * @return  - RefPtr to the App Logger
         */
        static RefPtr<Logger> &GetAppLogger() { return s_Application; }

        /**
         * Logs a message to a logger object.
         * Will not log if the message is below the cutoff level.
         * Locks itself to have threadsafety.
         * @param msg - Message to send
         * @param lvl - The Level of the message
         * @param args - The arguments for formatting
         */
        template <typename ...Args>
        auto log(const std::string &msg, const LogLevel &lvl, Args &&... args) -> void {

            #ifndef SINGLE_THREADED
            std::lock_guard guard(writeLock);
            #endif

            if (lvl >= m_CutoffLevel) {
                auto formatStr = ("[" + std::string(m_LogName) + "]") + "[" + logLevelToString(lvl) + "]: ";

                auto formatMsg = fmt::format(formatStr + msg + "\n", std::forward<Args>(args)...);
                if (m_UseColor) {
                    fmt::print(fg(getColorLevel(lvl)), formatMsg);
                } else {
                    fmt::print(formatMsg);
                }
                fmt::print(m_FileOut, formatMsg);
            }
        }

        /**
         * Sets the cutoff level
         * @param lvl - Level to cutoff past.
         */
        inline auto setCutoff(const LogLevel &lvl) const -> void {
            m_CutoffLevel = lvl;
        }

        /**
         * Utility functions for a specific level
         */
        template <typename... Args>
        inline auto trace(const std::string &msg, Args &... args) -> void {
            log(msg, LogLevel::Trace, std::forward<Args>(args)...);
        }

        template <typename... Args>
        inline auto debug(const std::string &msg, Args &... args) -> void {
            log(msg, LogLevel::Debug, std::forward<Args>(args)...);
        }

        template <typename... Args>
        inline auto info(const std::string &msg, Args &... args) -> void {
            log(msg, LogLevel::Info, std::forward<Args>(args)...);
        }

        template <typename... Args>
        inline auto warn(const std::string &msg, Args &... args) -> void {
            log(msg, LogLevel::Warn, std::forward<Args>(args)...);
        }

        template <typename... Args>
        inline auto error(const std::string &msg, Args &... args) -> void {
            log(msg, LogLevel::Error, std::forward<Args>(args)...);
        }

        inline auto setUseColor(const bool& use_col) {
            m_UseColor = use_col;
        }

    private:
        mutable LogLevel m_CutoffLevel;
        FILE *m_FileOut;
        const char *m_LogName;
        bool m_UseColor;

        static RefPtr<Logger> s_Core;
        static RefPtr<Logger> s_Application;

        #ifndef SINGLE_THREADED
        std::mutex writeLock;
        #endif

        /**
     * Converts LogLevel to const char*
     * @param level - level
     * @return - Return a string of the name
     */
        static inline auto logLevelToString(const LogLevel &level) -> const char* {
            switch (level) {
                case LogLevel::Trace:
                    return "TRACE";

                case LogLevel::Debug:
                    return "DEBUG";

                case LogLevel::Info:
                    return "INFO";

                case LogLevel::Warn:
                    return "WARN";

                case LogLevel::Error:
                    return "ERROR";
            }

            return "?";
        }

        /**
         * Get a color from LogLevel
         * @param lvl - LogLevel
         * @return - A format color
         */
        static constexpr auto getColorLevel(LogLevel lvl) -> fmt::color {
            switch (lvl) {
                case LogLevel::Trace:
                    return fmt::color::light_gray;
                case LogLevel::Debug:
                    return fmt::color::light_green;
                case LogLevel::Info:
                    return fmt::color::ghost_white;
                case LogLevel::Warn:
                    return fmt::color::orange;
                case LogLevel::Error:
                    return fmt::color::crimson;

                default:
                    return fmt::color::white;
            }
        }

    };
}

/**
 * Macros to use the core logger.
 */
#define CS_CORE_TRACE(...) Celeste::Utilities::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define CS_CORE_DEBUG(...) Celeste::Utilities::Logger::GetCoreLogger()->debug(__VA_ARGS__)
#define CS_CORE_INFO(...) Celeste::Utilities::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CS_CORE_WARN(...) Celeste::Utilities::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define CS_CORE_ERROR(...) Celeste::Utilities::Logger::GetCoreLogger()->error(__VA_ARGS__)

/**
 * Macros to use the application logger.
 */
#define CS_APP_TRACE(...) Celeste::Utilities::Logger::GetAppLogger()->trace(__VA_ARGS__)
#define CS_APP_DEBUG(...) Celeste::Utilities::Logger::GetAppLogger()->debug(__VA_ARGS__)
#define CS_APP_INFO(...) Celeste::Utilities::Logger::GetAppLogger()->info(__VA_ARGS__)
#define CS_APP_WARN(...) Celeste::Utilities::Logger::GetAppLogger()->warn(__VA_ARGS__)
#define CS_APP_ERROR(...) Celeste::Utilities::Logger::GetAppLogger()->error(__VA_ARGS__)

#include "Assertion.hpp"