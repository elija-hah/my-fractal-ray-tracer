#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#include "../include/save_png.h"

void save_png(const int WIDTH, const int HEIGHT, Vec3 camPos, Vec3 camTarget, Vec3 up, float fov, VoxelWorld world){
    Vec3 forward = (camTarget - camPos).normalize();
    Vec3 right = forward.cross(up).normalize();
    Vec3 camUp = right.cross(forward).normalize();

    float aspect = static_cast<float>(WIDTH) / HEIGHT;
    float halfHeight = std::tan(fov * 0.5f);
    float halfWidth = aspect * halfHeight;

    std::vector<unsigned char> image(WIDTH * HEIGHT * 3, 0);

    std::cout << "Rendering " << WIDTH << "x" << HEIGHT << "...\n";
    auto start = std::chrono::high_resolution_clock::now();

    for (int py = 0; py < HEIGHT; py++) {
        for (int px = 0; px < WIDTH; px++) {
            float u = (2.0f * px / WIDTH - 1.0f) * halfWidth;
            float v = (1.0f - 2.0f * py / HEIGHT) * halfHeight;

            Vec3 rayDir = (forward + right * u + camUp * v).normalize();
            Ray ray(camPos, rayDir);

            Vec3 hitPos, normal;
            unsigned char voxelType;

            int idx = (py * WIDTH + px) * 3;

            if (traceDDA(world, ray, 1000.0f, hitPos, voxelType, normal)) {
                int hx = static_cast<int>(std::floor(hitPos.x));
                int hy = static_cast<int>(std::floor(hitPos.y));
                int hz = static_cast<int>(std::floor(hitPos.z));

                Color baseColor = getFractalColor(hx, hy, hz, world);
                Color finalColor = applyLighting(baseColor, normal);

                image[idx + 0] = finalColor.r;
                image[idx + 1] = finalColor.g;
                image[idx + 2] = finalColor.b;
            } else {
		    // Космический фон
		    float t = (rayDir.y + 1.0f) * 0.5f;

		    // Градиент от тёмно-синего к фиолетовому
		    unsigned char r = 20 + 30 * t;
		    unsigned char g = 10 + 20 * t;
		    unsigned char b = 40 + 40 * t;

		    image[idx + 0] = r;
		    image[idx + 1] = g;
		    image[idx + 2] = b;
	    }
        }
        if (py % 64 == 0) {
            std::cout << "  Row " << py << "/" << HEIGHT << "\n";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << "Rendered in " << duration.count() << " seconds\n";

    std::cout << "Saving mandelbulb.png...\n";
    if (stbi_write_png("mandelbulb.png", WIDTH, HEIGHT, 3, image.data(), WIDTH * 3)) {
        std::cout << "Image saved successfully!\n";
    } else {
        std::cerr << "Failed to save image!\n";
    }
}

