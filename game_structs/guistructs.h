#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include "ImReflect.hpp"

extern HMODULE dll_handle;

std::string GetDLLPath(const std::string& path);
void HelpMarker(const char* desc);