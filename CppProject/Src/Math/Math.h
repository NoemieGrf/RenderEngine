#pragma once

#include <eigen/Eigen>
#include "Define/RendererApi.h"

namespace Math
{
    /**
     * Translate matrix.
     * @param pos Translate vector.
     */
    Eigen::Matrix4f Translate(const Eigen::Vector3f& pos);

    /**
     * Rotation matrix.
     * @param rot Rotate quaternion.
     */
    Eigen::Matrix4f Rotate(const Eigen::Quaternionf& rot);

    /**
     * Scale matrix.
     * @param scale Scale.
     */
    Eigen::Matrix4f Scale(const Eigen::Vector3f& scale);

    /**
     * Rotation matrix from standard coordinate frame to look-at coordinate frame.
     * @param startPos From position.
     * @param targetPos Target position.
     * @param up Up direction.
     */
    Eigen::Matrix4f LookAt(const Eigen::Vector3f& startPos, const Eigen::Vector3f& targetPos, const Eigen::Vector3f& up);

    /**
     * Create model matrix.
     * @param pos World coordinate position.
     * @param rot World coordinate rotation in quaternion.
     * @param scale World coordinate scale.
     */
    Eigen::Matrix4f MakeModelMatrix(const Eigen::Vector3f& pos, const Eigen::Quaternionf& rot, const Eigen::Vector3f& scale);

    /**
     * Make camera view matrix, assume that camera is always looking at -z.
     * @param pos Camera position.
     * @param rot Camera rotation.
     */
    Eigen::Matrix4f MakeViewMatrix(const Eigen::Vector3f& pos, const Eigen::Quaternionf& rot);

    /**
     * @brief Projection matrix of ortho camera, frustum is symmetry by x-axis & y-axis. \n\n
     *
     * For standard ortho projection, before projection matrix, camera looks at -z, near value
     * and far value are less than zero, 0 > near > far. The standard ortho projection maps near
     * value to -1 and maps far value to +1. After projection, camera is still looks to -z.\n\n
     *
     * If target api is OpenGL: in OpenGL standard NDC, y-axis is up, x-axis is right, looks to +z,
     * which is opposite with the result of the standard ortho projection. So the result will manually
     * reverse z-axis. (Change right-handed axis to left-handed axis.)\n\n
     *
     * @param ndcApi Target NDC coordinates API.
     * @param nearPlaneHalfX Near plane half width.
     * @param nearPlaneHalfY Near plane half height.
     * @param nearPlaneZ Near plane z value.
     * @param farPlaneZ Far plane z value.
     */
    Eigen::Matrix4f MakeOrthoProjectionMatrix(RendererApi ndcApi, float nearPlaneHalfX, float nearPlaneHalfY, float nearPlaneZ, float farPlaneZ);

    /**
     * @brief Projection matrix of perspective camera, frustum is symmetry by x-axis & y-axis. \n\n
     *
     * @param ndcApi Target NDC coordinates API.
     * @param nearPlaneHalfX Near plane half width.
     * @param nearPlaneHalfY Near plane half height.
     * @param nearPlaneZ Near plane z value.
     * @param farPlaneZ Far plane z value.
     */
    Eigen::Matrix4f MakePerspectiveProjectionMatrix(RendererApi ndcApi, float nearPlaneHalfX, float nearPlaneHalfY, float nearPlaneZ, float farPlaneZ);
}