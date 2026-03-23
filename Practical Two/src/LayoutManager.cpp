#include "LayoutManager.hpp"
#include "Gameobject.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

bool LayoutManager::saveLayout(const std::string& filename, const std::vector<GameObject*>& obj)
{
    std::ofstream file(filename);
    
    if (!file.is_open())
    {
        std::cerr << "Failed to open file loser: " << filename << std::endl;
        return false;
    }
    
    file << obj.size() << "\n";
    
    for (const auto& obj : obj)
    {
        vec3 pos = obj->getPosition();
        file << pos.x << " " << pos.y << " ";
        file << obj->getRotation() << " ";
        file << obj->getScale() << " ";
        
        vec3 color = obj->getOriginalColor();
        file << color.x << " " << color.y << " " << color.z << "\n";
    }
    
    file.close();
    std::cout << "Layout saved to " << filename << std::endl;
    return true;
}

bool LayoutManager::loadLayout(const std::string& filename, std::vector<GameObject*>& obj)
{
    std::ifstream file(filename);
    
    if (!file.is_open())
    {
        std::cerr << "Failed to open file for loading: " << filename << std::endl;
        return false;
    }
    
    int count;
    file >> count;
    
    if (count != obj.size())
    {
        std::cerr << "Object count incorrect, wanted " << obj.size() << " but file has " << count << std::endl;
        file.close();
        return false;
    }
    
    for (int i = 0; i < count; i++)
    {
        float x, y, rot, scale, r, g, b;
        file >> x >> y >> rot >> scale >> r >> g >> b;
        
        obj[i]->setPosition(vec3(x, y, 0.0f));
        obj[i]->setRotation(rot);
        obj[i]->setScale(scale);
    }
    
    file.close();
    std::cout << "Layout loaded from " << filename << std::endl;
    return true;
}