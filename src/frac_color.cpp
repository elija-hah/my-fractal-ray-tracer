#include "../include/frac_color.h"

// ==================== Цвет фрактала ====================
Color getFractalColor(int x, int y, int z, const VoxelWorld& world) {
    const int SIZE = world.sizeX;
    const float scale = 2.5f;
    const float offset = SIZE / 2.0f;

    float fx = (x - offset) / (SIZE / scale);
    float fy = (y - offset) / (SIZE / scale);
    float fz = (z - offset) / (SIZE / scale);

    Vec3 pos(fx, fy, fz);
    Vec3 current = pos;
    float r = 0.0f;
    const float power = 8.0f;
    int iter = 0;
    float escapedR = 0.0f;

    // Увеличиваем максимум итераций и сохраняем значение r при выходе
    for (int i = 0; i < 30; i++) {
        r = current.length();
        if (r > 2.0f) {
            escapedR = r;
            break;
        }

        float theta = std::acos(current.z / r) * power;
        float phi = std::atan2(current.y, current.x) * power;
        float zr = std::pow(r, power);

        current.x = zr * std::sin(theta) * std::cos(phi);
        current.y = zr * std::sin(theta) * std::sin(phi);
        current.z = zr * std::cos(theta);

        current = current + pos;
        iter = i;
    }

    // Нормализуем итерации - теперь они будут от 0 до ~25
    float iterNorm = iter / 25.0f;

    // Добавляем smooth coloring на основе escapedR
    if (r > 2.0f) {
        float logR = std::log(r);
        float smoothIter = iter + 1 - std::log(logR) / std::log(power);
        iterNorm = smoothIter / 25.0f;
    }

    iterNorm = std::min(1.0f, std::max(0.0f, iterNorm));

    // Яркий радужный градиент
    float r_color, g_color, b_color;

    // Используем синусоидальную палитру для ярких цветов
    float freq = 2.0f;
    r_color = 0.5f + 0.5f * std::sin(freq * iterNorm * 2.0f * 3.14159f + 0.0f);
    g_color = 0.5f + 0.5f * std::sin(freq * iterNorm * 2.0f * 3.14159f + 2.094f);
    b_color = 0.5f + 0.5f * std::sin(freq * iterNorm * 2.0f * 3.14159f + 4.188f);

    // Делаем цвета ярче и насыщеннее
    r_color = std::pow(r_color, 0.8f);
    g_color = std::pow(g_color, 0.8f);
    b_color = std::pow(b_color, 0.8f);

    // Добавляем вариацию на основе позиции
    float posVar = 0.8f + 0.3f * std::sin(pos.x * 2.0f) * std::cos(pos.y * 2.0f) * std::sin(pos.z * 2.0f);

    return Color(
        static_cast<unsigned char>(255 * r_color * posVar),
        static_cast<unsigned char>(255 * g_color * posVar),
        static_cast<unsigned char>(255 * b_color * posVar)
    );
}
