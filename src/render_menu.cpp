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
    refresh();
    getstr(input);
    HEIGHT = atoi(input);
    
    // Ask user to choose PNG or GIF
    mvprintw(3, 0, "Choose format: 1. PNG  2. GIF (animated camera)");
    mvprintw(4, 0, "Your choice: ");
    refresh();
    getstr(input);
    int formatChoice = atoi(input);
    
    Vec3 camTarget(VOX_SIZE/2.0f, VOX_SIZE/2.0f, VOX_SIZE/2.0f);
    Vec3 up(0.0f, 1.0f, 0.0f);
    float fov = 60.0f * PI_CONST / 180.0f;
    
    bool success = false;
    int infoLine = 5;
    
    if (formatChoice == 2) {
        // GIF format - animated camera circling around fractal
        mvprintw(infoLine++, 0, "Enter number of frames (e.g., 30): ");
        refresh();
        getstr(input);
        int frames = atoi(input);
        if (frames < 1) frames = 30;
        
        // Change extension to .gif
        size_t dotPos = filename.rfind('.');
        if (dotPos != std::string::npos) {
            filename = filename.substr(0, dotPos) + ".gif";
        } else {
            filename += ".gif";
        }
        
        noecho();
        if(save_gif(WIDTH, HEIGHT, frames, camTarget, up, fov, world, filename)) {
            mvprintw(infoLine++, 0, "GIF saved to %s!", filename.c_str());
            success = true;
        }
        else {
            mvprintw(infoLine++, 0, "GIF save failed");
        }
    } else {
        // PNG format - static image
        noecho();
        Vec3 camPos(VOX_SIZE * 1.8f, VOX_SIZE * 1.2f, VOX_SIZE * 1.8f);
        if(save_png(WIDTH, HEIGHT, camPos, camTarget, up, fov, world, filename)) {
            mvprintw(infoLine++, 0, "Image saved to %s!", filename.c_str());
            success = true;
        }
        else {
            mvprintw(infoLine++, 0, "Image save failed");
        }
    }
    
    mvprintw(infoLine++, 0, "Press any key to continue...");
    refresh();
    getch();
    endwin();
}
