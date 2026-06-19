#include "include/struct.h"
#include "include/mandelbulb.h"
#include "include/mandelbox.h"
#include "include/render_menu.h"
#include "include/select_menu.h"

int main() {
    const int VOX_SIZE = 512;
    VoxelWorld world(VOX_SIZE, VOX_SIZE, VOX_SIZE);
    
    FractalType current = selectFractalMenu();
    
    switch(current) {
    	case MANDELBULB: generateMandelbulb(world); renderFractalMenu(world, "mandelbulb"); break;
    	case MANDELBOX:  generateMandelbox(world); renderFractalMenu(world, "mandelbox"); break;
    }
    return 0;
}
