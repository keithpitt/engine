#include "shader.hpp"
#include "debug.hpp"
#include "file.hpp"

kp::Shader::Shader(File file, GLenum shaderType) {
    this->source = file.read();
    this->type = shaderType;
};

kp::Shader::Shader(const char* source, GLenum shaderType) {
    this->source = source;
    this->type = shaderType;
    
    // Compile the shader
    compile();
};

void kp::Shader::compile() {
    // Create a shader of the type specified
    GLuint shader = glCreateShader(type);
    if(shader == 0)
        kp::error("glCreateShader failed");
    
    // Send our shader source into the shader.
    glShaderSource(shader, 1, (const GLchar**)&source, NULL);
    
    // Actaully compile the shader now.
    glCompileShader(shader);
    
    // Find the status of the compilation
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if(status != GL_TRUE) {
        // Grab the shader log
        char buffer[1024];
        glGetShaderInfoLog(shader, sizeof(buffer), NULL, buffer);
        
        kp::error("Error:  Failed to compile buffer:\n%s", buffer);
    }
}