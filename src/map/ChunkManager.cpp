//
// Created by Cory Kacal on 7/28/24.
//

#include "ChunkManager.h"

//Chunk list, with dirty bit
//chunk struct? or chunk class
//make chunkmanager instanced, singleton

struct ChunkData
{
    ushort ChunkSize = 64;
};

struct NoiseData
{
    float Frequency = 0.01f;
    ushort Amplitude = 100;
    int Octaves = 3;
    siv::PerlinNoise::seed_type Seed = 1499926u;
};

static NoiseData s_NoiseData;
static ChunkData s_ChunkData;
static siv::PerlinNoise Perlin;

static vector<Chunk> chunks;
static unordered_map<glm::vec2, Chunk> chunkMap;

void ChunkManager::Init()
{
    Perlin = siv::PerlinNoise{s_NoiseData.Seed};
    chunks = {};
    chunkMap = {};
}

//TODO: add chunk coords
vector<Quadrilateral *> ChunkManager::GetOrCreateChunk(glm::vec2 coords) {
    if(chunkMap.contains(coords)) {
        return chunkMap[coords].quads;
    }
    vector<Quadrilateral*> quads = {};
    for(int i = 0; i<s_ChunkData.ChunkSize; i++) {
        for(int j=0; j<s_ChunkData.ChunkSize; j++) {
            float red = ((float) rand() / (RAND_MAX)) ;
            float green = ((float) rand() / (RAND_MAX)) ;
            float blue = ((float) rand() / (RAND_MAX)) ;

            int chunkXCoord = coords[0] * s_ChunkData.ChunkSize + i;
            int chunkZCoord = coords[1] * s_ChunkData.ChunkSize + j;

            glm::vec4 color = {red,green,blue,1.0f};
            glm::vec3 tlc = GetVertexHeightAt({chunkXCoord,  chunkZCoord});
            glm::vec3 trc = GetVertexHeightAt({chunkXCoord+1, chunkZCoord});
            glm::vec3 blc = GetVertexHeightAt({chunkXCoord, chunkZCoord+1});
            glm::vec3 brc = GetVertexHeightAt({chunkXCoord+1, chunkZCoord+1});

            if(i%2 != j%2) {
                Quadrilateral* quad = new Quadrilateral(tlc, trc, blc, brc, 1.0f);
                quads.push_back(quad);
            } else {
                Quadrilateral* quad = new Quadrilateral(trc, tlc, brc, blc, color);
                quads.push_back(quad);
            }
        }
    }
    Chunk newChunk = Chunk{coords, quads, 1};
    chunks.push_back(newChunk);
    chunkMap[coords] = newChunk;
    return quads;
}

double ChunkManager::GetNoiseAt(glm::vec2 coords) {
    return Perlin.normalizedOctave2D(coords[0] * s_NoiseData.Frequency,
                              coords[1] * s_NoiseData.Frequency,
                              s_NoiseData.Octaves) * s_NoiseData.Amplitude;
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

void ChunkManager::AddChunk(glm::vec2 coords) {
    GetOrCreateChunk(coords);
}

glm::vec3 ChunkManager::GetVertexHeightAt(glm::vec2 coords) {
    const double brc_noise = GetNoiseAt({coords[0], coords[1]});
    return {coords[0],brc_noise,coords[1]};
}
