#pragma once

#include <string>
#include <GL/glew.h>
#include "../../vendor/stb_image/stb_image.h"
#include "../debug/Debug.h"

class Texture
{
private:
    GLuint m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;

public:
    enum TextureType
    {
        STANDARD = 0, DISPLACEMENT = 0, NORMAL = 1
    };

    Texture(const std::string& path, TextureType type);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
    unsigned int GetId();

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }

};