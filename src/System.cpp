//
// Created by csong on 4/7/2023.
//

#include <iostream>
#include "System.hpp"
#include "View/stb_image.h"
#include "Model/Game.hpp"
#include "View/Menu.hpp"
#include "Controller.hpp"
#include "glm/gtc/matrix_transform.hpp"


unsigned int System::SCREEN_WIDTH;
unsigned int System::SCREEN_HEIGHT;
unsigned int System::REFRESH;

Game *System::game{};
Menu *System::activeMenu{};
std::map<State, Menu *> System::menus{};
GameMenu *System::gameMenu{};
State System::state = MAIN;

static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

System::System(unsigned int screenWidth, unsigned int screenHeight, unsigned int refresh) {
    SCREEN_WIDTH = screenWidth;
    SCREEN_HEIGHT = screenHeight;
    REFRESH = refresh;

    initializeGlfw();

    buildMenu();
    //init();
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

//initiliaze a new game
void System::init() {
    game = new Game();
    Controller::init(game, gameMenu);
    Controller::getInfo();
    Controller::sendInfo();
    gameMenu->build();
}

void System::run() {
    activeMenu = menus[state];

    while (!glfwWindowShouldClose(window)) {
        clear();

        if (state == PLAY) {

                Controller::getInfo();
                Controller::sendInfo();

                game->update();
                gameMenu->update();
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
    menus[State::WIN] = menus[State::PLAY];
    menus[State::DEAD] = menus[State::PLAY];
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
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
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
    if (!gameMenu) exit(2);

    return gameMenu;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (System::getState() == MAIN) {
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            System::changeState(PLAY);
            System::init();
        }
    } else if (System::getState() == PLAY) {
        System::handle(window, key, scancode, action, mods);
    } else if (System::getState() == WIN || System::getState() == DEAD) {
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            System::changeState(MAIN);
        }
    }
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << "Cursor Position at (" << xpos << " : " << ypos << ")\n";
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    System::setScreenHeight(height);
    System::setScreenWidth(width);
}

System::~System() {
    glfwTerminate();
}

unsigned int System::getScreenWidth() {
    return SCREEN_WIDTH;
}

unsigned int System::getScreenHeight() {
    return SCREEN_HEIGHT;
}

void System::setScreenWidth(unsigned int screenWidth) {
    SCREEN_WIDTH = screenWidth;
}

void System::setScreenHeight(unsigned int screenHeight) {
    SCREEN_HEIGHT = screenHeight;
}

State System::getState() {
    return state;
}

void System::handle(GLFWwindow *window, int key, int scancode, int action, int mods) {
    activeMenu->handle(window, key, scancode, action, mods);
}
