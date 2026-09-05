#include "panels.h"
#include <format>
#include "signaturescan.h"

using std::format;
std::vector<Panel*> panels;
ImSettings config;

// Panel
Panel::Panel()
{
	label = "Default";
	panels.push_back(this);
}

void Panel::RenderPanel()
{
	auto viewport = ImGui::GetMainViewport();
	ImVec2 pos = viewport->Pos;
	int h = viewport->Size.y;
	int headerHeight = h * 0.05f;
	int windowSizeX = viewport->Size.x * 0.25f;
	int windowSizeY = viewport->Size.y - headerHeight;

	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y + headerHeight));
	ImGui::SetNextWindowSize(ImVec2(windowSizeX,windowSizeY));

	if (ImGui::Begin(label.c_str(),nullptr, windowFlags))
	{
		if (ImGui::Button("Apply"))
		{
			ApplyChanges();
		}
		ImGui::SameLine();
		if (ImGui::Button("Refresh"))
		{
			Refresh();
		}

		RenderLogic();
		ImGui::End();
	}

	int childX = viewport->Size.x - windowSizeX;

	ImGui::SetNextWindowPos(ImVec2(childX, pos.y + headerHeight));
	ImGui::SetNextWindowSize(ImVec2(windowSizeX,windowSizeY));

	if (ImGui::Begin(childLabel,nullptr, windowFlags))
	{
		InspectorLogic();
		ImGui::End();
	}
}

// Searchable
void SearchablePanel::RenderLogic()
{
	ImGui::InputText("Search", searchText, 256);
}

template<typename T, std::size_t S,std::size_t NS>
void SearchablePanel::RenderList(std::array<T, S>* array, std::array<std::string, NS>* names)
{
	std::string search = searchText;
	for (int i = 0; i < S; i++)
	{
		if (search != "" && !TextMatch(search,names->at(i)))
			continue;

		std::string buttonName = format("ID: {:03d} | {}", i, names->at(i));

		if (ImGui::Button(buttonName.c_str()))
		{
			selectedIndex = i;
		}
	}
}

bool SearchablePanel::TextMatch(std::string search, std::string match)
{
	if (search.size() > match.size())
		return false;

	for (int i = 0; i < search.size(); i++)
	{
		char upperS = std::toupper(search[i]);
		char upperM = std::toupper(match[i]);

		if (upperS != upperM)
			return false;
	}

	return true;
}

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
	skillElementPtr = (std::array<SkillElement,SKILL_ELEMENT_SIZE>*)GetAddressFromGlobalRef(skillElements);
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
}

void SkillPanel::InspectorLogic()
{
	switch (tab)
	{
	case SkillTab::ACTIVE:
		ImReflect::Input(skillNames[selectedIndex].c_str(), activeSkillArray[selectedIndex],config);
		break;
	case SkillTab::ELEMENT:
		ImReflect::Input(skillNames[selectedIndex].c_str(), skillElementArray[selectedIndex],config);
			break;
	}
}

void SkillPanel::ApplyChanges()
{
	std::memcpy(activeSkillsPTR, activeSkillArray.data(), activeSkillArray.size() * sizeof(ActiveSkill));
	std::memcpy(skillElementPtr, skillElementArray.data(), skillElementArray.size() * sizeof(SkillElement));
}

void SkillPanel::Refresh()
{
	activeSkillArray = *activeSkillsPTR;
	skillElementArray = *skillElementPtr;
}

// Party Panel
void PartyPanel::ScanValues()
{
	std::string pattern;

	pattern = "48 03 1D ?? ?? ?? ?? E9 ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ??";
	DWORD_PTR partyNamesPTR = PatternScan(GetModuleHandle(NULL), pattern);
	partyNamesPTR = GetAddressFromGlobalRef(partyNamesPTR);

	partyNamesPTR = *(DWORD_PTR*)partyNamesPTR;
	while (*(BYTE*)partyNamesPTR == 0x00)
		partyNamesPTR++;

	DWORD_PTR partyMembersAddress = (DWORD_PTR)GetDatUnit(1);

	for (int i = 0; i < 10; i++)
	{
		partyMemberPTRs[i] = GetDatUnit(i + 1);
		partyMembers[i] = { *partyMemberPTRs[i],GetNameFromBinary(i + 1,partyNamesPTR) };
	}

	pattern = "48 03 1D ?? ?? ?? ?? F3 41 0F 59 FA";
	DWORD_PTR personaNamesAddress = PatternScan(GetModuleHandle(NULL), pattern);
	personaNamesAddress = *(DWORD_PTR*)GetAddressFromGlobalRef(personaNamesAddress);

	if (personaNamesAddress != 0)
	{
		for (int i = 0; i < PERSONA_LIST_SIZE; i++)
		{
			personaNames[i] = GetNameFromBinary(i, personaNamesAddress);
		}
	}
}

// Persona ID
void tag_invoke(ImReflect::ImInput_t, const char* label, PersonaID& value, ImSettings& settings, ImResponse& response)
{
	auto& persona_response = response.get<PersonaID>();

	bool changed = false;

	std::string valueName;

	if (value.id == 0)
		valueName = "Empty Slot";
	else if (value.id < partyPanel->personaNames.size())
		valueName = "ID: " + std::to_string(value.id) + " | " + partyPanel->personaNames[value.id];
	else
		valueName = "Error";

	if (ImGui::BeginCombo(label, valueName.c_str()))
	{
		for (int j = 0; j < partyPanel->personaNames.size(); j++)
		{
			bool is_selected = (j == value.id);

			if (j == 0)
				valueName = "Empty Slot";
			else
				valueName = "ID: " + std::to_string(j) + " | " + partyPanel->personaNames[j];

			if (ImGui::Selectable(valueName.c_str(), is_selected))
			{
				value.id = j;
				changed = true;
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}

		ImGui::EndCombo();
	}

	if (changed)
		persona_response.changed();

	ImReflect::Detail::check_input_states(persona_response);
}

// Skills
char skillSearch[256] = "";
void tag_invoke(ImReflect::ImInput_t, const char* label, DatUnit_Skills& value, ImSettings& settings, ImResponse& response)
{
	auto& skill_response = response.get<DatUnit_Skills>();

	bool changed = false;
	if (ImGui::CollapsingHeader("Skills"))
	{
		for (int i = 0; i < 8; i++)
		{
			std::string name = "Skill" + std::to_string(i);
			std::string valueName;

			if (value.skill[i] == 0)
				valueName = format("{} Empty", i);
			else if (value.skill[i] < skillPanel->skillNames.size())
				valueName = format("ID: {:04d} | {}", value.skill[i], skillPanel->skillNames[value.skill[i]]);
			else
				valueName = format("{} Default", i);

			if (ImGui::BeginCombo(name.c_str(), valueName.c_str()))
			{
				ImGui::InputText("Search", skillSearch, 256);
				ImGui::BeginChild("##separate");

				for (int j = 0; j < skillPanel->skillNames.size(); j++)
				{
					bool skip = !SearchablePanel::TextMatch(skillSearch, skillPanel->skillNames[j]);

					if (skip)
						continue;

					bool is_selected = (j == value.skill[i]);

					valueName = format("ID: {:04d} | {}", j, skillPanel->skillNames[j]);

					if (ImGui::Selectable(valueName.c_str(), is_selected))
					{
						value.skill[i] = j;
						changed = true;
					}
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndChild();
				ImGui::EndCombo();
			}
		}
	}

	if (changed)
		skill_response.changed();

	ImReflect::Detail::check_input_states(skill_response);
}


void PartyPanel::InspectorLogic()
{
	switch (tab)
	{
	case PartyTab::Members:
		ImReflect::Input(partyMembers[selectedIndex].second.c_str(), partyMembers[selectedIndex].first, config);
		break;
	case PartyTab::Personas:
		auto& persona = partyMembers[selectedIndex].first.StockPersonas[selectedPersona];
		const char* label = personaNames[persona.personaID].c_str();
		ImReflect::Input(label,persona,config);
		break;
	}

}

void PartyPanel::RenderLogic()
{
	if (ImGui::BeginTabBar("Party"))
	{
		if (ImGui::BeginTabItem("Members"))
		{
			tab = PartyTab::Members;
			for (int i = 0; i < PARTY_MAX; i++)
			{
				const char* label = partyMembers[i].second.c_str();
				if (ImGui::Button(label))
				{
					selectedIndex = i;
				}
			}
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Personas"))
		{
			tab = PartyTab::Personas;
			for (int i = 0; i < PARTY_MAX; i++)
			{
				int equippedPersona = partyMembers[i].first.equippedPersona;
				int personaID = partyMembers[i].first.StockPersonas[equippedPersona].personaID;
				const char* label = personaNames[personaID].c_str();
				ImGui::PushID(i);
				if (ImGui::CollapsingHeader(label))
				{
					for (int j = 0; j < 12; j++)
					{
						auto& persona = partyMembers[i].first.StockPersonas[j];
						std::string personaLabel;
						
						if (persona.personaID == 0)
						{
							personaLabel = format("{} Empty",j);
						}
						else
						{
							personaLabel = format("{} {}", j, personaNames[persona.personaID]);
						}

						if (ImGui::Button(personaLabel.c_str()))
						{
							selectedIndex = i;
							selectedPersona = j;
						}
					}
				}
				ImGui::PopID();
			}

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
}

void PartyPanel::ApplyChanges()
{
	for (int i = 0; i < PARTY_MAX; i++)
	{
		*partyMemberPTRs[i] = partyMembers[i].first;
	}
}

void PartyPanel::Refresh()
{
	for (int i = 0; i < PARTY_MAX; i++)
	{
		partyMembers[i].first = *partyMemberPTRs[i];
	}
}