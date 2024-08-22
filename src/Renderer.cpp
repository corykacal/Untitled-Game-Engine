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
    DynamicBuffer* DynamicBuffer = nullptr;
    Shader* shader = nullptr;

    std::array<GLuint, MaxTextures> TextureSlots;
    uint32_t TextureSlotIndex = 1;
};

static RendererData s_Data;

void Renderer::Init() {
    SetUpShader();
    VertexBufferLayout layout;
    layout.AddFloat(3);
    layout.AddFloat(3);
    layout.AddFloat(3);
    layout.AddFloat(2);
    layout.AddFloat(1);
    s_Data.DynamicBuffer = new DynamicBuffer(MaxBufferSize, layout);
    SetUpTextures();
}

void Renderer::Clear()
{
        GLCall( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) );
}

void Renderer::Shutdown()
{
    delete s_Data.DynamicBuffer;
}

void Renderer::Draw()
{
    s_Data.shader->Bind();
    s_Data.DynamicBuffer->Draw();
}

void Renderer::AddModel(Model *model)
{
    s_Data.DynamicBuffer->AddModel(model);
}

void Renderer::DeleteModel(Model *model)
{
    s_Data.DynamicBuffer->DeleteModel(model);
}

void Renderer::SetUniform1i(const string &name, GLint value)
{
    s_Data.shader->SetUniform1i(name, value);
}

void Renderer::SetUniform1f(const string &name, float value)
{
    s_Data.shader->SetUniform1f(name, value);
}

void Renderer::SetUniform3fv(string name, const glm::vec3& vector)
{
    s_Data.shader->SetUniform3fv(name, vector);
}

void Renderer::SetUniform4fv(string name, const glm::vec4& vector)
{
    s_Data.shader->SetUniform4fv(name, vector);
}

void Renderer::SetUniformMat4f(string name, const glm::mat4 &matrix)
{
    s_Data.shader->SetUniformMat4f(name, matrix);
}

void Renderer::SetUpShader() {
    s_Data.shader = new Shader("../res/shader/vertex.glsl", "../res/shader/fragment.glsl");
    s_Data.shader->Bind();
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

    LoadTexture("../res/texture/grass.png", Texture::NORMAL);
    LoadTexture("../res/texture/rock.png", Texture::NORMAL);
    LoadTexture("../res/texture/grassnormal.png", Texture::NORMAL);
    LoadTexture("../res/texture/rocknormal.png", Texture::NORMAL);
    LoadTexture("../res/texture/grassdisplacement.png", Texture::DISPLACEMENT);
    LoadTexture("../res/texture/rockdisplacement.png", Texture::DISPLACEMENT);
}

Texture* Renderer::LoadTexture(const string &filepath, Texture::TextureType type)
{
    Texture* texture = new Texture(filepath, type);
    texture->Bind(s_Data.TextureSlotIndex);
    s_Data.TextureSlotIndex++;
    return texture;
}

