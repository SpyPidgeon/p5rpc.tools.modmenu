#include "gamehooks.h"

std::array<std::string, PERSONA_LIST_SIZE> personaNames;

std::array<GFDFileInfo, FILE_ARRAY_SIZE>* gfdFiles;

GetDatUnitByID GetDatUnit;
std::array<std::pair<DatUnit, std::string>, PARTY_MAX> partyMembers;
std::array<DatUnit*, PARTY_MAX> partyMemberPTRs;

Inventory playerInventory;

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

void RefreshFullInventory(Inventory& inv)
{
	visit_struct::for_each(inv, RefreshInventory());
}

void SetInventoryAddresses(Inventory& inv, std::array<DWORD_PTR, 9>& addresses)
{
	int index = 0;
	visit_struct::for_each(inv, [&index, &addresses](const char* name, auto& member)
		{
			member.SetData(addresses[index]);
			index++;
		}
	);
}

enum ItemTypeNames : uint8_t
{
	ACCESSORY = 0,
	ARMOR = 1,
	CONSUMABLE = 2,
	KEY = 3,
	MATERIAL = 4,
	MELEE = 5,
	OUTFIT = 6,
	CARD = 7,
	RANGED = 8
};

void SetInventoryNames(Inventory& inv, std::array<DWORD_PTR, 9>& addresses)
{
	inv.accessory.SetNames(addresses[ACCESSORY]);
	inv.armor.SetNames(addresses[ARMOR]);
	inv.consumable.SetNames(addresses[CONSUMABLE]);
	inv.key.SetNames(addresses[KEY]);
	inv.material.SetNames(addresses[MATERIAL]);
	inv.melee.SetNames(addresses[MELEE]);
	inv.card.SetNames(addresses[CARD]);
	inv.outfit.SetNames(addresses[OUTFIT]);
	inv.ranged.SetNames(addresses[RANGED]);
}

void ApplyAllInventoryValues(Inventory& inv)
{
	visit_struct::for_each(inv, [](const char* name, auto& value)
		{
			value.ApplyValues();
		});
}

MouseState oMouseState;
extern bool fetchContext;
void MouseStateHook()
{
	if (fetchContext)
		return;

	oMouseState();
}