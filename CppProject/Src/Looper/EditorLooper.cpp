#include "EditorLooper.h"

EditorLooper::EditorLooper()
{
    _pEditor = new Editor::Editor(RendererApi::OpenGL);
    _pEditor->SetUp();
}

EditorLooper::~EditorLooper()
{
    _pEditor->Destroy();
    delete _pEditor;
}

void EditorLooper::Loop()
{
    _pEditor->Update();
}
