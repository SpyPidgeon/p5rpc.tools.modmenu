#include "gamehooks.h"
#include "signaturescan.h"
#include "skillstructs.h"
#include <type_traits>
#include "imguistyling.h"
#include "dx11_detour.h"

HMODULE dll_handle;
extern ImFont* windowFont;

void InitScan()
{
    for (auto panel : panels)
    {
        panel->ScanValues();
    }

    std::string pattern;

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

