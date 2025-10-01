#pragma once


// DEFINE BACKENDS HERE
#define _GLFW
// #define _SDL
// #define _SFML
// #define _WIN32
// #define _WIN64
// DEFINE RENDERERS HERE
// #define _OPENGL
// #define _VULKAN
// #define _DIRECTX11
// #define _DIRECTX12


// DO NOT EDIT BELOW THIS LINE UNLESS YOU KNOW WHAT YOU ARE DOING
namespace VIX {
    enum class WindowBackend {
        GLFW,
        SDL,
        Win32
    };

    enum class RendererBackend {
        OpenGL,
        Vulkan,
        DirectX12
    };
}