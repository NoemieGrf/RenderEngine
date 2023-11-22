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
        _projectionMatrix = Math::MakeOrthoProjectionMatrix(_left, _right, _bottom, _top, _near, _far);
    }

}