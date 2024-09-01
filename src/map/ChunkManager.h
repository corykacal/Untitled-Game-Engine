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
#include "../models/Cube.h"

#ifndef UNTITLED_CHUNKMANAGER_H
#define UNTITLED_CHUNKMANAGER_H

struct Chunk
{
    glm::vec2 coords;
    vector<Cube*> quads;
    bool dirty;
};

class ChunkManager {
public:
    static void Init();
    static vector<Cube *> GetOrCreateChunk(glm::vec3 coords);

    static vector<Chunk> GetDirtyChunks();
    static void AddChunk(glm::vec3 coords);
private:
    static bool ObjectPresentAt(glm::vec3 coords);
    static glm::vec3 GetVertexHeightAt(glm::vec3 coords);
};


#endif //UNTITLED_CHUNKMANAGER_H
