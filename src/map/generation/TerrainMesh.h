//
// Created by cory on 11/14/24.
//

#ifndef TERRAINMESH_H
#define TERRAINMESH_H

#pragma once
#include "NoiseFunction.h"
#include <vector>
#include <memory>

class TerrainMesh {
private:

    struct Operation {
        std::shared_ptr<NoiseFunction> noise;
        bool isAdditive;
    };
    std::vector<Operation> operations;

public:
    void add(std::shared_ptr<NoiseFunction> noise);
    void subtract(std::shared_ptr<NoiseFunction> noise);
    float getValue(const glm::vec3& pos) const;
};

#endif //TERRAINMESH_H
