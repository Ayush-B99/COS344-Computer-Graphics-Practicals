#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.hpp"
#include "Matrix.hpp"
#include "Scene.hpp"

using namespace std;

const char *getError()
{
    const char *errorDescription;
    glfwGetError(&errorDescription);
    return errorDescription;
}

inline void startUpGLFW()
{
    glewExperimental = true; // Needed for core profile
    if (!glfwInit())
    {
        throw getError();
    }
}

inline void startUpGLEW()
{
    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        throw getError();
    }
}

inline GLFWwindow *setUp()
{
    startUpGLFW();
    glfwWindowHint(GLFW_SAMPLES, 4);               // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
    GLFWwindow *window;                                            // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow(1000, 1000, "u23596351", NULL, NULL);
    if (window == NULL)
    {
        cout << getError() << endl;
        glfwTerminate();
        throw "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n";
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    startUpGLEW();
    return window;
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
        throw;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLuint programID = LoadShaders("Vertex.glsl", "fragment.glsl");

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    vector<float> triVertices;
    vector<float> lineVertices;
    vector<float> rotorTriVertices;
    vector<float> rotorLineVertices;

    buildScene(triVertices, lineVertices);
    buildRotor(rotorTriVertices, rotorLineVertices);

    GLuint sceneTriVAO, sceneTriVBO;
    GLuint sceneLineVAO, sceneLineVBO;
    GLuint rotorTriVAO, rotorTriVBO;
    GLuint rotorLineVAO, rotorLineVBO;

    glGenVertexArrays(1, &sceneTriVAO);
    glGenBuffers(1, &sceneTriVBO);
    glBindVertexArray(sceneTriVAO);
    glBindBuffer(GL_ARRAY_BUFFER, sceneTriVBO);
    glBufferData(GL_ARRAY_BUFFER, triVertices.size() * sizeof(float), &triVertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &sceneLineVAO);
    glGenBuffers(1, &sceneLineVBO);
    glBindVertexArray(sceneLineVAO);
    glBindBuffer(GL_ARRAY_BUFFER, sceneLineVBO);
    glBufferData(GL_ARRAY_BUFFER, lineVertices.size() * sizeof(float), &lineVertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &rotorTriVAO);
    glGenBuffers(1, &rotorTriVBO);
    glBindVertexArray(rotorTriVAO);
    glBindBuffer(GL_ARRAY_BUFFER, rotorTriVBO);
    glBufferData(GL_ARRAY_BUFFER, rotorTriVertices.size() * sizeof(float), &rotorTriVertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &rotorLineVAO);
    glGenBuffers(1, &rotorLineVBO);
    glBindVertexArray(rotorLineVAO);
    glBindBuffer(GL_ARRAY_BUFFER, rotorLineVBO);
    glBufferData(GL_ARRAY_BUFFER, rotorLineVertices.size() * sizeof(float), &rotorLineVertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    Mat4 projection = mat4Perspective(45.0f * 3.14159265f / 180.0f, 1.0f, 0.1f, 100.0f);
    Mat4 view = mat4LookAt(0.0f, 4.0f, 14.0f,
                           0.0f, 0.0f, 0.0f,
                           0.0f, 1.0f, 0.0f);

    float rotX = 0.0f;
    float rotY = 0.0f;
    float rotZ = 0.0f;

    float posX = 0.0f;
    float posY = 0.0f;
    float posZ = 0.0f;

    float rotorAngle = 0.0f;
    float rotorSpeed = 0.0f;

    bool wireframe = false;
    bool enterPressedLast = false;

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        glfwPollEvents();

        const float rotStep = 0.03f;
        const float moveStep = 0.05f;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
            rotX += rotStep;

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
            rotX -= rotStep;

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
            rotY += rotStep;

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
            rotY -= rotStep;

        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) 
            rotZ += rotStep;

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) 
            rotZ -= rotStep;

        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) posY += 
            moveStep;

        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) posY -= 
            moveStep;

        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) posX += 
            moveStep;

        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) posX -= 
            moveStep;

        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) posZ += 
            moveStep;

        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) posZ -= 
            moveStep;

        if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
        {
            rotorSpeed += 0.4f * deltaTime;
        }

        if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
        {
            rotorSpeed -= 0.4f * deltaTime;
            if (rotorSpeed < 0.0f) rotorSpeed = 0.0f;
        }

        bool enterPressedNow = (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS);
        if (enterPressedNow && !enterPressedLast)
        {
            wireframe = !wireframe;
        }
        enterPressedLast = enterPressedNow;

        rotorAngle += rotorSpeed;

        Mat4 T = mat4Translate(posX, posY, posZ);
        Mat4 Rx = mat4RotateX(rotX);
        Mat4 Ry = mat4RotateY(rotY);
        Mat4 Rz = mat4RotateZ(rotZ);

        Mat4 model = mat4Multiply(T, mat4Multiply(Rz, mat4Multiply(Ry, Rx)));

        // windmill rotate on origin
        Mat4 rotorToOrigin = mat4Translate(-ROTOR_CX, -ROTOR_CY, -ROTOR_CZ);
        Mat4 rotorBack = mat4Translate(ROTOR_CX, ROTOR_CY, ROTOR_CZ);
        Mat4 rotorSpin = mat4RotateX(rotorAngle);

        Mat4 rotorModelLocal = mat4Multiply(rotorBack,
                              mat4Multiply(rotorSpin, rotorToOrigin));

        Mat4 rotorModel = mat4Multiply(model, rotorModelLocal);

        Mat4 vp = mat4Multiply(projection, view);
        Mat4 mvpScene = mat4Multiply(vp, model);
        Mat4 mvpRotor = mat4Multiply(vp, rotorModel);

        glClearColor(0.90f, 0.85f, 0.88f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programID);

        if (!wireframe)
        {
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, mvpScene.m);
            glBindVertexArray(sceneTriVAO);
            glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(triVertices.size() / 6));

            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, mvpRotor.m);
            glBindVertexArray(rotorTriVAO);
            glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(rotorTriVertices.size() / 6));
        }
        else
        {
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, mvpScene.m);
            glBindVertexArray(sceneLineVAO);
            glDrawArrays(GL_LINES, 0, (GLsizei)(lineVertices.size() / 6));

            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, mvpRotor.m);
            glBindVertexArray(rotorLineVAO);
            glDrawArrays(GL_LINES, 0, (GLsizei)(rotorLineVertices.size() / 6));
        }

        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &sceneTriVBO);
    glDeleteBuffers(1, &sceneLineVBO);
    glDeleteBuffers(1, &rotorTriVBO);
    glDeleteBuffers(1, &rotorLineVBO);

    glDeleteVertexArrays(1, &sceneTriVAO);
    glDeleteVertexArrays(1, &sceneLineVAO);
    glDeleteVertexArrays(1, &rotorTriVAO);
    glDeleteVertexArrays(1, &rotorLineVAO);

    glDeleteProgram(programID);

    glfwTerminate();
    
    return 0;
}