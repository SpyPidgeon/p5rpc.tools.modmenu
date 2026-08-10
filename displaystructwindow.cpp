#include "displaystructwindow.h"
#include <iomanip>
#include <format>

extern ImSettings config;
using std::format;

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