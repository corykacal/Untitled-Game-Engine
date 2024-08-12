#pragma once

#include <GL/glew.h>
#include "buffers/VertexArray.h"
#include "buffers/IndexBuffer.h"
#include "buffers/Shader.h"
#include "buffers/Texture.h"
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

        static void BeginBatch();
        static void EndBatch();
        static void Flush();

        static void Clear();
        static void DrawModel(Model *model);

        static void SetUniform1i(const std::string& name, int value);
        static void SetUniform3fv(string name, const glm::vec3& vector);
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

        static Texture* LoadTexture(const string& filepath);
};
