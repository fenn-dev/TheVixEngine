#include <array>

inline std::array<float, 3> RGBtoFloat(int rgb) {
    constexpr float inv = 1.0f / 255.0f;
    return {
        ((rgb >> 16) & 0xFF) * inv, // Red
        ((rgb >> 8) & 0xFF) * inv,  // Green
        (rgb & 0xFF) * inv          // Blue
    };
}

inline std::array<float, 4> RGBAtoFloat(int rgba) {
    constexpr float inv = 1.0f / 255.0f;
    return {
        ((rgba >> 24) & 0xFF) * inv, // Red
        ((rgba >> 16) & 0xFF) * inv, // Green
        ((rgba >> 8) & 0xFF) * inv,  // Blue
        (rgba & 0xFF) * inv          // Alpha
    };
}