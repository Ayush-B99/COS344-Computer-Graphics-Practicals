#include "Shapes.hpp"
#include <cmath>

Rectangle::Rectangle(float width, float height, const vec3& color)
    : width(width), height(height), color(color)
{
    generateVertices();
    setupBuffers();
}

void Rectangle::generateVertices()
{
    float hw = width / 2.0f;
    float hh = height / 2.0f;
    
    addVertex(-hw, -hh, color);
    addVertex(hw, -hh, color);
    addVertex(hw, hh, color);
    
     addVertex(-hw, -hh, color);
    addVertex(hw, hh, color);
    addVertex(-hw, hh, color);
}

Triangle::Triangle(float size, const vec3& color)
    : size(size), color(color)
{
    generateVertices();
    setupBuffers();
}

void Triangle::generateVertices()
{
    // height of triangle
    float h = size * 0.866f;
    
    // top v
    addVertex(0.0f, h / 2.0f, color);  
    // bottom left v         
    addVertex(-size / 2.0f, -h / 2.0f, color); 
    // bottom right v
    addVertex(size / 2.0f, -h / 2.0f, color);  
}

Circle::Circle(float radius, int segments, const vec3& color)
    : radius(radius), segments(segments), color(color)
{
    generateVertices();
    setupBuffers();
}

void Circle::generateVertices()
{
    float angle = 2.0f * 3.14159265f / segments;
    
    for (int i = 0; i < segments; i++)
    {
        float theta1 = angle * i;
        float theta2 = angle * (i + 1);
        
        float x1 = radius * cos(theta1);
        float y1 = radius * sin(theta1);
        float x2 = radius * cos(theta2);
        float y2 = radius * sin(theta2);
        
        // Center
        addVertex(0.0f, 0.0f, color);
        addVertex(x1, y1, color);
        addVertex(x2, y2, color);
    }
}