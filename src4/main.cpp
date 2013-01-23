//========================================================================
// This is a small test application for GLFW.
// The program opens a window (640x480), and renders a spinning colored
// triangle (it is controlled with both the GLFW timer and the mouse).
//========================================================================

#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

#define GLFW_DLL
#define GLFW_INCLUDE_GLU
#include <GL/glew.h>

#include <GL/glfw3.h>
#include <glm/glm.hpp>

// For the file class
#include <stdio.h>
#include <fstream>
#include <string>
#include <cerrno>


#include <string>
#include <iostream>
#include <stdio.h>

std::string cmd(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL)
    		result += buffer;
    }
    pclose(pipe);
    return result;
}

namespace kp {

    class File {
        
    public:
        
        static const char* read(const char* filename) {
            // Create the file object and load the file
            File* file = new File(filename);
            const char* contents = file->read();
            
            // Free the file memory
            delete file;
            
            return contents;
        };
        
        const char* filename;
        
        File(const char* filename) {
            this->filename = filename;
        }
        
        const char* read() {
            std::ifstream in(filename, std::ios::in | std::ios::binary);
            
            if (in) {
                std::string contents;
                
                // Find out the size of the file
                in.seekg(0, std::ios::end);
                contents.resize(in.tellg());
                in.seekg(0, std::ios::beg);
                
                // Read in the data
                in.read(&contents[0], contents.size());
                
                // Close it again
                in.close();
                
                return contents.c_str();
            };
            
            throw(errno);
        };
        
    };

    class Shader {
    public:
        
        const char* source;
        GLenum type;
        
        Shader(const char* source, GLenum shaderType) {
            this->source = source;
            this->type = shaderType;
            
            // Compile the shader
            compile();
        };
        
        void compile() {
            // Create a shader of the type specified
            GLuint shader = glCreateShader(type);
            if(shader == 0)
                throw std::runtime_error("glCreateShader failed");
            
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
                
                // Output and exit
                printf("Error:  Failed to compile buffer:\n%s", buffer);
                
                exit(EXIT_FAILURE);
            }
        }
        
    };
    
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int main(void)
{
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    // Initialise GLFW
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(800, 600, "Mandrill", NULL, NULL);
    if (!window) {
        throw std::runtime_error("glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");
    }
    
    // Create an OpenGL context on the window we've just created
    glfwMakeContextCurrent(window);
    
    // Enable vertical sync (on cards that support it)
    glfwSwapInterval(1);
    
    // Initialise GLEW
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        printf("glewInit failed: %s\n", glewGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // print out some info about the graphics drivers
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));
    printf("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Define the vertices for our triangle
    float vertices[] = {
        0.0f,  0.5f,
        0.5f, -0.5f,
       -0.5f, -0.5f
    };
    
    // Create a vertex buffer
    GLuint vbo;
    glGenBuffers(1, &vbo);
    
    // Make the vbo the current vertext buffer object. We also tell
    // OpenGL that the VBO contains an array!
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    // Load the vertices array into the current vertext buffer object.
    // Note: GL_STATIC_DRAW: The vertex data will be uploaded once and drawn many times (e.g. the world)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    const char* contents = kp::File::read("shaders/vertex_shader.glsl");
    
    kp::Shader * shader = new kp::Shader(contents, GL_VERTEX_SHADER);
    
    delete shader;

    for (;;)
    {
        // Clear color buffer to black
        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Check if the ESC key was pressed or the window should be closed
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) || glfwGetKey(window, GLFW_KEY_ENTER))
            break;
        if (glfwGetWindowParam(window, GLFW_SHOULD_CLOSE))
            break;
    }

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    exit(EXIT_SUCCESS);
}
