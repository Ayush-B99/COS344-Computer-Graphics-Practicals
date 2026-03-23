#ifndef SCREENSHOTMANAGER_HPP
#define SCREENSHOTMANAGER_HPP

#include <string>

class ScreenshotManager
{
public:
    static bool takeScreenshot(const std::string& filename, int width, int height);
};

#endif