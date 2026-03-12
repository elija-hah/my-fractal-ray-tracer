#include <iostream>
#include "camera.h"

int main() {
    Vec3 up = Vec3(0., 0., 1.);
    Vec3 origin = Vec3(0., 0., 0.);
    Vec3 target = Vec3(10., 0., 3.);

    Camera cam = Camera(origin, target, 160, 2., up);

    std::cout << cam.up << std::endl;
    std::cout << cam.forward << std::endl;
    std::cout << cam.right << std::endl;
    
    return 0;
}
