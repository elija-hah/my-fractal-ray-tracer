#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

class Camera {
public:
    Vec3 origin;
    Vec3 target;
    double fov;
    double aspect_ratio;
    Vec3 forward;
    Vec3 right;
    Vec3 up;
    
    Camera(const Vec3& _origin, const Vec3& _target, double _fov, double _aspect_ratio, const Vec3& _up);
    
    Ray cast(double u, double v) const;
};

#endif // CAMERA_H
