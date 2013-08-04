#ifndef _GL_HPP_
#define _GL_HPP_

#include <GL/glew.h>
#include <GL/glfw3.h>

// Apples glGenVertexArrays extensions end with APPLE, but they
// work exactly the same. Lets just redefined them here with what
// they ought to be. If you call glGenVertexArrays on OSX without
// doing this, GLEW will step in and just accept the command, but fill
// glGetErrors with an GL_INVALID_OPERATION type error.
#ifdef __APPLE__
    #undef glDeleteVertexArrays
    #undef glGenVertexArrays
    #undef glBindVertexArray

    #define glDeleteVertexArrays glDeleteVertexArraysAPPLE
    #define glGenVertexArrays glGenVertexArraysAPPLE
    #define glBindVertexArray glBindVertexArrayAPPLE
#endif

namespace kp {
    
    namespace gl {
        
        void error(const char * function, GLenum code);
        
    }
    
}

#endif