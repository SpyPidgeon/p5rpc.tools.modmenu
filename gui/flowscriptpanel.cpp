#include "flowscriptpanel.h"
#include "signaturescan.h"

void FlowScriptPanel::ScanValues()
{
	std::string pattern;

	pattern = "4C 8D 3D ?? ?? ?? ?? 8B F5";
	DWORD_PTR flowStart = PatternScan(GetModuleHandle(NULL), pattern);
	flowStart = GetAddressFromGlobalRef(flowStart);

	flowCategories = (std::array<FlowCategory,6>*)flowStart;
}

void FlowScriptPanel::RenderLogic()
{
	SearchablePanel::RenderLogic();

	ImGui::BeginTabBar(this->label.c_str());

	for (int i = 0; i < flowCategories->size(); i++)
	{
		const char* categoryLabel = flowCategoryNames[i];
		if (ImGui::BeginTabItem(categoryLabel))
		{
			if (previouslySelected != i)
			{
				selectedIndex = 0;
				previouslySelected = i;

				flowVector.clear();

				size_t newSize = flowCategories->at(i).size;
				flowVector.resize(newSize);
				FlowScript* memoryStart = (FlowScript*)flowCategories->at(i).categoryStart;
				std::memcpy(flowVector.data(), memoryStart, flowVector.size() * sizeof(FlowScript));
			}

			for (int j = 0; j < flowVector.size(); j++)
			{
				auto& flowObject = flowVector[j];
				std::string label = flowObject.name == nullptr ? "Empty" : flowObject.name;

				if (!TextMatch(searchText, label))
					continue;

				label = std::format("{} | {}", j, label);

				ImGui::PushID(j);
				if (ImGui::Button(label.c_str()))
				{
					selectedIndex = j;
				}
				ImGui::PopID();
			}

			ImGui::EndTabItem();
		}
	}

	ImGui::EndTabBar();
}

void FlowScriptPanel::InspectorLogic()
{
	auto& flowObject = flowVector[selectedIndex];
	std::string label = flowObject.name == nullptr ? "Empty" : flowObject.name;
	
	ImGui::LabelText("##label", label.c_str());
	ImGui::Separator();
	for (int i = 0; i < flowObject.paramCount; i++)
	{
		std::string label = std::format("Param{}", i);

		float input = 0.0f;
		ImGui::InputFloat(label.c_str(), &input,0,0,"%g");
	}
}