#include "gl.hpp"
#include "debug.hpp"

void kp::gl::error(const char * function, GLenum code) {
    switch (code) {
        case GL_INVALID_ENUM:
            kp::error("GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument. (%s)", function);
            break;
            
        case GL_INVALID_VALUE:
            kp::error("GL_INVALID_VALUE: A numeric argument is out of range. (%s)", function);
            break;
            
        case GL_INVALID_OPERATION:
            kp::error("GL_INVALID_OPERATION: The specified operation is not allowed in the current state. (%s)", function);
            break;
            
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            kp::error("GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete. (%s)", function);
            break;
            
        case GL_OUT_OF_MEMORY:
            kp::error("GL_OUT_OF_MEMORY: There is not enough memory left to execute the command. (%s)", function);
            break;
            
        case GL_STACK_UNDERFLOW:
            kp::error("GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow. (%s)", function);
            break;
            
        case GL_STACK_OVERFLOW:
            kp::error("GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow. (%s)", function);
            break;
    }
};