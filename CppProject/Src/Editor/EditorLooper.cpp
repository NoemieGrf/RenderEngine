#include "EditorLooper.h"
#include "Application/Application.h"
#include "imgui.h"
#include "imgui_impl_win32.h"

using namespace Editor;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EditorLooper::EditorLooper()
{
    RendererApi api = Application::GetInstance()->GetRenderApi();

    _pBackend = EditorBackend::Create(api);

    Application::GetInstance()->AddWinMsgProc(this);

    // Create ImGui Context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsLight();

    // Backend Setup
    _pBackend->SetUp();

    // Get Dpi Scale
    auto hWnd = Application::GetInstance()->GetWindowHandle();
    float dpiScale = ImGui_ImplWin32_GetDpiScaleForHwnd(hWnd);
    ImGui::GetStyle().ScaleAllSizes(dpiScale);

    // Load Font
    float fontSize = 16 * dpiScale;
    ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\consola.ttf", fontSize, nullptr, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    IM_ASSERT(font != nullptr);
}

EditorLooper::~EditorLooper()
{
    Application::GetInstance()->RemoveWinMsgProc(this);

    _pBackend->Destroy();

    ImGui::DestroyContext();

    delete _pBackend;
}

void EditorLooper::Loop()
{
    _pBackend->BeforeUpdate();

    ImGui::NewFrame();

    // temp
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(main_viewport->WorkPos.x / 3, main_viewport->WorkPos.y / 2), ImGuiCond_Always);

    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Test", nullptr, window_flags);

    ImGui::Button("Test");

    ImGui::End();

    // TODO editor logic

    ImGui::Render();

    _pBackend->AfterUpdate();
}

void EditorLooper::OnWinMsg(int64_t hWnd, uint32_t msg, int64_t wParam, int64_t lParam)
{
    ImGui_ImplWin32_WndProcHandler(
            reinterpret_cast<HWND>(hWnd),
            static_cast<UINT>(msg),
            static_cast<WPARAM>(wParam),
            static_cast<LPARAM>(lParam));
}
