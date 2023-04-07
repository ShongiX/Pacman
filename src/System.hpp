//
// Created by csong on 4/7/2023.
//

#ifndef PACMAN_SYSTEM_HPP
#define PACMAN_SYSTEM_HPP

#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"
#include "shader.h"
#include "TexturedRectangle.hpp"

class System {
    unsigned int SCREEN_WIDTH;
    unsigned int SCREEN_HEIGHT;
    GLFWwindow *window{};

public:
    System(unsigned int screenWidth, unsigned int screenHeight);
    ~System();

    GLFWwindow *getWindow() const;

    void run();
    void clear(float r = 0.0, float g = 0.0, float b = 0.0);
    void draw();

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

    void initializeGlfw();

    //TEMPORARY
    TexturedRectangle* rec{};
};


#endif //PACMAN_SYSTEM_HPP
