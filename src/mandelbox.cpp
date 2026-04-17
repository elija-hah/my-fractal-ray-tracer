#include "../include/mandelbox.h"

float mandelboxDE(const Vec3& pos, int maxIter) {
    Vec3 z = pos;
    float dr = 1.0f;
    const float scale = 2.5f;        // Увеличил для более интересной формы
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
        float r2 = z.x*z.x + z.y*z.y + z.z*z.z;
        if (r2 < minRadius * minRadius) {
            float factor = fixedRadius / minRadius;
            z.x *= factor;
            z.y *= factor;
            z.z *= factor;
            dr *= factor;
        } else if (r2 < fixedRadius * fixedRadius) {
            float factor = fixedRadius / std::sqrt(r2);
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
        
        // Ранний выход
        if (z.x*z.x + z.y*z.y + z.z*z.z > 100.0f) break;
    }
    
    float r = std::sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
    return r / std::abs(dr);
}

void generateMandelbox(VoxelWorld& world) {
    ProgressUI ui("Generating Mandelbox Fractal");
    
    const int SIZE = world.sizeX;
    const float scale = 3.5f;  // Масштаб для маппинга
    const float offset = SIZE / 2.0f;
    const int maxIter = 12;
    
    int filled = 0;
    
    for (int x = 0; x < SIZE; x++) {
        if (x % 8 == 0) {
            char status[50];
            snprintf(status, sizeof(status), "Slice %d/%d, filled: %d", x, SIZE, filled);
            ui.update(status, x, SIZE);
        }
        
        for (int y = 0; y < SIZE; y++) {
            for (int z = 0; z < SIZE; z++) {
                // Маппинг в пространство [-2.5, 2.5]
                float fx = (x - offset) / (SIZE / (scale * 2.0f));
                float fy = (y - offset) / (SIZE / (scale * 2.0f));
                float fz = (z - offset) / (SIZE / (scale * 2.0f));
                
                float de = mandelboxDE(Vec3(fx, fy, fz), maxIter);
                
                if (de < 0.015f) {
                    world.at(x, y, z) = 2;
                    filled++;
                }
            }
        }
    }
    
    char message[50];
    snprintf(message, sizeof(message), "Done! Generated %d voxels", filled);
    ui.finish(message);
}