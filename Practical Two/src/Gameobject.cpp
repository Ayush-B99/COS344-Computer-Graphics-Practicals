#include "Gameobject.hpp"
#include <GL/glew.h>
#include <cmath>

GameObject::GameObject(Shape* shape, const vec3& position) : shape(shape), position(position), rotation(0.0f), scaling(1.0f), selected(false)
{
    originalColor = vec3(0.5f, 0.5f, 0.5f);
}

GameObject::~GameObject() {
    delete shape;
}

mat4 GameObject::getTransformMatrix() const {
    // scaling matrix
    mat4 scaleMatrix = mat4(1.0f);
    scaleMatrix[0][0] = scaling;
    scaleMatrix[1][1] = scaling;
    scaleMatrix[2][2] = 1.0f;
    scaleMatrix[3][3] = 1.0f;
    
    // rotation matrix
    float cosR = cos(rotation);
    float sinR = sin(rotation);
    mat4 rotMatrix = mat4(1.0f);
    rotMatrix[0][0] = cosR;
    rotMatrix[0][1] = -sinR;
    rotMatrix[1][0] = sinR;
    rotMatrix[1][1] = cosR;
    rotMatrix[2][2] = 1.0f;
    rotMatrix[3][3] = 1.0f;
    
    // translation matrix
    mat4 transMatrix = mat4(1.0f);
    transMatrix[3][0] = position.x;
    transMatrix[3][1] = position.y;
    transMatrix[3][2] = position.z;
    transMatrix[3][3] = 1.0f;
    
    // combine matrices
    mat4 result = transMatrix * rotMatrix * scaleMatrix;
    
    return result;
}

vec3 GameObject::getPastelColor() const
{
    // Convert to pastel by mixing with white
    return originalColor * 0.5f + vec3(1.0f) * 0.5f;
}

void GameObject::translate(const vec3& offset, bool checkCollision, 
                          const std::vector<GameObject*>* gameObjects, int selfIndex) {
    vec3 newPos = position + offset;
    
    if (newPos.x < -1.0f) newPos.x = -1.0f;
    if (newPos.x > 1.0f) newPos.x = 1.0f;
    if (newPos.y < -0.75f) newPos.y = -0.75f;
    if (newPos.y > 0.75f) newPos.y = 0.75f;
    
    if (checkCollision && gameObjects != nullptr)
    {
        if (CollisionManager::checkCollision(newPos, 0.05f, *gameObjects, selfIndex))
        {
            return; // Don't move if collision detected
        }
    }
    
    position = newPos;
}

void GameObject::scale(float factor) {
    scaling *= factor;

    if (scaling < 0.1f) scaling = 0.1f;
    if (scaling > 5.0f) scaling = 5.0f;
}

void GameObject::rotate(float angle) {
    rotation += angle;
}

void GameObject::select() {
    selected = true;
}

void GameObject::deselect() {
    selected = false;
}

void GameObject::render(unsigned int shaderProgram, bool wireframe) {
    mat4 transform = getTransformMatrix();
    GLint transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
    
    // Set color when selecting obj
    GLint colorLoc = glGetUniformLocation(shaderProgram, "objectColor");
    vec3 renderColor = selected ? getPastelColor() : originalColor;
    glUniform3f(colorLoc, renderColor.x, renderColor.y, renderColor.z);
    
    shape->render(wireframe);
}