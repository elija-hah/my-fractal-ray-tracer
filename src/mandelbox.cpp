#include "../include/mandelbox.h"

// ==================== Mandelbox ====================
float mandelboxDE(const Vec3& pos, int maxIter = 8) {
    Vec3 z = pos;
    const float scale = 2.0f;  // Классический Mandelbox

    for (int i = 0; i < maxIter; i++) {
        r = z.length();
        if (r > 2.0f) break;

        // Box Fold: Отражение координат, вышедших за пределы [-1, 1].
        if (z.x > 1) z.x = 2 - z.x;
        else if (z.x < -1) z.x = -2 - z.x;
        if (z.y > 1) z.y = 2 - z.y;
        else if (z.y < -1) z.y = -2 - z.y;
        if (z.z > 1) z.z = 2 - z.z;
        else if (z.z < -1) z.z = -2 - z.z;

        // Ball Fold: Сжатие/растяжение пространства
        float r = length(z);
        if (r < 0.5) z *= 4;
        else if (r < 1) z /= (r * r);

        z = z*scale + pos;
    }

    return z;
}

// Генерация Mandelbox в воксельной сетке
void generateMandelbox(VoxelWorld& world) {
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

                float de = mandelboxDE(Vec3(fx, fy, fz), 6);

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
