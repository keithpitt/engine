#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <GL/glew.h>

namespace kp {
    
    class Shader {
    public:
        
        const char* source;
        GLenum type;
        
        Shader(const char* source, GLenum shaderType);
        
        void compile();
        
    };
    
}

#endif