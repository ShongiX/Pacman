//
// Created by csong on 4/7/2023.
//

#include <string>
#include "TexturedRectangle.hpp"
#include "stb_image.h"
#include "iostream"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Menu.hpp"

std::vector<GLfloat> TexturedRectangle::defaultVertices = {
        // positions          // colors           // texture coords
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
        1.0f, -1.0, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom right
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom left
        -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // top left
};
std::vector<GLuint> TexturedRectangle::defaultIndices = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
};

TexturedRectangle::TexturedRectangle(Menu* m, const char* fileName, const std::vector<GLfloat>& _vertices, const std::vector<GLuint>& _indices, glm::mat4 _trans) {
    this->m = m;
    m->addWidget(this);
    this->vertices = _vertices;
    this->indices = _indices;
    this->trans = _trans;

    setupTexture(fileName);
    setupBuffers();
    setupShader();
    setupTransform();
}

void TexturedRectangle::setupTexture(const char* fileName) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void TexturedRectangle::setupBuffers() {
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    // ..:: Initialization code :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
    // 4. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // 5. unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TexturedRectangle::setupShader() {
    shader = new Shader("../shaders/vertexShader.vert", "../shaders/fragmentShader.frag");
}

void TexturedRectangle::setupTransform() {
    unsigned int transformLoc = glGetUniformLocation(shader->ID, "setupTransform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

void TexturedRectangle::draw() {
    shader->use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    shader->setMat4("transform",trans);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void TexturedRectangle::setTrans(const glm::mat4 &trans) {
    TexturedRectangle::trans = trans;
}


