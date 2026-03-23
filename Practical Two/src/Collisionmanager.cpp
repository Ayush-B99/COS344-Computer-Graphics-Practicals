#include "CollisionManager.hpp"
#include "Gameobject.hpp"
#include <cmath>
#include <iostream>

static float calculateDistance(const vec3& p1, const vec3& p2)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float dz = p2.z - p1.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

bool CollisionManager::checkCollision(const vec3& newPosition, float objRadius, const std::vector<GameObject*>& gameObj, int excludeIndex)
{
    // Check collision with all obstacles
    for (int i = 0; i < gameObj.size(); i++)
    {
        if (i == excludeIndex || i < 4) 
            continue;
        
        GameObject* obstacle = gameObj[i];
        vec3 obstaclePos = obstacle->getPosition();
        
        float obstacleRadius = getCollisionRadius(i, gameObj);
        
        float distance = calculateDistance(vec3(newPosition.x, newPosition.y, 0),
                                           vec3(obstaclePos.x, obstaclePos.y, 0));
        
        // Check if collision occurs
        float minDistance = objRadius + obstacleRadius;
        
        if (distance < minDistance)
        {
            std::cout << "Collision with obstacle " << i 
                      << " (distance: " << distance << ", min: " << minDistance << ")" << std::endl;
            return true; 
        }
    }
    
    return false; 
}

float CollisionManager::getCollisionRadius(int objIndex, const std::vector<GameObject*>& gameObj)
{
    
    if (objIndex < 4)
        return 0.0f; 
    
    // gb
    if (objIndex == 8) 
        return 0.05f;
    
    // gh
    if (objIndex == 7) 
        return 0.08f;
    
    // obstacles
    if (objIndex >= 4 && objIndex <= 6) 
        return 0.12f;
    
    // borders
    if (objIndex >= 9) 
        return 0.10f;
    
    return 0.1f; 
}
