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

template<std::size_t N>
struct InventoryType
{
	std::array<uint8_t, N> items;
	std::array<std::string, N> names;
	DWORD_PTR address = NULL;
	DWORD_PTR namesAddress = NULL;
	//std::string names; TODO: Implement

	void SetData(DWORD_PTR address)
	{
		this->address = address;
		//Refresh();
	}

	void SetNames(DWORD_PTR address)
	{
		namesAddress = address;
	}

	void Refresh()
	{
		std::memcpy(items.data(), (void*)address, N);

		for (int i = 0; i < N; i++)
		{
			names[i] = GetNameFromBinary(i, namesAddress);
		}
	}

	void RenderSliders(const char* name,bool &changed)
	{
		const char* label = std::format("{} | {:X}", name, namesAddress).c_str();
		if (ImGui::CollapsingHeader(label))
		{
			for (int i = 0; i < items.size(); i++)
			{
				int value = items[i];
				changed = ImGui::SliderInt(std::format("ID: {} | {}",i,names[i]).c_str(), &value, 0, 99);
				items[i] = value;
			}
		}
	}

	void ApplyValues()
	{
		std::memcpy((void*)address, items.data(), N);
	}
};

struct Inventory
{
	InventoryType<296> melee;
	InventoryType<299> armor;
	InventoryType<512> accessory;
	InventoryType<696> consumable;
	InventoryType<256> key;
	InventoryType<256> material;
	InventoryType<401> card;
	InventoryType<286> outfit;
	InventoryType<256> ranged;
};
VISITABLE_STRUCT(Inventory, melee, armor, accessory, consumable, key, material, card, outfit, ranged);
IMGUI_REFLECT(Inventory, melee, armor, accessory, consumable, key, material, card, outfit, ranged);

struct RefreshInventory
{
	template<typename T>
	void operator()(const char* name, T& member)
	{
		member.Refresh();
	}
};

void RefreshFullInventory(Inventory& inv);
void SetInventoryAddresses(Inventory& inv, std::array<DWORD_PTR, 9>& addresses);
void SetInventoryNames(Inventory& inv, std::array<DWORD_PTR, 9>& addresses);
void ApplyAllInventoryValues(Inventory& inv);

extern Inventory playerInventory;