#include "ScreenshotManager.hpp"
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

bool ScreenshotManager::takeScreenshot(const std::string& filename, int width, int height)
{
    std::vector<unsigned char> pixels(width * height * 3);
    
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
    
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error reading pixels womp womp: " << err << std::endl;
        return false;
    }
    
    std::vector<unsigned char> flipped(width * height * 3);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int src = ((height - 1 - y) * width + x) * 3;
            int dst = (y * width + x) * 3;
            flipped[dst] = pixels[src];         
            flipped[dst + 1] = pixels[src + 1];
            flipped[dst + 2] = pixels[src + 2];
        }
    }
    
    // Save as PPM file 
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file for screenshot: " << filename << std::endl;
        return false;
    }
    
    file << "P6\n";
    file << width << " " << height << "\n";
    file << "255\n";
    
    file.write(reinterpret_cast<char*>(flipped.data()), flipped.size());
    
    file.close();
    std::cout << "Screenshot saved to " << filename << std::endl;
    return true;
}