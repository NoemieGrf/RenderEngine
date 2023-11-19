#include "Shader.h"

#include <fstream>
#include <sstream>

namespace Renderer
{

    bool Shader::LoadFromFile(const char* path)
    {
        std::fstream fileStream(path, std::ios::in);

        if (!fileStream.is_open())
            return false;

        std::stringstream content;
        content << fileStream.rdbuf();

        fileStream.close();

        return LoadFromString(content.str().c_str());
    }

    bool Shader::LoadFromFile(const std::string& path)
    {
        return LoadFromFile(path.c_str());
    }
}