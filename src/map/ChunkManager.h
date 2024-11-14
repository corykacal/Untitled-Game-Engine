//
// Created by Cory Kacal on 7/28/24.
//
#include <GL/glew.h>
#include "../models/Model.h"
#include "../models/Triangle.h"
#include "../debug/Debug.h"
#include <iostream>
#include "../../vendor/perlin/PerlinNoise.hpp"
#include "../../vendor/glm/vec2.hpp"
#include <unordered_map>
#include "MarchingCubesLookupTable.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "../../vendor/glm/gtx/hash.hpp"

#ifndef UNTITLED_CHUNKMANAGER_H
#define UNTITLED_CHUNKMANAGER_H

struct Chunk
{
    glm::vec2 coords;
    vector<Triangle*> triangles;
    bool dirty;
};

struct GridCell
{
    std::array<glm::vec3, 8> position;
    std::array<float, 8> value;
};

class ChunkManager {
public:
    static void Init();
    static vector<Triangle *> GetOrCreateChunk(glm::vec3 coords);

    static vector<Chunk> GetDirtyChunks();
    static void AddChunk(glm::vec3 coords);
private:
    static vector<float> GetCornerValues(glm::vec3 pos);
    static uint8_t GetEdgeIndex(const vector<float>& cornerValues);
    static glm::vec3 InterpolateVertex(const glm::vec3& pos1, const glm::vec3& pos2, float val1, float val2);
    static float GetNoiseValue(glm::vec3 pos);
    static vector<Triangle*> GenerateTriangles(const glm::vec3& pos);
};


#endif //UNTITLED_CHUNKMANAGER_H
