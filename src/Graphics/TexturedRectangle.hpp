//
// Created by csong on 4/7/2023.
//

#ifndef PACMAN_TEXTUREDRECTANGLE_HPP
#define PACMAN_TEXTUREDRECTANGLE_HPP


#include <vector>
#include "glad/glad.h"
#include "shader.h"
#include "Widget.hpp"

class TexturedRectangle : public Widget {
private:
    unsigned int VAO{}, VBO{}, EBO{}, texture{};
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    Shader *shader{};
    glm::mat4 trans = glm::mat4(1.0f);

    void setupTexture(const char *fileName);
    void setupBuffers();
    void setupShader();

    void setupTransform();

public:
    static std::vector<GLfloat> defaultVertices;
    static std::vector<GLuint> defaultIndices;

    TexturedRectangle(Menu *m, const char *fileName, const std::vector<GLfloat> &_vertices,
                      const std::vector<GLuint> &_indices, glm::mat4 _trans);

    void draw() override;
};


#endif //PACMAN_TEXTUREDRECTANGLE_HPP
