#include "gl.hpp"
#include "logger.hpp"

void kp::gl::error(const char * function, GLenum code) {
    switch (code) {
        case GL_INVALID_ENUM:
            LOG_ERROR(OPENGL, "testing");
            //LOG_ERROR(OPENGL, "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument. (%s)");
            //kp::debug::error("GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument. (%s)", function);
            break;
            
        case GL_INVALID_VALUE:
            //kp::debug::error("GL_INVALID_VALUE: A numeric argument is out of range. (%s)", function);
            break;
            
        case GL_INVALID_OPERATION:
            //kp::debug::error("GL_INVALID_OPERATION: The specified operation is not allowed in the current state. (%s)", function);
            break;
            
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            //kp::debug::error("GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete. (%s)", function);
            break;
            
        case GL_OUT_OF_MEMORY:
            //kp::debug::error("GL_OUT_OF_MEMORY: There is not enough memory left to execute the command. (%s)", function);
            break;
            
        case GL_STACK_UNDERFLOW:
            //kp::debug::error("GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow. (%s)", function);
            break;
            
        case GL_STACK_OVERFLOW:
            //kp::debug::error("GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow. (%s)", function);
            break;
    }
};