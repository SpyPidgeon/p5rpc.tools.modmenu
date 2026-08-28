#pragma once
#include "guistructs.h"

constexpr uint8_t GFDPATH_MAX = 128;

struct GFDFileInfo
{
	uint64_t data0;
	uint64_t data1;
	std::array<char, GFDPATH_MAX> path;
	DWORD_PTR fileAddress;
	uint64_t fileSize;
	uint64_t unknown;
};

IMGUI_REFLECT(GFDFileInfo,data0,data1, path, fileAddress,fileSize,unknown);

static_assert(sizeof(GFDFileInfo) == 168, "GFDFileInfo is the wrong size");