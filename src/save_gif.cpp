#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#define GIF_IMPLEMENTATION
#include "../include/gif.h"

#include "../include/save_gif.h"

bool renderPngsToGif(const std::string& inputFolder,
                     const std::string& outputGifPath,
                     int nFrames, int delayCs = 10) {
    GifWriter gifWriter;
    bool gifStarted = false;
    int width = 0, height = 0;

    for (int i = 0; i < nFrames; ++i) {
        std::string pngPath = (std::filesystem::path(inputFolder) / (std::to_string(i) + ".png")).string();

        int w, h, channels;
        // req_comp = 4 принудительно возвращает RGBA
        unsigned char* data = stbi_load(pngPath.c_str(), &w, &h, &channels, 4);
        if (!data) {
            std::cerr << "[ERROR] Не удалось загрузить: " << pngPath << "\n";
            return false;
        }

        if (!gifStarted) {
            width = w;
            height = h;
            if (!GifBegin(&gifWriter, outputGifPath.c_str(), width, height, delayCs)) {
                std::cerr << "[ERROR] Не удалось инициализировать GIF\n";
                stbi_image_free(data);
                return false;
            }
            gifStarted = true;
        } else {
            if (w != width || h != height) {
                std::cerr << "[ERROR] Размеры кадра не совпадают: " << pngPath << "\n";
                stbi_image_free(data);
                GifEnd(&gifWriter);
                return false;
            }
        }

        if (!GifWriteFrame(&gifWriter, data, width, height, delayCs)) {
            std::cerr << "[ERROR] Ошибка записи кадра " << i << "\n";
            stbi_image_free(data);
            GifEnd(&gifWriter);
            return false;
        }

        stbi_image_free(data);
    }

    if (gifStarted) {
        GifEnd(&gifWriter);
    }
    return true;
}

bool save_gif(const int WIDTH, const int HEIGHT, const int nFrames, Vec3 up, float fov, VoxelWorld world, std::string filename) {
    std::filesystem::create_directory("tmp");
    int VOX_SIZE = world.sizeX;
    for(int i=0; i<nFrames; ++i) {
        Vec3 camPos(VOX_SIZE * 2.5f * cos(2.0f * M_PI * i / nFrames) + VOX_SIZE/2.0f, VOX_SIZE * 1.2f, VOX_SIZE * 2.5f * sin(2.0f * M_PI * i / nFrames) + VOX_SIZE/2.0f);
	Vec3 camTarget(VOX_SIZE/2.0f, VOX_SIZE/2.0f, VOX_SIZE/2.0f);
	
	save_png(WIDTH, HEIGHT, camPos, camTarget, up, fov, world, "tmp/" + std::to_string(i) + ".png");	
    }
    
    int delayCs = 500 / nFrames;
    bool res = renderPngsToGif("tmp", filename, nFrames, delayCs);
    std::filesystem::remove_all("tmp");
    return res;
}


