#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <glm/glm.hpp>
#include <vector>

using namespace glm;

class GameObject;

class InputManager
{
private:
    static std::vector<GameObject*>* gameObjects;
    static int windowWidth;
    static int windowHeight;
    
public:
    static void setGameObjects(std::vector<GameObject*>* objects);
    static void setWindowSize(int width, int height);
    static int getSelectedObjectAtMouse(float mouseX, float mouseY);
    static vec3 screenToWorld(float screenX, float screenY);
};

#endif