#pragma once

class IndexBuffer
{
    private:
        unsigned int m_RendererID;

    public:
        IndexBuffer(unsigned int size);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;
        void SetBuffer(void* indices, unsigned int size) const;
};
