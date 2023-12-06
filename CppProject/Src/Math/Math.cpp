#include "Math.h"

namespace Math
{
    Eigen::Matrix4f QuaternionToRotationMatrix(const Eigen::Quaternionf& rot)
    {
        float x = rot.x();
        float y = rot.y();
        float z = rot.z();
        float w = rot.w();

        Eigen::Matrix4f result = Eigen::Matrix4f::Zero();

        float v2xx = 2 * x * x;
        float v2yy = 2 * y * y;
        float v2zz = 2 * z * z;
        float v2xy = 2 * x * y;
        float v2zw = 2 * z * w;
        float v2xz = 2 * x * z;
        float v2yw = 2 * y * w;
        float v2yz = 2 * y * z;
        float v2xw = 2 * x * w;

        result(0, 0) = 1 - v2yy - v2zz;
        result(0, 1) = v2xy - v2zw;
        result(0, 2) = v2xz + v2yw;

        result(1, 0) = v2xy + v2zw;
        result(1, 1) = 1 - v2xx - v2zz;
        result(1, 2) = v2yz - v2xw;

        result(2, 0) = v2xz - v2yw;
        result(2, 1) = v2yz + v2xw;
        result(2, 2) = 1 - v2xx - v2yy;

        result(3, 3) = 1;

        return result;
    }

    Eigen::Matrix4f MakeOrthoProjectionMatrix(float left, float right, float bottom, float top, float near, float far)
    {
        assert(right > left);
        assert(top > bottom);
        assert(far > near);

        Eigen::Matrix4f result = Eigen::Matrix4f::Identity();

        // Translation
        result.col(3) = Eigen::Vector4f {
                -(right + left) / (right - left),
                -(top + bottom) / (top - bottom),
                -(far + near) / (far - near),
                1
        };

        // Scale
        result(0, 0) = 2 / (right - left);
        result(1, 1) = 2 / (top - bottom);
        result(2, 2) = 2 / (far - near);

        return result;
    }

    Eigen::Matrix4f MakePerspectiveProjectionMatrix(float left, float right, float bottom, float top, float near, float far)
    {
        assert(right > left);
        assert(top > bottom);
        assert(far > near);

        Eigen::Matrix4f result = Eigen::Matrix4f::Identity();

        result(0, 0) = 2 * near / (right - left);
        result(1, 1) = 2 * near / (top - bottom);
        result(2, 2) = - (far + near)/ (far - near);
        result(2, 3) = 0;

        result(0, 2) = (right + left) / (right - left);
        result(1, 2) = (top + bottom) / (top - bottom);
        result(2, 2) = -1;

        result(2, 3) = - 2 * near * far / (far - near);

        return result;
    }

    Eigen::Matrix4f MakeViewMatrix(const Eigen::Vector3f& pos, const Eigen::Quaternionf& rot)
    {
        // TODO Opt cal result
        Eigen::Matrix4f translationMatrix;
        translationMatrix << 1, 0, 0, -pos.x(),
                0, 1, 0, -pos.y(),
                0, 0, 1, -pos.z(),
                0, 0, 0, 1;

        Eigen::Matrix4f rotationMatrix = QuaternionToRotationMatrix(rot);

        return rotationMatrix * translationMatrix;
    }
}