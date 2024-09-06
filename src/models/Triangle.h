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
        glm::vec3 normal = calculateNormal(vertex1, vertex2, vertex3);
        glm::vec3 tangent = calculateTangent(vertex1, vertex2, vertex3, {0,0}, {0,1}, {1,0});
        verticies = {
                {vertex1, normal, tangent, {0, 0}, 1},
                {vertex2, normal, tangent, {0, 1}, 1},
                {vertex3, normal, tangent, {1, 0}, 1}
            };
        doubleSided = true;
    }

private:
    vector<Vertex> verticies;
    bool doubleSided;

    vector<Vertex> o_getVertexData() override;
    vector<Index> o_getIndicies() override;
};


#endif //UNTITLED_TRIANGLE_H
