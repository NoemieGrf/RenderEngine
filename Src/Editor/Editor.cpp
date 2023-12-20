#include "Editor.h"
#include "Application/Application.h"
#include "imgui.h"
#include "imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Editor
{

    void Environment::Init()
    {
        RendererApi api = Application::GetRenderApi();

        _pBackend = EditorBackend::Create(api);

        // Create ImGui Context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        ImGui::StyleColorsLight();

        // Backend Setup
        _pBackend->SetUp();

        // Get Dpi Scale
        auto hWnd = Application::GetWindowHandle();
        float dpiScale = ImGui_ImplWin32_GetDpiScaleForHwnd(hWnd);
        ImGui::GetStyle().ScaleAllSizes(dpiScale);

        // Load Font
        float fontSize = 16 * dpiScale;
        ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\consola.ttf", fontSize, nullptr, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
        IM_ASSERT(font != nullptr);
    }

    void Environment::Destroy()
    {
        _pBackend->Destroy();

        ImGui::DestroyContext();

        delete _pBackend;
    }

    void Environment::BeforeLoop()
    {
        _pBackend->BeforeUpdate();
        ImGui::NewFrame();
    }

    void Environment::AfterLoop()
    {
        ImGui::Render();
        _pBackend->AfterUpdate();
    }

    void Environment::OnWinMsg(int64_t hWnd, uint32_t msg, int64_t wParam, int64_t lParam)
    {
        ImGui_ImplWin32_WndProcHandler(
                reinterpret_cast<HWND>(hWnd),
                static_cast<UINT>(msg),
                static_cast<WPARAM>(wParam),
                static_cast<LPARAM>(lParam));
    }
}