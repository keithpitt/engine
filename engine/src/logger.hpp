#if !defined(ENGINE_H)
// Replication of the logging API so in other parts of the engine, we can include logger.h
// and have it compile with the right macros
#define OPENGL
#define GLEW
#define GLFW
#define LIBPNG
#define LOG_TRACE(logger, message)
#define LOG_DEBUG(logger, message)
#define LOG_INFO(logger, message)
#define LOG_WARNING(logger, message)
#define LOG_ERROR(logger, message)
#define LOG_FATAL(logger, message)
#endif