#include "IndexBuffer.h"
#include "../debug/Debug.h"

IndexBuffer::IndexBuffer(unsigned int size)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall( glGenBuffers(1, &m_RendererID) );
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID) );
    GLCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW) );
}

IndexBuffer::~IndexBuffer()
{
    GLCall( glDeleteBuffers(1, &m_RendererID) );
}

void IndexBuffer::Bind() const
{
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID) );
}

void IndexBuffer::Unbind() const
{
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
}

void IndexBuffer::SetBuffer(void* indices, unsigned int size) const
{
    Bind();
    GLCall( glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, indices) );
}
