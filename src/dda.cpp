#include "../include/dda.h"

// ==================== Пересечение с AABB ====================
bool intersectAABB(const Ray& ray, const Vec3& boxMin, const Vec3& boxMax, float& tNear, float& tFar) {
    Vec3 invDir(1.0f/ray.dir.x, 1.0f/ray.dir.y, 1.0f/ray.dir.z);

    float t1 = (boxMin.x - ray.origin.x) * invDir.x;
    float t2 = (boxMax.x - ray.origin.x) * invDir.x;
    float t3 = (boxMin.y - ray.origin.y) * invDir.y;
    float t4 = (boxMax.y - ray.origin.y) * invDir.y;
    float t5 = (boxMin.z - ray.origin.z) * invDir.z;
    float t6 = (boxMax.z - ray.origin.z) * invDir.z;

    tNear = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
    tFar = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

    return tNear <= tFar && tFar > 0;
}

// ==================== Трассировка с поддержкой внешней камеры ====================
bool traceDDA(const VoxelWorld& world, const Ray& ray, float maxDist, 
              Vec3& hitPos, unsigned char& voxelType, Vec3& normal) {

    // Сначала проверяем пересечение с bounding box мира
    Vec3 boxMin(0, 0, 0);
    Vec3 boxMax(world.sizeX, world.sizeY, world.sizeZ);
    float tNear, tFar;

    if (!intersectAABB(ray, boxMin, boxMax, tNear, tFar)) {
        return false;  // Луч не пересекает сцену
    }

    if (tNear > maxDist) return false;

    // Начинаем от точки входа в bounding box
    Vec3 pos = ray.origin + ray.dir * std::max(0.0f, tNear);

    int x = static_cast<int>(std::floor(pos.x));
    int y = static_cast<int>(std::floor(pos.y));
    int z = static_cast<int>(std::floor(pos.z));

    // Убеждаемся что мы внутри границ
    x = std::max(0, std::min(world.sizeX-1, x));
    y = std::max(0, std::min(world.sizeY-1, y));
    z = std::max(0, std::min(world.sizeZ-1, z));

    Vec3 dir = ray.dir;
    int stepX = dir.x > 0 ? 1 : -1;
    int stepY = dir.y > 0 ? 1 : -1;
    int stepZ = dir.z > 0 ? 1 : -1;

    float nextX = stepX > 0 ? x + 1.0f : x;
    float nextY = stepY > 0 ? y + 1.0f : y;
    float nextZ = stepZ > 0 ? z + 1.0f : z;

    float tMaxX = (std::abs(dir.x) > 1e-6f) ? (nextX - pos.x) / dir.x : 1e30f;
    float tMaxY = (std::abs(dir.y) > 1e-6f) ? (nextY - pos.y) / dir.y : 1e30f;
    float tMaxZ = (std::abs(dir.z) > 1e-6f) ? (nextZ - pos.z) / dir.z : 1e30f;

    float tDeltaX = (std::abs(dir.x) > 1e-6f) ? 1.0f / std::abs(dir.x) : 1e30f;
    float tDeltaY = (std::abs(dir.y) > 1e-6f) ? 1.0f / std::abs(dir.y) : 1e30f;
    float tDeltaZ = (std::abs(dir.z) > 1e-6f) ? 1.0f / std::abs(dir.z) : 1e30f;

    float t = tNear;
    int prevX = x, prevY = y, prevZ = z;

    while (t < tFar && t < maxDist) {
        if (!world.inBounds(x, y, z)) break;

        if (world.at(x, y, z) != 0) {
            hitPos = pos + dir * (t - tNear);
            voxelType = world.at(x, y, z);

            if (prevX != x) normal = Vec3(stepX > 0 ? -1.0f : 1.0f, 0, 0);
            else if (prevY != y) normal = Vec3(0, stepY > 0 ? -1.0f : 1.0f, 0);
            else if (prevZ != z) normal = Vec3(0, 0, stepZ > 0 ? -1.0f : 1.0f);
            else normal = Vec3(0, 1, 0);
            return true;
        }

        prevX = x; prevY = y; prevZ = z;

        if (tMaxX < tMaxY) {
            if (tMaxX < tMaxZ) {
                x += stepX;
                t = tMaxX;
                tMaxX += tDeltaX;
            } else {
                z += stepZ;
                t = tMaxZ;
                tMaxZ += tDeltaZ;
            }
        } else {
            if (tMaxY < tMaxZ) {
                y += stepY;
                t = tMaxY;
                tMaxY += tDeltaY;
            } else {
                z += stepZ;
                t = tMaxZ;
                tMaxZ += tDeltaZ;
            }
        }
    }

    return false;
}
