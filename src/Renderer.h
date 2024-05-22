#pragma once

#include <GL/glew.h>

#include "Debug.h"
#include "buffers/VertexArray.h"
#include "buffers/IndexBuffer.h"
#include "Shader.h"

class Renderer
{
    public:
        void Clear() const;
        void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
