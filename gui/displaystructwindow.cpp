#include "displaystructwindow.h"
#include <iomanip>
#include <format>

// tag_invokes must run before rendering code
#include <bitset>

extern ImSettings config;
using std::format;

// GFD Files
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
	ImGui::LabelText("File Address", "0x%012X", value.fileAddress);
	ImGui::LabelText("File Size", "%i", value.fileSize);
	ImGui::LabelText("Unknown", "%i", value.unknown);

	ImReflect::Detail::check_input_states(file_response);
}

// Skills
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
				valueName = format("ID: {} | {}", value.skill[i], skillPanel->skillNames[value.skill[i]]);
			else
				valueName = format("{} Default", i);

			if (ImGui::BeginCombo(name.c_str(), valueName.c_str()))
			{
				for (int j = 0; j < skillPanel->skillNames.size(); j++)
				{
					bool is_selected = (j == value.skill[i]);

					valueName = format("ID: {} | {}", j, skillPanel->skillNames[j]);

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
	}

	if (changed)
		skill_response.changed();

	ImReflect::Detail::check_input_states(skill_response);
}

// Persona ID
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

// Inventory
void tag_invoke(ImReflect::ImInput_t, const char* label, Inventory& value, ImSettings& settings, ImResponse& response)
{
	auto& item_response = response.get<Inventory>();

	bool changed = false;
	if (ImGui::CollapsingHeader(label))
	{
		visit_struct::for_each(value,[&changed](const char* name, auto& member)
		{
				member.RenderSliders(name, changed);
		});
	}

	if (changed)
		item_response.changed();

	ImReflect::Detail::check_input_states(item_response);
}

// Rendering Code
extern ImSettings config;
using std::format;

const char* windowName = "SpyPigeon's Mod Menu";

void RenderStructWidgets()
{
	const ImGuiViewport* viewport = ImGui::GetMainViewport();

	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(ImVec2(viewport->Size.x,viewport->Size.y * 0.05f));

	if (ImGui::Begin(windowName, nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
	{
		for (auto panel : panels)
		{
			if (ImGui::Button(panel->label.c_str()))
			{
				panel->open = !panel->open;

				for (auto others : panels)
				{
					if (others != panel)
					{
						others->open = false;
					}
				}
			}

			if (panel->open)
				panel->RenderPanel();
		}

		ImGui::End();
	}
}