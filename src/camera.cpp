#include "camera.h"
#include <cmath>

Camera::Camera(const Vec3& _origin, const Vec3& _target, const Vec3& _up,
               double _fov, double _aspect_ratio)
    : origin(_origin), target(_target), fov(_fov), aspect_ratio(_aspect_ratio),
      forward((_target - _origin).normalize()),
      right(forward.cross(_up).normalize()), 
      up(right.cross(forward).normalize()) {}

Ray Camera::cast(double u, double v) const {
    const double pi = 3.14159265358979323846;
    Vec3 dir = forward + right * u * std::tan(fov * pi / 360.0) 
                       + up * v * std::tan(fov * pi / 360.0) * aspect_ratio;
    return Ray(origin, dir);
}
