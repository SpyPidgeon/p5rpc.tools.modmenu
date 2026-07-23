#pragma once
#include "guistructs.h"
#include "displaystructwindow.h"
#include "skillstructs.h"
#include "battlestructs.h"
#include "filestructs.h"

constexpr uint16_t ACTIVE_SKILL_SIZE = 800;
constexpr uint16_t SKILL_ELEMENT_SIZE = 1056;
constexpr uint8_t PARTY_MAX = 10;
constexpr uint16_t PERSONA_LIST_SIZE = 464;
constexpr uint16_t FILE_ARRAY_SIZE = 512;

std::string GetNameFromBinary(const uint32_t currentIndex, const uintptr_t nameAddress);

extern std::array<ActiveSkill,ACTIVE_SKILL_SIZE> ActiveSkillArray;
extern std::array<ActiveSkill, ACTIVE_SKILL_SIZE>* ActiveSkillsPTR;

extern std::array<std::string, SKILL_ELEMENT_SIZE> SkillNames;
extern std::array<std::string, PERSONA_LIST_SIZE> personaNames;

extern std::array<SkillElement, SKILL_ELEMENT_SIZE> SkillElementArray;

extern std::array<GFDFileInfo, FILE_ARRAY_SIZE>* gfdFiles;

typedef DatUnit* (__stdcall* GetDatUnitByID)(uint16_t ID);
extern GetDatUnitByID GetDatUnit;

extern std::array<std::pair<DatUnit,std::string>, PARTY_MAX> partyMembers;
extern std::array<DatUnit*,PARTY_MAX> partyMemberPTRs;