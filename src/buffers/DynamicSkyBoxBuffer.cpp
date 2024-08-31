//
// Created by Cory Kacal on 8/31/24.
//
#include "DynamicBuffer.h"

class DynamicSkyBoxBuffer : DynamicBuffer
{
    DynamicSkyBoxBuffer() : DynamicBuffer(0, VertexBufferLayout(), nullptr, nullptr) {}

    void Draw()
    {
        glDepthFunc(GL_LEQUAL);
        DynamicBuffer::Draw();
        glDepthFunc(GL_LESS);
    }
};