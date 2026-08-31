#include "gamehooks.h"
#include "signaturescan.h"
#include "skillstructs.h"
#include <type_traits>
#include "imguistyling.h"
#include "dx11_detour.h"

HMODULE dll_handle;
extern ImFont* windowFont;
ImSettings config;

void InitScan()
{
    std::string pattern;

    pattern = "48 8D 0D ?? ?? ?? ?? 48 8D 15 ?? ?? ?? ?? 0F 1F 00 8B 41 ??";
    DWORD_PTR activeSkills = PatternScan(GetModuleHandle(NULL), pattern);
    activeSkills = GetAddressFromGlobalRef(activeSkills);
    SkillPanel* skillPanel = SkillPanel::GetInstance();

    skillPanel->activeSkillsPTR = (std::array<ActiveSkill, skillPanel->ACTIVE_SKILL_SIZE>*)(activeSkills - 0x20);
    skillPanel->activeSkillArray = *skillPanel->activeSkillsPTR;

    pattern = "48 8D 0D ?? ?? ?? ?? 66 89 05 ?? ?? ?? ?? 48 8D 15 ?? ?? ?? ?? 66 66 0F 1F 84 ?? 00 00 00 00";
    DWORD_PTR skillElements = PatternScan(GetModuleHandle(NULL), pattern);
    skillElements = GetAddressFromGlobalRef(skillElements);
    skillPanel->skillElementArray = *(std::array<SkillElement, skillPanel->SKILL_ELEMENT_SIZE>*)(skillElements);

    pattern = "48 89 05 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 49 8B C8 48 89 05 ?? ?? ?? ?? 48 D1 E9 66 89 0D ?? ?? ?? ?? 48 8B C8 E8 ?? ?? ?? ?? 66 3B 1D ?? ?? ?? ?? 44 8B C3 73 ?? 48 8B 05 ?? ?? ?? ?? 41 8B C8 41 FF C0 48 8D 14 ?? 0F B7 04 ?? 66 C1 C0 08 66 89 02 0F B7 05 ?? ?? ?? ?? 44 3B C0 72 ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 48 8B C8 48 89 05 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 49 8B C8 48 89 05 ?? ?? ?? ?? 48 D1 E9 66 89 0D ?? ?? ?? ?? 48 8B C8 E8 ?? ?? ?? ?? 66 3B 1D ?? ?? ?? ?? 44 8B C3 73 ?? 66 66 0F 1F 84 ?? 00 00 00 00 48 8B 05 ?? ?? ?? ?? 41 8B C8 41 FF C0 48 8D 14 ?? 0F B7 04 ?? 66 C1 C0 08 66 89 02 0F B7 05 ?? ?? ?? ?? 44 3B C0 72 ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 48 8B C8 48 89 05 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 49 8B C8 48 89 05 ?? ?? ?? ?? 48 D1 E9 66 89 0D ?? ?? ?? ?? 48 8B C8 E8 ?? ?? ?? ?? 66 3B 1D ?? ?? ?? ?? 44 8B C3 73 ?? 48 8B 05 ?? ?? ?? ?? 41 8B C8 41 FF C0 48 8D 14 ?? 0F B7 04 ?? 66 C1 C0 08 66 89 02 0F B7 05 ?? ?? ?? ?? 44 3B C0 72 ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 48 8B C8 48 89 05 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 49 8B C8 48 89 05 ?? ?? ?? ?? 48 D1 E9 66 89 0D ?? ?? ?? ?? 48 8B C8 E8 ?? ?? ?? ?? 66 3B 1D ?? ?? ?? ?? 44 8B C3 73 ?? 66 66 0F 1F 84 ?? 00 00 00 00 48 8B 05 ?? ?? ?? ?? 41 8B C8 41 FF C0 48 8D 14 ?? 0F B7 04 ?? 66 C1 C0 08 66 89 02 0F B7 05 ?? ?? ?? ?? 44 3B C0 72 ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 48 8B C8 48 89 05 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 49 8B C8 48 89 05 ?? ?? ?? ?? 48 D1 E9 66 89 0D ?? ?? ?? ?? 48 8B C8 E8 ?? ?? ?? ?? 66 3B 1D ?? ?? ?? ?? 44 8B C3 73 ?? 48 8B 05 ?? ?? ?? ?? 41 8B C8 41 FF C0 48 8D 14 ?? 0F B7 04 ?? 66 C1 C0 08 66 89 02 0F B7 05 ?? ?? ?? ?? 44 3B C0 72 ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3";
    DWORD_PTR activeSkillNames = PatternScan(GetModuleHandle(NULL), pattern);

    activeSkillNames = *(DWORD_PTR*)GetAddressFromGlobalRef(activeSkillNames);

    if (activeSkillNames != 0)
    {
        for (int i = 0; i < skillPanel->SKILL_ELEMENT_SIZE; i++)
        {
            skillPanel->skillNames[i] = GetNameFromBinary(i, activeSkillNames);
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

    pattern = "48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 41 0F B7 C6";
    DWORD_PTR inventoryAddresses = PatternScan(GetModuleHandle(NULL), pattern);
    std::array<DWORD_PTR,9> itemAddresses;

    // Getting correct offsets
    for (int i = 0; i < 9; i++)
    {
        int offset = i * 12;
        itemAddresses[i] = GetAddressFromGlobalRef(inventoryAddresses + offset);

        if (i != 4)
            itemAddresses[i] = GetAddressFromGlobalRef(itemAddresses[i] + 17);
        else
            itemAddresses[i] = GetAddressFromGlobalRef(itemAddresses[i] + 10);
    }

    pattern = "48 8B 0D ?? ?? ?? ?? 48 89 1D ?? ?? ?? ?? 48 85 C9 74 ?? E8 ?? ?? ?? ?? 41 B8 04 00 00 00";
    DWORD_PTR rangedNameAddress = PatternScan(GetModuleHandle(NULL), pattern);
    DWORD_PTR otherItemsNameAddress = rangedNameAddress - 360;
    std::array<DWORD_PTR, 9> itemNameAddresses;

    itemNameAddresses[8] = *(DWORD_PTR*)GetAddressFromGlobalRef(rangedNameAddress);

    for (int i = 0; i < 8; i++)
    {
        int offset = i * 24;
        itemNameAddresses[i] = *(DWORD_PTR*)GetAddressFromGlobalRef(otherItemsNameAddress + offset);
    }

    SetInventoryAddresses(playerInventory, itemAddresses);
    SetInventoryNames(playerInventory, itemNameAddresses);

    pattern = "48 8B C4 48 81 EC 98 00 00 00 80 3D ? ? ? ? 00";
    oMouseState = (MouseState)PatternScan(GetModuleHandle(NULL), pattern);

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)oMouseState, MouseStateHook);
    DetourTransactionCommit();
}

extern bool quit;
int WINAPI ModMenuMain()
{
    while (true)
    {
        Sleep(50);
        if (GetAsyncKeyState(VK_F1))
            break;
    }

    InitScan();

    IMGUI_CHECKVERSION();

    if (!DX11Hook())
    {
        printf("Failed to hook dx11\n");
        return 1;
    }

    printf("Loaded mod\n");
    ImGuiIO& io = ImGui::GetIO();
    SetImReflectConfig();

    while (!quit)
    {
        Sleep(500);
    }

    printf("Mod exited\n");
    io.Fonts->RemoveFont(windowFont);

    ImGui::DestroyContext();
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

