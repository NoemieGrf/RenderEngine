#include "OrthoCamera.h"
#include "Math/Math.h"

namespace Renderer
{
    OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float near, float far)
        : Camera(left, right, bottom, top, near, far)
    {
    }

    void OrthoCamera::UpdateProjectionMatrixImp()
    {
        _projectionMatrix = Math::MakeOrthoProjectionMatrix(
                _frustum.left, _frustum.right,
                _frustum.bottom, _frustum.top,
                _frustum.near, _frustum.far);
    }

}