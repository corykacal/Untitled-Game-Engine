//
// Created by cory on 11/14/24.
//

#include "TerrainMesh.h"
#include <algorithm>

void TerrainMesh::add(std::shared_ptr<NoiseFunction> noise) {
    operations.push_back({noise, true});
}

void TerrainMesh::subtract(std::shared_ptr<NoiseFunction> noise) {
    operations.push_back({noise, false});
}

float TerrainMesh::getValue(const glm::vec3& pos) const {
    float value = 0.0f;
    for(const auto& op : operations) {
        float noiseValue = op.noise->getValue(pos);
        if(op.isAdditive) {
            value += noiseValue;
        } else {
            value -= noiseValue;
        }
    }
    return value / operations.size();
}