#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
#include <string>
#include <fstream>
#include <GL/glew.h>

#include "../util/FileHelper.h"
#include "../debug/Debug.h"
#include "../../vendor/glm/gtc/matrix_transform.hpp"

class Shader
{
    private:
        unsigned int m_RendererID;
        std::string m_VertexFilePath;
        std::string m_FragmentFilePath;
        std::unordered_map<std::string, int> m_UniformLocationCache;

    public:
        Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        // Set uniforms
        void SetUniform1i(const std::string& name, int value);
        void SetUniform1iv(const std::string &name, int value, GLint* data);
        void SetUniform1f(const std::string& name, float value);
        void SetUniform3fv(const std::string& name, const glm::vec3& vector);
        void SetUniform4fv(const std::string& name, const glm::vec4& vector);
        void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
        void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

    private:
        int GetUniformLocation(const std::string& name);
        static std::string parseShaderFile(const std::string& filePath);
        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

};
