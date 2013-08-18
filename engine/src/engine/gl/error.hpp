#if !defined(GL_ERROR_HPP)
#define GL_ERROR_HPP

#include <glew/glew.h>
#include <glfw/glfw3.h>
#include "../logger.hpp"

#define ASSERT_OPENGL_ERROR(logger) \
    do { \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) { \
            LOG(logger, Engine::Logger::LEVEL_ERROR, glGetErrorString(error)); \
        } \
    } while (false)

inline const char* glGetErrorString(GLenum code) {
    switch (code) {
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
            
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE: A numeric argument is out of range.";
            
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
            
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
            
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
            
        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow.";
            
        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow.";
    }
    
    return NULL;
}

#endif