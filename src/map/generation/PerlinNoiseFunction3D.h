//
// Created by cory on 11/14/24.
//

#ifndef PERLINNOISEFUNCTION3D_H
#define PERLINNOISEFUNCTION3D_H

#pragma once
#include "NoiseFunction.h"

class PerlinNoiseFunction3D : public NoiseFunction {
public:
    PerlinNoiseFunction3D(float freq, ushort amp, int oct, siv::PerlinNoise::seed_type s)
        : NoiseFunction(freq, amp, oct, s) {}
    float getValue(const glm::vec3& pos) const override;
};

#endif //PERLINNOISEFUNCTION3D_H
