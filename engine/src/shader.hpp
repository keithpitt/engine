#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <glew/glew.h>

namespace kp {
    
    namespace gl {
        
        class Shader {
        public:
            
            const char* source;
            const char* name;
            
            GLenum type;
            GLuint shader;
            
            Shader(const char* name, const char* source, GLenum shaderType);
            
            ~Shader();
            
            void compile();
            
        };
        
    }
    
}

#endif
