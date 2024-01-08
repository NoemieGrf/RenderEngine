#include "UniformBlockOpenGL.h"

namespace Renderer
{
    UniformBlockOpenGL::UniformBlockOpenGL(const std::string& name)
        : UniformBlock(name)
    {
    }

    void UniformBlockOpenGL::UpdateOffset()
    {
        int currentLeftAlign = STD140_ALIGN;
        int currentOffset = 0;
        for (const auto& [name, shaderDataType]: _uniformData)
        {
            int needAlign = ShaderDataTypeHelper::GetShaderDataTypeSize(shaderDataType);

            // The left space of current line is sufficient to insert the next data.
            if (needAlign < currentLeftAlign)
            {
                _uniformOffsetMap[name] = currentOffset;

                currentLeftAlign -= needAlign;
                currentOffset += needAlign;
            }
            else
            {
                // If current line is not empty, padding this line
                if (currentLeftAlign != STD140_ALIGN)
                {
                    currentOffset += currentLeftAlign;
                    currentLeftAlign = STD140_ALIGN;
                }

                _uniformOffsetMap[name] = currentOffset;

                int fullLineNeeded = needAlign / STD140_ALIGN;
                int leftSpaceNeededAfterFullLine = needAlign % STD140_ALIGN;

                currentOffset += fullLineNeeded * STD140_ALIGN;

                currentOffset += leftSpaceNeededAfterFullLine;
                currentLeftAlign -= leftSpaceNeededAfterFullLine;
            }

        }

        // Fill up the last line
        if (currentLeftAlign < STD140_ALIGN)
            currentOffset += currentLeftAlign;

        _totalSize = currentOffset;
    }
}
