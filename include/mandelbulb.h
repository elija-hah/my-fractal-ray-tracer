#ifndef MANDELBULB_H
#define MANDELBULB_H

#include <iostream>
#include <cmath>
#include <chrono>
#include "struct.h"

float mandelbulbDE(const Vec3& pos, int maxIter);
void generateMandelbulb(VoxelWorld& world);

#endif