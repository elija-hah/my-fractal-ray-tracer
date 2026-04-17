#ifndef SAVE_PNG_H
#define SAVE_PNG_H

#include <iostream>
#include <chrono>
#include <string.h>
#include "struct.h"
#include "frac_color.h"
#include "dda.h"
#include "light.h"
#include "progress_ui.h"

bool save_png(const int WIDTH, const int HEIGHT, Vec3 camPos, Vec3 camTarget, Vec3 up, float fov, VoxelWorld world, std::string filename);

#endif
