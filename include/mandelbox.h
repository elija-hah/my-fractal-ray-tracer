#ifndef MANDELBULB_H
#define MANDELBULB_H

#include <iostream>
#include <chrono>
#include "struct.h"

float mandelboxDE(const Vec3& pos, int maxIter);
void generateMandelbox(VoxelWorld& world);

#endif
