// dllmain.cpp : Defines the entry point for the DLL application.
#include "SDL3/SDL.h"
#include <sstream>
#include "guistructs.h"

HMODULE dll_handle;
static SDL_Window *window = nullptr;
static SDL_Renderer* renderer = nullptr;
static SDL_Surface *background = nullptr;

std::vector<GUIElement*> guiElements;
GUIElement* activeElement;

TTF_Font* windowFont;
int32_t* money;

std::string GetDLLPath(const std::string& path)
{
    char dllPath[MAX_PATH] = { 0 };
    GetModuleFileNameA(dll_handle, dllPath, MAX_PATH);

    std::string fullPath(dllPath);

    size_t lastSlash = fullPath.find_last_of("\\/");
    std::string baseDirectory = (lastSlash != std::string::npos) ? fullPath.substr(0, lastSlash + 1) : "";

    std::ostringstream ss;
    ss << baseDirectory << path;

    return ss.str();
}

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

    windowFont = TTF_OpenFont(GetDLLPath("font\\arial.ttf").c_str(), h * 0.05f);

    w /= 4;
    h /= 4;

    SDL_CreateWindowAndRenderer("Mod Menu",w,h,SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALWAYS_ON_TOP,&window,&renderer);

    int top, left, bottom, right;
    SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right);
    SDL_SetWindowPosition(window,left,top);
    SDL_SetWindowOpacity(window, 0.75f);

    if (!window)
        return 1;

    background = SDL_GetWindowSurface(window);

    if (!background)
        return 1;

    SDL_Event e;
    bool quit = false;

    Button getMoney = Button();

    getMoney.Behavior = &SetMoney;
    getMoney.rect = new SDL_FRect();
    getMoney.rect->x = w / 2;
    getMoney.rect->y = h / 2;
    getMoney.rect->w = 100;
    getMoney.rect->h = 100;

    guiElements.push_back((GUIElement*)&getMoney);
    money = (int32_t*)(0x1428551fc);

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
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    POINT start;
                    start.x = getMoney.rect->x;
                    start.y = getMoney.rect->y;
                    
                    POINT end;
                    end.x = start.x + getMoney.rect->w;
                    end.y = start.y + getMoney.rect->h;

                    POINT cursor;
                    GetCursorPos(&cursor);
                    ScreenToClient(GetForegroundWindow(), &cursor);

                    if (AABBMouseCheck(start, end, cursor))
                    {
                        getMoney.Behavior();
                    }
                }
                break;
            }
        }

        SDL_FillSurfaceRect(background, nullptr, SDL_MapSurfaceRGB(background,66,66,66));
        SDL_UpdateWindowSurface(window);

        RenderGUI(window, renderer);

        SDL_RenderPresent(renderer);
    }

    guiElements.clear();
    delete(getMoney.rect);

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
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

