#include <GLFW/glfw3.h>
#include <iostream>
#include "../../ErrorHandler.hpp"
#include "GLFWImplementation.hpp"

namespace VIX::GLFW
{
    int Initialize()
    {
        if (!glfwInit()) {
            REPORT_ERROR(ErrorHandler::ErrorID::GLFW_INIT_FAIL, ErrorHandler::Severity::FATAL, "Failed to initialize GLFW!");
            return -1;
        }

        return 0;
    }

    int createWindow(int width, int height, const char* title, GLFWwindow** window)
    {
        *window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!*window) {
            glfwTerminate();
            REPORT_ERROR(ErrorHandler::ErrorID::GLFW_WINDOW_FAIL, ErrorHandler::Severity::FATAL, "Failed to create GLFW window!");
            return -1;
        }
        glfwMakeContextCurrent((GLFWwindow*)*window);
        glfwSwapInterval(1); // Enable V-Sync

        return 0;
    }

    bool shouldClose(GLFWwindow* window)
    {
        return glfwWindowShouldClose(window);
    }

    void pollEvents()
    {
        glfwPollEvents();
    }

    void swapBuffers(GLFWwindow* window)
    {
        glfwSwapBuffers(window);
    }

    void terminate()
    {
        glfwTerminate();
    }

    void clearWindow(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

} // namespace VIX::GLFW