#include "include/struct.h"
#include "include/mandelbulb.h"
#include "include/frac_color.h"
#include "include/dda.h"
#include "include/light.h"
#include "include/save_png.h"

int main() {
    const int WIDTH = 1920;
    const int HEIGHT = 1920;
    const int VOX_SIZE = 256;
    
    VoxelWorld world(VOX_SIZE, VOX_SIZE, VOX_SIZE);
    
    // Генерируем фрактал
    generateMandelbulb(world);
    
    // Камера смотрит на центр фрактала
    Vec3 camPos(VOX_SIZE * 1.1f, VOX_SIZE * 1.0f, VOX_SIZE * 1.1f);
    Vec3 camTarget(VOX_SIZE/2.0f, VOX_SIZE/2.0f, VOX_SIZE/2.0f);
    Vec3 up(0.0f, 1.0f, 0.0f);
    float fov = 60.0f * PI_CONST / 180.0f;
    
    save_png(WIDTH, HEIGHT, camPos, camTarget, up, fov, world);
    
    return 0;
}
