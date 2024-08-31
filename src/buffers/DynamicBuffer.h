#pragma once

#include "../models/Model.h"
#include "map"
#include <stack>
#include "DynamicIndexBuffer.h"
#include "DynamicVertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"


struct ModelBufferEntry
{
    vector<IndexTriangle*> triangles;
    vector<unsigned int> vertexIndices;
};

class DynamicBuffer
{
    private:
        //need????
        unsigned int m_MaxSize;
        map<unsigned int, ModelBufferEntry> m_ModelToIndices;

        Shader m_shader;
        DynamicVertexBuffer m_dynamicVB;
        VertexArray m_vertexArray;
        DynamicIndexBuffer m_dynamicIB;

    public:
        explicit DynamicBuffer(unsigned int size, VertexBufferLayout layout,
                               const std::string& fragmentShader, const std::string& vertexShader);
        ~DynamicBuffer();

        void Bind() const;
        void Unbind() const;
        void Draw() const;
        Shader GetShader();

        void AddModel(Model* model);
        void DeleteModel(Model* model);
};
