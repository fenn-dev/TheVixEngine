#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

namespace VIX::GLFW
{
    int Initialize();
    int createWindow(int width, int height, const char* title, GLFWwindow** window);
    bool shouldClose(GLFWwindow* window);
    void pollEvents();
    void swapBuffers(GLFWwindow* window);
    void terminate();
    void clearWindow(float r, float g, float b, float a);
} // namespace VIX::GLFW