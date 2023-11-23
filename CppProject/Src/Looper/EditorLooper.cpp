#include "EditorLooper.h"
#include "Application/Application.h"

EditorLooper::EditorLooper()
{
    _pEditor = new Editor::Editor(RendererApi::OpenGL);
    _pEditor->SetUp();

    Application::GetInstance()->AddWinMsgProc(this);
}

EditorLooper::~EditorLooper()
{
    Application::GetInstance()->RemoveWinMsgProc(this);

    _pEditor->Destroy();
    delete _pEditor;
}

void EditorLooper::Loop()
{
    _pEditor->Update();
}

void EditorLooper::OnWinMsg(int64_t hWnd, uint32_t msg, int64_t wParam, int64_t lParam)
{
    _pEditor->OnWinMsg(hWnd, msg, wParam, lParam);
}
