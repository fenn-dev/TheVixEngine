#pragma once
#include "config.hpp"
#include <functional>
#include "Handlers/WindowHandler/WindowHandler.hpp"

namespace VIX
{
    class TheVIXEngine
    {
    public:
        TheVIXEngine();
        ~TheVIXEngine();

        void Initialize(RendererBackend renderer = RendererBackend::OpenGL, WindowBackend windowSystem = WindowBackend::GLFW);

        void CreateWindow(int width, int height, const std::string& title);

        void shutdown();
        bool shouldClose();

        void BeginFrame();

        void Render();

        void SetClearColor(float r, float g, float b, float a);

    private:
        float _clearColor[4] = {0.1f, 0.1f, 0.1f, 1.0f};
        void* _window = nullptr; // Placeholder for window object

        WindowHandler _windowHandler;
    };
} // namespace VIX
