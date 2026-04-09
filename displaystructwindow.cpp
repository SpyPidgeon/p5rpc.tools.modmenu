#include "displaystructwindow.h"
#include <iomanip>

extern ImSettings activeSkillConfig;


void RenderStructWidgets()
{
	if (!ImGui::Begin("Menu"))
	{
		return;
	}

	if (ImGui::BeginTabBar("Tabs"))
	{
		if (ImGui::BeginTabItem("Active Skills"))
		{
			for (int i = 0; i < ACTIVE_SKILL_SIZE; i++)
			{
				std::ostringstream oss;
				oss << std::setw(3) << std::setfill('0') << i;

				std::string name = "ID: " + oss.str() + " | " + ActiveSkillNames[i];
				if (ImGui::CollapsingHeader(name.c_str()))
				{
					ImReflect::Input(name.c_str(), ActiveSkillArray[i],activeSkillConfig);
				}
			}
		}
		ImGui::EndTabItem();
	}
	ImGui::EndTabBar();

	ImGui::End();
}