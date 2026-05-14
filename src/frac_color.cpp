#include "../include/frac_color.h"

Color getFractalColor(float x, float y, float z, const int SIZE, const float scale) {
    // 1. Строгая нормализация координат в [0, 1]
    // Делим на (SIZE - 1), чтобы крайние воксели были ровно 0.0 и 1.0
    float nx = x / (float)(SIZE - 1);
    float ny = y / (float)(SIZE - 1);
    float nz = z / (float)(SIZE - 1);

    // Палитра углов куба
    Color colors[2][2][2] = {
        // z = 0 (ближний слой)
        {
            {Color(80, 200, 60),   Color(60, 220, 120)},  // y=0
            {Color(255, 240, 80),  Color(255, 200, 50)}   // y=1
        },
        // z = 1 (дальний слой)
        {
            {Color(100, 180, 200), Color(80, 200, 220)},  // y=0
            {Color(200, 150, 255), Color(255, 180, 255)}  // y=1
        }
    };

    auto lerp = [](float a, float b, float t) {
        return a + (b - a)*t;
    };

    // Интерполяция по X (внутри каждого слоя и строки)
    float r00 = lerp(static_cast<float>(colors[0][0][0].r), static_cast<float>(colors[0][0][1].r), nx);
    float g00 = lerp(static_cast<float>(colors[0][0][0].g), static_cast<float>(colors[0][0][1].g), nx);
    float b00 = lerp(static_cast<float>(colors[0][0][0].b), static_cast<float>(colors[0][0][1].b), nx);

    float r01 = lerp(static_cast<float>(colors[0][1][0].r), static_cast<float>(colors[0][1][1].r), nx);
    float g01 = lerp(static_cast<float>(colors[0][1][0].g), static_cast<float>(colors[0][1][1].g), nx);
    float b01 = lerp(static_cast<float>(colors[0][1][0].b), static_cast<float>(colors[0][1][1].b), nx);

    float r10 = lerp(static_cast<float>(colors[1][0][0].r), static_cast<float>(colors[1][0][1].r), nx);
    float g10 = lerp(static_cast<float>(colors[1][0][0].g), static_cast<float>(colors[1][0][1].g), nx);
    float b10 = lerp(static_cast<float>(colors[1][0][0].b), static_cast<float>(colors[1][0][1].b), nx);

    float r11 = lerp(static_cast<float>(colors[1][1][0].r), static_cast<float>(colors[1][1][1].r), nx);
    float g11 = lerp(static_cast<float>(colors[1][1][0].g), static_cast<float>(colors[1][1][1].g), nx);
    float b11 = lerp(static_cast<float>(colors[1][1][0].b), static_cast<float>(colors[1][1][1].b), nx);

    // Интерполяция по Y
    float r0 = lerp(r00, r01, ny);
    float g0 = lerp(g00, g01, ny);
    float b0 = lerp(b00, b01, ny);

    float r1 = lerp(r10, r11, ny);
    float g1 = lerp(g10, g11, ny);
    float b1 = lerp(b10, b11, ny);

    // Интерполяция по Z (финальная)
    float r = lerp(r0, r1, nz);
    float g = lerp(g0, g1, nz);
    float b = lerp(b0, b1, nz);

    return Color(static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b));
}
