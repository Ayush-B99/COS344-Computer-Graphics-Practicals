#ifndef LAYOUTMANAGER_HPP
#define LAYOUTMANAGER_HPP

#include <vector>
#include <string>
#include <glm/glm.hpp>

using namespace glm;

class GameObject;

class LayoutManager
{
private:
    struct ObjectData
    {
        std::string type;
        float posX, posY;
        float rotation;
        float scale;
        float colorR, colorG, colorB;
    };
    
public:
    static bool saveLayout(const std::string& filename, const std::vector<GameObject*>& obj);
    static bool loadLayout(const std::string& filename, std::vector<GameObject*>& obj);
    
};

#endif