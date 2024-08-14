#pragma once

#include "../models/Model.h"
#include "map"
#include <stack>
#include "DynamicIndexBuffer.h"
#include "DynamicVertexBuffer.h"


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

        DynamicIndexBuffer m_dynamicIB;
        DynamicVertexBuffer m_dynamicVB;



    public:
        explicit DynamicBuffer(unsigned int size);
        ~DynamicBuffer();

        void Bind() const;
        void Unbind() const;
        void Draw() const;

        void AddModel(Model* model);
        void DeleteModel(Model* model);
};
