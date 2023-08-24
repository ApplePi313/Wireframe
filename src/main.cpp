#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Entity/Character.hpp"
#include "Entity/Hitbox.hpp"

#include "World/Room.hpp"
#include "World/Hall.hpp"

#include "UniversalResources.hpp"

/*
    Some things to remember:
        We do radians here, but 0 is up
        Coord system is the normal computer screen
        
*/

UniversalResources resources;

int windowWidth = 800;
int windowHeight = 600;

float xPos = 0;
float yPos = 0;

float xChange = 0.0f;
float yChange = 0.0f;

float speed = 1;

Character character;

Room room;
Hitbox** roomHitboxesPtr;
int roomWidth = 10;
int roomHeight = 10;

Hall hall;

void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);

void checkHitboxInteractions(float*, float*);

int main(void) {

            /*
            
            Window Setup
            
            */

    // Initialize glfw
    glfwInit();

    // Set the window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // gl version 4.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0); // gl version x.0 (both add up to 4.0)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    resources.windowWidth = windowWidth;
    resources.windowHeight = windowHeight;
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Window", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;

        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Tell openGL the size of the window
    glViewport(0, 0, windowWidth, windowHeight); // arg1 and 2 are the coords of the bottom left

    // For if the window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  


    // Set the window title
    glfwSetWindowTitle(window, "Wireframe");

    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHintString(GLFW_X11_CLASS_NAME, "Wireframe");

            /*
            
            Config Setup
            
            */

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // These two are for textures, probably don't need them
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Go into wireframe mode
    glLineWidth(4.0f); // Set the stroke size (max of 10)


    character.setup("src/Assets/Characters/Player.attr", "src/Shaders/VertexShader.vert", "src/Shaders/FragmentShader.frag", 32.0f, windowWidth/2.0f - 16 + xPos, windowHeight/2.0f - 16 + yPos);

    hall.setup(0.0f, 576.0f, 8, 4, 0, "src/Shaders/VertexShader.vert", "src/Shaders/FragmentShader.frag");

    room.setup(0.0f, 0.0f, roomWidth, roomHeight, 0, "src/Shaders/VertexShader.vert", "src/Shaders/FragmentShader.frag");

            /*
            
            Main Rendering Loop
            
            */

    while(!glfwWindowShouldClose(window)) {
        glfwGetWindowSize(window, &resources.windowWidth, &resources.windowHeight); // update the screen dimensions in case of a resize
        xPos += (windowWidth - resources.windowWidth) / 2;
        yPos += (windowHeight - resources.windowHeight) / 2;
        windowWidth = resources.windowWidth;
        windowHeight = resources.windowHeight;

        // check inputs
        for (int i = 0; i < 10; i++) {
            processInput(window);
        }

        // clear the screen
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // currently clears to be black
        glClear(GL_COLOR_BUFFER_BIT);


        /*
        
        Stuff for rendering
        
        */ 

        room.draw(xPos, yPos);

        character.draw(windowWidth, windowHeight, xPos, yPos);


        // update the screen
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    room.close();


    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    xChange = 0.0f;
    yChange = 0.0f;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        yChange -= speed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        xChange -= speed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        yChange += speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        xChange += speed;
    }

    checkHitboxInteractions(&xChange, &yChange);

    xPos += xChange;
    yPos += yChange;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        character.shoot(0);
    }
}

void checkHitboxInteractions(float* xPtr, float* yPtr) {
    float x = *xPtr;
    float y = *yPtr;

    room.getHitboxes(&roomHitboxesPtr, &roomWidth, &roomHeight);

    xPos += x;

    character.translate(x, 0);

    bool alreadyMovedBack = false;

    for (int i = 0; i < roomHeight; i++) {
        for (int j = 0; j < roomWidth; j++) {
            if (character.getHitbox().isColliding(*(*(roomHitboxesPtr + i) + j))) {
                if ((*(*(roomHitboxesPtr + i) + j)).isBlocking() && !alreadyMovedBack) {
                    *xPtr -= x;

                    character.translate(-x, 0);

                    alreadyMovedBack = true;
                }
            }
        }
    }

    xPos -= x;


    yPos += y;

    character.translate(0, y);

    alreadyMovedBack = false;

    for (int i = 0; i < roomHeight; i++) {
        for (int j = 0; j < roomWidth; j++) {
            if (character.getHitbox().isColliding(*(*(roomHitboxesPtr + i) + j))) {
                if ((*(*(roomHitboxesPtr + i) + j)).isBlocking() && !alreadyMovedBack) {
                    *yPtr -= y;

                    character.translate(0, -y);

                    Hitbox tmp = character.getHitbox();

                    alreadyMovedBack = true;

                    break;
                }
            }
        }

        if (alreadyMovedBack) break;
    }

    yPos -= y;
}
