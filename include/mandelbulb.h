#ifndef MANDELBULB_H
#define MANDELBULB_H

#include <iostream>
#include <chrono>
#include "struct.h"
#include "progress_ui.h"


float mandelbulbDE(const Vec3& pos, int maxIter);
void generateMandelbulb(VoxelWorld& world);

#endif
