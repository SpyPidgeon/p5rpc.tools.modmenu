#include "gamehooks.h"

std::array<ActiveSkill, ACTIVE_SKILL_SIZE> ActiveSkillArray;
std::array<ActiveSkill, ACTIVE_SKILL_SIZE>* ActiveSkillsPTR;

std::array<std::string, SKILL_ELEMENT_SIZE> SkillNames;
std::array<std::string, PERSONA_LIST_SIZE> personaNames;

std::array<SkillElement, SKILL_ELEMENT_SIZE> SkillElementArray;

std::array<GFDFileInfo, FILE_ARRAY_SIZE>* gfdFiles;

GetDatUnitByID GetDatUnit;
std::array<std::pair<DatUnit, std::string>, PARTY_MAX> partyMembers;
std::array<DatUnit*, PARTY_MAX> partyMemberPTRs;

std::string GetNameFromBinary(const uint32_t currentIndex, const uintptr_t nameAddress)
{
	unsigned int j = 0;
	unsigned int nameOffset = 0;

	while (j < currentIndex)
	{
		if (*reinterpret_cast<BYTE*>(nameAddress + nameOffset) == 0x00)
		{
			j++;
		}
		nameOffset++;
	}

	std::string binaryName;

	while (*reinterpret_cast<BYTE*>(nameAddress + nameOffset) != 0x00)
	{
		binaryName.push_back((char)*reinterpret_cast<char*>(nameAddress + nameOffset));
		nameOffset++;
	}

	return binaryName;
}