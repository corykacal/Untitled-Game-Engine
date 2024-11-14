//
// Created by cory on 11/14/24.
//

#include "PerlinNoiseFunction2D.h"

float PerlinNoiseFunction2D::getValue(const glm::vec3& pos) const {
    float height = perlin.normalizedOctave2D(pos.x * frequency, pos.z * frequency, octaves) * amplitude;
    return height - pos.y;
}