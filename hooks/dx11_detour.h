#pragma once
#include "gamehooks.h"

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <detours.h>

#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx11.h"

#include <iostream>

extern bool fetchContext;

bool DX11Hook();
void ToggleRender();