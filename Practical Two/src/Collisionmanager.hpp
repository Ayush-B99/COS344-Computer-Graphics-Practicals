#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include <glm/glm.hpp>
#include <vector>
using namespace glm;

class GameObject;

class CollisionManager
{
public:
    // Check if moving object would collide with obstacles
    static bool checkCollision(const vec3& newPosition, float objRadius, const std::vector<GameObject*>& gameObj,int excludeIndex = -1);
    
    // Get collision radius for each object
    static float getCollisionRadius(int objIndex, const std::vector<GameObject*>& gameObj);
};

#endif
