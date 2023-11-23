
#include "Define/RendererApi.h"
#include "Application/Application.h"
#include "Looper/RenderLooper.h"
#include "Looper/EditorLooper.h"

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PWSTR lpCmdLine, int nCmdShow)
{
    Application::CreateInstance();
    Application::GetInstance()->InitWindow(RendererApi::OpenGL, 900, 600);
    Application::GetInstance()->AddLooper<RenderLooper>();
    Application::GetInstance()->AddLooper<EditorLooper>();

    Application::GetInstance()->RunLoop();

    return 0;
}