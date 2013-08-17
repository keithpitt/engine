#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

#include "string.hpp"
#include "file.hpp"
#include "debug.hpp"

#include <GL/glew.h>

#define GLFW_DLL
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include <glm/glm.hpp> // Base glm types which include glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include <glm/gtc/type_ptr.hpp> // Includes functions in converting glm matricies to opengl ones
#include <glm/gtc/matrix_transform.hpp> // Matrix transformation functions

#include "gl.hpp"
#include "shader.hpp"

bool jumping = false;
float yVelocity = 0;
float leftVelocity = 0;
float rightVelocity = 0;
float speed = 0.05;

bool qToggle = false;

static void error_callback(int error, const char* description)
{
    kp::debug::fatal(description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        jumping = true;
        yVelocity += 0.4f;
    }
    
    if(key == GLFW_KEY_Q && action == GLFW_PRESS) {
        qToggle = !qToggle;
    }
    
    if(key == GLFW_KEY_RIGHT) {
        if(action == GLFW_PRESS) {
            rightVelocity += speed;
        } else if (action == GLFW_RELEASE) {
            rightVelocity = 0;
        }
    }
    
    if(key == GLFW_KEY_LEFT) {
        if(action == GLFW_PRESS) {
            leftVelocity -= speed;
        } else if (action == GLFW_RELEASE) {
            leftVelocity = 0;
        }
    }
}

int SCREEN_WIDTH = 1400;
int SCREEN_HEIGHT = 900;

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
    glfwWindowHint(GLFW_SAMPLES, 32);

    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Engine", NULL, NULL);
    if (!window) {
        kp::debug::fatal("glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");
    }

    // Create an OpenGL context on the window we've just created
    glfwMakeContextCurrent(window);
    
    glfwSetKeyCallback(window, key_callback);

    // Enable vertical sync (on cards that support it)
    glfwSwapInterval(1);

    // Initialise GLEW
    // The glewExperimental line is necessary to force GLEW to use a modern OpenGL method for checking if a function is available.
    // See: http://open.gl/context
    glewExperimental = GL_TRUE;
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
        -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, // Top-left
        0.5f,  0.5f, 1.0f, 1.0f, 1.0f, // Top-right
        0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
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

    // Create an element buffer
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLuint elementBuffer;
    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    // Define and compile the shaders
    kp::gl::Shader* vertextShader = new kp::gl::Shader("vertex_shader.vsh", kp::file::read("shaders/vertex_shader.vsh"), GL_VERTEX_SHADER);
    kp::gl::Shader* fragmentShader = new kp::gl::Shader("fragment_shader.fsh", kp::file::read("shaders/fragment_shader.fsh"), GL_FRAGMENT_SHADER);

    // Create the shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertextShader->shader);
    glAttachShader(shaderProgram, fragmentShader->shader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    glEnableVertexAttribArray(posAttrib);

    GLint colorAttribute = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colorAttribute);
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
    
    GLint cameraAttribute = glGetUniformLocation(shaderProgram, "camera");
    glEnableVertexAttribArray(cameraAttribute);
    
    GLint modelAttribute = glGetUniformLocation(shaderProgram, "model");
    glEnableVertexAttribArray(modelAttribute);
    
    GLint projectionAttribute = glGetUniformLocation(shaderProgram, "projection");
    glEnableVertexAttribArray(projectionAttribute);
    
    glm::mat4 cameraMatrix = glm::mat4();
    glm::mat4 modelMatrix;
    glm::mat4 projectionMatrix;
    
    glm::vec3 position = glm::vec3(0, 2, 0);
    
    glm::vec3 cameraPosition = glm::vec3(3, 3, 3);
    
    jumping = true;
    
    float counter = 0.0;
    
    float gravity = -0.05f;
    
    while(1)
    {
        
        if(jumping) {
            yVelocity += gravity;
        }
        
        position.y += yVelocity;
        position.x += rightVelocity + leftVelocity;
        
        if(position.y <= 0) {
            position.y = 0;
            yVelocity = 0;
            jumping = false;
        }
        
        glm::vec3 lookAtPosition;
        
        ////////////////////
        
        modelMatrix = glm::translate(glm::mat4(), position);
        glUniformMatrix4fv(modelAttribute, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        
        ////////////////////
        
        float aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
        
        if(qToggle) {
            projectionMatrix = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, 0.0f, 100.0f);
            
            cameraPosition = glm::vec3(0, 0, 3);
            lookAtPosition = glm::vec3(cameraPosition.x, cameraPosition.y + 0.25, cameraPosition.z - 3);
            
            //cameraPosition = glm::vec3(position.x, position.y, position.z);
            //cameraPosition.z -= 5;
            //cameraPosition.y += 1;
        } else {
            projectionMatrix = glm::perspective(50.0f, aspectRatio, 0.1f, 100.0f);
            
            cameraPosition = glm::vec3(0, 0, 3);
            lookAtPosition = glm::vec3(position.x, cameraPosition.y + 0.25, cameraPosition.z - 3);
        }
        
        glUniformMatrix4fv(projectionAttribute, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        
        ////////////////////
        
        cameraMatrix = glm::lookAt(cameraPosition, lookAtPosition, glm::vec3(0,1,0));
        
        glUniformMatrix4fv(cameraAttribute, 1, GL_FALSE, glm::value_ptr(cameraMatrix));
        
        ////////////////////
        
        // Clear color buffer to black
        glClearColor(4.0 / 255.0f, 57.0 / 255.0f, 83.0 / 255.0f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle
        //glDrawArrays( GL_TRIANGLES, 0, 3 );
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Check if the ESC key was pressed or the window should be closed
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) || glfwGetKey(window, GLFW_KEY_ENTER))
            break;
        if (glfwWindowShouldClose(window))
            break;
        
        counter+= 0.14;
    }

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    // Cleanup our file handlers
    kp::file::cleanup();

    delete vertextShader;
    delete fragmentShader;

    exit(EXIT_SUCCESS);
}
