#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include <glm/glm.hpp>

using namespace glm;

class Shape
{
protected:
    void addVertex(float x, float y, const vec3& color);
    
public:
    Shape();
    virtual ~Shape();
    
    virtual void generateVertices() = 0;
    void setupBuffers();
    void render(bool wireframe = false);
    void renderWireframe();
    
    std::vector<vec3> vertices;
    std::vector<vec3> colors;
    unsigned int VAO, VBO, colorVBO;
    int vertexCount;
    
};

#endif