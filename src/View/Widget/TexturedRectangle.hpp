//
// Created by laccs on 4/7/2023.
//

#ifndef PACMAN_TEXTUREDRECTANGLE_HPP
#define PACMAN_TEXTUREDRECTANGLE_HPP


#include <vector>
#include "glad/glad.h"
#include "../shader.h"
#include "Widget.hpp"

/**
 * This class represent a Widget which has a rectangular form and also has a texture attached to it. It could be
 * derived from a Rectangle class, but since it would not have been used in this project it is inheriting from Widget.
 */
class TexturedRectangle : public Widget {
private:
    // OpenGL related variables
    unsigned int VAO{}, VBO{}, EBO{}, texture{};
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    Shader *shader{};
    glm::mat4 trans = glm::mat4(1.0f);

    // Initialize the texture, buffers and shader
    void setupTexture(const char *fileName);

    void setupBuffers();

    void setupShader();

    // Set the transformation matrix
    void setupTransform();

public:
    /**
     * Default vertices and indices are defined since they are the same for all TexturedRectangles. Meaning that
     * everything is drawn in the same way, but with different transformations.
     */
    static std::vector<GLfloat> defaultVertices;
    static std::vector<GLuint> defaultIndices;

    // Constructor, which takes a Menu pointer, a file name, vertices, indices and a transformation matrix
    TexturedRectangle(Menu *m, const std::string &fileName, const std::vector<GLfloat> &_vertices,
                      const std::vector<GLuint> &_indices, glm::mat4 _trans);

    // Override the draw function
    void draw() override;

    // Set the transformation matrix
    void setTrans(const glm::mat4 &_trans);
};


#endif //PACMAN_TEXTUREDRECTANGLE_HPP
