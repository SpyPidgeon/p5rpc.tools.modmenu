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

#pragma pack(push,1)
struct ActiveSkill
{
	uint8_t casterEffect2;
	uint8_t casterEffect1;
	uint8_t conditionUsage;	
	uint8_t unkr0;	
	uint8_t areaType;	
	uint8_t unkr1;
	uint8_t damageStatType;
	uint8_t costType;
	uint16_t cost;	
	uint8_t skillType;	
	uint8_t multiplyCost;	
	uint8_t targetType;
	BYTE validTargetFlags;	
	uint8_t targetRestrictions;	
	uint8_t unk0;	
	uint8_t unk1;	
	uint8_t unk2;	
	uint8_t unk3;
	uint8_t unk4;
	uint8_t accuracy;
	uint8_t minHits;
	uint8_t maxHits;
	uint8_t damageOrHeal;
	uint16_t damageValue;
	uint8_t spEffect;
	uint8_t unk5;	
	uint16_t spRestoreValue;
	uint8_t applyOrCure;
	uint8_t effectChance;
	BYTE commonAilments1;
	uint8_t unk6;
	BYTE specialAilments;
	BYTE commonAilments2;
	BYTE buffsAndDebuffs;
	BYTE commonBuffs;
	BYTE breakSkills;
	BYTE shields;
	uint8_t otherBuffs;
	uint16_t reserve;
	uint8_t unkr2;
	uint8_t extraEffects;
	uint8_t critChance;
	bool forItem;
	uint8_t unk7;
};
#pragma pack(pop)

static_assert(sizeof(ActiveSkill) == 48, "ActiveSkill size must be 48 bytes.");

IMGUI_REFLECT
(ActiveSkill, casterEffect2,casterEffect1,conditionUsage,unkr0,areaType,unkr1,damageStatType,costType,cost,skillType,multiplyCost,targetType,
validTargetFlags,targetRestrictions,unk0,unk1,unk2,unk3,unk4,accuracy,minHits,maxHits,damageOrHeal,damageValue,spEffect,unk5,spRestoreValue,
applyOrCure,effectChance,commonAilments1,unk6,specialAilments,commonAilments2,buffsAndDebuffs,commonBuffs,breakSkills,shields,otherBuffs,
reserve,unkr2,extraEffects,critChance,forItem,unk7);