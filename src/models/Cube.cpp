//
// Created by Cory Kacal on 6/30/24.
//

#include "Cube.h"

vector<Vertex> Cube::o_getVertexData()
{
    return
    {
            { {pos.x - size, pos.y - size, pos.z - size}, {color.r, color.g, color.b, color.a}, {0,0,0}, {0.0f, 0.0f}, texIndex},
            { {pos.x - size, pos.y - size, pos.z + size}, {color.r, color.g, color.b, color.a}, {0,0,0}, {1.0f, 0.0f}, texIndex},
            { {pos.x - size, pos.y + size, pos.z + size}, {color.r, color.g, color.b, color.a}, {0,0,0}, {1.0f, 1.0f}, texIndex},
            { {pos.x - size, pos.y + size, pos.z - size}, {color.r, color.g, color.b, color.a}, {0,0,0}, {0.0f, 1.0f}, texIndex},
            { {pos.x + size, pos.y - size, pos.z - size}, {color.r, color.g, color.b, color.a}, {0,0,0}, {1.0f, 0.0f}, texIndex},
            { {pos.x + size, pos.y - size, pos.z + size}, {color.r, color.g, color.b, color.a}, {0,0,0}, {0.0f, 0.0f}, texIndex},
            { {pos.x + size, pos.y + size, pos.z + size}, {color.r, color.g, color.b, color.a}, {0,0,0}, {0.0f, 1.0f}, texIndex},
            { {pos.x + size, pos.y + size, pos.z - size}, {color.r, color.g, color.b, color.a}, {0,0,0}, {1.0f, 1.0f}, texIndex}    };
}

vector<Index> Cube::o_getIndicies()
{
    return
    {
            {0}, {1}, {2},  {0}, {2}, {3},  // Left face
            {4}, {7}, {6},  {4}, {6}, {5},  // Right face
            {0}, {4}, {5},  {0}, {5}, {1},  // Bottom face
            {2}, {6}, {7},  {2}, {7}, {3},  // Top face
            {0}, {3}, {7},  {0}, {7}, {4},  // Back face
            {1}, {5}, {6},  {1}, {6}, {2}   // Front face
    };
}
