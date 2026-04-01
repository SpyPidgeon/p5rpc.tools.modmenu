#include "guistructs.h"

HMODULE dll_handle;
SDL_Window *window = nullptr;
SDL_Renderer* renderer = nullptr;
ImFont* windowFont;

void GetMainMonitorResolution(int& w, int& h)
{
    HMONITOR monitor = MonitorFromWindow(GetForegroundWindow(), MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO info;

    info.cbSize = sizeof(MONITORINFO);
    if (GetMonitorInfoA(monitor, &info))
    {
        w = info.rcMonitor.right - info.rcMonitor.left;
        h = info.rcMonitor.bottom - info.rcMonitor.top;
    }
    else
    {
        w = 100;
        h = 100;
    }
}

int WINAPI ModMenuMain()
{
    Sleep(5000);
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
        return 1;

    int w;
    int h;
    GetMainMonitorResolution(w, h);

    w /= 4;
    h /= 3;

    SDL_CreateWindowAndRenderer("SpyPigeon's Mod Menu",w,h,SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALWAYS_ON_TOP,&window,&renderer);

    int top, left, bottom, right;
    SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right);
    SDL_SetWindowPosition(window,left,top);
    SDL_SetWindowOpacity(window, 0.75f);

    if (!window)
        return 1;

    SDL_Event e;
    bool quit = false;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    windowFont = io.Fonts->AddFontFromFileTTF(GetDLLPath("font\\arial.ttf").c_str(), h * 0.03f);

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    while (!quit)
    {
        while (SDL_PollEvent(&e) == true)
        {
            ImGui_ImplSDL3_ProcessEvent(&e);

            switch (e.type)
            {
            case SDL_EVENT_QUIT:
                quit = true;
                break;
            case SDL_EVENT_WINDOW_FOCUS_LOST:
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                break;
            case SDL_EVENT_MOUSE_MOTION:
                break;
            }
        }

        SDL_RenderClear(renderer);

        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();
        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

        SDL_RenderPresent(renderer);
    }

    io.Fonts->RemoveFont(windowFont);

    ImGui_ImplSDL3_Shutdown();
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

extern "C" __declspec(dllexport) void __stdcall Init()
{
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ModMenuMain, 0,0,0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        dll_handle = hModule;
        FILE* newOut;
        freopen_s(&newOut, "CONOUT$", "w", stdout);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

