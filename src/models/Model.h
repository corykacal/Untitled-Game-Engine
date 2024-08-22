//
// Created by Cory Kacal on 5/8/24.
//
#define GLM_ENABLE_EXPERIMENTAL
#include "../../vendor/glm/gtx/string_cast.hpp"

#include <vector>
#include <GL/glew.h>
#include <iostream>

#include "../../vendor/glm/vec4.hpp"
#include "../../vendor/glm/vec3.hpp"
#include "../../vendor/glm/vec2.hpp"
#include "../util/ModelIdManager.h"
#include "../../vendor/glm/gtc/matrix_transform.hpp"

#ifndef UNTITLED_SHAPE_H
#define UNTITLED_SHAPE_H

using namespace std;

//make vertex buffer auto build off this
struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 Tangent;
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

protected:
    glm::vec3 calculateNormal(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3) {
        glm::vec3 edge1 = v2 - v1;
        glm::vec3 edge2 = v3 - v1;

        glm::vec3 normal(
                edge2.y * edge1.z - edge2.z * edge1.y,
                edge2.z * edge1.x - edge2.x * edge1.z,
                edge2.x * edge1.y - edge2.y * edge1.x
        );

        return glm::normalize(normal);
    }

    glm::vec3 calculateTangent(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3,
                                              const glm::vec2& uv1, const glm::vec2& uv2, const glm::vec2& uv3) {
        glm::vec3 edge1 = v2 - v1;
        glm::vec3 edge2 = v3 - v1;
        glm::vec2 deltaUV1 = uv2 - uv1;
        glm::vec2 deltaUV2 = uv3 - uv1;

        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        glm::vec3 tangent;
        tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

        return glm::normalize(tangent);
    }
};


#endif //UNTITLED_SHAPE_H
