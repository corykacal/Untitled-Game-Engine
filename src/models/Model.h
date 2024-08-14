//
// Created by Cory Kacal on 5/8/24.
//
#include <vector>
#include "../../vendor/glm/vec4.hpp"
#include "../../vendor/glm/vec3.hpp"
#include "../../vendor/glm/vec2.hpp"
#include "../util/ModelIdManager.h"
#include <GL/glew.h>

#ifndef UNTITLED_SHAPE_H
#define UNTITLED_SHAPE_H

using namespace std;

//make vertex buffer auto build off this
struct Vertex
{
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoords;
    float TexIndex;
};

struct Index
{
    GLuint Position;
};

class Model {
public:
    vector<Vertex> GetVertexData() { return o_getVertexData(); };
    vector<Index> getIndicies() { return o_getIndicies(); };

    unsigned int getModelID() { return m_ModelID; };

    Model(): m_ModelID(ModelIdManager::getId()) {}
    virtual ~Model() = default;

private:
    virtual vector<Vertex> o_getVertexData() = 0;
    virtual vector<Index> o_getIndicies() = 0;
    unsigned int m_ModelID;
};


#endif //UNTITLED_SHAPE_H
