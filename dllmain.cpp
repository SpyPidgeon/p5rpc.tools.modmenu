#include "guistructs.h"

HMODULE dll_handle;
SDL_Window *window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Surface *background = nullptr;

std::vector<GUIElement*> guiElements;
GUIElement* activeElement;

TTF_Font* windowFont;

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
    h /= 4;

    SDL_CreateWindowAndRenderer("SpyPigeon's Mod Menu",w,h,SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALWAYS_ON_TOP,&window,&renderer);

    int top, left, bottom, right;
    SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right);
    SDL_SetWindowPosition(window,left,top);
    SDL_SetWindowOpacity(window, 0.75f);

    if (!window)
        return 1;

    background = SDL_GetWindowSurface(window);

    if (!background)
        return 1;

    TTF_Init();
    windowFont = TTF_OpenFont(GetDLLPath("font\\arial.ttf").c_str(), h * 0.05f);


    GUIElement test;
    test.borderOnly = true;
    test.mainTexture->LoadTextTexture("Test", SDL_Color{ 255,255,255,255 });

    guiElements.push_back(&test);

    SDL_Event e;
    bool quit = false;

    while (!quit)
    {
        if (GetAsyncKeyState(VK_BACK))
            break;

        while (SDL_PollEvent(&e) == true)
        {
            switch (e.type)
            {
            case SDL_EVENT_QUIT:
                quit = true;
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                background = SDL_GetWindowSurface(window);
                break;
            case SDL_EVENT_WINDOW_FOCUS_LOST:
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                break;
            }
        }

        SDL_RenderClear(renderer);

        SDL_FillSurfaceRect(background, nullptr, SDL_MapSurfaceRGB(background,66,66,128));
        SDL_UpdateWindowSurface(window);

        RenderGUI();

        SDL_RenderPresent(renderer);
    }

    guiElements.clear();

    TTF_CloseFont(windowFont);
    TTF_Quit();
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

