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

bool SearchablePanel::TextMatch(std::string search, std::string match)
{
	if (search.size() > match.size())
		return false;

	for (int i = 0; i < match.size(); i++)
	{
		if (i < search.size()) search[i] = std::tolower(search[i]);
		match[i] = std::tolower(match[i]);
	}

	return match.find(search) != std::string::npos;
}

// Exportable
void Exportable::RenderExplorer()
{
	auto viewport = ImGui::GetMainViewport();
	ImVec2 pos = viewport->Pos;
	ImVec2 size = viewport->Size;

	ImGui::SetNextWindowPos(pos, ImGuiCond_Once);
	ImGui::SetNextWindowSize(size, ImGuiCond_Once);

	if (directories.empty())
		directories = GetDirectories(currentDirectory);

	if (ImGui::Begin("Select Directory"))
	{
		if (ImGui::Button("Set Directory To Current"))
		{
			renderExplorer = false;
		}

		ImGui::LabelText("Current Directory", currentDirectory.c_str());

		ImGui::Separator();
		ImGui::BeginChild("##child");

		if (currentDirectory.size() > 3)
		{
			if (ImGui::Button("../"))
			{
				std::filesystem::path p(currentDirectory);
				p = p.parent_path();
				currentDirectory = p.string();

				directories.clear();
			}
		}

		for (const auto& directory : directories)
		{
			if (ImGui::Button(directory.c_str()))
			{
				currentDirectory += '\\' + directory;
				directories.clear();
				break;
			}
		}

		ImGui::EndChild();
	}

	ImGui::End();
}

namespace fs = std::filesystem;

std::vector<std::string> Exportable::GetDirectories(const std::string& path)
{
	std::vector<std::string> folders;

	for (const auto& entry : fs::directory_iterator(path))
	{
		if (fs::is_directory(entry.status()) && !entry.is_symlink())
		{
			folders.push_back(entry.path().filename().string());
		}
	}

	return folders;
}

void Exportable::RenderButton()
{
	if (ImGui::Button("Set Directory"))
	{
		renderExplorer = true;
	}

	if (ImGui::Button("Export File"))
	{
		ExportFile(currentDirectory);
	}
}