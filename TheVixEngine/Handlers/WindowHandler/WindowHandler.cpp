#include "../../config.hpp"
#include "WindowHandler.hpp"
#include "../ErrorHandler.hpp"

#ifdef _GLFW
#include "GLFW/GLFWImplementation.hpp"
#endif


namespace VIX
{
    WindowHandler::WindowHandler() = default;
    WindowHandler::~WindowHandler() = default;

    void WindowHandler::Initialize()
    {
        // Initialization logic based on the selected backend
        switch (_backend)
        {
        case WindowBackend::GLFW:
            // Initialize GLFW backend
            #ifdef _GLFW
            REPORT_ERROR_IF(GLFW::Initialize() != 0, ErrorHandler::ErrorID::GLFW_INIT_FAIL, ErrorHandler::Severity::FATAL, "Failed to initialize GLFW!");
            #else
                #if __has_include(<GLFW/glfw3.h>)
                REPORT_ERROR(ErrorID::GLFW_MISSING, Severity::FATAL, "GLFW header found but _GLFW not defined!");
                #else
                REPORT_ERROR(ErrorID::GLFW_MISSING, Severity::FATAL, "GLFW backend not available!");
                #endif
            #endif
            break;
        case WindowBackend::SDL:
            // Initialize SDL backend
            #ifdef _SDL
            // SDL::Initialize();
            #else
                #if __has_include(<SDL.h>)
                REPORT_ERROR(ErrorID::SDL_MISSING, Severity::FATAL, "SDL header found but _SDL not defined!");
                #else
                REPORT_ERROR(ErrorID::SDL_MISSING, Severity::FATAL, "SDL backend not available!");
                #endif
            #endif
            break;
        case WindowBackend::Win32:
            // Initialize Win32 backend
            #ifdef _WIN32
            // Win32::Initialize();
            #else
                #if defined(_WIN32) || defined(_WIN64)
                REPORT_ERROR(ErrorID::Win32_MISSING, Severity::FATAL, "Win32 header found but _WIN32 not defined!");
                #else
                REPORT_ERROR(ErrorID::Win32_MISSING, Severity::FATAL, "Win32 backend not available!");
                #endif
            #endif
            break;
        default:
            // Handle unknown backend
            REPORT_ERROR(ErrorID::UNKNOWN_BACKEND, Severity::FATAL, "Unknown window backend selected!");
            break;
        }
    }

    void WindowHandler::createWindow(int width, int height, const std::string& title, void** window) {
        // Create window based on the selected backend
        switch (_backend)
        {
        case WindowBackend::GLFW:
            // Initialize GLFW backend
            #ifdef _GLFW
            GLFW::createWindow(width, height, title.c_str(), (GLFWwindow**)window);
            _windows.push_back({width, height, title, *window, true, false});
            #else
            #if __has_include(<GLFW/glfw3.h>)
                REPORT_ERROR(ErrorID::GLFW_MISSING, Severity::FATAL, "GLFW header found but _GLFW not defined!");
                #else
                REPORT_ERROR(ErrorID::GLFW_MISSING, Severity::FATAL, "GLFW backend not available!");
                #endif
            #endif
            break;
        case WindowBackend::SDL:
            // Initialize SDL backend
            break;
        case WindowBackend::Win32:
            // Initialize Win32 backend
            break;
        default:
            // Handle unknown backend
            REPORT_ERROR(ErrorID::UNKNOWN_BACKEND, Severity::FATAL, "Unknown window backend selected!");
            break;
        }
    }

    bool WindowHandler::shouldClose() {
        switch (_backend)
        {
        case WindowBackend::GLFW:
            // Initialize GLFW backend
            #ifdef _GLFW
            return GLFW::shouldClose((GLFWwindow*)_windows[0].window);
            #else
                #if __has_include(<GLFW/glfw3.h>)
                REPORT_ERROR(ErrorID::GLFW_MISSING, Severity::FATAL, "GLFW header found but _GLFW not defined!");
                #else
                REPORT_ERROR(ErrorID::GLFW_MISSING, Severity::FATAL, "GLFW backend not available!");
                #endif
            #endif
            break;
        default:
            // Handle unknown backend
            REPORT_ERROR(ErrorID::UNKNOWN_BACKEND, Severity::FATAL, "Unknown window backend selected!");
            break;
        }
        return true; // Default to true if backend is unknown
    }

    void WindowHandler::shutdown() {
        switch (_backend)
        {
        case WindowBackend::GLFW:
            // Initialize GLFW backend
            #ifdef _GLFW
            GLFW::terminate();
            #else
                #if __has_include(<GLFW/glfw3.h>)
                REPORT_ERROR(ErrorID::GLFW_MISSING, Severity::FATAL, "GLFW header found but _GLFW not defined!");
                #else
                REPORT_ERROR(ErrorID::GLFW_MISSING, Severity::FATAL, "GLFW backend not available!");
                #endif
            #endif
            break;
        case WindowBackend::SDL:
            // Initialize SDL backend
            break;
        case WindowBackend::Win32:
            // Initialize Win32 backend
            break;
        default:
            // Handle unknown backend
            REPORT_ERROR(ErrorID::UNKNOWN_BACKEND, Severity::FATAL, "Unknown window backend selected!");
            break;
        }
    }

    void* WindowHandler::getWindowHandle() const {
        if (_windows.empty()) return nullptr;
        return _windows[0].window;
    }

    void WindowHandler::clear() {
        switch (_backend)
        {
        case WindowBackend::GLFW:
            // Initialize GLFW backend
            #ifdef _GLFW
            GLFW::clearWindow(0.0f, 0.0f, 0.0f, 1.0f);
            #else
                #if __has_include(<GLFW/glfw3.h>)
                REPORT_ERROR(ErrorID::GLFW_MISSING, Severity::FATAL, "GLFW header found but _GLFW not defined!");
                #else
                REPORT_ERROR(ErrorID::GLFW_MISSING, Severity::FATAL, "GLFW backend not available!");
                #endif
            #endif
            break;
        case WindowBackend::SDL:
            // Initialize SDL backend
            break;
        case WindowBackend::Win32:
            // Initialize Win32 backend
            break;
        default:
            // Handle unknown backend
            REPORT_ERROR(ErrorID::UNKNOWN_BACKEND, Severity::FATAL, "Unknown window backend selected!");
            break;
        }
    }

    void WindowHandler::render() {
        switch (_backend)
        {
        case WindowBackend::GLFW:
            // Initialize GLFW backend
            #ifdef _GLFW
            GLFW::swapBuffers((GLFWwindow*)_windows[0].window);
            GLFW::pollEvents();
            #else
                #if __has_include(<GLFW/glfw3.h>)
                REPORT_ERROR(ErrorID::GLFW_MISSING, Severity::FATAL, "GLFW header found but _GLFW not defined!");
                #else
                REPORT_ERROR(ErrorID::GLFW_MISSING, Severity::FATAL, "GLFW backend not available!");
                #endif
            #endif
            break;
        case WindowBackend::SDL:
            // Initialize SDL backend
            break;
        case WindowBackend::Win32:
            // Initialize Win32 backend
            break;
        default:
            // Handle unknown backend
            REPORT_ERROR(ErrorID::UNKNOWN_BACKEND, Severity::FATAL, "Unknown window backend selected!");
            break;
        }
    }

} // namespace VIX