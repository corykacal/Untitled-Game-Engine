#pragma once

#include "../models/Model.h"
#include "map"
#include <stack>

struct IndexTriangle
{
    Index point1;
    Index point2;
    Index point3;
};

class DynamicIndexBuffer
{
    private:
        unsigned int m_RendererID;
        unsigned int m_MaxSize;
        vector<IndexTriangle> m_IndexBuffer;
        stack<IndexTriangle*> m_FreeIndices;

    public:
        DynamicIndexBuffer(unsigned int size);
        ~DynamicIndexBuffer();

        void Bind() const;
        void Unbind() const;
        void Draw() const;

        vector<IndexTriangle*> AddTriangles(vector<IndexTriangle> triangles);
        void RemoveTriangles(vector<IndexTriangle*> triangles);
};
