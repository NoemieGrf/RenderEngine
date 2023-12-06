#pragma once

#include <eigen/Eigen>

namespace Math
{
    Eigen::Matrix4f QuaternionToRotationMatrix(const Eigen::Quaternionf& rot);
    Eigen::Matrix4f MakeViewMatrix(const Eigen::Vector3f& pos, const Eigen::Quaternionf& rot);
    Eigen::Matrix4f MakeOrthoProjectionMatrix(float nearPlaneHalfX, float nearPlaneHalfY, float nearPlaneZ, float farPlaneZ);
    Eigen::Matrix4f MakePerspectiveProjectionMatrix(float nearPlaneHalfX, float nearPlaneHalfY, float nearPlaneZ, float farPlaneZ);
}