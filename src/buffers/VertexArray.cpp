#include "VertexArray.h"

VertexArray::VertexArray(VertexBufferLayout& layout)
{
    GLCall( glGenVertexArrays(1, &m_RendererID) );
    Bind();
    AddBuffer(layout);
}

VertexArray::~VertexArray()
{
    GLCall( glDeleteVertexArrays(1, &m_RendererID) );
}

void VertexArray::AddBuffer(const VertexBufferLayout& layout) {
    Bind();
    const std::vector<VertexBufferElement> elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size() ; i++)
    {
        const VertexBufferElement element = elements[i];
        GLCall( glEnableVertexAttribArray(i) );
        GLCall( glVertexAttribPointer(i, element.count, element.type, element.normalized,
                                      layout.GetStride(), INT2VOIDP(offset)) );
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
    m_Stride = layout.GetStride();
}

void VertexArray::Bind() const
{
    GLCall( glBindVertexArray(m_RendererID) );
}

void VertexArray::Unbind() const
{
    GLCall( glBindVertexArray(0) );
}

unsigned int VertexArray::GetStride() const
{
    return m_Stride;
};
