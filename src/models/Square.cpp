//
// Created by Cory Kacal on 5/8/24.
//

#include "Square.h"

vector<Vertex> Square::o_getVertexData()  {
    glm::vec3 normal = glm::vec3(0.0f, 1.0f, 0.0f);

    // Tangent along the X-axis
    glm::vec3 tangent = glm::vec3(1.0f, 0.0f, 0.0f);
    vector<Vertex> things = {
            {glm::vec3(pos[0]-size/2, pos[1], pos[2]-size/2), normal, tangent, {0,1}, texIndex},  // Top-left
            {glm::vec3(pos[0]+size/2, pos[1], pos[2]-size/2), normal, tangent, {1,1}, texIndex},  // Top-right
            {glm::vec3(pos[0]-size/2, pos[1], pos[2]+size/2), normal, tangent, {0,0}, texIndex},  // Bottom-left
            {glm::vec3(pos[0]+size/2, pos[1], pos[2]+size/2), normal, tangent, {1,0}, texIndex}   // Bottom-right
    };
    return things;
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
