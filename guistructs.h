#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern HMODULE dll_handle;

std::string GetDLLPath(const std::string& path);