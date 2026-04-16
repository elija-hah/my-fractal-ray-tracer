#ifndef DDA_H
#define DDA_H

#include <cmath>
#include "struct.h"

bool intersectAABB(const Ray& ray, const Vec3& boxMin, const Vec3& boxMax, float& tNear, float& tFar);
bool traceDDA(const VoxelWorld& world, const Ray& ray, float maxDist, 
              Vec3& hitPos, unsigned char& voxelType, Vec3& normal);

#endif