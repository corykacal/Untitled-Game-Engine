//
// Created by Cory Kacal on 7/28/24.
//
#include <GL/glew.h>
#include "../models/Model.h"
#include "../models/Quadrilateral.h"
#include "../debug/Debug.h"
#include <iostream>
#include "../../vendor/perlin/PerlinNoise.hpp"
#include "../../vendor/glm/vec2.hpp"
#include <unordered_map>

#define GLM_ENABLE_EXPERIMENTAL
#include "../../vendor/glm/gtx/hash.hpp"

#ifndef UNTITLED_CHUNKMANAGER_H
#define UNTITLED_CHUNKMANAGER_H

struct Chunk
{
    glm::vec2 coords;
    vector<Quadrilateral*> quads;
    bool dirty;
};

class ChunkManager {
public:
    static void Init();
    static vector<Quadrilateral *> GetOrCreateChunk(glm::vec2 coords);

    static vector<Chunk> GetDirtyChunks();
    static void AddChunk(glm::vec2 coords);
private:
    static double GetNoiseAt(glm::vec2 coords);
    static glm::vec3 GetVertexHeightAt(glm::vec2 coords);
};


#endif //UNTITLED_CHUNKMANAGER_H
