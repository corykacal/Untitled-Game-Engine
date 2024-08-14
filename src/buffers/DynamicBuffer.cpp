#include "../debug/Debug.h"
#include "DynamicBuffer.h"

DynamicBuffer::DynamicBuffer(unsigned int size, VertexBufferLayout layout)
: m_dynamicVB(DynamicVertexBuffer(size)),
  m_vertexArray(layout),
  m_dynamicIB(DynamicIndexBuffer(size)),
  m_MaxSize(size)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    //TODO change stride to just take size of Vertex then do maxbuffersize/sizeof(vertex
    //s_Data.VertexBuffer = new Vertex[MaxBufferSize / s_Data.VertexVA->GetStride()];
    //s_Data.IndexBuffer = new Index[MaxBufferSize / sizeof(Index)];
}

DynamicBuffer::~DynamicBuffer()
{
}

void DynamicBuffer::Bind() const
{
    m_dynamicVB.Bind();
    m_dynamicIB.Bind();
}

void DynamicBuffer::Unbind() const
{
    m_dynamicVB.Unbind();
    m_dynamicIB.Unbind();
}

void DynamicBuffer::Draw() const
{
    m_dynamicVB.Draw();
    m_dynamicIB.Draw();
}

void DynamicBuffer::AddModel(Model *model)
{
    vector<unsigned int> vertexIndices = m_dynamicVB.AddVertices(model->GetVertexData());
    vector<IndexTriangle> indexTriangles;
    for(int i=0; i<model->getIndicies().size(); i+=3)
    {
        vector<Index> indicies = model->getIndicies();
        Index point1 = {vertexIndices[indicies[i].Position]};
        Index point2 = {vertexIndices[indicies[i+1].Position]};
        Index point3 = {vertexIndices[indicies[i+2].Position]};
        IndexTriangle indexTriangle = {point1, point2, point3};
        indexTriangles.push_back(indexTriangle);
    }
    vector<IndexTriangle*> addedTriangles = m_dynamicIB.AddTriangles(indexTriangles);
    m_ModelToIndices.emplace(model->getModelID(), ModelBufferEntry{addedTriangles, vertexIndices});
}

void DynamicBuffer::DeleteModel(Model *model)
{
    //TODO: instead of re-adding the to free stack, if on end, actually free up that memory????
    ModelBufferEntry entry = m_ModelToIndices[model->getModelID()];
    m_dynamicIB.DeleteTriangles(entry.triangles);
    m_dynamicVB.DeleteVertices(entry.vertexIndices);
}
