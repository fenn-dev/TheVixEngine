#include "thevixengine.hpp"
#include "config.hpp"

namespace VIX
{
    TheVIXEngine::TheVIXEngine() = default;
    TheVIXEngine::~TheVIXEngine() = default;

    void TheVIXEngine::Initialize(RendererBackend renderer, WindowBackend windowSystem) {
        _windowHandler.setBackend(windowSystem);

        _windowHandler.Initialize();
    };

    void TheVIXEngine::CreateWindow(int width, int height, const std::string& title) {
        _windowHandler.createWindow(width, height, title, &_window);
    }

    void TheVIXEngine::shutdown() {
        _windowHandler.shutdown();
    }

    bool TheVIXEngine::shouldClose() {
        return _windowHandler.shouldClose();
    }

    void TheVIXEngine::BeginFrame() {
        _windowHandler.clear();
    }

    void TheVIXEngine::Render() {
        _windowHandler.render();
    }


} // namespace VIX
