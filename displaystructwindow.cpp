#include "displaystructwindow.h"

void RenderStructWidgets()
{
	if (!ImGui::Begin("ActiveSkills"))
	{
		return;
	}

	for (int i = 0; i < ACTIVE_SKILL_SIZE; i++)
	{
		std::string name = ActiveSkillNames[i] + " ID:" + std::to_string(i);
		if (ImGui::CollapsingHeader(name.c_str()))
		{
			ImReflect::Input(name.c_str(), ActiveSkillArray[i]);
		}
	}

	ImGui::End();
}