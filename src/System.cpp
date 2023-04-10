//
// Created by csong on 4/7/2023.
//

#include <iostream>
#include "System.hpp"
#include "View/stb_image.h"
#include "Model/Game.hpp"
#include "View/Widget/Menu.hpp"
#include "Controller/Controller.hpp"
#include "glm/gtc/matrix_transform.hpp"


unsigned int System::SCREEN_WIDTH;
unsigned int System::SCREEN_HEIGHT;

Game *System::game{};
Menu *System::activeMenu{};
std::map<State, Menu *> System::menus{};
GameMenu *System::gameMenu{};
State System::state = MAIN;

static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

System::System(unsigned int screenWidth, unsigned int screenHeight) {
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

//initiliaze a new game
void System::init() {
    gameMenu = dynamic_cast<GameMenu *>(buildGameMenu());
    menus[State::PLAY] = gameMenu;
    game = new Game();
    Controller::init(game, gameMenu);
    Controller::getInfo();
    Controller::sendInfo();
    gameMenu->build();
}

void System::run() {
    activeMenu = menus[state];

    double limitFPS = 1.0 / 60.0;

    double startTime = glfwGetTime(), lastTime = startTime, timer = lastTime;
    double deltaTime = 0, nowTime = 0;
    int frames = 0 , updates = 0;

    while (!glfwWindowShouldClose(window)) {
        nowTime = glfwGetTime();
        deltaTime += (nowTime - lastTime) / limitFPS;
        lastTime = nowTime;

        if (state == PLAY) {

            if (deltaTime >= 1.0){
                Controller::getInfo();
                Controller::sendInfo();

                game->update();
                gameMenu->update();

                updates++;
                deltaTime--;
            }
        }

        clear();
        activeMenu->draw();
        glfwSwapBuffers(window);
        glfwPollEvents();

        ++frames;
        if (glfwGetTime() - timer > 1.0) {
            timer ++;
            //std::cout << "FPS: " << frames << " Updates:" << updates << "  " << timer << std::endl;
            updates = 0, frames = 0;
        }
    }
}

void System::changeState(State newState) {
    state = newState;
    activeMenu = menus[newState];
}

void System::buildMenu() {
    menus[State::MAIN] = buildMainMenu();
    menus[State::PLAY] = buildGameMenu();
    menus[State::WIN] = buildWinMenu();
    menus[State::DEAD] = buildDeadMenu();
}

Menu *System::buildMainMenu() {
    Menu *menu = new Menu();

    //Title screen
    glm::mat4 trans = glm::mat4(1.0f);
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

Menu *System::buildWinMenu() {
    Menu *menu = new Menu();

    //Win text
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::scale(trans, glm::vec3(0.8, 0.3, 1));

    new TexturedRectangle(
            menu,
            "../assets/win_text.png",
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
            trans
    );

    return menu;
}

Menu *System::buildDeadMenu() {
    Menu *menu = new Menu();

    //Dead text
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::scale(trans, glm::vec3(0.8, 0.3, 1));
    new TexturedRectangle(
            menu,
            "../assets/dead_text.png",
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
            trans
    );

    return menu;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    //Exit on escape
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (System::getState() == MAIN) {
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            System::init(); //restart game
            System::changeState(PLAY);
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
        glfwGetCursorPos(window, &xpos, &ypos);
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    System::setScreenHeight(height);
    System::setScreenWidth(width);
}

System::~System() {
    glfwTerminate();
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
