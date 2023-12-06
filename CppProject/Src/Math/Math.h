#pragma once

#include <eigen/Eigen>

namespace Math
{
    Eigen::Matrix4f QuaternionToRotationMatrix(const Eigen::Quaternionf& rot);
    Eigen::Matrix4f MakeOrthoProjectionMatrix(float left, float right, float bottom, float top, float near, float far);
    Eigen::Matrix4f MakePerspectiveProjectionMatrix(float left, float right, float bottom, float top, float near, float far);
    Eigen::Matrix4f MakeViewMatrix(const Eigen::Vector3f& pos, const Eigen::Quaternionf& rot);
}