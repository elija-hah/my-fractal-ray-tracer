#include "../include/frac_color.h"

Color getFractalColor(float x, float y, float z, const int SIZE, const float scale) {
    // 1. Строгая нормализация координат в [0, 1]
    // Делим на (SIZE - 1), чтобы крайние воксели были ровно 0.0 и 1.0
    float nx = x / (float)(SIZE - 1);
    float ny = y / (float)(SIZE - 1);
    float nz = z / (float)(SIZE - 1);

    // 2. Smoothstep для сглаживания цветовых переходов
    float sx = nx * nx * (3.0f - 2.0f * nx);
    float sy = ny * ny * (3.0f - 2.0f * ny);
    float sz = nz * nz * (3.0f - 2.0f * nz);

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

    auto lerp = [](unsigned char a, unsigned char b, float t) {
        return static_cast<unsigned char>(a + (b - a) * t);
    };

    // Интерполяция по X (внутри каждого слоя и строки)
    unsigned char r00 = lerp(colors[0][0][0].r, colors[0][0][1].r, sx);
    unsigned char g00 = lerp(colors[0][0][0].g, colors[0][0][1].g, sx);
    unsigned char b00 = lerp(colors[0][0][0].b, colors[0][0][1].b, sx);

    unsigned char r01 = lerp(colors[0][1][0].r, colors[0][1][1].r, sx);
    unsigned char g01 = lerp(colors[0][1][0].g, colors[0][1][1].g, sx);
    unsigned char b01 = lerp(colors[0][1][0].b, colors[0][1][1].b, sx);

    unsigned char r10 = lerp(colors[1][0][0].r, colors[1][0][1].r, sx);
    unsigned char g10 = lerp(colors[1][0][0].g, colors[1][0][1].g, sx);
    unsigned char b10 = lerp(colors[1][0][0].b, colors[1][0][1].b, sx);

    unsigned char r11 = lerp(colors[1][1][0].r, colors[1][1][1].r, sx);
    unsigned char g11 = lerp(colors[1][1][0].g, colors[1][1][1].g, sx);
    unsigned char b11 = lerp(colors[1][1][0].b, colors[1][1][1].b, sx);

    // Интерполяция по Y
    unsigned char r0 = lerp(r00, r01, sy);
    unsigned char g0 = lerp(g00, g01, sy);
    unsigned char b0 = lerp(b00, b01, sy);

    unsigned char r1 = lerp(r10, r11, sy);
    unsigned char g1 = lerp(g10, g11, sy);
    unsigned char b1 = lerp(b10, b11, sy);

    // Интерполяция по Z (финальная)
    unsigned char r = lerp(r0, r1, sz);
    unsigned char g = lerp(g0, g1, sz);
    unsigned char b = lerp(b0, b1, sz);

    return Color(r, g, b);
}
