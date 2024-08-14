#include "DynamicVertexBuffer.h"

DynamicVertexBuffer::DynamicVertexBuffer(unsigned int size)
{
    GLCall( glGenBuffers(1, &m_RendererID) );
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_RendererID) );
    GLCall( glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW) );
}

DynamicVertexBuffer::~DynamicVertexBuffer()
{
    GLCall( glDeleteBuffers(1, &m_RendererID) );
}

void DynamicVertexBuffer::Bind() const
{
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_RendererID) );
}

void DynamicVertexBuffer::Unbind() const
{
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
}

void DynamicVertexBuffer::Draw() const
{
    Bind();
    GLCall( glBufferSubData(GL_ARRAY_BUFFER, 0, m_VertexBuffer.size(), &m_VertexBuffer.front()) );
}

vector<unsigned int> DynamicVertexBuffer::AddVertices(vector<Vertex> verticies) {
    vector<unsigned int> addedIndices;
    //TODO get rid of this counter?
    int currentVertex = 0;
    while(!m_FreeVertices.empty() && currentVertex < verticies.size())
    {
        unsigned int freeIndex = m_FreeVertices.top();
        m_FreeVertices.pop();
        m_VertexBuffer[freeIndex] = verticies[currentVertex];
        currentVertex++;
        addedIndices.push_back(freeIndex);
    }
    if(currentVertex != verticies.size())
    {
        for(int i=currentVertex; i<verticies.size(); i++) {
            m_VertexBuffer.push_back(verticies[i]);
            addedIndices.push_back(m_VertexBuffer.size()-1);
        }
    }
    return addedIndices;
}

void DynamicVertexBuffer::DeleteVertices(vector<unsigned int> vertexIndecies)
{
    for(unsigned int vertexIndex : vertexIndecies)
    {
        m_VertexBuffer[vertexIndex].Position = {0,0,0};
        m_FreeVertices.push(vertexIndex);
    }
}
