
#include "Define/RendererApi.h"
#include "Application/Application.h"
#include "Looper/TestLooper.h"

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PWSTR lpCmdLine, int nCmdShow)
{
    Application::InitWindow(RendererApi::OpenGL, 900, 900);
    Application::AddLooper<TestLooper>();
    Application::RunLoop();
    Application::DestroyWindow();
    return 0;
}