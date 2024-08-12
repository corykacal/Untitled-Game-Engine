//
// Created by Cory Kacal on 6/30/24.
//

#ifndef UNTITLED_CUBE_H
#define UNTITLED_CUBE_H


#include "Model.h"

class Cube : public Model
{
public:
    Cube(float size, glm::vec3 pos, glm::vec4 color) :
    size(size), pos(pos), color(color)
    {
        texIndex = 0.0f;
    }

    Cube(float size, glm::vec3 pos, float texIndex) :
    size(size), pos(pos), texIndex(texIndex)
    {
        color = {1.0f, 1.0f, 1.0f, 1.0f};
    }

private:
    float size;
    glm::vec3 pos;
    glm::vec4 color;
    float texIndex;

    vector<Vertex> o_getVertexData()  override;
    vector<Index> o_getIndicies()  override;
};


#endif //UNTITLED_CUBE_H
