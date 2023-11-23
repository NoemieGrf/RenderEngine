#pragma once

#include "Application/AppLooper.h"
#include "Editor/Editor.h"

class EditorLooper : public AppLooper
{
public:
    EditorLooper();
    ~EditorLooper() override;

public:
    void Loop() override;

private:
    Editor::Editor* _pEditor = nullptr;
};