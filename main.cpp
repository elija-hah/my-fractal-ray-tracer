#include "include/struct.h"
#include "include/mandelbulb.h"
#include "include/mandelbox.h"
#include "include/render_menu.h"
#include "include/select_menu.h"

int main() {
    const int VOX_SIZE = 256;
    VoxelWorld world(VOX_SIZE, VOX_SIZE, VOX_SIZE);
    
    FractalType current = selectFractalMenu();
    
    switch(current) {
    	case MANDELBULB: generateMandelbulb(world); renderFractalMenu(world, "mandelbulb.png"); break;
    	case MANDELBOX:  generateMandelbox(world); renderFractalMenu(world, "mandelbox.png"); break;
    }
    return 0;
}
