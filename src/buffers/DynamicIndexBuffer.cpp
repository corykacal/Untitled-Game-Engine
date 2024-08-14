#include "IndexBuffer.h"
#include "../debug/Debug.h"
#include "DynamicIndexBuffer.h"

DynamicIndexBuffer::DynamicIndexBuffer(unsigned int size)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    m_MaxSize = size;
    m_IndexBuffer.reserve(m_MaxSize/3);
    GLCall( glGenBuffers(1, &m_RendererID) );
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID) );
    GLCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW) );
}

DynamicIndexBuffer::~DynamicIndexBuffer()
{
    GLCall( glDeleteBuffers(1, &m_RendererID) );
}

void DynamicIndexBuffer::Bind() const
{
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID) );
}

void DynamicIndexBuffer::Unbind() const
{
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
}

void DynamicIndexBuffer::Draw() const
{
    Bind();
    GLCall( glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_IndexBuffer.size(), &m_IndexBuffer.front()) );
}

vector<IndexTriangle*> DynamicIndexBuffer::AddTriangles(vector<IndexTriangle> triangles)
{
    //TODO: add some error checking for max size overloading????
    vector<IndexTriangle*> addedTriangles;
    //TODO get rid of this counter?
    int currentTriangle = 0;
    while(!m_FreeIndices.empty() && currentTriangle < triangles.size())
    {
        IndexTriangle* freeIndex = m_FreeIndices.top();
        m_FreeIndices.pop();
        freeIndex->point1 = triangles[currentTriangle].point1;
        freeIndex->point2 = triangles[currentTriangle].point2;
        freeIndex->point3 = triangles[currentTriangle].point3;
        addedTriangles.push_back(freeIndex);
        currentTriangle++;
    }
    if(currentTriangle != triangles.size())
    {
        for(int i=currentTriangle; i<triangles.size(); i++)
        {
            m_IndexBuffer.push_back(triangles[i]);
            //Memory errors????
            addedTriangles.push_back(&m_IndexBuffer.back());
        }
    }
    return addedTriangles;
}

void DynamicIndexBuffer::RemoveTriangles(vector<IndexTriangle*> triangles) {
    //TODO: I am assuming these triangles now all have the same point to avoid rasturization.
    //The DB should take care of this later.
    for (IndexTriangle* triangle : triangles) {
        m_FreeIndices.push(triangle);
    }
}
