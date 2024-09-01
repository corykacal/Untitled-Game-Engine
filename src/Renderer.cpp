#include "Renderer.h"

static const size_t MaxBufferSize = BytesHelper::Megabyte(256);
static const size_t MaxTextures = 16;

struct TextureSlot
{
    GLuint TexId;
    string TexName;
    string FilePath;
};

struct RendererData
{
    DynamicBuffer* ModelBuffer = nullptr;
    DynamicBuffer* SkyboxBuffer = nullptr;

    std::array<GLuint, MaxTextures> TextureSlots;
    uint32_t TextureSlotIndex = 1;
};

static RendererData s_Data;

void Renderer::Init() {
    VertexBufferLayout layout;
    layout.AddFloat(3);
    layout.AddFloat(3);
    layout.AddFloat(3);
    layout.AddFloat(2);
    layout.AddFloat(1);
    s_Data.ModelBuffer = new DynamicBuffer(MaxBufferSize, layout, "../res/shader/simple.vert", "../res/shader/simple.frag");
    s_Data.SkyboxBuffer = new DynamicSkyBoxBuffer(MaxBufferSize, layout, "../res/shader/skybox.vert", "../res/shader/skybox.frag");
    s_Data.SkyboxBuffer->AddModel(new Cube(1, {0.0f, 0.0f, 0.0f}, 2.0f));
    SetUpTextures();
    //textures can be used by any shader.
    //make dynamic buffer take a shader path too and make the shader. then just make whatever kind of shaders you want in the renderer here
    //s_Data.SkyBoxBuffer = new ModelBuffer(smol, layout, shaders)
    //list of all buffers? draw each one?
}

void Renderer::Shutdown()
{
    delete s_Data.ModelBuffer;
    delete s_Data.SkyboxBuffer;
}

void Renderer::Draw()
{
    GLCall( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) );

    s_Data.ModelBuffer->Draw();
    s_Data.SkyboxBuffer->Draw();
}

void Renderer::AddModel(Model *model)
{
    s_Data.ModelBuffer->AddModel(model);
}

void Renderer::DeleteModel(Model *model)
{
    s_Data.ModelBuffer->DeleteModel(model);
}

void Renderer::SetView(const glm::mat4& matrix)
{
    s_Data.ModelBuffer->GetShader().SetUniformMat4f("u_View", matrix);
    s_Data.SkyboxBuffer->GetShader().SetUniformMat4f("u_View", matrix);
}

void Renderer::SetProjection(const glm::mat4& matrix)
{
    s_Data.ModelBuffer->GetShader().SetUniformMat4f("u_Projection", matrix);
    s_Data.SkyboxBuffer->GetShader().SetUniformMat4f("u_Projection", matrix);
}

void Renderer::SetCameraPos(const glm::vec3& vector)
{
    s_Data.ModelBuffer->GetShader().SetUniform3fv("u_CameraPos", vector);
}

void Renderer::SetLightPosition(const glm::vec3& vector)
{
    s_Data.ModelBuffer->GetShader().SetUniform3fv("u_LightPosition", vector);
}

void Renderer::SetLightColor(const glm::vec3& vector)
{
    s_Data.ModelBuffer->GetShader().SetUniform3fv("u_LightColor", vector);
}

void Renderer::SetAmbientLightColor(const glm::vec3& vector)
{
    s_Data.ModelBuffer->GetShader().SetUniform3fv("u_AmbientLightColor", vector);
}

void Renderer::SetAmbientLightStrength(float value)
{
    s_Data.ModelBuffer->GetShader().SetUniform1f("u_AmbientLightStrength", value);
}

void Renderer::SetFogDistance(int value)
{
    s_Data.ModelBuffer->GetShader().SetUniform1i("u_FogDistance", value);
}

void Renderer::SetUpTextures()
{
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

    s_Data.ModelBuffer->GetShader().SetUniform1iv("u_Textures", MaxTextures, samplers);

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

