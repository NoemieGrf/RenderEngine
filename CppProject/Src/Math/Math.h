#pragma once

#include <eigen/Eigen>

class Math
{
public:
    Math() = delete;

public:
    static Eigen::Matrix4f QuaternionToRotationMatrix(const Eigen::Quaternionf& rot);

    static Eigen::Matrix4f MakeOrthoProjectionMatrix(float left, float right, float bottom, float top, float near, float far);
    static Eigen::Matrix4f MakeViewMatrix(const Eigen::Vector3f& pos, const Eigen::Quaternionf& rot);
};