//
// Created by Cory Kacal on 5/8/24.
//

#include "Quadrilateral.h"

vector<Vertex> Quadrilateral::o_getVertexData()  {
    return
    {
            {vertex1, color, {0,1}, texIndex},
            {vertex2, color, {1,0}, texIndex},
            {vertex3, color, {0,0}, texIndex},
            {vertex4, color, {1,1}, texIndex}
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