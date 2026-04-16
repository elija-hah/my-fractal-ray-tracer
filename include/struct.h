#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>
#include <cmath>

const float PI_CONST = 3.14159f;

struct VoxelWorld {
    std::vector<unsigned char> voxels;
    int sizeX, sizeY, sizeZ;

    VoxelWorld(int sx, int sy, int sz) : sizeX(sx), sizeY(sy), sizeZ(sz) {
        voxels.resize(sx * sy * sz, 0);
    }

    unsigned char& at(int x, int y, int z) {
        return voxels[x + y * sizeX + z * sizeX * sizeY];
    }

    unsigned char at(int x, int y, int z) const {
        return voxels[x + y * sizeX + z * sizeX * sizeY];
    }

    bool inBounds(int x, int y, int z) const {
        return x >= 0 && x < sizeX && y >= 0 && y < sizeY && z >= 0 && z < sizeZ;
    }
};

struct Vec3 {
    float x, y, z;
    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& o) const { return {x+o.x, y+o.y, z+o.z}; }
    Vec3 operator-(const Vec3& o) const { return {x-o.x, y-o.y, z-o.z}; }
    Vec3 operator*(float s) const { return {x*s, y*s, z*s}; }
    float dot(const Vec3& o) const { return x*o.x + y*o.y + z*o.z; }
    float length() const { return std::sqrt(x*x + y*y + z*z); }
    Vec3 normalize() const {
        float len = length();
        if (len < 1e-6f) return *this;
        return {x/len, y/len, z/len};
    }
    Vec3 cross(const Vec3& o) const {
        return {y*o.z - z*o.y, z*o.x - x*o.z, x*o.y - y*o.x};
    }
};

struct Ray {
    Vec3 origin, dir;
    Ray(const Vec3& o, const Vec3& d) : origin(o), dir(d.normalize()) {}
};

struct Color {
    unsigned char r, g, b;
    Color() : r(0), g(0), b(0) {}
    Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}
};

#endif
