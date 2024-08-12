#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
    private:
        unsigned int m_RendererID;
        unsigned int m_Stride;

    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBufferLayout& layout);
        void Bind() const;
        void Unbind() const;
        unsigned int GetStride() const;
};
