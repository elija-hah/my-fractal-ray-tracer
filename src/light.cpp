#include "../include/light.h"

Color applyLighting(const Color& baseColor, const Vec3& normal) {
    const Vec3 lightDir1 = Vec3(-0.5f, 0.8f, -0.3f).normalize();  // Основной свет
    const Vec3 lightDir2 = Vec3(-0.5f, -0.3f, 0.8f).normalize();  // Заполняющий свет

    float ambient = 0.4f;
    float diff1 = std::max(0.0f, normal.dot(lightDir1));
    float diff2 = std::max(0.0f, normal.dot(lightDir2)) * 0.5f;  // второй источник слабее

    float lighting = ambient + 0.8f * diff1 + diff2;
    lighting = std::min(1.4f, std::max(0.6f, lighting));

    return Color(
        static_cast<unsigned char>(std::min(255.0f, baseColor.r * lighting)),
        static_cast<unsigned char>(std::min(255.0f, baseColor.g * lighting)),
        static_cast<unsigned char>(std::min(255.0f, baseColor.b * lighting))
    );
}
