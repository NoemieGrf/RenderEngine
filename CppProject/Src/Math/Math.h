#pragma once

#include <eigen/Eigen>

namespace Math
{
    /**
     * Translate matrix
     * @param pos Translate vector
     */
    Eigen::Matrix4f Translate(const Eigen::Vector3f& pos);

    /**
     * Rotation matrix
     * @param rot Rotate quaternion
     */
    Eigen::Matrix4f Rotate(const Eigen::Quaternionf& rot);

    /**
     * Scale matrix
     * @param scale Scale
     */
    Eigen::Matrix4f Scale(const Eigen::Vector3f& scale);

    /**
     * Rotation matrix from standard coordinate frame to look-at coordinate frame
     * @param forward Look-at forward direction
     * @param up Up direction
     * @param flipZ Do flip z, camera always look at -z
     */
    Eigen::Matrix4f LookAt(const Eigen::Vector3f& forward, const Eigen::Vector3f& up);

    /**
     * Create model matrix
     * @param pos World coordinate position
     * @param rot World coordinate rotation in quaternion
     * @param scale World coordinate scale
     */
    Eigen::Matrix4f MakeModelMatrix(const Eigen::Vector3f& pos, const Eigen::Quaternionf& rot, const Eigen::Vector3f& scale);

    /**
     * Make camera view matrix
     * @param pos Camera position
     * @param rot Camera rotation
     */
    Eigen::Matrix4f MakeViewMatrix(const Eigen::Vector3f& pos, const Eigen::Quaternionf& rot);

    /**
     * Projection matrix of ortho camera, frustum is symmetry by x-axis & y-axis
     * @param nearPlaneHalfX Near plane half width
     * @param nearPlaneHalfY Near plane half height
     * @param nearPlaneZ Near plane z value
     * @param farPlaneZ Far plane z value
     */
    Eigen::Matrix4f MakeOrthoProjectionMatrix(float nearPlaneHalfX, float nearPlaneHalfY, float nearPlaneZ, float farPlaneZ);

    /**
     * Projection matrix of perspective camera, frustum is symmetry by x-axis & y-axis
     * @param nearPlaneHalfX Near plane half width
     * @param nearPlaneHalfY Near plane half height
     * @param nearPlaneZ Near plane z value
     * @param farPlaneZ Far plane z value
     */
    Eigen::Matrix4f MakePerspectiveProjectionMatrix(float nearPlaneHalfX, float nearPlaneHalfY, float nearPlaneZ, float farPlaneZ);
}