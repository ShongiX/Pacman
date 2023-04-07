//
// Created by csong on 4/7/2023.
//

#ifndef PACMAN_TEXTUREDRECTANGLE_HPP
#define PACMAN_TEXTUREDRECTANGLE_HPP


#include <vector>
#include "glad/glad.h"
#include "shader.h"

class TexturedRectangle {
private:
    unsigned int VAO{}, VBO{}, EBO{}, texture{};
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    Shader* shader{};

    void setupTexture(const char* fileName);
    void setupBuffers(const std::vector<GLfloat>& _vertices, const std::vector<GLuint>& _indices);
    void setupShader();

    void transform();


public:
    TexturedRectangle(const char* fileName, const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
    void draw();
};


#endif //PACMAN_TEXTUREDRECTANGLE_HPP
