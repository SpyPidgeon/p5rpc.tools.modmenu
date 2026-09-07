#pragma once
#include <cstdint>
#include "guistructs.h"
#include "displaystructwindow.h"
#include "skillstructs.h"
#include "battlestructs.h"
#include "filestructs.h"
#include "panels.h"

constexpr uint16_t FILE_ARRAY_SIZE = 512;
extern std::array<GFDFileInfo, FILE_ARRAY_SIZE>* gfdFiles;

typedef DatUnit* (__stdcall* GetDatUnitByID)(uint16_t ID);
extern GetDatUnitByID GetDatUnit;

typedef void(__stdcall* MouseState)();
extern MouseState oMouseState;
void MouseStateHook();