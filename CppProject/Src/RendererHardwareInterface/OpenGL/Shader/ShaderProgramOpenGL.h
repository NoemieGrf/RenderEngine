#pragma once

#include "Renderer/Shader/ShaderProgram.h"

namespace Renderer
{
    class ShaderProgramOpenGL: public ShaderProgram
    {
    public:
        ShaderProgramOpenGL();

    public:
        void AttachShader(const Ptr<Shader>& pShader) override;
        bool Compile() override;
        void Bind() override;

        void SetUniformInt(const std::string& name, int value) override;
        void SetUniformUnsignedInt(const std::string& name, unsigned int value) override;
        void SetUniformFloat(const std::string& name, float value) override;
        void SetUniformFloat2(const std::string& name, const Eigen::Vector2f& value) override;
        void SetUniformFloat3(const std::string& name, const Eigen::Vector3f& value) override;
        void SetUniformFloat4(const std::string& name, const Eigen::Vector4f& value) override;
        void SetUniformMat3(const std::string& name, const Eigen::Matrix3f& mat) override;
        void SetUniformMat4(const std::string& name, const Eigen::Matrix4f& mat) override;

    private:
        unsigned int _shaderProgramId = 0;
    };
}