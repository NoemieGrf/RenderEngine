#include <numbers>
#include "Math.h"

namespace Math
{
    Eigen::AngleAxisf AngleAxis(const Eigen::Vector3f& axis, float angle)
    {
        return { angle * (float)std::numbers::pi / 180, axis };
    }

    Eigen::Matrix4f AngleAxisToRotationMatrix(const Eigen::AngleAxisf& angleAxis)
    {
        Eigen::Matrix4f result = Eigen::Matrix4f::Identity();
        result.block<3, 3>(0, 0) = angleAxis.toRotationMatrix();
        return result;
    }

    Eigen::AngleAxisf RotationMatrixToAngleAxis(const Eigen::Matrix4f& rotationMat)
    {
        return Eigen::AngleAxisf(rotationMat.block<3, 3>(0, 0));
    }

    Eigen::Quaternionf AngleAxisToQuaternion(const Eigen::AngleAxisf& angleAxis)
    {
        return Eigen::Quaternionf(angleAxis).normalized();
    }

    Eigen::AngleAxisf QuaternionToAngleAxis(const Eigen::Quaternionf& q)
    {
        return Eigen::AngleAxisf(q);
    }

    Eigen::Matrix4f QuaternionToRotationMatrix(const Eigen::Quaternionf& q)
    {
        Eigen::Matrix4f result = Eigen::Matrix4f::Identity();
        result.block<3, 3>(0, 0) = q.toRotationMatrix();
        return result;
    }

    Eigen::Quaternionf RotationMatrixToQuaternion(const Eigen::Matrix4f& rotationMat)
    {
        return Eigen::Quaternionf(rotationMat.block<3, 3>(0, 0));
    }

    Eigen::Matrix4f TranslateMatrix(const Eigen::Vector3f& pos)
    {
        Eigen::Matrix4f result = Eigen::Matrix4f::Identity();
        result.col(3) = Eigen::Vector4f{pos.x(), pos.y(), pos.z(), 1};
        return result;
    }

    Eigen::Matrix4f ScaleMatrix(const Eigen::Vector3f& scale)
    {
        Eigen::Matrix4f result = Eigen::Matrix4f::Identity();
        result(0, 0) = scale.x();
        result(1, 1) = scale.y();
        result(2, 2) = scale.z();
        return result;
    }

    Eigen::Matrix4f MakeModelMatrix(const Eigen::Vector3f& pos, const Eigen::Quaternionf& rot, const Eigen::Vector3f& scale)
    {
        return TranslateMatrix(pos) * QuaternionToRotationMatrix(rot) * ScaleMatrix(scale);
    }

    Eigen::Matrix4f MakeViewMatrix(const Eigen::Vector3f& pos, const Eigen::Quaternionf& rot)
    {
        Eigen::Matrix4f translationMatrix = TranslateMatrix(-pos);
        Eigen::Matrix4f rotationMatrix = QuaternionToRotationMatrix(rot.conjugate());

        return rotationMatrix * translationMatrix;
    }

    Eigen::Matrix4f MakeOrthoProjectionMatrix(RendererApi ndcApi, float nearPlaneHalfX, float nearPlaneHalfY, float nearPlaneZ, float farPlaneZ)
    {
        float left = -nearPlaneHalfX;
        float right = nearPlaneHalfX;
        float top = nearPlaneHalfY;
        float bottom = -nearPlaneHalfY;
        float near = nearPlaneZ;
        float far = farPlaneZ;

        Eigen::Matrix4f translationMatrix = TranslateMatrix({-(right + left) / 2,
                                                             -(top + bottom) / 2,
                                                             -(near + far) / 2});

        Eigen::Matrix4f scaleMatrix = ScaleMatrix({2 / (right - left),
                                                   2 / (top - bottom),
                                                   2 / (near - far)});

        Eigen::Matrix4f standardOrthoProj = scaleMatrix * translationMatrix;

        return standardOrthoProj;
    }

    Eigen::Matrix4f MakePerspectiveProjectionMatrix(RendererApi ndcApi, float nearPlaneHalfX, float nearPlaneHalfY, float nearPlaneZ, float farPlaneZ)
    {
        float left = -nearPlaneHalfX;
        float right = nearPlaneHalfX;
        float top = nearPlaneHalfY;
        float bottom = -nearPlaneHalfY;
        float near = nearPlaneZ;
        float far = farPlaneZ;

        Eigen::Matrix4f translationMatrix = TranslateMatrix({-(right + left) / 2,
                                                             -(top + bottom) / 2,
                                                             -(near + far) / 2});

        Eigen::Matrix4f scaleMatrix = ScaleMatrix({2 / (right - left),
                                                   2 / (top - bottom),
                                                   2 / (near - far)});

        Eigen::Matrix4f standardOrthoProj = scaleMatrix * translationMatrix;

        Eigen::Matrix4f compressMatrix;
        compressMatrix <<
                        near,        0,          0,              0,
                        0,           near,       0,              0,
                        0,           0,          near + far,     - far * near,
                        0,           0,          1,              0;

        if (ndcApi == RendererApi::OpenGL)
            return -1 * scaleMatrix * translationMatrix * compressMatrix;
        else
            return scaleMatrix * translationMatrix * compressMatrix;
    }
}