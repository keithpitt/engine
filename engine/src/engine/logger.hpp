#if !defined(LOGGER_H)
#define LOGGER_H

// Logging usually uses formatting
#include <boost/format.hpp>

// The different logging streams
#define MAIN          "MAIN"
#define OPENGL        "OPENGL"
#define OPENGL_SHADER "OPENGL.SHADER"
#define GLEW          "GLEW"
#define GLFW          "GLFW"
#define LIBPNG        "LIBPNG"

namespace Engine {
    namespace Logger {
        enum LogLevel {
            LEVEL_DEBUG,
            LEVEL_INFO,
            LEVEL_WARNING,
            LEVEL_ERROR,
            LEVEL_FATAL
        };
        
        // Generic type so we can accept either a boost formatted string, or a regular c string
        template <typename T>
        
        inline void log(const char * logger, LogLevel log_level, T message, const char* file, int line, const char* function) {
            const char* level;
            
            switch (log_level) {
                case LEVEL_DEBUG:   level = "DEBUG"; break;
                case LEVEL_INFO:    level = "INFO"; break;
                case LEVEL_WARNING: level = "WARNING"; break;
                case LEVEL_ERROR:   level = "ERROR"; break;
                case LEVEL_FATAL:   level = "FATAL"; break;
                default:            level = "UNKNOWN"; break;
            }
            
            // Format and print our log message
            std::cout << boost::format("[%s:%i %s] %s %s: %s\n") % file % line % function % logger % level % message;
            
            // Exit out of the program if the log level was fatal
            if (log_level == LEVEL_FATAL) abort();
        };
    }
}

#define LOG(logger, level, message) Engine::Logger::log(logger, Engine::Logger::LEVEL_INFO, message, __FILE__, __LINE__, __FUNCTION__)

#define LOG_DEBUG(logger, message) LOG(logger, Engine::Logger::LOG_DEBUG, message)
#define LOG_INFO(logger, message) LOG(logger, Engine::Logger::LEVEL_INFO, message)
#define LOG_WARNING(logger, message) LOG(logger, Engine::Logger::LEVEL_WARNING, message)
#define LOG_ERROR(logger, message) LOG(logger, Engine::Logger::LEVEL_ERROR, message)
#define LOG_FATAL(logger, message) LOG(logger, Engine::Logger::LEVEL_FATAL, message)

#endif