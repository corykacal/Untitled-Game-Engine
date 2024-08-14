#pragma once


#include <GL/glew.h>
#include "../debug/Debug.h"
#include "../models/Model.h"
#include "stack"

class DynamicVertexBuffer
{
    private:
        unsigned int m_RendererID;
        vector<Vertex> m_VertexBuffer;
        stack<unsigned int> m_FreeVertices;

    public:
        DynamicVertexBuffer(unsigned int size);
        ~DynamicVertexBuffer();

        void Bind() const;
        void Unbind() const;
        void Draw() const;

        //I'm assuming the models will not be deleted or go out of scope.
        //if it does it should be deleted?
        vector<unsigned int> AddVertices(vector<Vertex> verticies);
        void DeleteVertices(vector<unsigned int> vertexIndecies);
};
