#include "inventorypanel.h"
#include "signaturescan.h"

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

// Inventory Panel
void InventoryPanel::ScanValues()
{
	std::string pattern;

	pattern = "48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 48 8D 05 ?? ?? ?? ?? 48 89 44 24 ?? 41 0F B7 C6";
	DWORD_PTR inventoryAddresses = PatternScan(GetModuleHandle(NULL), pattern);
	std::array<DWORD_PTR, 9> itemAddresses;

	// Getting correct offsets
	for (int i = 0; i < 9; i++)
	{
		int offset = i * 12;
		itemAddresses[i] = GetAddressFromGlobalRef(inventoryAddresses + offset);

		if (i != 4)
			itemAddresses[i] = GetAddressFromGlobalRef(itemAddresses[i] + 17);
		else
			itemAddresses[i] = GetAddressFromGlobalRef(itemAddresses[i] + 10);
	}

	pattern = "48 8B 0D ?? ?? ?? ?? 48 89 1D ?? ?? ?? ?? 48 85 C9 74 ?? E8 ?? ?? ?? ?? 41 B8 04 00 00 00";
	DWORD_PTR rangedNameAddress = PatternScan(GetModuleHandle(NULL), pattern);
	DWORD_PTR otherItemsNameAddress = rangedNameAddress - 360;
	std::array<DWORD_PTR, 9> itemNameAddresses;

	itemNameAddresses[8] = *(DWORD_PTR*)GetAddressFromGlobalRef(rangedNameAddress);

	for (int i = 0; i < 8; i++)
	{
		int offset = i * 24;
		itemNameAddresses[i] = *(DWORD_PTR*)GetAddressFromGlobalRef(otherItemsNameAddress + offset);
	}

	SetInventoryAddresses(playerInventory, itemAddresses);
	SetInventoryNames(playerInventory, itemNameAddresses);
	RefreshFullInventory(playerInventory);
}

void InventoryPanel::RenderLogic()
{
	int i = 0;
	visit_struct::for_each(playerInventory, [&i,this](const char* name, auto& value)
		{
			if (ImGui::Button(name))
			{
				selected = i;
			}
			i++;
		});
}

void InventoryPanel::InspectorLogic()
{
	int i = 0;
	visit_struct::for_each(playerInventory, [&i,this](const char* name, auto& value)
		{
			if (i == selected)
			{
				value.RenderSliders();
			}

			i++;
		});
}

void InventoryPanel::Refresh()
{
	RefreshFullInventory(playerInventory);
}

void InventoryPanel::ApplyChanges()
{
	ApplyAllInventoryValues(playerInventory);
}