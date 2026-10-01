#include "filepanel.h"
#include "signaturescan.h"

void FilePanel::ScanValues()
{
    std::string pattern;

    pattern = "48 8D 15 ?? ?? ?? ?? 8B 8C ?? ?? ?? ?? ?? 41 89 0F";
    DWORD_PTR fileArrayStart = PatternScan(GetModuleHandle(NULL), pattern);
    fileArrayStart = GetAddressFromGlobalRef(fileArrayStart);

    gfdFiles = (std::array<GFDFileInfo, FILE_ARRAY_SIZE>*)fileArrayStart;
}

void tag_invoke(ImReflect::ImInput_t, const char* label, GFDFileInfo& value, ImSettings& settings, ImResponse& response)
{
	auto& file_response = response.get<GFDFileInfo>();

	const ImGuiViewport* viewport = ImGui::GetMainViewport();

	ImGui::LabelText("Data0", "%i", value.data0);

	ImVec2 size = ImVec2(0, 0);

	ImGui::Separator();
	ImGui::LabelText("Data1", "");
	for (int i = 0; i < value.data1.size(); i++)
	{
		ImGui::PushID(i);
		ImGui::LabelText("##value","0x%02X",value.data1[i]);
		ImGui::PopID();
	}
	ImGui::Separator();

	ImGui::LabelText("File Path", value.path.data());
	ImGui::LabelText("File Address", "0x%012X", value.fileAddress);
	ImGui::LabelText("File Size", "%i", value.fileSize);
	ImGui::LabelText("Unknown1", "%i", value.unknown);

	ImReflect::Detail::check_input_states(file_response);
}

void FilePanel::RenderLogic()
{
	SearchablePanel::RenderLogic();
	if (ImGui::BeginTabBar("Files"))
	{
		if (ImGui::BeginTabItem("Visual Objects"))
		{
			for (int i = 0; i < gfdFiles->size(); i++)
			{

				std::string path = std::format("{:03d} | {}", i, gfdFiles->at(i).path.data());

				if (!TextMatch(searchText, path))
					continue;

				if (ImGui::Button(path.c_str()))
				{
					selectedIndex = i;
				}
			}

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
}

void FilePanel::InspectorLogic()
{
	auto selected = gfdFiles->at(selectedIndex);
	ImReflect::Input(selected.path.data(), selected);
}