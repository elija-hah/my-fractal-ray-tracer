#include "../include/render_menu.h"

void renderFractalMenu(VoxelWorld world, std::string filename){
    clear();
    int HEIGHT, WIDTH;
    int VOX_SIZE = world.sizeX;
    
    mvprintw(0, 0, "Choose PNG or GIF."); 
    mvprintw(1, 0, "1 - PNG, 2 - GIF: ");
    refresh();
    echo();
    char input[20];
    getstr(input);
    int mode = atoi(input);
    noecho();
    
    clear();
    mvprintw(0, 0, "Enter width and height of the output image");
    mvprintw(1, 0, "Enter width: ");
    refresh();

    echo();
    getstr(input);
    WIDTH = atoi(input);
    mvprintw(2, 0, "Enter height: ");
    getstr(input);
    HEIGHT = atoi(input);
    noecho();

    if(mode == 1){
        filename += ".png";
	Vec3 camPos(VOX_SIZE * 1.8f, VOX_SIZE * 1.2f, VOX_SIZE * 1.8f);
	Vec3 camTarget(VOX_SIZE/2.0f, VOX_SIZE/2.0f, VOX_SIZE/2.0f);
	Vec3 up(0.0f, 1.0f, 0.0f);
	float fov = 60.0f * PI_CONST / 180.0f;
	    
	if(save_png(WIDTH, HEIGHT, camPos, camTarget, up, fov, world, filename)) {
	    mvprintw(4, 0, "Image saved to %s!", filename.c_str());
	}
	else {
	    mvprintw(4, 0, "Image save failed");
	}
    }
    else if(mode == 2){
        filename += ".gif";
        clear();
        mvprintw(0, 0, "Enter number of frames (I recomend 25 <= nFrames <= 100): ");
        refresh();

        echo();
        getstr(input);
        int nFrames = atoi(input);
        noecho();
        
    	Vec3 up(0.0f, 1.0f, 0.0f);
	float fov = 40.0f * PI_CONST / 180.0f;
	    
	if(save_gif(WIDTH, HEIGHT, nFrames, up, fov, world, filename)) {
	    mvprintw(4, 0, "Image saved to %s!", filename.c_str());
	}
	else {
	    mvprintw(4, 0, "Image save failed");
	}
    }
    else{
        throw std::invalid_argument("mode (PNG or GIF) must be 1 or 2");
    }
    
    mvprintw(5, 0, "Press any key to continue...");
    refresh();
    getch();
    endwin();
}
