#include "panels.h"
#include <format>

using std::format;
std::vector<Panel*> panels;

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

	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y + (h * 0.05f)));
	ImGui::SetNextWindowSize(ImVec2(viewport->Size.x / 4, viewport->Size.y));

	if (ImGui::Begin(label.c_str(), &p_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
	{
		RenderLogic();
		ImGui::End();
	}

	int childX = viewport->Size.x - (viewport->Size.x / 4);

	ImGui::SetNextWindowPos(ImVec2(childX, pos.y + (h * 0.05f)));
	ImGui::SetNextWindowSize(ImVec2(viewport->Size.x / 4, viewport->Size.y));

	if (ImGui::Begin(childLabel,&p_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
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
		if (search[i] != match[i])
			return false;
	}

	return true;
}

// Skill Panel
void SkillPanel::RenderLogic()
{
	SearchablePanel::RenderLogic();
	RenderList(&activeSkillArray, &skillNames);
}

void SkillPanel::InspectorLogic()
{
	ImReflect::Input(skillNames[selectedIndex].c_str(), activeSkillArray[selectedIndex]);
}