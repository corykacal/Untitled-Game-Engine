#pragma once

#include "../models/Model.h"
#include "map"
#include <stack>
#include "DynamicIndexBuffer.h"
#include "DynamicVertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"


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

        DynamicVertexBuffer m_dynamicVB;
        VertexArray m_vertexArray;
        DynamicIndexBuffer m_dynamicIB;



    public:
        explicit DynamicBuffer(unsigned int size, VertexBufferLayout layout);
        ~DynamicBuffer();

        void Bind() const;
        void Unbind() const;
        void Draw() const;

        void AddModel(Model* model);
        void DeleteModel(Model* model);
};
