//
// Created by cory on 11/14/24.
//

#ifndef PERLINNOISEFUNCTION2D_H
#define PERLINNOISEFUNCTION2D_H

#pragma once
#include "NoiseFunction.h"

class PerlinNoiseFunction2D : public NoiseFunction {
public:
    PerlinNoiseFunction2D(float freq, ushort amp, int oct, siv::PerlinNoise::seed_type s)
        : NoiseFunction(freq, amp, oct, s) {}
    float getValue(const glm::vec3& pos) const override;
};

#endif //PERLINNOISEFUNCTION2D_H
