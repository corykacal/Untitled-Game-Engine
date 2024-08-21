//
// Created by Cory Kacal on 8/20/24.
//

#include "Model.h"

#ifndef UNTITLED_OBJMODEL_H
#define UNTITLED_OBJMODEL_H
class OBJModel : public Model {
public:
    OBJModel(const std::vector<Vertex>& vertices, const std::vector<Index>& indices)
            : m_Vertices(vertices), m_Indices(indices) {}

private:
    std::vector<Vertex> o_getVertexData() override { return m_Vertices; }
    std::vector<Index> o_getIndicies() override { return m_Indices; }

    std::vector<Vertex> m_Vertices;
    std::vector<Index> m_Indices;
};

#endif //UNTITLED_OBJMODEL_H
