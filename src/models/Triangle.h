//
// Created by Cory Kacal on 8/10/24.
//

#ifndef UNTITLED_TRIANGLE_H
#define UNTITLED_TRIANGLE_H

#include "Model.h"

class Triangle : public Model {
public:
    Triangle(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3, glm::vec4 color)
    : Model()
    {
        verticies = {
                {vertex1, color, {0,0,0}, {0, 0}, 0},
                {vertex2, color, {0,0,0}, {0, 1}, 0},
                {vertex3, color, {0,0,0}, {1, 0}, 0}
            };
        doubleSided = false;
    }

private:
    vector<Vertex> verticies;
    bool doubleSided;

    vector<Vertex> o_getVertexData() override;
    vector<Index> o_getIndicies() override;
};


#endif //UNTITLED_TRIANGLE_H
