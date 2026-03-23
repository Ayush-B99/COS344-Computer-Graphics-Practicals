#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "Gameobject.hpp"
#include "Shapes.hpp"
#include "LayoutManager.hpp"
#include "ScreenshotManager.hpp"
#include "InputManager.hpp"

using namespace glm;
using namespace std;

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;

vector<GameObject*> gameObjects;
vector<int> selectedObjects;
int selectedGolfBall = -1;
int selectedObstacle1 = -1;
int selectedObstacle2 = -1;
int selectedGolfHole = -1;
bool wireframeMode = false;
double lastWireframeToggleTime = 0;
double lastSaveLoadTime = 0;
double lastScreenshotTime = 0;

mat4 createOrthoMatrix(float left, float right, float bottom, float top, float near, float far)
{
    mat4 result = mat4(1.0f);
    
    result[0][0] = 2.0f / (right - left);
    result[1][1] = 2.0f / (top - bottom);
    result[2][2] = -2.0f / (far - near);
    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][2] = -(far + near) / (far - near);
    result[3][3] = 1.0f;
    
    return result;
}

float manualClamp(float value, float minVal, float maxVal)
{
    if (value < minVal) 
    {
        return minVal;
    }

    if (value > maxVal) 
    {
        return maxVal;
    }

    return value;
}

// all the time error error error
const char *getError()
{
    const char *errorDescription;
    glfwGetError(&errorDescription);
    return errorDescription;
}

inline void startUpGLFW()
{
    glewExperimental = true;

    if (!glfwInit())
    {
        throw getError();
    }
}

inline void startUpGLEW()
{
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        throw getError();
    }
}

inline GLFWwindow *setUp()
{
    startUpGLFW();
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "u23596351", NULL, NULL);
    if (window == NULL)
    {
        cout << getError() << endl;
        glfwTerminate();
        throw "Failed to open window\n";
    }
    glfwMakeContextCurrent(window);
    startUpGLEW();
    
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    
    return window;
}

// trackpad click 
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        // Gets cursor position
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        
        // Get the object @ mouse position
        int clickedIndex = InputManager::getSelectedObjectAtMouse((float)xpos, (float)ypos);
        
        // Check if Shift is held
        bool shiftHeld = (mods & GLFW_MOD_SHIFT) != 0;
        
        if (clickedIndex >= 0)
        {
            if (shiftHeld)
            {
                // add to selection (multi-select) to move mult. obj etc....
                bool alreadySelected = false;
                for (int idx : selectedObjects)
                {
                    if (idx == clickedIndex)
                    {
                        alreadySelected = true;
                        break;
                    }
                }
                
                if (!alreadySelected)
                {
                    gameObjects[clickedIndex]->select();
                    selectedObjects.push_back(clickedIndex);
                    cout << "Added object " << clickedIndex << " to selection (now " 
                         << selectedObjects.size() << " selected)" << endl;
                }
                else
                {
                    // Remove from selection if already selected
                    gameObjects[clickedIndex]->deselect();
                    auto it = find(selectedObjects.begin(), selectedObjects.end(), clickedIndex);
                    if (it != selectedObjects.end())
                        selectedObjects.erase(it);
                    cout << "Removed object " << clickedIndex << " from selection (now " 
                         << selectedObjects.size() << " selected)" << endl;
                }
            }

            else
            {
                // replace selection for single select
                for (auto idx : selectedObjects)
                    if (idx >= 0) gameObjects[idx]->deselect();
                selectedObjects.clear();
                
                gameObjects[clickedIndex]->select();
                selectedObjects.push_back(clickedIndex);
                
                cout << "Selected object " << clickedIndex << " (single select)" << endl;
            }
        }

        else
        {
            // Deslecect if clicking on empty space
            if (!shiftHeld)
            {
                for (auto idx : selectedObjects)
                    if (idx >= 0) 
                        gameObjects[idx]->deselect();
                selectedObjects.clear();
                
                cout << "Deselected all objects" << endl;
            }
        }
    }
}

void createScene()
{
    
    // Floor 
    Rectangle* floor = new Rectangle(1.6f, 1.2f, vec3(0.7f, 0.7f, 0.7f));
    GameObject* floorObj = new GameObject(floor, vec3(0.0f, 0.0f, 0.0f));
    floorObj->setOriginalColor(vec3(0.7f, 0.7f, 0.7f));
    gameObjects.push_back(floorObj);
    
    // Grass
    Rectangle* grass = new Rectangle(1.5f, 1.1f, vec3(0.2f, 0.8f, 0.2f));
    GameObject* grassObj = new GameObject(grass, vec3(0.0f, 0.0f, 0.01f));
    grassObj->setOriginalColor(vec3(0.2f, 0.8f, 0.2f));
    gameObjects.push_back(grassObj);
    
    // starting place (gf should be ontop of this)
    Rectangle* startPoint = new Rectangle(0.1f, 0.1f, vec3(0.6f, 0.1f, 0.1f));
    GameObject* startObj = new GameObject(startPoint, vec3(-0.65f, 0.0f, 0.02f));
    startObj->setOriginalColor(vec3(0.6f, 0.1f, 0.1f));
    gameObjects.push_back(startObj);
    
    // Gf
    Circle* golfBall = new Circle(0.04f, 8, vec3(1.0f, 1.0f, 1.0f));
    GameObject* ballObj = new GameObject(golfBall, vec3(-0.65f, 0.0f, 0.03f));
    ballObj->setOriginalColor(vec3(1.0f, 1.0f, 1.0f));
    gameObjects.push_back(ballObj);
    selectedGolfBall = gameObjects.size() - 1;
    
    //river
    Rectangle* river = new Rectangle(1.2f, 0.08f, vec3(0.1f, 0.4f, 0.8f));
    GameObject* riverObj = new GameObject(river, vec3(0.0f, 0.0f, 0.02f));
    riverObj->setOriginalColor(vec3(0.1f, 0.4f, 0.8f));
    gameObjects.push_back(riverObj);
    
    // rectangles
    Rectangle* obstacle1a = new Rectangle(0.15f, 0.1f, vec3(0.7f, 0.5f, 0.2f));
    GameObject* obs1aObj = new GameObject(obstacle1a, vec3(-0.35f, 0.35f, 0.02f));
    obs1aObj->setOriginalColor(vec3(0.7f, 0.5f, 0.2f));
    gameObjects.push_back(obs1aObj);
    selectedObstacle1 = gameObjects.size() - 1;
    
    Rectangle* obstacle1b = new Rectangle(0.15f, 0.1f, vec3(0.7f, 0.5f, 0.2f));
    GameObject* obs1bObj = new GameObject(obstacle1b, vec3(0.35f, -0.35f, 0.02f));
    obs1bObj->setOriginalColor(vec3(0.7f, 0.5f, 0.2f));
    gameObjects.push_back(obs1bObj);
    
    // triangles
    Triangle* obstacle2a = new Triangle(0.15f, vec3(0.85f, 0.15f, 0.15f));
    GameObject* obs2aObj = new GameObject(obstacle2a, vec3(0.0f, 0.48f, 0.02f));
    obs2aObj->setOriginalColor(vec3(0.85f, 0.15f, 0.15f));
    gameObjects.push_back(obs2aObj);
    selectedObstacle2 = gameObjects.size() - 1;
    
    Triangle* obstacle2b = new Triangle(0.15f, vec3(0.85f, 0.15f, 0.15f));
    GameObject* obs2bObj = new GameObject(obstacle2b, vec3(0.0f, -0.48f, 0.02f));
    obs2bObj->setOriginalColor(vec3(0.85f, 0.15f, 0.15f));
    gameObjects.push_back(obs2bObj);
    
    // curcles
    Circle* obstacle3a = new Circle(0.07f, 8, vec3(0.1f, 0.6f, 0.6f));
    GameObject* obs3aObj = new GameObject(obstacle3a, vec3(-0.2f, 0.35f, 0.02f));
    obs3aObj->setOriginalColor(vec3(0.1f, 0.6f, 0.6f));
    gameObjects.push_back(obs3aObj);

    Circle* obstacle3b = new Circle(0.07f, 8, vec3(0.1f, 0.6f, 0.6f));
    GameObject* obs3bObj = new GameObject(obstacle3b, vec3(0.2f, -0.35f, 0.02f));
    obs3bObj->setOriginalColor(vec3(0.1f, 0.6f, 0.6f));
    gameObjects.push_back(obs3bObj);
    
    Circle* golfHole = new Circle(0.07f, 60, vec3(0.9f, 0.4f, 0.6f));
    GameObject* holeObj = new GameObject(golfHole, vec3(0.65f, 0.0f, 0.02f));
    holeObj->setOriginalColor(vec3(0.9f, 0.4f, 0.6f));
    gameObjects.push_back(holeObj);
    selectedGolfHole = gameObjects.size() - 1;
    
    // tha brown borders
    Rectangle* borderTop = new Rectangle(1.5f, 0.05f, vec3(0.4f, 0.25f, 0.0f));
    GameObject* borderTopObj = new GameObject(borderTop, vec3(0.0f, 0.6f, 0.015f));
    borderTopObj->setOriginalColor(vec3(0.4f, 0.25f, 0.0f));
    gameObjects.push_back(borderTopObj);
    
    Rectangle* borderBottom = new Rectangle(1.5f, 0.05f, vec3(0.4f, 0.25f, 0.0f));
    GameObject* borderBottomObj = new GameObject(borderBottom, vec3(0.0f, -0.6f, 0.015f));
    borderBottomObj->setOriginalColor(vec3(0.4f, 0.25f, 0.0f));
    gameObjects.push_back(borderBottomObj);
    
    Rectangle* borderLeft = new Rectangle(0.05f, 1.1f, vec3(0.4f, 0.25f, 0.0f));
    GameObject* borderLeftObj = new GameObject(borderLeft, vec3(-0.775f, 0.0f, 0.015f));
    borderLeftObj->setOriginalColor(vec3(0.4f, 0.25f, 0.0f));
    gameObjects.push_back(borderLeftObj);
    
    Rectangle* borderRight = new Rectangle(0.05f, 1.1f, vec3(0.4f, 0.25f, 0.0f));
    GameObject* borderRightObj = new GameObject(borderRight, vec3(0.775f, 0.0f, 0.015f));
    borderRightObj->setOriginalColor(vec3(0.4f, 0.25f, 0.0f));
    gameObjects.push_back(borderRightObj);
}

void clearSelection()
{
    for (auto idx : selectedObjects)
        if (idx >= 0) gameObjects[idx]->deselect();
    selectedObjects.clear();
}

void handleInput(GLFWwindow* window)
{
    double currentTime = glfwGetTime();
    
    // Selection keys 
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        clearSelection();
        if (selectedGolfBall >= 0)
        {
            gameObjects[selectedGolfBall]->select();
            selectedObjects.push_back(selectedGolfBall);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        clearSelection();
        if (selectedObstacle1 >= 0)
        {
            gameObjects[selectedObstacle1]->select();
            selectedObjects.push_back(selectedObstacle1);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        clearSelection();
        if (selectedObstacle2 >= 0)
        {
            gameObjects[selectedObstacle2]->select();
            selectedObjects.push_back(selectedObstacle2);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        clearSelection();
        if (selectedGolfHole >= 0)
        {
            gameObjects[selectedGolfHole]->select();
            selectedObjects.push_back(selectedGolfHole);
        }
    }
    
    // Deselect key 0
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        clearSelection();
    }
    
    // Apply transformations to all selected objects
    if (!selectedObjects.empty())
    {
        float moveSpeed = 0.02f;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            for (auto idx : selectedObjects) gameObjects[idx]->translate(vec3(0.0f, moveSpeed, 0.0f));

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            for (auto idx : selectedObjects) gameObjects[idx]->translate(vec3(0.0f, -moveSpeed, 0.0f));

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            for (auto idx : selectedObjects) gameObjects[idx]->translate(vec3(-moveSpeed, 0.0f, 0.0f));

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            for (auto idx : selectedObjects) gameObjects[idx]->translate(vec3(moveSpeed, 0.0f, 0.0f));
        
        // Scaling
        if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
            for (auto idx : selectedObjects) gameObjects[idx]->scale(1.02f);
        if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
            for (auto idx : selectedObjects) gameObjects[idx]->scale(0.98f);
        
        // Rotation
        float rotSpeed = 0.05f;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            for (auto idx : selectedObjects) gameObjects[idx]->rotate(rotSpeed);
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            for (auto idx : selectedObjects) gameObjects[idx]->rotate(-rotSpeed);
    }
    
    // Wireframe toggle
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && currentTime - lastWireframeToggleTime > 0.3)
    {
        wireframeMode = !wireframeMode;
        lastWireframeToggleTime = currentTime;
    }
    
    // Save layout (Ctrl+S)
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && 
        glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS &&
        currentTime - lastSaveLoadTime > 0.5)
    {
        LayoutManager::saveLayout("layout.txt", gameObjects);
        lastSaveLoadTime = currentTime;
    }
    
    // Load layout (Ctrl+L)
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && 
        glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS &&
        currentTime - lastSaveLoadTime > 0.5)
    {
        LayoutManager::loadLayout("layout.txt", gameObjects);
        lastSaveLoadTime = currentTime;
    }
    
    // Screenshot (P key)
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && currentTime - lastScreenshotTime > 0.5)
    {
        time_t now = time(0);
        struct tm* timeinfo = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "screenshot_%Y%m%d_%H%M%S.ppm", timeinfo);
        
        ScreenshotManager::takeScreenshot(buffer, WINDOW_WIDTH, WINDOW_HEIGHT);
        lastScreenshotTime = currentTime;
    }
}

int main()
{
    GLFWwindow *window;
    try
    {
        window = setUp();
    }
    catch (const char *e)
    {
        cout << e << endl;
        return 1;
    }
    
    // Load shaders
    GLuint shaderProgram = LoadShaders("vertex.glsl", "fragment.glsl");
    glUseProgram(shaderProgram);
    
    mat4 projection = createOrthoMatrix(-1.0f, 1.0f, -0.75f, 0.75f, -1.0f, 1.0f);
    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);
    
    createScene();
    
    // Setup input manager geet geet
    InputManager::setGameObjects(&gameObjects);
    InputManager::setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // Set trackpad  gget get
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    
    cout << "\n=== GOLF COURSE CONTROLS ===" << endl;
    cout << "KEYBOARD:" << endl;
    cout << "1/2/3/4 - Select objects" << endl;
    cout << "0 - Deselect" << endl;
    cout << "W/A/S/D - Move" << endl;
    cout << "+/- - Scale" << endl;
    cout << "E/Q - Rotate" << endl;
    cout << "Enter - Wireframe toggle" << endl;
    cout << "Ctrl+S - Save layout" << endl;
    cout << "Ctrl+L - Load layout" << endl;
    cout << "P - Take screenshot" << endl;
    cout << "\nMOUSE:" << endl;
    cout << "Left Click - Select object" << endl;
    cout << "Shift+Click - Add to selection (multi-select)" << endl;
    cout << "note hold shift and click on objects to get multiple";
    
    while (!glfwWindowShouldClose(window))
    {
        handleInput(window);
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        for (auto obj : gameObjects)
        {
            obj->render(shaderProgram, wireframeMode);
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    for (auto obj : gameObjects)
        delete obj;
    
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}