#pragma once

#include <eigen/Eigen>

namespace Math
{
    Eigen::Matrix4f Translate(const Eigen::Vector3f& pos);
    Eigen::Matrix4f Rotate(const Eigen::Quaternionf& rot);
    Eigen::Matrix4f Scale(const Eigen::Vector3f& pos);

    Eigen::Matrix4f MakeModelMatrix(const Eigen::Vector3f& pos, const Eigen::Quaternionf& rot, const Eigen::Vector3f& scale);
    Eigen::Matrix4f MakeViewMatrix(const Eigen::Vector3f& pos, const Eigen::Quaternionf& rot);
    Eigen::Matrix4f MakeOrthoProjectionMatrix(float nearPlaneHalfX, float nearPlaneHalfY, float nearPlaneZ, float farPlaneZ);
    Eigen::Matrix4f MakePerspectiveProjectionMatrix(float nearPlaneHalfX, float nearPlaneHalfY, float nearPlaneZ, float farPlaneZ);
}