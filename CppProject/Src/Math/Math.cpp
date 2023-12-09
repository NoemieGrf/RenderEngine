#include "Math.h"

namespace Math
{
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
        return Eigen::Quaternionf(angleAxis);
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

    Eigen::Matrix4f LookAt(const Eigen::Vector3f& forward, const Eigen::Vector3f& up)
    {
        Eigen::Vector3f rightNorm = forward.cross(up).normalized();
        Eigen::Vector3f forwardNorm = forward.normalized();
        Eigen::Vector3f upNorm = up.normalized();

        Eigen::Matrix4f rotateMatrix;
        rotateMatrix <<
                rightNorm.x(),      rightNorm.y(),      rightNorm.z(),      0,
                upNorm.x(),         upNorm.y(),         upNorm.z(),         0,
                forwardNorm.x(),    forwardNorm.y(),    forwardNorm.z(),    0,
                0,                  0,                  0,                  1;

        return rotateMatrix;
    }

    Eigen::Matrix4f MakeModelMatrix(const Eigen::Vector3f& pos, const Eigen::Quaternionf& rot, const Eigen::Vector3f& scale)
    {
        return ScaleMatrix(scale) * QuaternionToRotationMatrix(rot) * TranslateMatrix(pos);
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

        if (ndcApi == RendererApi::OpenGL)
        {
            Eigen::Matrix4f zReverse = Eigen::Matrix4f::Identity();
            //zReverse(2, 2) = -1;
            return zReverse * standardOrthoProj;
        }

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
        {
            compressMatrix(3, 2) = -1;
        }

        return scaleMatrix * translationMatrix * compressMatrix;
    }
}