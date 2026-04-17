#include "../include/render_menu.h"

void renderFractalMenu(VoxelWorld world, std::string filename){
    clear();
    int HEIGHT, WIDTH;
    int VOX_SIZE = world.sizeX;
    mvprintw(0, 0, "Enter width and height of the output image");
    mvprintw(1, 0, "Enter width: ");
    refresh();

    echo();
    char input[20];
    getstr(input);
    WIDTH = atoi(input);
    mvprintw(2, 0, "Enter height: ");
    getstr(input);
    HEIGHT = atoi(input);
    noecho();

    Vec3 camPos(VOX_SIZE * 1.1f, VOX_SIZE * 1.0f, VOX_SIZE * 1.1f);
    Vec3 camTarget(VOX_SIZE/2.0f, VOX_SIZE/2.0f, VOX_SIZE/2.0f);
    Vec3 up(0.0f, 1.0f, 0.0f);
    float fov = 60.0f * PI_CONST / 180.0f;
    
    save_png(WIDTH, HEIGHT, camPos, camTarget, up, fov, world, "mandelbulb.png");
}
