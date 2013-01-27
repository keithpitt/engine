#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <GL/glew.h>

namespace kp {
    
    class File;
    
    class Shader {
    public:
        
        const char* source;
        GLenum type;
        GLuint shader;
        
        Shader(const char* source, GLenum shaderType);
        
        ~Shader();
        
        void compile();
        
    };
    
}

#endif
