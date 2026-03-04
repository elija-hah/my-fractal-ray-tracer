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
    
    Vec3 operator+(const Vec3& b) const;
    Vec3 operator-(const Vec3& b) const;
    Vec3 operator*(double b) const;
    Vec3 operator/(double b) const;
    
    friend std::ostream& operator<<(std::ostream& os, const Vec3& vec);
};

#endif // VEC3_H
