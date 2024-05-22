#pragma once

#include <string>
#include <unordered_map>

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
        void SetUniform1f(const std::string& name, float value);
        void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);

    private:
        int GetUniformLocation(const std::string& name);
        static std::string parseShaderFile(const std::string& filePath);
        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

};
