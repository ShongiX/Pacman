//
// Created by csong on 4/7/2023.
//

#include <iostream>
#include "System.hpp"
#include "Graphics/stb_image.h"
#include "Game/Game.hpp"
#include "Graphics/Menu.hpp"
#include "Controller.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

unsigned int System::SCREEN_WIDTH;
unsigned int System::SCREEN_HEIGHT;
unsigned int System::REFRESH;

Menu *System::activeMenu{};
std::map<State, Menu *> System::menus{};
State System::state = MAIN;

System::System(unsigned int screenWidth, unsigned int screenHeight, unsigned int refresh) {
    SCREEN_WIDTH = screenWidth;
    SCREEN_HEIGHT = screenHeight;

    initializeGlfw();

    buildMenu();
    init();
}

void System::initializeGlfw() {
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    window = glfwCreateWindow((int) SCREEN_WIDTH, (int) SCREEN_HEIGHT, "Pac-Man", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    // Set callback functions
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    stbi_set_flip_vertically_on_load(true);
}

void System::clear(float r, float g, float b) {
    glClearColor(r, g, b, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void System::init() {
    game = new Game();
    Controller::init(game, gameMenu);
    Controller::getInfo();
    Controller::sendInfo();
    if (gameMenu) gameMenu->build();
}

void System::run() {
    activeMenu = menus[state];

    int loopCount = 0;
    while (!glfwWindowShouldClose(window)) {
        clear();

        if (state == PLAY) {
            if (++loopCount >= REFRESH && game) {

                Controller::getInfo();
                Controller::sendInfo();

                game->update();
                loopCount = 0;
            }
        }

        activeMenu->draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void System::changeState(State newState) {
    state = newState;
    activeMenu = menus[newState];
}

void System::buildMenu() {
    menus[State::MAIN] = buildMainMenu();
    menus[State::PLAY] = buildGameMenu();
}

Menu *System::buildMainMenu() {
    Menu *menu = new Menu();



    //Title screen
    glm::mat4 trans = glm::mat4(1.0f);
    //trans = glm::scale(trans, glm::vec3(1,0.5,1));
    //trans = glm::translate(trans, glm::vec3(0,0.75,1));
    //trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));

    new TexturedRectangle(
            menu,
            "../assets/pacman_titlescreen.png",
            {
                    // positions          // colors           // texture coords
                    1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
                    1.0f, -1.0, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom right
                    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom left
                    -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // top left
            },
            {
                    0, 1, 3,   // first triangle
                    1, 2, 3    // second triangle
            },
            trans
    );

    //Start text
    trans = glm::mat4(1.0f);
    trans = glm::scale(trans, glm::vec3(0.8, 0.1, 1));
    trans = glm::translate(trans, glm::vec3(0, -8.0, 0));

    new TexturedRectangle(
            menu,
            "../assets/pacman_starttext.png",
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
            trans
    );

    return menu;
}

Menu *System::buildGameMenu() {
    gameMenu = new GameMenu();

    //map
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::scale(trans, glm::vec3(1, 31.0 / 36.0, 1));
    trans = glm::translate(trans, glm::vec3(0, -0.5 / 36, 0));

    new TexturedRectangle(
            gameMenu,
            "../assets/map.png",
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
            trans
    );

    glm::mat4 pacman = glm::mat4(1.0f);
    pacman = glm::scale(pacman, glm::vec3(1.0/28,1.0/36,1));

    new TexturedRectangle(
            gameMenu,
            "../assets/pacman2.png",
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
            pacman
            );

    return gameMenu;
}


void System::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (System::state == MAIN) {
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            changeState(PLAY);
        }
    } else if (System::state == PLAY) {
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            if (Controller::askIfCanTurn(LEFT)) {
                Controller::turn(LEFT);
            }
        }
    }
}

void System::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << "Cursor Position at (" << xpos << " : " << ypos << ")\n";
    }
}

void System::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    System::SCREEN_HEIGHT = height;
    System::SCREEN_WIDTH = width;
}

System::~System() {
    glfwTerminate();
}
