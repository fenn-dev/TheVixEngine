// This WindowHandler.hpp file is the main include file and manager for all window handlers
// It includes the necessary includes based on #includes and selects the appropriate window handler based on the enumarator provided
// This is written by Sondre Rasmussen - 30.09.2025 - C++20 standard - For TheVixEngine project - V0.1
#pragma once
#include "../../config.hpp"
#include <functional>
#include "GLFW/GLFWImplementation.hpp"
#include <vector>
#include <string>

// #include "SDLImplementation.hpp" // Future implementation
// #include "SFMLImplementation.hpp" // Future implementation
// #include "Win32Implementation.hpp" // Future implementation

namespace VIX {

    class WindowHandler
    {
        public:

        WindowHandler();
        ~WindowHandler();

        void setBackend(WindowBackend backend) { _backend = backend; }

        void createWindow(int width, int height, const std::string& title, void** window);
        void* getWindowHandle() const;
        bool shouldClose();
        void shutdown();

        void Initialize();

        void clear();
        void render();

        private:

        struct WindowData
        {
            int width = 0;
            int height = 0;
            std::string title = "";
            void* window = nullptr; // Pointer to the actual window object
            bool isOpen = true;
            bool docked = false;
        };

        std::vector<WindowData> _windows;

        WindowBackend _backend;
    };

} // namespace VIX
