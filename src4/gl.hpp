#ifndef _GL_HPP_
#define _GL_HPP_

#include <GL/glew.h>
#include <GL/glfw3.h>

namespace kp {
    
    namespace gl {
        
        void error(const char * function, GLenum code);
        
    }
    
}

#endif