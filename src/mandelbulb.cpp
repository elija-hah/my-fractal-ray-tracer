#include "../include/mandelbulb.h"

// ==================== Mandelbulb ====================
float mandelbulbDE(const Vec3& pos, int maxIter = 8) {
    Vec3 z = pos;
    float dr = 1.0f;
    float r = 0.0f;
    const float power = 8.0f;  // Классический Mandelbulb

    for (int i = 0; i < maxIter; i++) {
        r = z.length();
        if (r > 2.0f) break;

        // Конвертация в сферические координаты
        float theta = std::acos(z.z / r) * power;
        float phi = std::atan2(z.y, z.x) * power;
        float zr = std::pow(r, power);

        // Обратно в декартовы
        z.x = zr * std::sin(theta) * std::cos(phi);
        z.y = zr * std::sin(theta) * std::sin(phi);
        z.z = zr * std::cos(theta);

        z = z + pos;
        dr = dr * power * std::pow(r, power - 1.0f) + 1.0f;
    }

    return 0.5f * std::log(r) * r / dr;
}

// Генерация Mandelbulb в воксельной сетке
void generateMandelbulb(VoxelWorld& world) {
    std::cout << "Generating Mandelbulb fractal...\n";
    auto start = std::chrono::high_resolution_clock::now();

    const int SIZE = world.sizeX;
    const float scale = 2.5f;
    const float offset = SIZE / 2.0f;

    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            for (int z = 0; z < SIZE; z++) {
                // Маппинг воксельных координат в пространство фрактала [-1.5, 1.5]
                float fx = (x - offset) / (SIZE / scale);
                float fy = (y - offset) / (SIZE / scale);
                float fz = (z - offset) / (SIZE / scale);

                float de = mandelbulbDE(Vec3(fx, fy, fz), 6);

                if (de < 0.01f) {
                    world.at(x, y, z) = 1;
                }
            }
        }
        if (x % 32 == 0) {
            std::cout << "  Slice " << x << "/" << SIZE << "\n";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << "Spent " << duration.count() << " seconds\n";
}
