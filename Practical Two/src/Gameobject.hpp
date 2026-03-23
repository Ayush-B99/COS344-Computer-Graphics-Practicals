#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Shape.hpp"
#include "CollisionManager.hpp"
#include <glm/glm.hpp>
#include <vector>

using namespace glm;

class GameObject
{
private:
    Shape* shape;
    vec3 position;
    float rotation;
    float scaling;
    bool selected;
    vec3 originalColor;
    
    mat4 getTransformMatrix() const;
    vec3 getPastelColor() const;

public:
    GameObject(Shape* shape, const vec3& position = vec3(0, 0, 0));
    ~GameObject();
    
    void render(unsigned int shaderProgram, bool wireframe = false);
    void select();
    void deselect();
    bool isSelected() const { return selected; }
    
    // Transformations - with collision detection support
    void translate(const vec3& offset, bool checkCollision = false,
                  const std::vector<GameObject*>* gameObjects = nullptr, int selfIndex = -1);
    void scale(float factor);
    void rotate(float angle);
    
    // Getters/Setters
    vec3 getPosition() const { 
        return position; 
    }

    void setPosition(const vec3& pos) { 
        position = pos; 
    }

    float getRotation() const { 
        return rotation; 
    }

    float getScale() const { 
        return scaling; 
    }

    vec3 getOriginalColor() const { 
        return originalColor; 
    }

    void setOriginalColor(const vec3& color) { 
        originalColor = color; 
    }

    // Bonus mark save/load
    void setRotation(float r) { 
        rotation = r; 
    }

    void setScale(float s) { 
        scaling = s; 
    }

};

#endif