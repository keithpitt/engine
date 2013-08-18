#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

#include "engine.h"

#include "file.hpp"


#include <glew/glew.h>

#define GLFW_DLL
#define GLFW_INCLUDE_GLU
#include <glfw/glfw3.h>

#include <glm/glm.hpp> // Base glm types which include glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include <glm/gtc/type_ptr.hpp> // Includes functions in converting glm matricies to opengl ones
#include <glm/gtc/matrix_transform.hpp> // Matrix transformation functions

#include <libpng/png.h>

#include "gl.hpp"
#include "shader.hpp"

#include <physfs/physfs.h>


#include <boost/format.hpp>

bool jumping = false;
bool facingRight = true;

float yVelocity = 0;
float leftVelocity = 0;
float rightVelocity = 0;
float speed = 0.1f;

bool qToggle = false;

static void error_callback(int error, const char* description)
{
    //kp::debug::fatal(description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        jumping = true;
        yVelocity += 0.5f;
    }
    
    if(key == GLFW_KEY_Q && action == GLFW_PRESS) {
        qToggle = !qToggle;
    }
    
    if(key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) {
        if(action == GLFW_PRESS) {
            rightVelocity += speed;
            facingRight = true;
        } else if (action == GLFW_RELEASE) {
            rightVelocity = 0;
        }
    }
    
    if(key == GLFW_KEY_LEFT || key == GLFW_KEY_A) {
        if(action == GLFW_PRESS) {
            leftVelocity -= speed;
            facingRight = false;
        } else if (action == GLFW_RELEASE) {
            leftVelocity = 0;
        }
    }
}

void user_read_data(png_structp png_ptr, png_bytep data, png_size_t length) {
    //Here we get our IO pointer back from the read struct.
    //This is the parameter we passed to the png_set_read_fn() function.
    //Our std::istream pointer.
    PHYSFS_File* handle = (PHYSFS_File*)png_get_io_ptr(png_ptr);
    
    PHYSFS_readBytes(handle, data, length);
}

int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;

bool fullscreen = false;

int main(int argc, char** argv)
{
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    // Initialise GLFW
    if (!glfwInit()) {
        LOG_FATAL(GLFW, "glfwInit failed");
    }

    
    // Initialize the file system reader
    kp::file::init(argv[0]);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 32);
    
    // Open a window and create its OpenGL context
    
    GLFWmonitor * monitorToFullscreenTo = NULL;
    if(fullscreen) {
        monitorToFullscreenTo = glfwGetPrimaryMonitor();
    }
    
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cat", monitorToFullscreenTo, NULL);
    if (!window)
        LOG_FATAL(GLFW, "glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");

    // Create an OpenGL context on the window we've just created
    glfwMakeContextCurrent(window);
    
    glfwSetKeyCallback(window, key_callback);

    // Enable vertical sync (on cards that support it)
    glfwSwapInterval(1);
    

    glEnable(GL_BLEND);
    kp::gl::error("glEnable", glGetError());
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    kp::gl::error("glBlendFunc", glGetError());


    // Initialise GLEW
    // The glewExperimental line is necessary to force GLEW to use a modern
    // OpenGL method for checking if a function is available.
    // See: http://open.gl/context
    
    // GLEW has a problem with core contexts. It calls glGetString(GL_EXTENSIONS)​, which causes GL_INVALID_ENUM​ on GL 3.2+ core
    // context as soon as glewInit()​ is called. It also doesn't fetch the function pointers. The solution is for GLEW to use
    // glGetStringi​ instead. The current version of GLEW is 1.10.0 but they still haven't corrected it.
    // The only fix is to use glewExperimental​ for now:

    glewExperimental = GL_TRUE;
    kp::gl::error("glewExperimental", glGetError());
    
    GLenum err = glewInit();
    kp::gl::error("glewInit", glGetError());
    
    if(err == GLEW_OK) {
        LOG_INFO(GLEW, boost::format("glewInit loaded version: %s") % glewGetString(GLEW_VERSION));
    } else {
        LOG_FATAL(GLEW, boost::format("glewInit failed: %s\n") % glewGetErrorString(err));
    }
    

    // print out some info about the graphics drivers
    
    LOG_INFO(OPENGL, boost::format("OpenGL version: %s") % glGetString(GL_VERSION));
    kp::gl::error("glGetString", glGetError());
    
    LOG_INFO(OPENGL, boost::format("GLSL version: %s") % glGetString(GL_SHADING_LANGUAGE_VERSION));
    kp::gl::error("glGetString", glGetError());
    
    LOG_INFO(OPENGL, boost::format("Vendor: %s") % glGetString(GL_VENDOR));
    kp::gl::error("glGetString", glGetError());
    
    LOG_INFO(OPENGL, boost::format("Renderer: %s") % glGetString(GL_RENDERER));
    kp::gl::error("glGetString", glGetError());
    
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    
    
    
    
    // Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays( 1, &vao ); kp::gl::error("glGenVertexArrays", glGetError());
	glBindVertexArray( vao ); kp::gl::error("glBindVertexArray", glGetError());
    
    
    
	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers( 1, &vbo ); kp::gl::error("glGenBuffers", glGetError());
    
    
    // Define the vertices for our triangle
    float vertices[] = {
        // x      y     color             texcords
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
    };
    
    
    
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    kp::gl::error("glBindBuffer", glGetError());
    
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
    kp::gl::error("glBufferData", glGetError());
    

    
    
    // Create an element array
	GLuint ebo;
	glGenBuffers( 1, &ebo );
    
	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};
    
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    kp::gl::error("glBindBuffer", glGetError());
    
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( elements ), elements, GL_STATIC_DRAW );
    kp::gl::error("glBufferData", glGetError());
    

    
    
    
    
    
    // Define and compile the shaders
    kp::gl::Shader* vertextShader = new kp::gl::Shader("vertex_shader.vsh", kp::file::read("shaders/vertex_shader.vsh"), GL_VERTEX_SHADER);
    kp::gl::Shader* fragmentShader = new kp::gl::Shader("fragment_shader.fsh", kp::file::read("shaders/fragment_shader.fsh"), GL_FRAGMENT_SHADER);
    
    // Create the shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertextShader->shader);
    glAttachShader(shaderProgram, fragmentShader->shader);
    glBindFragDataLocation( shaderProgram, 0, "outColor" );
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    

    
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0);
    glEnableVertexAttribArray(posAttrib);
    
    GLint colorAttribute = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colorAttribute);
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(2*sizeof(float)));
    
    GLint texCordAttribute = glGetAttribLocation(shaderProgram, "texcord");
    glEnableVertexAttribArray(texCordAttribute);
    glVertexAttribPointer(texCordAttribute, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(5*sizeof(float)));
    
    
    
    
    
    
    
    
    
    
    
    
    // Texture time!
    GLuint texture;
    glGenTextures(1, &texture);
    kp::gl::error("glGenTextures", glGetError());
    
    glBindTexture(GL_TEXTURE_2D, texture);
    kp::gl::error("glBindTexture", glGetError());
    
    glActiveTexture( GL_TEXTURE0 );
    
    // When the texture gets bigger/smaller, how to do the actual resizing?
    // Nearest neighbour interpolation is more suited in games that want to mimic 8 bit graphics, because of the pixelated look.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    // Clamp the texture right up to the edges of the thing
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    
    
    
    

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    // Stolen mostly from: http://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures
    // Expect mine uses PhysicsFS as a source
    // With help from: http://www.piko3d.com/tutorials/libpng-tutorial-loading-png-files-from-streams
    
    const char* filename = "cat.png";
    
    PHYSFS_File* handle = PHYSFS_openRead(filename);
    
    if(handle == NULL)
    {
        //kp::debug::error("PHYSFS_openRead(%s): %s", filename, PHYSFS_getLastError());
        
        return NULL;
    }
    
    int pngSigSize = 8;
    png_byte pngsig[8];
    
    // Read the bytes
    if(PHYSFS_readBytes(handle, pngsig, pngSigSize) != pngSigSize)
    {
        //kp::debug::error("PHYSFS_read: %s", PHYSFS_getLastError());
        
        return NULL;
    }
    
    int is_png = png_sig_cmp(pngsig, 0, pngSigSize);
    if (is_png != 0) LOG_ERROR(LIBPNG, boost::format("libpng failed to validate %s with error code %i") % filename % is_png);
    
    png_structp pngReadStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    //if(!pngReadStruct) kp::debug::error("Failed png_create_read_struct");
    
    png_infop pngInfoStruct = png_create_info_struct(pngReadStruct);
    //if(!pngInfoStruct) kp::debug::error("Failed png_create_info_struct");
    
    
    png_set_read_fn(pngReadStruct, (png_voidp)handle, user_read_data);
    
    png_set_sig_bytes(pngReadStruct, pngSigSize);
    
    png_read_info(pngReadStruct, pngInfoStruct);
    
    
    png_uint_32 imgWidth =  png_get_image_width(pngReadStruct, pngInfoStruct);
    png_uint_32 imgHeight = png_get_image_height(pngReadStruct, pngInfoStruct);
    
    
    // Update the png info struct.
    png_read_update_info(pngReadStruct, pngInfoStruct);
    
    // Row size in bytes.
    png_size_t rowbytes = png_get_rowbytes(pngReadStruct, pngInfoStruct);
    
    // Allocate the image_data as a big block, to be given to opengl
    png_byte *image_data = new png_byte[rowbytes * imgHeight];
    if (!image_data) {
        //clean up memory and close stuff
        //break
    }
    
    //row_pointers is for pointing to image_data for reading the png with libpng
    png_bytep *row_pointers = new png_bytep[imgHeight];
    if (!row_pointers) {
        //break
    }
    
    // set the individual row_pointers to point at the correct offsets of image_data
    for (int i = 0; i < imgHeight; ++i) {
        row_pointers[i] = image_data + i * rowbytes;
        // load image in reverse order
        // row_pointers[imgHeight - 1 - i] = image_data + i * rowbytes;
    }
    
    //read the png into image_data through row_pointers
    png_read_image(pngReadStruct, row_pointers);
    
    //kp::debug::info("Successfully loaded %s [%ix%i]", filename, imgWidth, imgHeight);
    
    
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)image_data);
    
    //clean up memory and close stuff
    png_destroy_read_struct(&pngReadStruct, &pngInfoStruct, NULL);
    delete[] image_data;
    delete[] row_pointers;
    
    
    // Close the file handle
    PHYSFS_close(handle);
    
    
    // Black/white checkerboard
    //float pixels[] = {
    //    0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
    //    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
    //};
    //glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels );
    
    // Pre-generate the mip maps for performance
    glGenerateMipmap(GL_TEXTURE_2D);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    GLint cameraAttribute = glGetUniformLocation(shaderProgram, "camera");
    
    GLint modelAttribute = glGetUniformLocation(shaderProgram, "model");
    
    GLint projectionAttribute = glGetUniformLocation(shaderProgram, "projection");
    
    glm::mat4 cameraMatrix = glm::mat4();
    glm::mat4 modelMatrix;
    glm::mat4 projectionMatrix;

    glm::vec3 position = glm::vec3(0, 2, 0);
    glm::vec3 cameraPosition = glm::vec3(3, 3, 3);
    
    
    
    
    
    
    jumping = true;
    

    float gravity = -0.05f;
    

    
	while ( !glfwWindowShouldClose(window) )
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
        
        if (!facingRight) {
            modelMatrix = glm::rotate(modelMatrix, 180.0f, glm::vec3(0, 1, 0));
        }
        
        glUniformMatrix4fv(modelAttribute, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        
        ////////////////////
        
        float aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
        
        if(!qToggle) {
            projectionMatrix = glm::ortho(-1.0f * aspectRatio, 1.0f * aspectRatio, -1.0f, 1.0f, 0.0f, 100.0f);
            
            // scale the project down so we can see more of the screen - not sure if this is a good
            // idea or not. we'll see i suppose.
            projectionMatrix = glm::scale(projectionMatrix, glm::vec3(0.25f));
            
            cameraPosition = glm::vec3(0, 2.5, 5);
            lookAtPosition = glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z - 3);
            
        } else {
            projectionMatrix = glm::perspective(50.0f, aspectRatio, 0.1f, 100.0f);
            
            // fly by cam
            //cameraPosition = glm::vec3(0, 0, 3);
            //lookAtPosition = glm::vec3(position.x, cameraPosition.y + 0.25, cameraPosition.z - 3);
            
            //cameraPosition = glm::vec3(position.x, 0, position.z);
            //cameraPosition.z += 5;
            //cameraPosition.y += 1;
            //lookAtPosition = glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z);
            //lookAtPosition.z -= 1;
            
            // scene cam
            cameraPosition = glm::vec3(2, 2, 4);
            lookAtPosition = glm::vec3(0, 0, 0);
            
        }
        
        glUniformMatrix4fv(projectionAttribute, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        
        ////////////////////
        
        cameraMatrix = glm::lookAt(cameraPosition, lookAtPosition, glm::vec3(0,1,0));
        
        glUniformMatrix4fv(cameraAttribute, 1, GL_FALSE, glm::value_ptr(cameraMatrix));
        
        ////////////////////
        
        // Clear color buffer to black
        glClearColor(253.0 / 255.0f, 238.0 / 255.0f, 230.0 / 255.0f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

		
		// Draw a rectangle from the 2 triangles using 6 indices
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        // Check if the ESC key was pressed or the window should be closed
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) || glfwGetKey(window, GLFW_KEY_ENTER))
            break;
	}
    
	glDeleteProgram( shaderProgram );
    delete vertextShader;
    delete fragmentShader;
    
	glDeleteBuffers( 1, &ebo );
	glDeleteBuffers( 1, &vbo );
    
	glDeleteVertexArrays( 1, &vao );

    
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    // Cleanup our file handlers
    kp::file::cleanup();
    
    

    exit(EXIT_SUCCESS);
}
