#include "displaystructwindow.h"
#include <iomanip>
#include <format>
#include <bitset>

extern ImSettings config;
using std::format;

void tag_invoke(ImReflect::ImInput_t, const char* label, GFDFileInfo& value, ImSettings& settings, ImResponse& response)
{
	auto& file_response = response.get<GFDFileInfo>();

	const ImGuiViewport* viewport = ImGui::GetMainViewport();

	ImGui::LabelText("Data0", "%i", value.data0);

	std::string bitString = std::bitset<64>(value.data1).to_string();

	ImVec2 size = ImVec2(0, 0);

	ImGui::PushTextWrapPos(viewport->Size.x);
	ImGui::LabelText("Data1", bitString.c_str());
	ImGui::PopTextWrapPos();

	ImGui::LabelText("File Path", value.path.data());
	ImGui::LabelText("File Address","0x%012X", value.fileAddress);
	ImGui::LabelText("File Size", "%i", value.fileSize);
	ImGui::LabelText("Unknown", "%i", value.unknown);

	ImReflect::Detail::check_input_states(file_response);
}

void tag_invoke(ImReflect::ImInput_t, const char* label, DatUnit_Skills& value, ImSettings& settings, ImResponse& response)
{
	auto& skill_response = response.get<DatUnit_Skills>();

	bool changed = false;
	for (int i = 0; i < 8; i++)
	{
		std::string name = "Skill" + std::to_string(i);
		std::string valueName;

		if (value.skill[i] == 0)
			valueName = format("{} Empty", i);
		else if (value.skill[i] < SkillNames.size())
			valueName = format("ID: {} | {}", value.skill[i], SkillNames[value.skill[i]]);
		else
			valueName = format("{} Default",i);

		if (ImGui::BeginCombo(name.c_str(), valueName.c_str()))
		{
			for (int j = 0; j < SkillNames.size(); j++)
			{
				bool is_selected = (j == value.skill[i]);

				valueName = format("ID: {} | {}",j,SkillNames[j]);

				if (ImGui::Selectable(valueName.c_str(), is_selected))
				{
					value.skill[i] = j;
					changed = true;
				}
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}
	}

	if (changed)
		skill_response.changed();

	ImReflect::Detail::check_input_states(skill_response);
}

void tag_invoke(ImReflect::ImInput_t, const char* label, PersonaID& value, ImSettings& settings, ImResponse& response)
{
	auto& persona_response = response.get<PersonaID>();

	bool changed = false;

	std::string valueName;

	if (value.id == 0)
		valueName = "Empty Slot";
	else if (value.id < personaNames.size())
		valueName = "ID: " + std::to_string(value.id) + " | " + personaNames[value.id];
	else
		valueName = "Error";

	if (ImGui::BeginCombo(label, valueName.c_str()))
	{
		for (int j = 0; j < personaNames.size(); j++)
		{
			bool is_selected = (j == value.id);

			if (j == 0)
				valueName = "Empty Slot";
			else
				valueName = "ID: " + std::to_string(j) + " | " + personaNames[j];

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

void RenderSkillTBL()
{
	if (ImGui::BeginTabBar("SKILL.TBL (WIP)"))
	{
		if (ImGui::BeginTabItem("Skill Elements"))
		{
			for (int i = 0; i < SKILL_ELEMENT_SIZE; i++)
			{
				std::ostringstream oss;
				oss << std::setw(3) << std::setfill('0') << i;

				std::string name = "ID: " + oss.str() + " | " + SkillNames[i];
				if (ImGui::CollapsingHeader(name.c_str()))
				{
					ImReflect::Input(name.c_str(), SkillElementArray[i], config);
				}
			}
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Active Skills"))
		{
			if (ImGui::Button("Apply Changes"))
			{
				*ActiveSkillsPTR = ActiveSkillArray;
			}

			for (int i = 0; i < ACTIVE_SKILL_SIZE; i++)
			{
				std::ostringstream oss;
				oss << std::setw(3) << std::setfill('0') << i;

				std::string name = "ID: " + oss.str() + " | " + SkillNames[i];
				if (ImGui::CollapsingHeader(name.c_str()))
				{
					ImReflect::Input(name.c_str(), ActiveSkillArray[i], config);
				}
			}
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
}

bool alwaysOnTop = true;

void RenderStructWidgets()
{
	const ImGuiViewport* viewport = ImGui::GetMainViewport();

	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);

	if (ImGui::Begin("##Menu",nullptr,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
	{
		if (ImGui::Button("Always On Top?"))
		{
			alwaysOnTop = alwaysOnTop ? false : true;
			SDL_SetWindowAlwaysOnTop(window, alwaysOnTop);
		}

		ImGui::SameLine();
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::Checkbox("##ontop", &alwaysOnTop);
		ImGui::PopItemFlag();

		ImGui::SameLine();

		if (ImGui::Button("Refresh"))
		{
			ActiveSkillArray = *ActiveSkillsPTR;

			for (int i = 0; i < 10; i++)
			{
				partyMembers[i].first = *partyMemberPTRs[i];
			}
		}

		if (ImGui::BeginTabBar("Tabs"))
		{
			if (ImGui::BeginTabItem("Tables(WIP)"))
			{
				RenderSkillTBL();

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Party"))
			{
				if (ImGui::Button("Apply All Changes"))
				{
					for (int i = 0; i < 10; i++)
					{
						*partyMemberPTRs[i] = partyMembers[i].first;
					}
				}

				for (int i = 0; i < 10; i++)
				{
					std::string name = partyMembers[i].second;
					std::string namePersonas = partyMembers[i].second + " Personas";
					if (ImGui::CollapsingHeader(name.c_str()))
					{
						ImReflect::Input(std::to_string(i).c_str(), partyMembers[i].first, config);

						if (ImGui::CollapsingHeader(namePersonas.c_str()))
						{
							for (int j = 0; j < 12; j++)
							{
								auto& persona = partyMembers[i].first.StockPersonas[j];
								std::string personaLabel;
								if (persona.personaID == 0)
									personaLabel = "Empty Persona Slot " + std::to_string(j);
								else
									personaLabel = personaNames[persona.personaID] + " | Slot: " + std::to_string(j);

								if (ImGui::CollapsingHeader(personaLabel.c_str()))
								{
									ImReflect::Input(personaLabel.c_str(), persona, config);

									std::string changes = "Apply Changes To " + std::to_string(j);
									if (ImGui::Button(changes.c_str()))
									{
										partyMemberPTRs[i]->StockPersonas[j] = persona;
									}
								}
							}
						}
					}
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Loaded Files"))
			{
				for (int i = 0; i < FILE_ARRAY_SIZE; i++)
				{
					if (gfdFiles->at(i).fileAddress == NULL)
						continue;

					std::string filePath = format("Index: {} | {}",i,gfdFiles->at(i).path.data());
					if (ImGui::CollapsingHeader(filePath.c_str()))
					{
						ImReflect::Input(std::to_string(i).c_str(),gfdFiles->at(i));
					}
				}

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}

		ImGui::End();
	}
}