//
// Created by Cory Kacal on 5/8/24.
//

#ifndef UNTITLED_SQUARE_H
#define UNTITLED_SQUARE_H


#include "Model.h"

class Square : public Model {
public:
    Square(float size, glm::vec3 pos, glm::vec4 color):
            size(size), pos(pos), color(color) {
    }

private:
    float size;
    glm::vec3 pos;
    glm::vec4 color;

    float texIndex;

    vector<Vertex> o_getVertexData()  override;
    vector<Index> o_getIndicies()  override;
};


#endif //UNTITLED_SQUARE_H
