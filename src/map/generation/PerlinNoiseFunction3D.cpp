//
// Created by cory on 11/14/24.
//

#include "PerlinNoiseFunction3D.h"

float PerlinNoiseFunction3D::getValue(const glm::vec3& pos) const {
    return perlin.normalizedOctave3D(
        pos.x * frequency,
        pos.y * frequency,
        pos.z * frequency,
        octaves);
}
