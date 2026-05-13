#include "../include/save_gif.h"
#include <cstdio>
#include <vector>
#include <cmath>

// stb_image_write implementation is already in save_png.cpp

bool save_gif(const int WIDTH, const int HEIGHT, int frames, Vec3 camTarget, 
              Vec3 up, float fov, VoxelWorld world, std::string filename) {
    
    // Create temporary directory for frames
    std::string tempDir = "/tmp/frac_frames";
    std::string mkdirCmd = "mkdir -p " + tempDir;
    (void)system(mkdirCmd.c_str());
    
    float radius = world.sizeX * 1.8f;
    float centerY = world.sizeY / 2.0f;
    
    ProgressUI ui("Rendering GIF Animation");
    
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int frame = 0; frame < frames; frame++) {
        char status[80];
        snprintf(status, sizeof(status), "Frame %d/%d", frame + 1, frames);
        ui.update(status, frame, frames);
        
        // Calculate camera position circling around the fractal
        float angle = (static_cast<float>(frame) / frames) * 2.0f * PI_CONST;
        float camX = camTarget.x + radius * std::cos(angle);
        float camZ = camTarget.z + radius * std::sin(angle);
        float camY = camTarget.y + radius * 0.3f * std::sin(angle * 2.0f);
        
        Vec3 camPos(camX, camY, camZ);
        Vec3 forward = (camTarget - camPos).normalize();
        Vec3 right = forward.cross(up).normalize();
        Vec3 camUp = right.cross(forward).normalize();
        
        float aspect = static_cast<float>(WIDTH) / HEIGHT;
        float halfHeight = std::tan(fov * 0.5f);
        float halfWidth = aspect * halfHeight;
        
        std::vector<unsigned char> image(WIDTH * HEIGHT * 3, 0);
        
        for (int py = 0; py < HEIGHT; py++) {
            for (int px = 0; px < WIDTH; px++) {
                float u = (2.0f * px / WIDTH - 1.0f) * halfWidth;
                float v = (1.0f - 2.0f * py / HEIGHT) * halfHeight;
                
                Vec3 rayDir = (forward + right * u + camUp * v).normalize();
                Ray ray(camPos, rayDir);
                
                Vec3 hitPos, normal;
                unsigned char voxelType;
                
                int idx = (py * WIDTH + px) * 3;
                
                if (traceDDA(world, ray, 10000.0f, hitPos, voxelType, normal)) {
                    Color baseColor = getFractalColor(hitPos.x, hitPos.y, hitPos.z, world.sizeX, 3.0f);
                    Color finalColor = applyLighting(baseColor, normal);
                    
                    image[idx + 0] = finalColor.r;
                    image[idx + 1] = finalColor.g;
                    image[idx + 2] = finalColor.b;
                } else {
                    float t = (rayDir.y + 1.0f) * 0.5f;
                    unsigned char r = 20 + 30 * t;
                    unsigned char g = 10 + 20 * t;
                    unsigned char b = 40 + 40 * t;
                    
                    image[idx + 0] = r;
                    image[idx + 1] = g;
                    image[idx + 2] = b;
                }
            }
        }
        
        // Save frame as PNG using external function declaration
        char frameFilename[256];
        snprintf(frameFilename, sizeof(frameFilename), "%s/frame_%04d.png", tempDir.c_str(), frame);
        stbi_write_png(frameFilename, WIDTH, HEIGHT, 3, image.data(), WIDTH * 3);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    
    char message[60];
    snprintf(message, sizeof(message), "Rendered in %ld seconds", duration.count());
    ui.update(message, frames, frames);
    ui.finish("Creating GIF with ffmpeg...");
    
    // Use ffmpeg to create GIF from frames
    std::string gifCmd = "ffmpeg -y -framerate 15 -i " + tempDir + "/frame_%04d.png -vf \"split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse\" -loop 0 " + filename + " 2>/dev/null";
    int result = system(gifCmd.c_str());
    
    // Cleanup temporary files
    std::string cleanupCmd = "rm -rf " + tempDir;
    (void)system(cleanupCmd.c_str());
    
    return (result == 0);
}
