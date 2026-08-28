#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"
#include "ImReflect.hpp"

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern HMODULE dll_handle;

std::string GetDLLPath(const std::string& path);
void HelpMarker(const char* desc);

struct Texture
{
	Texture() : texture(nullptr) {}
	~Texture() { Destroy(); }

	bool LoadTexture(const char* path);
	void Destroy();

	SDL_Texture* texture;
};