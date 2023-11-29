#pragma once

namespace Renderer
{
    struct IOpenGLShaderId
    {
    public:
        unsigned int GetShaderId() const;

    protected:
        unsigned int _shaderId = 0;
    };
}