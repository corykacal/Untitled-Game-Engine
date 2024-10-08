#include "Shader.h"

Shader::Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath)
    : m_VertexFilePath(vertexFilepath), m_FragmentFilePath(fragmentFilepath), m_RendererID(0)
{
    const std::string& vertexSource = parseShaderFile(vertexFilepath);
    const std::string& fragmentSource = parseShaderFile(fragmentFilepath);

    m_RendererID = CreateShader(vertexSource, fragmentSource);

    GLCall( glUseProgram(m_RendererID) );
}

Shader::~Shader()
{
    GLCall( glDeleteProgram(m_RendererID) );
}

void Shader::Bind() const
{
    GLCall( glUseProgram(m_RendererID) );
}

void Shader::Unbind() const
{
    GLCall( glUseProgram(0) );
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall( int location = glGetUniformLocation(m_RendererID, name.c_str()) );
    if (location == -1)
        std::cout << "No active uniform variable with name " << name << " found" << std::endl;

    m_UniformLocationCache[name] = location;

    return location;
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall( glUniform1i(GetUniformLocation(name), value) );
}

void Shader::SetUniform1iv(const std::string &name, int value, GLint* data)
{
    GLCall( glUniform1iv(GetUniformLocation(name), value, data) );
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    GLCall( glUniform1f(GetUniformLocation(name), value) );
}

void Shader::SetUniform3fv(const std::string& name, const glm::vec3& vector)
{
    GLCall( glUniform3fv(GetUniformLocation(name), 1, &vector[0]) );
}

void Shader::SetUniform4fv(const std::string &name, const glm::vec4 &vector)
{
    GLCall( glUniform4fv(GetUniformLocation(name), 1, &vector[0]) );

}

void Shader::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
    GLCall( glUniform4f(GetUniformLocation(name), f0, f1, f2, f3) );
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall( glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]) );
}

std::string Shader::parseShaderFile(const std::string &filePath)
{
    std::ifstream file = FileHelper::openFile(filePath);
    std::string str;
    std::string content;
    while (std::getline(file, str)) {
        content.append(str + "\n");
    }
    return content;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    GLCall( unsigned int id = glCreateShader(type) );
    const char* src = source.c_str();
    GLCall( glShaderSource(id, 1, &src, nullptr) );
    GLCall( glCompileShader(id) );

    // Error handling
    int result;
    GLCall( glGetShaderiv(id, GL_COMPILE_STATUS, &result) );
    std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader compile status: " << result << std::endl;
    if ( result == GL_FALSE )
    {
        int length;
        GLCall( glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length) );
        char* message = (char*) alloca(length * sizeof(char));
        GLCall( glGetShaderInfoLog(id, length, &length, message) );
        std::cout 
            << "Failed to compile "
            << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << " shader"
            << std::endl;
        std::cout << message << std::endl;
        GLCall( glDeleteShader(id) );
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    // create a shader program
    unsigned int program = GLCall( glCreateProgram() );
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall( glAttachShader(program, vs) );
    GLCall( glAttachShader(program, fs) );

    GLCall( glLinkProgram(program) );

    GLint program_linked;

    GLCall( glGetProgramiv(program, GL_LINK_STATUS, &program_linked) );
    std::cout << "Program link status: " << program_linked << std::endl;
    if (program_linked != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        GLCall( glGetProgramInfoLog(program, 1024, &log_length, message) );
        std::cout << "Failed to link program" << std::endl;
        std::cout << message << std::endl;
    }

    GLCall( glValidateProgram(program) );

    GLCall( glDeleteShader(vs) );
    GLCall( glDeleteShader(fs) );

    return program;
}

unsigned int Shader::GetID() const
{
    return m_RendererID;
}
