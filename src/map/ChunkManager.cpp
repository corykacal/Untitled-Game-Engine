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
                glm::vec3 pos = coords * static_cast<float>(s_ChunkData.ChunkSize) + glm::vec3(i, j, k);
                vector<Triangle*> cubeTriangles = GenerateTriangles(pos);
                triangles.insert(triangles.end(), cubeTriangles.begin(), cubeTriangles.end());            }
        }
    }
    //cache
    const auto newChunk = Chunk{coords, triangles, true};
    chunks.push_back(newChunk);
    chunkMap[coords] = newChunk;
    return triangles;
}

vector<Triangle*> ChunkManager::GenerateTriangles(const glm::vec3& pos) {
    const auto cornerValues = GetCornerValues(pos);
    const uint8_t cubeIndex = GetEdgeIndex(cornerValues);
    const int edgeMask = edgeTable[cubeIndex];
    if (edgeMask == 0) return {};

    const vector<int> vertexIndices = GetTriangles(cubeIndex);
    if (vertexIndices.empty()) return {};

    array<glm::vec3, 8> cornerPositions{};
    for (int i = 0; i < 8; i++) {
        const auto& corner = GetCorner(i);
        cornerPositions[i] = pos + glm::vec3(corner[0], corner[1], corner[2]);
    }

    array<glm::vec3, 12> vertices{};
    for (int i = 0; i < 12; i++) {
        if (edgeMask & (1 << i)) {
            int v1 = edgeToVertex[i][0];
            int v2 = edgeToVertex[i][1];
            vertices[i] = InterpolateVertex(
                cornerPositions[v1],
                cornerPositions[v2],
                cornerValues[v1],
                cornerValues[v2]
            );
        }
    }

    vector<Triangle*> triangles;
    triangles.reserve(vertexIndices.size()/3);
    for (size_t i = 0; i < vertexIndices.size(); i += 3) {
        triangles.push_back(new Triangle(
            vertices[vertexIndices[i]],
            vertices[vertexIndices[i + 1]],
            vertices[vertexIndices[i + 2]],
            glm::vec4(1.0f)
        ));
    }

    return triangles;
}

vector<float> ChunkManager::GetCornerValues(const glm::vec3 pos) {
    vector<float> cornerValues(8);
    for (int i = 0; i < 8; i++) {
        auto corner = GetCorner(i);
        const glm::vec3 cornerPos = pos + glm::vec3(corner[0], corner[1], corner[2]);
        cornerValues[i] = GetNoiseValue(cornerPos);
    }
    return cornerValues;
}

uint8_t ChunkManager::GetEdgeIndex(const vector<float>& cornerValues) {
    uint8_t edgeIndex = 0;
    for (int i = 0; i < cornerValues.size(); i++) {
        edgeIndex |= (cornerValues[i] > 0.0f) << i;
    }
    return edgeIndex;
}

glm::vec3 ChunkManager::InterpolateVertex(const glm::vec3& pos1, const glm::vec3& pos2, const float val1, const float val2) {
    float t = (0.0f - val1) / (val2 - val1);
    return pos1 + t * (pos2 - pos1);
}

float ChunkManager::GetNoiseValue(const glm::vec3 pos) {
    const double noise = Perlin.normalizedOctave3D(
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

void ChunkManager::AddChunk(const glm::vec3 coords) {
    GetOrCreateChunk(coords);
}