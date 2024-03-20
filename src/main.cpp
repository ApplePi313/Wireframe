#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Entity/Character.hpp"
#include "Entity/Hitbox.hpp"
#include "Entity/Bullet.hpp"

#include "World/Room.hpp"
#include "World/Hall.hpp"
#include "World/Level.hpp"

#include "Globals.hpp"

#include "Writer.hpp"

using namespace Globals;

/*
    Some things to remember:
        We do radians here, but 0 is up
        Coord system is the normal computer screen
        
*/

Writer writer;

int newWindowWidth;
int newWindowHeight;

float xPos = 0;
float yPos = 0;

float xChange = 0.0f;
float yChange = 0.0f;

float speed = 4.0f;

Character character;

// Room room;

Level level;

Shader bulletsShader;
std::vector<Bullet> bullets;
bool bulletShot;

Hitbox** levelHitboxesPtr;
int levelWidth = 81;
int levelHeight = 41;

// Hall hall;

void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);
void updateEntities();

void checkHitboxInteractions(float*, float*);

int main(void) {
    windowWidth = 800;
    windowHeight = 600;

            /*
            
            Window Setup
            
            */

    // Initialize glfw
    glfwInit();

    // Set the window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // gl version 4.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0); // gl version x.0 (both add up to 4.0)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // resources.windowWidth = windowWidth;
    // resources.windowHeight = windowHeight;
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


    character.setup("src/Assets/Characters/Player.attr", "src/Shaders/VertexShader.vert", "src/Shaders/FragmentShader.frag", 32.0f, Coord(windowWidth/2.0f - 16 + xPos, windowHeight/2.0f - 16 + yPos));

    // hall.setup(0.0f, 576.0f, 8, 4, 0, "src/Shaders/VertexShader.vert", "src/Shaders/FragmentShader.frag");

    // room.setup(0.0f, 0.0f, levelWidth, levelHeight, 0, "src/Shaders/VertexShader.vert", "src/Shaders/FragmentShader.frag");

    // room.formEntry(0, 2, 2);

    // Room bleh = Room(0.0f, 0.0f, levelWidth, levelHeight, 0, "src/Shaders/VertexShader.vert", "src/Shaders/FragmentShader.frag");

    level = Level(Coord(0.0f, 0.0f), levelWidth, levelHeight, "src/Shaders/VertexShader.vert", "src/Shaders/FragmentShader.frag");

    bulletsShader.fileSetup("src/Shaders/VertexShader.vert", "src/Shaders/FragmentShader.frag");
            /*
            
            Main Rendering Loop
            
            */

    while(!glfwWindowShouldClose(window)) {
        glfwGetWindowSize(window, &newWindowWidth, &newWindowHeight); // update the screen dimensions in case of a resize
        if (newWindowHeight != windowWidth || newWindowHeight != windowHeight) {
            xPos += (windowWidth - newWindowWidth) / 2;
            yPos += (windowHeight - newWindowHeight) / 2;
            windowWidth = newWindowWidth;
            windowHeight = newWindowHeight;
        }

        // check inputs
        processInput(window);
        // clear the screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // currently clears to be grey
        glClear(GL_COLOR_BUFFER_BIT);

        // writer.render_text("hello", 50, 50, 24, 24);

        /*
        
        Stuff for rendering
        
        */ 

        level.draw(Coord(xPos, yPos));

        character.draw(Coord(xPos, yPos));

        updateEntities();

        // update the screen
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    // room.close();


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
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE) {
        // generate hall
    }

    if (xChange && yChange) {
        xChange /= 1.414; // divide by sqrt(2)
        yChange /= 1.414;
    }

    checkHitboxInteractions(&xChange, &yChange);

    xPos += xChange;
    yPos += yChange;

    if (!bulletShot && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        bullets.push_back(character.shoot(0));
        bulletShot = true;
        std::cout << "new bullet\n";
    } else if (!glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        bulletShot = false;
    }
}

void updateEntities() {
    bulletsShader.activate();
    bulletsShader.set2f("dimensions", 32.0f, 32.0f);
    bulletsShader.set2f("resize", 32.0f/2.0f, -32.0f/2.0f);
    bulletsShader.set2f("worldCoords", xPos, yPos);
    for (int i = bullets.size() - 1; i >= 0; i--) {
        if (bullets.at(i).signal(Signal(Update)).type == Delete) {
            std::cout << "dead bullet\n";
            bullets.erase(bullets.begin() + i);
        } else {
            bullets.at(i).draw(&bulletsShader);
        }
    }
}

void checkHitboxInteractions(float* xPtr, float* yPtr) {
    float x = *xPtr;
    float y = *yPtr;

    level.getHitboxes(&levelHitboxesPtr, &levelWidth, &levelHeight);

    xPos += x;

    character.translate(Coord(x, 0));

    bool alreadyMovedBack = false;

    for (int i = 0; i < levelHeight; i++) {
        for (int j = 0; j < levelWidth; j++) {
            if (character.getHitbox().isColliding(*(*(levelHitboxesPtr + i) + j))) {
                if ((*(*(levelHitboxesPtr + i) + j)).isBlocking() && !alreadyMovedBack) {
                    *xPtr -= x;

                    character.translate(Coord(-x, 0));

                    alreadyMovedBack = true;
                }
            }
        }
    }

    xPos -= x;


    yPos += y;

    character.translate(Coord(0, y));

    alreadyMovedBack = false;

    for (int i = 0; i < levelHeight; i++) {
        for (int j = 0; j < levelWidth; j++) {
            if (character.getHitbox().isColliding(*(*(levelHitboxesPtr + i) + j))) {
                if ((*(*(levelHitboxesPtr + i) + j)).isBlocking() && !alreadyMovedBack) {
                    *yPtr -= y;

                    character.translate(Coord(0, -y));

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
