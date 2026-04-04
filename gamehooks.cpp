#include "gamehooks.h"

std::array<ActiveSkill, ACTIVE_SKILL_SIZE> ActiveSkillArray;
std::array<std::string, ACTIVE_SKILL_SIZE> ActiveSkillNames;

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