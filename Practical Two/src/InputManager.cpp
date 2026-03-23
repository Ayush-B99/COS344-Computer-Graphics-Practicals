#include "InputManager.hpp"
#include "Gameobject.hpp"
#include <cmath>
#include <iostream>

std::vector<GameObject*>* InputManager::gameObjects = nullptr;
int InputManager::windowWidth = 1000;
int InputManager::windowHeight = 1000;

void InputManager::setGameObjects(std::vector<GameObject*>* objects)
{
    gameObjects = objects;
}

void InputManager::setWindowSize(int width, int height)
{
    windowWidth = width;
    windowHeight = height;
}

vec3 InputManager::screenToWorld(float screenX, float screenY)
{
    // Convert screen coords to OpenGL coords
    float x = (screenX / windowWidth) * 2.0f - 1.0f;
    // Flip Y
    float y = -((screenY / windowHeight) * 2.0f - 1.0f); 
    
    // Scale 
    x = x * 1.0f;  
    y = y * 0.75f; 
    
    return vec3(x, y, 0.0f);
}

static float calculateDistance(const vec3& p1, const vec3& p2)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float dz = p2.z - p1.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

int InputManager::getSelectedObjectAtMouse(float mouseX, float mouseY)
{
    if (!gameObjects)
        return -1;
    
    vec3 worldPos = screenToWorld(mouseX, mouseY);
    
    // Check collision with all objects 
    for (int i = gameObjects->size() - 1; i >= 0; i--)
    {
        GameObject* obj = (*gameObjects)[i];
        vec3 objPos = obj->getPosition();
        
        float clickRadius = 0.15f;
        
        float distance = calculateDistance(vec3(worldPos.x, worldPos.y, 0), 
                                           vec3(objPos.x, objPos.y, 0));
        
        if (distance < clickRadius)
        {
            // just prints in terminal to see if it wurk
            std::cout << "Clicked on object at index " << i << std::endl;
            return i;
        }
    }
    
    return -1;
}