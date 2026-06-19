#ifndef SAVE_GIF_H
#define SAVE_GIF_H

#include <string.h>
#include <cmath>
#include <filesystem>
#include "struct.h"
#include "save_png.h"

bool save_gif(const int WIDTH, const int HEIGHT, const int nFrames, Vec3 up, float fov, VoxelWorld world, std::string filename);

#endif
