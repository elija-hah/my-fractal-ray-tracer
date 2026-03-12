#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <stdexcept>

class Vec3 {
public:
    double x, y, z;

    Vec3(double _x, double _y, double _z);

    double abs() const;
    Vec3 normalize() const;
    Vec3 cross(const Vec3& b) const;

    inline Vec3 operator+(const Vec3& b) const {
        return Vec3(x + b.x, y + b.y, z + b.z);
    }

    inline Vec3 operator-(const Vec3& b) const {
        return Vec3(x - b.x, y - b.y, z - b.z);
    }

    inline Vec3 operator*(double b) const {
        return Vec3(b*x, b*y, b*z);
    }

    inline Vec3 operator/(double b) const {
        if (b != 0)
            return Vec3(x/b, y/b, z/b);
        else
            throw std::invalid_argument("dividing vector by zero");
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec3& vec);
};

#endif // VEC3_H
