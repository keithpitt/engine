#include "shader.hpp"
#include "engine/logger.hpp"
#include "engine/open_gl/error.hpp"

kp::gl::Shader::Shader(const char* name, const char* source, GLenum shaderType)
{
    this->name = name;
    this->source = source;
    this->type = shaderType;
    
    compile();
};

kp::gl::Shader::~Shader()
{
    LOG_INFO(OPENGL_SHADER, boost::format("Freeing shader #%i") % shader);
    
    // Free the shader
    glDeleteShader(shader);
}

void kp::gl::Shader::compile()
{
    // Create a shader of the type specified
    shader = glCreateShader(type);
    
    LOG_INFO(OPENGL_SHADER, boost::format("Creating shader #%i") % shader);
    
    if(shader == 0)
    {
        //kp::debug::error("glCreateShader failed");
        return;
    }
    
    // Send our shader source into the shader.
    glShaderSource(shader, 1, (const GLchar**)&source, NULL);
    ASSERT_OPENGL_ERROR(OPENGL_SHADER);
    
    // Actaully compile the shader now.
    glCompileShader(shader);
    ASSERT_OPENGL_ERROR(OPENGL_SHADER);
    
    // Find the status of the compilation
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if(status != GL_TRUE)
    {
        // Grab the shader log
        char buffer[1024];
        glGetShaderInfoLog(shader, sizeof(buffer), NULL, buffer);
        
        LOG_ERROR(OPENGL_SHADER, boost::format("Failed to compile shader `%s`:\n%s") % name % buffer);
    }
}
