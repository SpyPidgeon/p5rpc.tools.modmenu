#pragma once
#include <windows.h>
#include <psapi.h>
#include <string>
#include <vector>

DWORD_PTR PatternScan(HMODULE handle, const std::string& pattern);
bool BulkScan(std::vector<std::pair<std::string, DWORD_PTR*>>& patterns);
DWORD_PTR GetAddressFromString(DWORD_PTR startAddress, const char* stringSearch);


// Credit to DeathChaos
uint64_t GetAddressFromFuncCall(uint64_t a1);
uint64_t GetAddressFromGlobalRef(uint64_t a1);
uint64_t GetAddressFromMOV(uint64_t a1);
