#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "Shape.hpp"

// inheritance from shape class

class Rectangle : public Shape
{
private:
    float width, height;
    vec3 color;

public:
    Rectangle(float width, float height, const vec3& color);
    void generateVertices();
};

class Triangle : public Shape
{
private:
    float size;
    vec3 color;

public:
    Triangle(float size, const vec3& color);
    void generateVertices();
};

class Circle : public Shape
{
private:
    float radius;
    int segments;
    vec3 color;
    
public:
    Circle(float radius, int segments, const vec3& color);
    void generateVertices();
};

#endif