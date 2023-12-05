#include "OrthoCamera.h"
#include "Math/Math.h"

OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float near, float far)
        : Camera(left, right, bottom, top, near, far)
{
}

void OrthoCamera::UpdateProjectionMatrixImp()
{
    _projectionMatrix = Math::MakeOrthoProjectionMatrix(
            _frustum.leftCoord, _frustum.rightCoord,
            _frustum.bottomCoord, _frustum.topCoord,
            _frustum.nearCoord, _frustum.farCoord);
}