//
// Created by Cory Kacal on 5/8/24.
//

#ifndef UNTITLED_QUADRILATERAL_H
#define UNTITLED_QUADRILATERAL_H


#include "Model.h"

class Quadrilateral : public Model {
public:

    Quadrilateral(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3, glm::vec3 vertex4, float texIndex) :
    vertex1(vertex1), vertex2(vertex2), vertex3(vertex3), vertex4(vertex4), texIndex(texIndex)
    {
        Quadrilateral::color = {1.0f, 1.0f, 1.0f, 1.0f};
    }

    Quadrilateral(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3, glm::vec3 vertex4, glm::vec4 color) :
            vertex1(vertex1), vertex2(vertex2), vertex3(vertex3), vertex4(vertex4), color(color)
    {
        texIndex = 0.0f;
    }

private:
    glm::vec3 vertex1;
    glm::vec3 vertex2;
    glm::vec3 vertex3;
    glm::vec3 vertex4;

    float texIndex;
    glm::vec4 color;

    vector<Vertex> o_getVertexData()  override;
    vector<Index> o_getIndicies()  override;
};


#endif //UNTITLED_QUADRILATERAL_H
