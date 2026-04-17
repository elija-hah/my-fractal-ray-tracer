#include "../include/mandelbox.h"

// ==================== Mandelbox Distance Estimation ====================
float mandelboxDE(const Vec3& pos, int maxIter) {
    Vec3 z = pos;
    float dr = 1.0f;  // Для корректной оценки расстояния
    const float scale = 2.0f;
    const float fixedRadius = 1.0f;
    const float minRadius = 0.5f;
    
    for (int i = 0; i < maxIter; i++) {
        // Box Fold
        if (z.x > 1.0f) z.x = 2.0f - z.x;
        else if (z.x < -1.0f) z.x = -2.0f - z.x;
        
        if (z.y > 1.0f) z.y = 2.0f - z.y;
        else if (z.y < -1.0f) z.y = -2.0f - z.y;
        
        if (z.z > 1.0f) z.z = 2.0f - z.z;
        else if (z.z < -1.0f) z.z = -2.0f - z.z;
        
        // Ball Fold
        float r = std::sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
        if (r < minRadius) {
            z.x *= fixedRadius / minRadius;
            z.y *= fixedRadius / minRadius;
            z.z *= fixedRadius / minRadius;
            dr *= fixedRadius / minRadius;
        } else if (r < fixedRadius) {
            float factor = fixedRadius / r;
            z.x *= factor;
            z.y *= factor;
            z.z *= factor;
            dr *= factor;
        }
        
        // Масштабирование и добавление константы
        z.x = z.x * scale + pos.x;
        z.y = z.y * scale + pos.y;
        z.z = z.z * scale + pos.z;
        
        dr = dr * std::abs(scale) + 1.0f;
        
        // Ранний выход, если точка ушла слишком далеко
        if (std::sqrt(z.x*z.x + z.y*z.y + z.z*z.z) > 10.0f) break;
    }
    
    float r = std::sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
    return r / std::abs(dr);
}

// ==================== Генерация Mandelbox ====================
void generateMandelbox(VoxelWorld& world) {
    std::cout << "Generating Mandelbox fractal...\n";
    auto start = std::chrono::high_resolution_clock::now();
    
    const int SIZE = world.sizeX;
    const float scale = 2.0f;  // Масштаб для Mandelbox
    const float offset = SIZE / 2.0f;
    
    int filled = 0;
    
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            for (int z = 0; z < SIZE; z++) {
                // Маппинг воксельных координат в пространство фрактала [-2.0, 2.0]
                float fx = (x - offset) / (SIZE / (scale * 2.0f));
                float fy = (y - offset) / (SIZE / (scale * 2.0f));
                float fz = (z - offset) / (SIZE / (scale * 2.0f));
                
                float de = mandelboxDE(Vec3(fx, fy, fz), 8);
                
                if (de < 0.01f) {
                    world.at(x, y, z) = 2;  // Тип 2 для Mandelbox
                    filled++;
                }
            }
        }
        if (x % 32 == 0) {
            auto now = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start);
            std::cout << "  Slice " << x << "/" << SIZE 
                      << " (filled: " << filled << ", time: " << elapsed.count() << "s)\n";
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << "Generated " << filled << " voxels in " << duration.count() << " seconds\n";
}

