#include <TheVixEngine/thevixengine.hpp>

int main() {
    VIX::TheVIXEngine engine;
    engine.Initialize(VIX::RendererBackend::OpenGL, VIX::WindowBackend::GLFW);
    engine.CreateWindow(800, 600, "The VIX Engine Example");

    while (!engine.shouldClose()) {
        engine.BeginFrame();

        engine.Render();
    }

    engine.shutdown();
    return 0;
}