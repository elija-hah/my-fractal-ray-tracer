#ifndef SAVE_PNG_H
#define SAVE_PNG_H

#include <iostream>
#include <chrono>
#include "struct.h"
#include "frac_color.h"
#include "dda.h"
#include "light.h"

void save_png(const int WIDTH, const int HEIGHT, Vec3 camPos, Vec3 camTarget, Vec3 up, float fov, VoxelWorld world);

#endif
