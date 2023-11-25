#pragma once

#include "Backend/EditorBackend.h"

namespace Editor
{
    class Environment
    {
    public:
        Environment() = delete;
        ~Environment() = delete;
        Environment& operator=(const Environment&) = delete;

    public:
        static void Init();
        static void Destroy();
        static void BeforeLoop();
        static void AfterLoop();
        static void OnWinMsg(int64_t hWnd, uint32_t msg, int64_t wParam, int64_t lParam);

    private:
        inline static EditorBackend* _pBackend = nullptr;
    };
}