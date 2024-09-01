//
// Created by Cory Kacal on 7/28/24.
//

#include "ChunkManager.h"

//Chunk list, with dirty bit
//chunk struct? or chunk class
//make chunkmanager instanced, singleton

struct ChunkData
{
    ushort ChunkSize = 32;
};

struct NoiseData
{
    float Frequency = 0.01f;
    ushort Amplitude = 100;
    int Octaves = 3;
    siv::PerlinNoise::seed_type Seed = 85112826u;
};

static NoiseData s_NoiseData;
static ChunkData s_ChunkData;
static siv::PerlinNoise Perlin;

static vector<Chunk> chunks;
static unordered_map<glm::vec3, Chunk> chunkMap;

void ChunkManager::Init()
{
    Perlin = siv::PerlinNoise{s_NoiseData.Seed};
    chunks = {};
    chunkMap = {};
}

//TODO: add chunk coords
vector<Triangle *> ChunkManager::GetOrCreateChunk(glm::vec3 coords) {
    if(chunkMap.contains(coords)) {
        return chunkMap[coords].triangles;
    }
    vector<Triangle*> triangles = {};
    for(int i = 0; i<s_ChunkData.ChunkSize; i++) {
        for(int j=0; j<s_ChunkData.ChunkSize; j++) {
            for(int k=0; k<s_ChunkData.ChunkSize; k++) {
                glm::vec3 pos = coords * (float)s_ChunkData.ChunkSize + glm::vec3(i, j, k);
                vector<Triangle*> cubeTriangles = GenerateTriangles(pos);
                triangles.insert(triangles.end(), cubeTriangles.begin(), cubeTriangles.end());            }
        }
    }
    //cache
    Chunk newChunk = Chunk{coords, triangles, 1};
    chunks.push_back(newChunk);
    chunkMap[coords] = newChunk;
    return triangles;
}

vector<Triangle*> ChunkManager::GenerateTriangles(glm::vec3 pos) {
    uint8_t cubeIndex = GetEdgeIndex(pos);
    vector<int> vertexIndices = GetTriangles(cubeIndex);
    if (vertexIndices.empty()) return {};

    // Corrected edge midpoints
    array<glm::vec3, 12> edgeMidpoints = {
            pos + glm::vec3(0.5f, 0.0f, 0.0f), // Edge 0:  (0,0,0) - (1,0,0)
            pos + glm::vec3(1.0f, 0.5f, 0.0f), // Edge 1:  (1,0,0) - (1,1,0)
            pos + glm::vec3(0.5f, 1.0f, 0.0f), // Edge 2:  (0,1,0) - (1,1,0)
            pos + glm::vec3(0.0f, 0.5f, 0.0f), // Edge 3:  (0,0,0) - (0,1,0)
            pos + glm::vec3(0.5f, 0.0f, 1.0f), // Edge 4:  (0,0,1) - (1,0,1)
            pos + glm::vec3(1.0f, 0.5f, 1.0f), // Edge 5:  (1,0,1) - (1,1,1)
            pos + glm::vec3(0.5f, 1.0f, 1.0f), // Edge 6:  (0,1,1) - (1,1,1)
            pos + glm::vec3(0.0f, 0.5f, 1.0f), // Edge 7:  (0,0,1) - (0,1,1)
            pos + glm::vec3(0.0f, 0.0f, 0.5f), // Edge 8:  (0,0,0) - (0,0,1)
            pos + glm::vec3(1.0f, 0.0f, 0.5f), // Edge 9:  (1,0,0) - (1,0,1)
            pos + glm::vec3(1.0f, 1.0f, 0.5f), // Edge 10: (1,1,0) - (1,1,1)
            pos + glm::vec3(0.0f, 1.0f, 0.5f)  // Edge 11: (0,1,0) - (0,1,1)
    };

    vector<Triangle *> triangles;
    for (size_t i = 0; i < vertexIndices.size(); i += 3) {
        glm::vec3 v1 = edgeMidpoints[vertexIndices[i]];
        glm::vec3 v2 = edgeMidpoints[vertexIndices[i + 1]];
        glm::vec3 v3 = edgeMidpoints[vertexIndices[i + 2]];
        glm::vec4 color(1.0f); // Set color as needed
        triangles.push_back(new Triangle(v1, v2, v3, color));
    }

    return triangles;
}

uint8_t ChunkManager::GetEdgeIndex(glm::vec3 pos) {
    static const array<array<int, 3>, 8> corners = {{
        {0, 0, 0}, // 0
        {1, 0, 0}, // 1
        {0, 1, 0}, // 2
        {1, 1, 0}, // 3
        {0, 0, 1}, // 4
        {1, 0, 1}, // 5
        {0, 1, 1}, // 6
        {1, 1, 1}  // 7
    }};
    uint8_t edgeIndex = 0;
    for (int i = 0; i < 8; i++) {
        glm::vec3 cornerPos = pos + glm::vec3(corners[i][0], corners[i][1], corners[i][2]);
        float noiseValue = GetNoiseValue(cornerPos);
        edgeIndex |= (noiseValue > 0.0f) << i;
    }
    return edgeIndex;
}

float ChunkManager::GetNoiseValue(glm::vec3 pos) {
    double noise = Perlin.normalizedOctave3D(
            pos.x * s_NoiseData.Frequency,
            pos.y * s_NoiseData.Frequency,
            pos.z * s_NoiseData.Frequency,
            s_NoiseData.Octaves);
    return noise;
}

vector<Chunk> ChunkManager::GetDirtyChunks() {
    vector<Chunk> dirtyChunks = {};
    for(Chunk& chunk : chunks) {
        if(chunk.dirty) {
            dirtyChunks.push_back(chunk);
        }
        chunk.dirty = false;
    }
    return dirtyChunks;
}

void ChunkManager::AddChunk(glm::vec3 coords) {
    GetOrCreateChunk(coords);
}