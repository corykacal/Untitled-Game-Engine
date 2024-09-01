//
// Created by Cory Kacal on 7/28/24.
//

#include "ChunkManager.h"

//Chunk list, with dirty bit
//chunk struct? or chunk class
//make chunkmanager instanced, singleton

struct ChunkData
{
    ushort ChunkSize = 20;
};

struct NoiseData
{
    float Frequency = 0.01f;
    ushort Amplitude = 100;
    int Octaves = 3;
    siv::PerlinNoise::seed_type Seed = 2592826u;
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
vector<Cube *> ChunkManager::GetOrCreateChunk(glm::vec3 coords) {
    if(chunkMap.contains(coords)) {
        return chunkMap[coords].quads;
    }
    vector<Cube*> cubes = {};
    for(int i = 0; i<s_ChunkData.ChunkSize; i++) {
        for(int j=0; j<s_ChunkData.ChunkSize; j++) {
            for(int k=0; k<s_ChunkData.ChunkSize; k++) {
                float red = ((float) rand() / (RAND_MAX)) ;
                float green = ((float) rand() / (RAND_MAX)) ;
                float blue = ((float) rand() / (RAND_MAX)) ;

                int chunkXCoord = coords[0] * s_ChunkData.ChunkSize + i;
                int chunkZCoord = coords[1] * s_ChunkData.ChunkSize + j;
                int chunkYCoord = coords[2] * s_ChunkData.ChunkSize + k;

                glm::vec3 pos = {chunkXCoord, chunkZCoord, chunkYCoord};
                bool thingAtCoord = ObjectPresentAt(pos);
                if(thingAtCoord)
                {
                    Cube* cube = new Cube(1.0f, pos, 0.0f);
                    cubes.push_back(cube);
                }
            }
        }
    }
    Chunk newChunk = Chunk{coords, cubes, 1};
    chunks.push_back(newChunk);
    chunkMap[coords] = newChunk;
    return cubes;
}

bool ChunkManager::ObjectPresentAt(glm::vec3 coords) {
    double noise = Perlin.normalizedOctave3D(coords[0] * s_NoiseData.Frequency,
                              coords[1] * s_NoiseData.Frequency,
                              coords[2] * s_NoiseData.Frequency,
                              s_NoiseData.Octaves);
    return noise > 0.0;
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