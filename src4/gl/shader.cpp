#include "shader.hpp"
#include "gl.hpp"

#include "../debug.hpp"

kp::gl::Shader::Shader(const char* source, GLenum shaderType)
{
    this->source = source;
    this->type = shaderType;
    
    compile();
};

kp::gl::Shader::~Shader()
{
    kp::debug::info("Freeing shader #%i",shader);
    
    // Free the shader
    glDeleteShader(shader);
}

void kp::gl::Shader::compile()
{
    // Create a shader of the type specified
    shader = glCreateShader(type);
    
    kp::debug::info("Creating shader #%i",shader);
    
    if(shader == 0)
    {
        kp::debug::error("glCreateShader failed");
        return;
    }
    
    // Send our shader source into the shader.
    glShaderSource(shader, 1, (const GLchar**)&source, NULL);
    kp::gl::error("glShaderSource", glGetError());
    
    // Actaully compile the shader now.
    glCompileShader(shader);
    kp::gl::error("glCompileShader", glGetError());
    
    // Find the status of the compilation
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if(status != GL_TRUE)
    {
        // Grab the shader log
        char buffer[1024];
        glGetShaderInfoLog(shader, sizeof(buffer), NULL, buffer);
        
        kp::debug::error("Failed to compile buffer:\n%s", buffer);
    }
}
