#include "../include/mandelbulb.h"

float mandelbulbDE(const Vec3& pos, int maxIter) {
    Vec3 z = pos;
    float dr = 1.0f;
    float r = 0.0f;
    const float power = 8.0f;

    for (int i = 0; i < maxIter; i++) {
        r = std::sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
        if (r > 2.0f) break;

        float theta = std::acos(z.z / r) * power;
        float phi = std::atan2(z.y, z.x) * power;
        float zr = std::pow(r, power);

        z.x = zr * std::sin(theta) * std::cos(phi);
        z.y = zr * std::sin(theta) * std::sin(phi);
        z.z = zr * std::cos(theta);

        z = z + pos;
        dr = dr * power * std::pow(r, power - 1.0f) + 1.0f;
    }

    return 0.5f * std::log(r) * r / dr;
}

void generateMandelbulb(VoxelWorld& world) {
    ProgressUI ui("Generating Mandelbulb Fractal");
    
    const int SIZE = world.sizeX;
    const float scale = 2.5f;
    const float offset = SIZE / 2.0f;
    const int maxIter = 8;
    
    int filled = 0;
    
    for (int x = 0; x < SIZE; x++) {
        if (x % 8 == 0) {
            char status[50];
            snprintf(status, sizeof(status), "Slice %d/%d, filled: %d", x, SIZE, filled);
            ui.update(status, x, SIZE);
        }
        
        for (int y = 0; y < SIZE; y++) {
            for (int z = 0; z < SIZE; z++) {
                float fx = (x - offset) / (SIZE / scale);
                float fy = (y - offset) / (SIZE / scale);
                float fz = (z - offset) / (SIZE / scale);

                float de = mandelbulbDE(Vec3(fx, fy, fz), maxIter);

                if (de < 0.01f) {
                    world.at(x, y, z) = 1;
                    filled++;
                }
            }
        }
    }
    
    char message[50];
    snprintf(message, sizeof(message), "Done! Generated %d voxels", filled);
    ui.finish(message);
}