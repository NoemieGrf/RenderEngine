#pragma once

#include "Backend/EditorBackend.h"
#include "Define/RendererApi.h"
#include "Util/NonCopyable.h"

namespace Editor
{
    class Editor
    {
    public:
        explicit Editor(RendererApi api);
        ~Editor() = default;

    public:
        void SetUp();
        void Update();
        void Destroy();
        void OnWinMsg(int64_t hWnd, uint32_t msg, int64_t wParam, int64_t lParam);

    private:
        EditorBackend* _pBackend = nullptr;

    };
}