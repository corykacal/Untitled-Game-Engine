//
// Created by Cory Kacal on 8/10/24.
//

#include "Triangle.h"


vector<Vertex> Triangle::o_getVertexData() {
    return verticies;
}

vector<Index> Triangle::o_getIndicies() {
    if (doubleSided)
        return {{0},{1},{2},
                {1},{0},{2}};
    return {{0},{1},{2}};
}
