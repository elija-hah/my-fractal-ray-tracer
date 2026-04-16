#include "../include/frac_color.h"

// ==================== Цвет фрактала с 8 угловыми цветами ====================
Color getFractalColor(float x, float y, float z, const int SIZE, const float scale) {
    const float offset = SIZE / 2.0f;

    // Конвертируем воксельные координаты в пространство фрактала
    float fx = (x - offset) / (SIZE / scale);
    float fy = (y - offset) / (SIZE / scale);
    float fz = (z - offset) / (SIZE / scale);

    // Нормализуем координаты в диапазон [0, 1]
    float nx = (fx + 2.0f) / 4.0f;
    float ny = (fy + 2.0f) / 4.0f;
    float nz = (fz + 2.0f) / 4.0f;

    // Ограничиваем
    nx = std::max(0.0f, std::min(1.0f, nx));
    ny = std::max(0.0f, std::min(1.0f, ny));
    nz = std::max(0.0f, std::min(1.0f, nz));

    Color colors[2][2][2] = {
        // z = 0 (ближний слой)
        {
            {Color(80, 200, 60),   Color(60, 220, 120)},  // y=0 (низ): зелёный -> мятный
            {Color(255, 240, 80),  Color(255, 200, 50)}   // y=1 (верх): жёлтый -> оранжевый
        },
        // z = 1 (дальний слой)
        {
            {Color(100, 180, 200), Color(80, 200, 220)},  // y=0 (низ): голубой -> светло-голубой
            {Color(200, 150, 255), Color(255, 180, 255)}  // y=1 (верх): фиолетовый -> розовый
        }
    };

    // Smoothstep для всех трёх осей (плавная интерполяция)
    float sx = nx * nx * (3.0f - 2.0f * nx);
    float sy = ny * ny * (3.0f - 2.0f * ny);
    float sz = nz * nz * (3.0f - 2.0f * nz);

    // Трилинейная интерполяция
    // Сначала интерполируем по X (4 пары)
    auto lerp = [](unsigned char a, unsigned char b, float t) {
        return static_cast<unsigned char>(a + (b - a) * t);
    };

    // Слой z=0, y=0
    unsigned char r00 = lerp(colors[0][0][0].r, colors[0][0][1].r, sx);
    unsigned char g00 = lerp(colors[0][0][0].g, colors[0][0][1].g, sx);
    unsigned char b00 = lerp(colors[0][0][0].b, colors[0][0][1].b, sx);

    // Слой z=0, y=1
    unsigned char r01 = lerp(colors[0][1][0].r, colors[0][1][1].r, sx);
    unsigned char g01 = lerp(colors[0][1][0].g, colors[0][1][1].g, sx);
    unsigned char b01 = lerp(colors[0][1][0].b, colors[0][1][1].b, sx);

    // Слой z=1, y=0
    unsigned char r10 = lerp(colors[1][0][0].r, colors[1][0][1].r, sx);
    unsigned char g10 = lerp(colors[1][0][0].g, colors[1][0][1].g, sx);
    unsigned char b10 = lerp(colors[1][0][0].b, colors[1][0][1].b, sx);

    // Слой z=1, y=1
    unsigned char r11 = lerp(colors[1][1][0].r, colors[1][1][1].r, sx);
    unsigned char g11 = lerp(colors[1][1][0].g, colors[1][1][1].g, sx);
    unsigned char b11 = lerp(colors[1][1][0].b, colors[1][1][1].b, sx);

    // Интерполяция по Y (объединяем пары по Y)
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
