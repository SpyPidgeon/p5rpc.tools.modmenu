#include "gamehooks.h"
#include "skillstructs.h"
#include "signaturescan.h"

HMODULE dll_handle;
SDL_Window *window = nullptr;
SDL_Renderer* renderer = nullptr;
ImFont* windowFont;
ImSettings config;

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

void InitScan()
{
    std::string pattern;

    pattern = "48 8D 0D ?? ?? ?? ?? 48 8D 15 ?? ?? ?? ?? 0F 1F 00 8B 41 ??";
    DWORD_PTR activeSkills = PatternScan(GetModuleHandle(NULL), pattern);
    activeSkills = GetAddressFromGlobalRef(activeSkills);
    ActiveSkillsPTR = (std::array<ActiveSkill,ACTIVE_SKILL_SIZE>*)(activeSkills - 0x20);
    ActiveSkillArray = *ActiveSkillsPTR;

    pattern = "48 8D 0D ?? ?? ?? ?? 66 89 05 ?? ?? ?? ?? 48 8D 15 ?? ?? ?? ?? 66 66 0F 1F 84 ?? 00 00 00 00";
    DWORD_PTR skillElements = PatternScan(GetModuleHandle(NULL), pattern);
    skillElements = GetAddressFromGlobalRef(skillElements);
    SkillElementArray = *(std::array<SkillElement, SKILL_ELEMENT_SIZE>*)(skillElements);

    pattern = "48 89 05 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 49 8B C8 48 89 05 ?? ?? ?? ?? 48 D1 E9 66 89 0D ?? ?? ?? ?? 48 8B C8 E8 ?? ?? ?? ?? 66 3B 1D ?? ?? ?? ?? 44 8B C3 73 ?? 48 8B 05 ?? ?? ?? ?? 41 8B C8 41 FF C0 48 8D 14 ?? 0F B7 04 ?? 66 C1 C0 08 66 89 02 0F B7 05 ?? ?? ?? ?? 44 3B C0 72 ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 48 8B C8 48 89 05 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 49 8B C8 48 89 05 ?? ?? ?? ?? 48 D1 E9 66 89 0D ?? ?? ?? ?? 48 8B C8 E8 ?? ?? ?? ?? 66 3B 1D ?? ?? ?? ?? 44 8B C3 73 ?? 66 66 0F 1F 84 ?? 00 00 00 00 48 8B 05 ?? ?? ?? ?? 41 8B C8 41 FF C0 48 8D 14 ?? 0F B7 04 ?? 66 C1 C0 08 66 89 02 0F B7 05 ?? ?? ?? ?? 44 3B C0 72 ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 48 8B C8 48 89 05 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 49 8B C8 48 89 05 ?? ?? ?? ?? 48 D1 E9 66 89 0D ?? ?? ?? ?? 48 8B C8 E8 ?? ?? ?? ?? 66 3B 1D ?? ?? ?? ?? 44 8B C3 73 ?? 48 8B 05 ?? ?? ?? ?? 41 8B C8 41 FF C0 48 8D 14 ?? 0F B7 04 ?? 66 C1 C0 08 66 89 02 0F B7 05 ?? ?? ?? ?? 44 3B C0 72 ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 48 8B C8 48 89 05 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 49 8B C8 48 89 05 ?? ?? ?? ?? 48 D1 E9 66 89 0D ?? ?? ?? ?? 48 8B C8 E8 ?? ?? ?? ?? 66 3B 1D ?? ?? ?? ?? 44 8B C3 73 ?? 66 66 0F 1F 84 ?? 00 00 00 00 48 8B 05 ?? ?? ?? ?? 41 8B C8 41 FF C0 48 8D 14 ?? 0F B7 04 ?? 66 C1 C0 08 66 89 02 0F B7 05 ?? ?? ?? ?? 44 3B C0 72 ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 48 8B C8 48 89 05 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 49 8B C8 48 89 05 ?? ?? ?? ?? 48 D1 E9 66 89 0D ?? ?? ?? ?? 48 8B C8 E8 ?? ?? ?? ?? 66 3B 1D ?? ?? ?? ?? 44 8B C3 73 ?? 48 8B 05 ?? ?? ?? ?? 41 8B C8 41 FF C0 48 8D 14 ?? 0F B7 04 ?? 66 C1 C0 08 66 89 02 0F B7 05 ?? ?? ?? ?? 44 3B C0 72 ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3";
    DWORD_PTR activeSkillNames = PatternScan(GetModuleHandle(NULL), pattern);

    activeSkillNames = *(DWORD_PTR*)GetAddressFromGlobalRef(activeSkillNames);

    if (activeSkillNames != 0)
    {
        for (int i = 0; i < SKILL_ELEMENT_SIZE; i++)
        {
            SkillNames[i] = GetNameFromBinary(i, activeSkillNames);
        }
    }

    pattern = "48 03 1D ?? ?? ?? ?? F3 41 0F 59 FA";
    DWORD_PTR personaNamesAddress = PatternScan(GetModuleHandle(NULL), pattern);
    personaNamesAddress = *(DWORD_PTR*)GetAddressFromGlobalRef(personaNamesAddress);

    if (personaNamesAddress != 0)
    {
        for (int i = 0; i < PERSONA_LIST_SIZE; i++)
        {
            personaNames[i] = GetNameFromBinary(i, personaNamesAddress);
        }
    }

    pattern = "0F B7 C1 48 8D 0D ? ? ? ? 48 69 C0 A0 02 00 00 48 01 C8";
    GetDatUnit = (GetDatUnitByID)(PatternScan(GetModuleHandle(NULL), pattern));

    pattern = "48 03 1D ?? ?? ?? ?? E9 ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ??";
    DWORD_PTR partyNamesPTR = PatternScan(GetModuleHandle(NULL), pattern);
    partyNamesPTR = GetAddressFromGlobalRef(partyNamesPTR);

    partyNamesPTR = *(DWORD_PTR*)partyNamesPTR;
    while (*(BYTE*)partyNamesPTR == 0x00)
        partyNamesPTR++;

    DWORD_PTR partyMembersAddress = (DWORD_PTR)GetDatUnit(1);

    for (int i = 0; i < 10; i++)
    {
        partyMemberPTRs[i] = GetDatUnit(i + 1);
        partyMembers[i] = { *partyMemberPTRs[i],GetNameFromBinary(i + 1,partyNamesPTR) };
    }

    pattern = "48 8D 15 ?? ?? ?? ?? 8B 8C ?? ?? ?? ?? ?? 41 89 0F";
    DWORD_PTR fileArrayStart = PatternScan(GetModuleHandle(NULL), pattern);
    fileArrayStart = GetAddressFromGlobalRef(fileArrayStart);

    gfdFiles = (std::array<GFDFileInfo, FILE_ARRAY_SIZE>*)fileArrayStart;
}

int WINAPI ModMenuMain()
{
    Sleep(10000);
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
        return 1;

    InitScan();

    int w;
    int h;
    GetMainMonitorResolution(w, h);

    w /= 4;
    h /= 2;

    SDL_CreateWindowAndRenderer("SpyPigeon's Mod Menu",w,h,SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALWAYS_ON_TOP,&window,&renderer);

    int top, left, bottom, right;
    SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right);
    SDL_SetWindowPosition(window,left,top);
//    SDL_SetWindowOpacity(window, 0.75f);

    if (!window)
        return 1;

    SDL_Event e;
    bool quit = false;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    windowFont = io.Fonts->AddFontFromFileTTF(GetDLLPath("font\\arial.ttf").c_str(), h * 0.025f);

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    config = ImSettings();
    config.push_member<&ActiveSkill::validTargetFlags>()
        .as_flags()
        .pop();
    config.push_member<&ActiveSkill::effectChance>()
        .as_slider()
        .min(0)
        .max(100)
        .pop();
    config.push_member<&ActiveSkill::critChance>()
        .as_slider()
        .min(0)
        .max(100)
        .pop();
    config.push_member<&ActiveSkill::accuracy>()
        .as_slider()
        .min(0)
        .max(100)
        .pop();
    config.push_member<&ActiveSkill::commonAilments1>()
        .as_flags()
        .pop();
    config.push_member<&ActiveSkill::specialAilments>()
        .as_flags()
        .pop();
    config.push_member<&ActiveSkill::commonAilments2>()
        .as_flags()
        .pop();
    config.push_member<&ActiveSkill::buffsAndDebuffs>()
        .as_flags()
        .pop();
    config.push_member<&ActiveSkill::commonBuffs>()
        .as_flags()
        .pop();
    config.push_member<&ActiveSkill::shields>()
        .as_flags()
        .pop();
    config.push_member<&ActiveSkill::breakSkills>()
        .as_flags()
        .pop();

    config.push_member<&SkillElement::inheritable>()
        .as_slider()
        .min(0)
        .max(8)
        .pop();

    config.push_member < &DatUnit_Stats::strength>()
        .as_slider()
        .min(0)
        .max(99)
        .pop();
    config.push_member < &DatUnit_Stats::magic>()
        .as_slider()
        .min(0)
        .max(99)
        .pop();
    config.push_member < &DatUnit_Stats::endurance>()
        .as_slider()
        .min(0)
        .max(99)
        .pop();
    config.push_member < &DatUnit_Stats::agility>()
        .as_slider()
        .min(0)
        .max(99)
        .pop();
    config.push_member < &DatUnit_Stats::luck>()
        .as_slider()
        .min(0)
        .max(99)
        .pop();

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
        RenderStructWidgets();
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

