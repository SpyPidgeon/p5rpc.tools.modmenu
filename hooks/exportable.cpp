#include "exportable.h"

std::string Exportable::currentDirectory;
std::vector<std::string> Exportable::directories;

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