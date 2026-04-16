#ifndef LIGHT_H
#define LIGHT_H

#include <cmath>
#include "struct.h"

Color applyLighting(const Color& baseColor, const Vec3& normal);

#endif
