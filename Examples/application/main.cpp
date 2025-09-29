#include <TheVixEngine/thevixengine.hpp>

int main() {
    VIX::TheVIXEngine engine;
    engine.Initialize();

    while (true) {
        engine.Update(0.016f);
        engine.Render();
    }

    engine.Shutdown();
}
