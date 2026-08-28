#include "signaturescan.h"
#include <cstring>
#include <algorithm>
#include <iostream>

DWORD_PTR PatternScan(HMODULE handle, const std::string& pattern)
{
    if (!handle)
    {
        printf("Failed to acquire handle.\n");
        return 0;
    }

    MODULEINFO moduleInfo;
    GetModuleInformation(GetCurrentProcess(), handle, &moduleInfo, sizeof(moduleInfo));

    BYTE* baseAddress = (BYTE*)moduleInfo.lpBaseOfDll;
    SIZE_T size = moduleInfo.SizeOfImage;

    std::vector<BYTE> patternBytes;
    std::string mask;

    for (size_t i = 0; i < pattern.length(); i++)
    {
        if (pattern[i] == ' ')
            continue;

        std::string byteStr = pattern.substr(i, 2);
        if (byteStr == "??")
        {
            patternBytes.push_back(0xFF);
            mask.push_back('?');
        }
        else if (byteStr == "? ")
        {
            patternBytes.push_back(0xFF);
            mask.push_back('?');
            continue;
        }
        else
        {
            patternBytes.push_back((BYTE)std::stoi(byteStr, nullptr, 16));
            mask.push_back('x');
        }

        i++;
    }

    for (SIZE_T i = 0; i < size - patternBytes.size(); i++)
    {
        bool foundAddress = true;

        for (size_t j = 0; j < patternBytes.size(); j++)
        {
            if (patternBytes[j] == 0xFF && mask[j] == '?')
                continue;

            if (baseAddress[i + j] != patternBytes[j])
            {
                foundAddress = false;
                break;
            }

        }

        if (foundAddress)
        {   
            return (DWORD_PTR)(baseAddress + i);
        }
    }

    printf("Could not find address of: %s\n",pattern.c_str());
    return 0;
}

bool BulkScan(std::vector<std::pair<std::string, DWORD_PTR*>> &patterns)
{
    HMODULE currentProcess = GetModuleHandle(NULL);
    if (!currentProcess)
    {
        printf("Failed to acquire current P5R handle.\n");
        return false;
    }

    if (patterns.empty())
    {
        printf("No patterns found!\n");
        return false;
    }

    MODULEINFO moduleInfo;
    GetModuleInformation(GetCurrentProcess(), currentProcess, &moduleInfo, sizeof(moduleInfo));

    BYTE* baseAddress = (BYTE*)moduleInfo.lpBaseOfDll;
    SIZE_T size = moduleInfo.SizeOfImage;

    std::vector<std::vector<BYTE>> patternsBytes;
    std::vector<std::string> masks;
    patternsBytes.resize(patterns.size());
    masks.resize(patterns.size());
    size_t largestPattern = 0;

    for (int i = 0; i < patterns.size(); i++)
    {
        for (size_t j = 0; j < patterns[i].first.length(); j++)
        {
            if (patterns[i].first[j] == ' ')
                continue;

            std::string byteStr = patterns[i].first.substr(j, 2);
            if (byteStr == "??")
            {
                patternsBytes[i].push_back(0xFF);
                masks[i].push_back('?');
            }
            else if (byteStr == "? ")
            {
                patternsBytes[i].push_back(0xFF);
                masks[i].push_back('?');
                continue;
            }
            else
            {
                patternsBytes[i].push_back((BYTE)std::stoi(byteStr, nullptr, 16));
                masks[i].push_back('x');
            }

            j++;
        }

        if (i != 0 && patterns[i] > patterns[i - 1])
            largestPattern = patternsBytes[i].size();
    }

    for (SIZE_T i = 0; i < size - largestPattern; i++)
    {
        bool foundAddress = true;

        for (int o = 0; o < patternsBytes.size(); o++)
        {
            if (patternsBytes.empty())
                return true;

            foundAddress = true;
            for (size_t j = 0; j < patternsBytes[o].size(); j++)
            {
                if (patternsBytes[o].size() <= j)
                {
                    foundAddress = false;
                    break;
                }

                if (masks[o][j] == '?')
                    continue;

                if (baseAddress[i + j] != patternsBytes[o][j])
                {
                    foundAddress = false;
                    break;
                }

            }

            if (foundAddress)
            {
                *patterns[o].second = (DWORD_PTR)(baseAddress + i);
                patterns.erase(patterns.begin() + o);
                patternsBytes.erase(patternsBytes.begin() + o);
                masks.erase(masks.begin() + o);
                break;
            }
        }
    }

    if (patternsBytes.empty())
    {
        return true;
    }

    if (patternsBytes.size() == patterns.size())
        printf("Could not find any addresses\n");
    else
    {
        for (auto pattern : patternsBytes)
        {
            printf("Could not find patterns:\n");
            std::cout << "Pattern: ";
            for (auto byte : pattern)
            {
                std::cout << std::hex << std::uppercase << byte;
            }
            std::cout << '\n';
        }
    }

    return false;
}

uint64_t GetAddressFromFuncCall(uint64_t a1)
{
    int opd = *(int*)(a1 + 1);
    return (a1 + opd + 5);
}

uint64_t GetAddressFromGlobalRef(uint64_t a1)
{
    int opd = *(int*)(a1 + 3);
    return (a1 + opd + 7);
}

uint64_t GetAddressFromMOV(uint64_t a1)
{
    int opd = *(int*)(a1 + 2);
    return (a1 + opd + 7);
}

DWORD_PTR GetAddressFromString(DWORD_PTR startAddress, const char* stringSearch)
{
    uint8_t stringLength = strlen(stringSearch);
    char firstChar = stringSearch[0];

    MODULEINFO moduleInfo;
    GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &moduleInfo, sizeof(moduleInfo));

    uint64_t searchSize = moduleInfo.SizeOfImage - startAddress;

    for (uint64_t i = 0; i < searchSize; i++)
    {
        BYTE currentByte = *reinterpret_cast<BYTE*>(startAddress + i);

        if ((char)currentByte != firstChar)
            continue;

        if (std::memcmp((void*)startAddress,stringSearch,stringLength) == 0)
        {
            return startAddress + i;
        }
    }

    return 0x00;
}