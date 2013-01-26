#include "shader.hpp"
#include "debug.hpp"
#include "file.hpp"
#include "gl.hpp"

kp::Shader::Shader(File file, GLenum shaderType) {
    this->source = file.read();
    this->type = shaderType;
    
    // Compile the shader
    compile();
};

kp::Shader::Shader(const char* source, GLenum shaderType) {
    this->source = source;
    this->type = shaderType;
    
    // Compile the shader
    compile();
};

kp::Shader::~Shader() {
    kp::debug("Freeing shader: %i",shader);
    
    // Free the shader
    glDeleteShader(shader);
}

void kp::Shader::compile() {
    // Create a shader of the type specified
    shader = glCreateShader(type);
    
    kp::debug("I created a shader, its value is: %i", this->shader);
    
    if(shader == 0)
        kp::error("glCreateShader failed");
    
    // Send our shader source into the shader.
    glShaderSource(shader, 1, (const GLchar**)&source, NULL);
    
    kp::debug("I created a shader, its value is: %i", this->shader);
    
    // Actaully compile the shader now.
    glCompileShader(shader);
    kp::gl::error("glCompileShader", glGetError());
    
    kp::debug("I created a shader, its value is: %i", this->shader);
    
    // Find the status of the compilation
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if(status != GL_TRUE) {
        // Grab the shader log
        char buffer[1024];
        glGetShaderInfoLog(shader, sizeof(buffer), NULL, buffer);
        
        kp::error("Failed to compile buffer:\n%s", buffer);
    }
}