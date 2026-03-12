#include "vec3.h"
#include <cmath>

Vec3::Vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

double Vec3::abs() const {
    return std::sqrt(x*x + y*y + z*z);
}

Vec3 Vec3::normalize() const {
    double length = this->abs();
    if (length != 0)
        return *this / length;
    else
        throw std::invalid_argument("cannot normalize vector with length zero");
}

Vec3 Vec3::cross(const Vec3& b) const {
    return Vec3(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
}

std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}
