//
// Created by Cory Kacal on 5/8/24.
//

#include "Quadrilateral.h"

vector<Vertex> Quadrilateral::o_getVertexData()  {
    glm::vec3 normal = calculateNormal(vertex1, vertex2, vertex3);
    glm::vec3 tangent = calculateTangent(vertex1, vertex2, vertex3,
                                          glm::vec2(0,1), glm::vec2(1,1), glm::vec2(0,0));
    return
    {
            {vertex1, normal, tangent, {0,1}, texIndex},
            {vertex2, normal, tangent, {1,1}, texIndex},
            {vertex3, normal, tangent, {0,0}, texIndex},
            {vertex4, normal, tangent, {1,0}, texIndex}
    };
}

vector<Index> Quadrilateral::o_getIndicies()  {
    return
    {
            {0}, {2}, {1},  // First triangle
            {2}, {3}, {1},   // Second triangle
            {0}, {1}, {2},  // First triangle
            {2}, {1}, {3}   // Second triangle
    };
}