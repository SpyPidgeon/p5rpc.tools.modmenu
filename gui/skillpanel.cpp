#include "skillpanel.h"
#include "signaturescan.h"

using std::format;

// Skill Panel
void SkillPanel::RenderLogic()
{
	SearchablePanel::RenderLogic();
	if (ImGui::BeginTabBar(label.c_str()))
	{
		if (ImGui::BeginTabItem("Active Skill"))
		{
			tab = SkillTab::ACTIVE;
			RenderList(&activeSkillArray, &skillNames);
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Skill Element"))
		{
			tab = SkillTab::ELEMENT;
			RenderList(&skillElementArray, &skillNames);
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Technical Combos"))
		{
			tab = SkillTab::TECHNICAL;
			RenderListNoName(&technicalArray, "Technical Combo");
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Traits"))
		{
			tab = SkillTab::TRAIT;
			RenderList(&traitsArray, &traitNamesArray);
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
}

void SkillPanel::ScanValues()
{
	std::string pattern;
	pattern = "48 8D 0D ?? ?? ?? ?? 48 8D 15 ?? ?? ?? ?? 0F 1F 00 8B 41 ??";
	DWORD_PTR activeSkills = PatternScan(GetModuleHandle(NULL), pattern);
	activeSkills = GetAddressFromGlobalRef(activeSkills);

	activeSkillsPTR = (std::array<ActiveSkill, ACTIVE_SKILL_SIZE>*)(activeSkills - 0x20);
	activeSkillArray = *activeSkillsPTR;

	pattern = "48 8D 0D ?? ?? ?? ?? 66 89 05 ?? ?? ?? ?? 48 8D 15 ?? ?? ?? ?? 66 66 0F 1F 84 ?? 00 00 00 00";
	DWORD_PTR skillElements = PatternScan(GetModuleHandle(NULL), pattern);
	skillElementPtr = (std::array<SkillElement, SKILL_ELEMENT_SIZE>*)(GetAddressFromGlobalRef(skillElements) - 4);
	skillElementArray = *skillElementPtr;

	pattern = "48 89 05 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 49 8B C8 48 89 05 ?? ?? ?? ?? 48 D1 E9 66 89 0D ?? ?? ?? ?? 48 8B C8 E8 ?? ?? ?? ?? 66 3B 1D ?? ?? ?? ?? 44 8B C3 73 ?? 48 8B 05 ?? ?? ?? ?? 41 8B C8 41 FF C0 48 8D 14 ?? 0F B7 04 ?? 66 C1 C0 08 66 89 02 0F B7 05 ?? ?? ?? ?? 44 3B C0 72 ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 48 8B C8 48 89 05 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 49 8B C8 48 89 05 ?? ?? ?? ?? 48 D1 E9 66 89 0D ?? ?? ?? ?? 48 8B C8 E8 ?? ?? ?? ?? 66 3B 1D ?? ?? ?? ?? 44 8B C3 73 ?? 66 66 0F 1F 84 ?? 00 00 00 00 48 8B 05 ?? ?? ?? ?? 41 8B C8 41 FF C0 48 8D 14 ?? 0F B7 04 ?? 66 C1 C0 08 66 89 02 0F B7 05 ?? ?? ?? ?? 44 3B C0 72 ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 48 8B C8 48 89 05 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 49 8B C8 48 89 05 ?? ?? ?? ?? 48 D1 E9 66 89 0D ?? ?? ?? ?? 48 8B C8 E8 ?? ?? ?? ?? 66 3B 1D ?? ?? ?? ?? 44 8B C3 73 ?? 48 8B 05 ?? ?? ?? ?? 41 8B C8 41 FF C0 48 8D 14 ?? 0F B7 04 ?? 66 C1 C0 08 66 89 02 0F B7 05 ?? ?? ?? ?? 44 3B C0 72 ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 48 8B C8 48 89 05 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 49 8B C8 48 89 05 ?? ?? ?? ?? 48 D1 E9 66 89 0D ?? ?? ?? ?? 48 8B C8 E8 ?? ?? ?? ?? 66 3B 1D ?? ?? ?? ?? 44 8B C3 73 ?? 66 66 0F 1F 84 ?? 00 00 00 00 48 8B 05 ?? ?? ?? ?? 41 8B C8 41 FF C0 48 8D 14 ?? 0F B7 04 ?? 66 C1 C0 08 66 89 02 0F B7 05 ?? ?? ?? ?? 44 3B C0 72 ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 48 8B C8 48 89 05 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3 2B CA 85 C9 0F 4F C1 48 8D 4D ?? 48 03 45 ?? 48 03 F8 48 8B D7 E8 ?? ?? ?? ?? 8B 45 ?? 48 83 C7 04 0F C8 89 45 ?? 48 8B 4D ?? E8 ?? ?? ?? ?? 4C 8B 45 ?? 48 8B D7 49 8B C8 48 89 05 ?? ?? ?? ?? 48 D1 E9 66 89 0D ?? ?? ?? ?? 48 8B C8 E8 ?? ?? ?? ?? 66 3B 1D ?? ?? ?? ?? 44 8B C3 73 ?? 48 8B 05 ?? ?? ?? ?? 41 8B C8 41 FF C0 48 8D 14 ?? 0F B7 04 ?? 66 C1 C0 08 66 89 02 0F B7 05 ?? ?? ?? ?? 44 3B C0 72 ?? 8B 55 ?? 83 C2 04 8B C2 25 0F 00 00 80 7D ?? FF C8 83 C8 F0 FF C0 F7 D8 41 B8 04 00 00 00 8B C2 1B C9 83 E0 F0 83 E1 10 03 C8 8B C3";
	DWORD_PTR activeSkillNames = PatternScan(GetModuleHandle(NULL), pattern);

	activeSkillNames = *(DWORD_PTR*)GetAddressFromGlobalRef(activeSkillNames);

	if (activeSkillNames != 0)
	{
		for (int i = 0; i < SKILL_ELEMENT_SIZE; i++)
		{
			skillNames[i] = GetNameFromBinary(i, activeSkillNames);
		}
	}

	pattern = "48 8D 05 ?? ?? ?? ?? 48 8D 15 ?? ?? ?? ?? 0F 1F 80 00 00 00 00 8B 48 ??";
	DWORD_PTR technicals = PatternScan(GetModuleHandle(NULL), pattern);
	technicalPtr = (std::array<Technical, TECHNICAL_SIZE>*)((GetAddressFromGlobalRef(technicals)) - 8);
	technicalArray = *technicalPtr;

	pattern = "48 8D 0D ?? ?? ?? ?? 48 8D 15 ?? ?? ?? ?? 66 66 66 0F 1F 84 ?? 00 00 00 00 0F B7 41 ??";
	DWORD_PTR traits = PatternScan(GetModuleHandle(NULL), pattern);
	traitsPtr = (std::array<Trait, TRAIT_SIZE>*)(GetAddressFromGlobalRef(traits) - 4);
	traitsArray = *traitsPtr;

	pattern = "4C 03 05 ?? ?? ?? ?? 48 8B 4B ?? E8 ?? ?? ?? ?? 48 8B 43 ?? BA FD FF 00 00 48 8B 48 ?? 66 C7 41 ?? 00 30";
	DWORD_PTR traitNames = PatternScan(GetModuleHandle(NULL), pattern);
	traitNames = *(DWORD_PTR*)GetAddressFromGlobalRef(traitNames);

	if (traitNames != 0)
	{
		for (int i = 0; i < TRAIT_SIZE; i++)
		{
			traitNamesArray[i] = GetNameFromBinary(i, traitNames);
		}
	}
}

void SkillPanel::InspectorLogic()
{
	switch (tab)
	{
	case SkillTab::ACTIVE:
		ImReflect::Input(skillNames[selectedIndex].c_str(), activeSkillArray[selectedIndex], config);
		break;
	case SkillTab::ELEMENT:
		ImReflect::Input(skillNames[selectedIndex].c_str(), skillElementArray[selectedIndex], config);
		break;
	case SkillTab::TECHNICAL:
	{
		auto& selected = technicalArray[selectedIndex];
		ImReflect::Input("Technical Combo", selected, config);

		const char* preview = selected.requireKnowingHeart == knowingHeartNumber.back() ? "Yes" : "No";
		if (ImGui::BeginCombo("Require Knowing Heart", preview))
		{
			for (int i = 0; i < knowingHeartOption.size(); i++)
			{
				bool is_selected = strcmp(preview, knowingHeartOption[i]);

				if (ImGui::Selectable(knowingHeartOption[i], is_selected))
				{
					selected.requireKnowingHeart = knowingHeartNumber[i];
					preview = knowingHeartOption[i];
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		break;
	}
	case SkillTab::TRAIT:
	{
		auto& selected = traitsArray[selectedIndex];
		ImReflect::Input(traitNamesArray[selectedIndex].c_str(), selected, config);
		ImGui::LabelText("##warning", "Warning: element flags after Almighty are untested.");
		ImGui::InputInt("Sub Trait ID", (int*)&selected.elementFlags);
		break;
	}
	}
}

void SkillPanel::ApplyChanges()
{
	std::memcpy(activeSkillsPTR, activeSkillArray.data(), activeSkillArray.size() * sizeof(ActiveSkill));
	std::memcpy(skillElementPtr, skillElementArray.data(), skillElementArray.size() * sizeof(SkillElement));
	std::memcpy(technicalPtr, technicalArray.data(), technicalArray.size() * sizeof(Technical));
	std::memcpy(traitsPtr, traitsArray.data(), traitsArray.size() * sizeof(Trait));
}

void SkillPanel::Refresh()
{
	activeSkillArray = *activeSkillsPTR;
	skillElementArray = *skillElementPtr;
	technicalArray = *technicalPtr;
	traitsArray = *traitsPtr;
}