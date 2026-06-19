#ifndef RENDER_MENU_H
#define RENDER_MENU_H

#include <ncurses.h>
#include <stdexcept>
#include "save_png.h"
#include "save_gif.h"
#include "struct.h"

void renderFractalMenu(VoxelWorld world, std::string filename);

#endif
