//========================================================================
// This is a small test application for GLFW.
// The program opens a window (640x480), and renders a spinning colored
// triangle (it is controlled with both the GLFW timer and the mouse).
//========================================================================

#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

#include <GL/glew.h>

#define GLFW_DLL
#define GLFW_INCLUDE_GLU
#include <GL/glfw3.h>

#include <glm/glm.hpp>

#include "string.hpp"
#include "file.hpp"
#include "debug.hpp"

#include "gl/gl.hpp"
#include "gl/shader.hpp"

static void error_callback(int error, const char* description)
{
    kp::debug::fatal(description);
}

int main(int argc, char** argv)
{
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    // Initialise GLFW
    if (!glfwInit()) {
        kp::debug::fatal("glfwInit failed");
    }

    // Initialize the file system reader
    kp::file::init(argv[0]);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(1024, 768, "Mandrill", NULL, NULL);
    if (!window) {
        kp::debug::fatal("glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");
    }
    
    // Create an OpenGL context on the window we've just created
    glfwMakeContextCurrent(window);
    
    // Enable vertical sync (on cards that support it)
    glfwSwapInterval(1);
    
    // Initialise GLEW
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        kp::debug::fatal("glewInit failed: %s\n", glewGetErrorString(err));
    }

    // print out some info about the graphics drivers
    kp::debug::info("OpenGL version: %s", glGetString(GL_VERSION));
    kp::debug::info("GLSL version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    kp::debug::info("Vendor: %s", glGetString(GL_VENDOR));
    kp::debug::info("Renderer: %s", glGetString(GL_RENDERER));

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    kp::gl::error("glGenVertexArrays", glGetError());
    
    glBindVertexArray(vao);
    kp::gl::error("glBindVertexArray", glGetError());
    
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
    
    // Define and compile the shaders
    kp::gl::Shader* vertextShader = new kp::gl::Shader(kp::file::read("shaders/vertex_shader.glsl"), GL_VERTEX_SHADER);
    kp::gl::Shader* fragmentShader = new kp::gl::Shader(kp::file::read("shaders/fragment_shader.glsl"), GL_FRAGMENT_SHADER);

    // Create the shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertextShader->shader);
    glAttachShader(shaderProgram, fragmentShader->shader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    
    // Send a color to the shader program
    GLint triangleColor = glGetUniformLocation(shaderProgram, "triangleColor");
    glUniform3f(triangleColor, 1.0f, 1.0f, 1.0f);
    
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    int mouseX, mouseY;
    int windowWidth, windowHeight;
    
    while(1)
    {
        glfwGetCursorPos(window, &mouseX, &mouseY);
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        
        if (mouseX < 0)
        {
            mouseX = 0;
        }
        else if (mouseX > windowWidth)
        {
            mouseX = windowWidth;
        }
        
        if (mouseY < 0)
        {
            mouseY = 0;
        }
        else if (mouseY > windowHeight)
        {
            mouseY = windowHeight;
        }
        
        glUniform3f(triangleColor,
                    (float)mouseX / (float)windowWidth,
                    (float)mouseY / (float)windowHeight,
                    1.0f - (float)mouseX / (float)windowWidth);
        
        // Clear color buffer to black
        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Draw the triangle
        glDrawArrays( GL_TRIANGLES, 0, 3 );

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

    // Cleanup our file handlers
    kp::file::cleanup();

    delete vertextShader;
    delete fragmentShader;

    exit(EXIT_SUCCESS);
}
