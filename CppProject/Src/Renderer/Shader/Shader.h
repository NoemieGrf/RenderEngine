#pragma once

#include <string>

namespace Renderer
{
    class Shader
    {
    public:
        Shader() = default;
        virtual ~Shader() = default;

    public:
        bool LoadFromFile(const char* path);
        bool LoadFromFile(const std::string& path);

        virtual bool Compile() = 0;
        virtual void LoadFromString(const char* data) = 0;
    };
}