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
			ImGui::SameLine();
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