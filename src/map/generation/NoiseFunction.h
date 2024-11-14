//
// Created by cory on 11/14/24.
//

#ifndef NOISEFUNCTION_H
#define NOISEFUNCTION_H

#pragma once
#include "../../../vendor/glm/vec3.hpp"
#include "../../../vendor/perlin/PerlinNoise.hpp"

class NoiseFunction {
private:
    siv::PerlinNoise::seed_type seed;
protected:
    float frequency;
    ushort amplitude;
    int octaves;
    siv::PerlinNoise perlin;

public:
    NoiseFunction(float freq, ushort amp, int oct, siv::PerlinNoise::seed_type s)
        : frequency(freq), amplitude(amp), octaves(oct), perlin(siv::PerlinNoise{s}) {}
    virtual float getValue(const glm::vec3& pos) const = 0;
    virtual ~NoiseFunction() = default;
};


#endif //NOISEFUNCTION_H
