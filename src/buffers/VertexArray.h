#pragma once

#include "VertexBufferLayout.h"

class VertexArray
{
    private:
        unsigned int m_RendererID;
        unsigned int m_Stride;
        VertexBufferLayout m_bufferLayout;
        void AddBuffer(const VertexBufferLayout& layout);

    public:
        VertexArray(VertexBufferLayout& layout);
        ~VertexArray();

        void Bind() const;
        void Unbind() const;
        unsigned int GetStride() const;
};
