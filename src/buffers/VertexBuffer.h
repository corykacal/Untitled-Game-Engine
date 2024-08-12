#pragma once

#include <GL/glew.h>
#include "../debug/Debug.h"

class VertexBuffer
{
    private:
        unsigned int m_RendererID;

    public:
        VertexBuffer(unsigned int size);
        ~VertexBuffer();

        void SendBufferData(void* buffer, unsigned int size) const;
        void Bind() const;
        void Unbind() const;
};
