#pragma once

#include <GL/glew.h>
#include "buffers/VertexArray.h"
#include "buffers/Shader.h"
#include "buffers/Texture.h"
#include "buffers/DynamicBuffer.h"
#include "models/Model.h"
#include "models/Cube.h"
#include "util/ByteHelper.h"
#include "debug/Debug.h"
#include <iostream>
#include "../vendor/stb_image/stb_image.h"
#include <array>

class Renderer
{
    public:
        static void Init();
        static void Shutdown();
        static void Draw();
        static void Clear();
        static void AddModel(Model* model);
        static void DeleteModel(Model* model);

        static void SetUniform1i(const std::string& name, int value);
        static void SetUniform1f(const std::string& name, float value);
        static void SetUniform3fv(string name, const glm::vec3& vector);
        static void SetUniform4fv(string name, const glm::vec4& vector);
        static void SetUniformMat4f(string name, const glm::mat4& matrix);

        struct Stats
        {
            uint32_t Quads = 0;
            uint32_t Draws = 0;
        };

        static const Stats& GetStats();
        static void ResetStats();

    private:
        static void SetUpVertexArray();
        static void SetUpVertexBuffer();
        static void SetUpShader();
        static void SetUpIndexBuffer();
        static void SetUpTextures();

        static Texture* LoadTexture(const string& filepath, Texture::TextureType type);
};
