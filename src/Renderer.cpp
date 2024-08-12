#include "Renderer.h"

static const size_t MaxBufferSize = BytesHelper::Megabyte(64);
static const size_t MaxTextures = 16;

struct TextureSlot
{
    GLuint TexId;
    string TexName;
    string FilePath;
};

struct RendererData
{
    VertexArray* VertexVA = nullptr;
    VertexBuffer* VertexVB = nullptr;
    IndexBuffer* VertexIB = nullptr;
    Shader* shader = nullptr;

    uint32_t IndexCount = 0;
    GLuint IndexOffset = 0;

    Vertex* VertexBuffer = nullptr;
    Vertex* VertexBufferPtr = nullptr;

    Index* IndexBuffer = nullptr;
    Index* IndexBufferPtr = nullptr;

    GLuint BlankTexture = 0;
    uint32_t BlankTextureSlot = 0;

    std::array<GLuint, MaxTextures> TextureSlots;
    uint32_t TextureSlotIndex = 1;
};

static RendererData s_Data;

void Renderer::Init() {
    SetUpShader();
    SetUpVertexBuffer();
    SetUpVertexArray();
    SetUpIndexBuffer();
    SetUpTextures();
}

void Renderer::Clear()
{
        GLCall( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) );
}

void Renderer::Shutdown() {
    delete s_Data.VertexVA;
    delete s_Data.VertexVB;
    delete s_Data.VertexIB;

    delete s_Data.IndexBuffer;
    delete s_Data.IndexBufferPtr;

    delete s_Data.VertexBuffer;
    delete s_Data.VertexBufferPtr;
}

void Renderer::BeginBatch() {
    s_Data.VertexBufferPtr = s_Data.VertexBuffer;
    s_Data.IndexBufferPtr = s_Data.IndexBuffer;
}

void Renderer::EndBatch() {
    GLsizeiptr indexBufferSize = (uint8_t*)s_Data.IndexBufferPtr - (uint8_t*)s_Data.IndexBuffer;
    GLsizeiptr vertexBufferSize = (uint8_t*)s_Data.VertexBufferPtr - (uint8_t*)s_Data.VertexBuffer;
    s_Data.VertexIB->SetBuffer(s_Data.IndexBuffer, indexBufferSize);
    s_Data.VertexVB->SendBufferData(s_Data.VertexBuffer, vertexBufferSize);
}

void Renderer::Flush() {
    s_Data.VertexVA->Bind();
    s_Data.VertexIB->Bind();
    s_Data.VertexVB->Bind();
    s_Data.shader->Bind();


    GLCall( glDrawElements(GL_TRIANGLES, s_Data.IndexCount, GL_UNSIGNED_INT, nullptr) );

    //set up with flush end and begin assume new buffer creation everytime
    //s_Data.IndexCount = 0;
    //s_Data.IndexOffset = 0;
}

void Renderer::DrawModel(Model *model) {
    vector<Vertex> verticies = model->GetVertexData();
    vector<Index> indicies = model->getIndicies();
    //check model index count + current index count
    if((uint8_t*)(verticies.size() + s_Data.VertexBufferPtr) - (uint8_t*)s_Data.VertexBuffer > MaxBufferSize ||
    (uint8_t*)(verticies.size() + s_Data.IndexBufferPtr) - (uint8_t*)s_Data.IndexBuffer > MaxBufferSize)
    {
        EndBatch();
        Flush();
        BeginBatch();
    }

    for(auto & vertex : verticies) {
        s_Data.VertexBufferPtr->Position = vertex.Position;
        s_Data.VertexBufferPtr->Color = vertex.Color;
        s_Data.VertexBufferPtr->TexCoords = vertex.TexCoords;
        s_Data.VertexBufferPtr->TexIndex = vertex.TexIndex;
        s_Data.VertexBufferPtr++;
    }

    for(auto & index : indicies) {
        s_Data.IndexBufferPtr->Position = s_Data.IndexOffset + index.Position;
        s_Data.IndexBufferPtr++;
    }

    s_Data.IndexCount+=model->getIndicies().size();
    s_Data.IndexOffset+=model->GetVertexData().size();
}

void Renderer::SetUniform1i(const string &name, GLint value)
{
    s_Data.shader->SetUniform1i(name, value);
}

void Renderer::SetUniform3fv(string name, const glm::vec3& vector)
{
    s_Data.shader->SetUniform3fv(name, vector);
}

void Renderer::SetUniformMat4f(string name, const glm::mat4 &matrix)
{
    s_Data.shader->SetUniformMat4f(name, matrix);
}

void Renderer::SetUpVertexArray() {
    s_Data.VertexVA = new VertexArray;
    s_Data.VertexVA->Bind();

    VertexBufferLayout layout;
    layout.AddFloat(3);
    layout.AddFloat(4);
    layout.AddFloat(2);
    layout.AddFloat(1);

    s_Data.VertexVA->AddBuffer(layout);
    s_Data.VertexVA->Bind();
}

void Renderer::SetUpVertexBuffer() {
    s_Data.VertexVB = new VertexBuffer(MaxBufferSize);
    s_Data.VertexVB->Bind();
}

void Renderer::SetUpShader() {
    s_Data.shader = new Shader("../res/shader/vertex.glsl", "../res/shader/fragment.glsl");
    s_Data.shader->Bind();
}

void Renderer::SetUpIndexBuffer() {
    //TODO move VertexBuffer to vb area somehow
    //TODO change stride to just take size of Vertex then do maxbuffersize/sizeof(vertex
    s_Data.VertexBuffer = new Vertex[MaxBufferSize / s_Data.VertexVA->GetStride()];
    s_Data.IndexBuffer = new Index[MaxBufferSize / sizeof(Index)];

    s_Data.VertexIB = new IndexBuffer(MaxBufferSize);
    s_Data.VertexIB->Bind();

}

void Renderer::SetUpTextures() {
    s_Data.shader->Bind();

    GLuint secondColor;
    glGenTextures(1, &secondColor);
    glBindTexture(GL_TEXTURE_2D, secondColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    uint32_t secondcolor = 0xffffffff;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &secondcolor);

    glActiveTexture(GL_TEXTURE0 + s_Data.TextureSlotIndex);
    glBindTexture(GL_TEXTURE_2D, secondColor);
    s_Data.TextureSlotIndex++;

    int samplers[MaxTextures];
    memset(samplers, 0, sizeof(samplers));
    for(int i = 0; i < MaxTextures; ++i) samplers[i] = i;

    s_Data.shader->SetUniform1iv("u_Textures", MaxTextures, samplers);

    LoadTexture("../res/texture/grass.png");
    LoadTexture("../res/texture/rock.png");
}

Texture* Renderer::LoadTexture(const string &filepath)
{
    Texture* texture = new Texture(filepath);
    texture->Bind(s_Data.TextureSlotIndex);
    s_Data.TextureSlotIndex++;
    return texture;
}
