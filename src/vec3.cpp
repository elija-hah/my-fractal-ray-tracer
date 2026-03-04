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

Vec3 Vec3::operator+(const Vec3& b) const {
    return Vec3(x + b.x, y + b.y, z + b.z);
}

Vec3 Vec3::operator-(const Vec3& b) const {
    return Vec3(x - b.x, y - b.y, z - b.z);
}

Vec3 Vec3::operator*(double b) const {
    return Vec3(b*x, b*y, b*z);
}

Vec3 Vec3::operator/(double b) const {
    if (b != 0)
        return Vec3(x/b, y/b, z/b);
    else
        throw std::invalid_argument("dividing vector by zero");
}

std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}
