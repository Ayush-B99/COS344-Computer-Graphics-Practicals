#include "shape.hpp"
#include <GL/glew.h>
#include <cmath>

Shape::Shape() : VAO(0), VBO(0), colorVBO(0), vertexCount(0) {}

Shape::~Shape()
{
    if (VAO != 0)
        glDeleteVertexArrays(1, &VAO);
    if (VBO != 0)
        glDeleteBuffers(1, &VBO);
    if (colorVBO != 0)
        glDeleteBuffers(1, &colorVBO);
}

void Shape::addVertex(float x, float y, const vec3& color)
{
    vertices.push_back(vec3(x, y, 0.0f));
    colors.push_back(color);
}

void Shape::setupBuffers()
{
    vertexCount = vertices.size();
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &colorVBO);
    
    glBindVertexArray(VAO);
    
    // Position buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(vec3), colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Shape::render(bool wireframe)
{
    if (wireframe)
        renderWireframe();
    else
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        glBindVertexArray(0);
    }
}

void Shape::renderWireframe()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
    glBindVertexArray(0);
}