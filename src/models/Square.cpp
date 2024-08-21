//
// Created by Cory Kacal on 5/8/24.
//

#include "Square.h"

vector<Vertex> Square::o_getVertexData()  {
    return {
            // Positions                           // Colors
            {glm::vec3(pos[0]-size/2, pos[1]+size/2, pos[2]), color, {0,0,0}, {0,1}, texIndex},  // Top-left
            {glm::vec3(pos[0]+size/2, pos[1]+size/2, pos[2]), color, {0,0,0}, {1,1}, texIndex},  // Top-right
            {glm::vec3(pos[0]-size/2, pos[1]-size/2, pos[2]), color, {0,0,0}, {0,0}, texIndex},  // Bottom-left
            {glm::vec3(pos[0]+size/2, pos[1]-size/2, pos[2]), color, {0,0,0}, {1,0}, texIndex}   // Bottom-right
    };
}

vector<Index> Square::o_getIndicies()  {
    if(doubleSided)
        return {{0}, {2}, {1},
                {2}, {3}, {1},
                {2}, {0}, {1},
                {3}, {2}, {1}};
    return {{0}, {2}, {1},
            {2}, {3}, {1}};
}
