#ifndef SAVE_GIF_H
#define SAVE_GIF_H

#include <iostream>
#include <chrono>
#include <string.h>
#include "struct.h"
#include "frac_color.h"
#include "dda.h"
#include "light.h"
#include "progress_ui.h"

// Forward declaration of stbi_write_png from stb_image_write.h (implemented in save_png.cpp)
extern "C" int stbi_write_png(char const *filename, int w, int h, int comp, const void *data, int stride_in_bytes);

bool save_gif(const int WIDTH, const int HEIGHT, int frames, Vec3 camTarget, Vec3 up, float fov, VoxelWorld world, std::string filename);

#endif
