//
// Created by Cory Kacal on 8/31/24.
//

#ifndef UNTITLED_DYNAMICSKYBOXBUFFER_H
#define UNTITLED_DYNAMICSKYBOXBUFFER_H
#include <utility>

#include "DynamicBuffer.h"

class DynamicSkyBoxBuffer : public DynamicBuffer
{
public:
    DynamicSkyBoxBuffer(unsigned int size, VertexBufferLayout layout, const std::string& vertexShader, const std::string& fragmentShader)
            : DynamicBuffer(size, std::move(layout), vertexShader, fragmentShader) {}

    void Draw() override
    {
        glDepthFunc(GL_LEQUAL);
        glDisable(GL_CULL_FACE);
        DynamicBuffer::Draw();
        glEnable(GL_CULL_FACE);
        glDepthFunc(GL_LESS);
    }
};

#endif //UNTITLED_DYNAMICSKYBOXBUFFER_H
