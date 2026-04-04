#pragma once
#include "guistructs.h"
#include "displaystructwindow.h"

constexpr uint16_t ACTIVE_SKILL_SIZE = 800;

std::string GetNameFromBinary(const uint32_t currentIndex, const uintptr_t nameAddress);

extern std::array<ActiveSkill,ACTIVE_SKILL_SIZE> ActiveSkillArray;
extern std::array<std::string, ACTIVE_SKILL_SIZE> ActiveSkillNames;