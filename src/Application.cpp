// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "SceneManager.h"
#include "models/Quadrilateral.h"


Renderer renderer;

GLFWwindow* InitWindow()
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow( 1440, 900, "Tutorial 02 - Red triangle", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return nullptr;

    }
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return nullptr;
    }

    std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return window;
}

int main( void )
{
    GLFWwindow* window = InitWindow();
    if (!window)
        return -1;

    GLCall( glEnable(GL_BLEND) );
    GLCall( glEnable(GL_MULTISAMPLE); )
    GLCall( glEnable(GL_CULL_FACE); )
    GLCall( glEnable(GL_DEPTH_TEST );)
    GLCall( glDepthFunc(GL_LESS); )
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );
    GLCall( glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); )

    {
        SceneManager& sceneManager = SceneManager::init();
        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
            SceneManager::static_callback(window, xpos, ypos);
        });

        const siv::PerlinNoise::seed_type seed = 123456u;

        const siv::PerlinNoise perlin{ seed };

        float cameraSpeed = 0.2f;

        float sidewaysMovement = 0;
        float forwardMovement = 0;


        do {
            sceneManager.Compile();

            glfwSwapBuffers(window);
            glfwPollEvents();
            if(glfwGetKey(window, GLFW_KEY_W)) {
                forwardMovement=cameraSpeed;
            }
            if(glfwGetKey(window, GLFW_KEY_S)) {
                forwardMovement=-cameraSpeed;
            }
            if(!glfwGetKey(window, GLFW_KEY_S) && !glfwGetKey(window, GLFW_KEY_W)) {
                forwardMovement = 0;
            }
            if(glfwGetKey(window, GLFW_KEY_A)) {
                sidewaysMovement=-cameraSpeed;
            }
            if(glfwGetKey(window, GLFW_KEY_D)) {
                sidewaysMovement=cameraSpeed;
            }
            if(!glfwGetKey(window, GLFW_KEY_A) && !glfwGetKey(window, GLFW_KEY_D)) {
                sidewaysMovement = 0;
            }
            sceneManager.getCamera()->moveFoward(forwardMovement, sidewaysMovement);
        } // Check if the ESC key was pressed or the window was closed
        while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                glfwWindowShouldClose(window) == 0 );
    }

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

