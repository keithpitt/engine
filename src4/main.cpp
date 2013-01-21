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
    
    GLuint vertexBuffer;
    glGenBuffers( 1, &vertexBuffer );
    
    printf( "%u\n", vertexBuffer );

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    for (;;)
    {
        // Clear color buffer to black
        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Check if the ESC key was pressed or the window should be closed
        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
            break;
        if (glfwGetWindowParam(window, GLFW_SHOULD_CLOSE))
            break;
    }

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    exit(EXIT_SUCCESS);
}
