#include "quickpanel.h"

void QuickPanel::RenderLogic()
{
	if (ImGui::Button("Noclip"))
	{
		selectedIndex = QuickSelection::NOCLIP;
	}

	if (ImGui::Button("Teleport"))
	{
		selectedIndex = QuickSelection::TELEPORT;
	}
}

void QuickPanel::InspectorLogic()
{
	switch (selectedIndex)
	{
	case QuickSelection::NOCLIP:
		ImReflect::Input("Noclip", noclip);

		if (noclip.enabled == false && keyState != 0)
			keyState = 0;
		break;
	case QuickSelection::TELEPORT:

		ImReflect::Input("Teleport", teleport);

		if (ImGui::Button("Teleport"))
		{
			Teleport(teleport);
		}

		if (ImGui::Button("Save Current Position"))
		{
			SavePosition();
		}

		break;
	}
}

void QuickPanel::SavePosition()
{
	RUN_FLOWSCRIPT_BY_NAME(FLD_PC_GET_RESHND, 0);
	float reshnd = GET_RETURN_INT();

	RUN_FLOWSCRIPT_BY_NAME(FLD_MODEL_GET_X_TRANSLATE, reshnd);
	float x = GET_RETURN_FLOAT();
	RUN_FLOWSCRIPT_BY_NAME(FLD_MODEL_GET_Y_TRANSLATE, reshnd);
	float y = GET_RETURN_FLOAT();
	RUN_FLOWSCRIPT_BY_NAME(FLD_MODEL_GET_Z_TRANSLATE, reshnd);
	float z = GET_RETURN_FLOAT();

	printf("Saved Position: %f, %f, %f\n", x, y, z);
	teleport = Vector3(x, y, z);
}

void QuickPanel::Teleport(const Vector3& position)
{
	RUN_FLOWSCRIPT_BY_NAME(FLD_PC_GET_RESHND, 0);
	float reshnd = GET_RETURN_INT();

	RUN_FLOWSCRIPT_BY_NAME(FLD_MODEL_SET_TRANSLATE,reshnd, position.x, position.y, position.z, 0);
	RUN_FLOWSCRIPT_BY_NAME(FLD_MODEL_SYNC_TRANSLATE,reshnd);
}

// Noclip
void NoclipSettings::NoclipKeyStateOn(WPARAM wParam)
{
	auto* keyState = &quickPanel->keyState;

	if (wParam == 'W')
		*keyState |= KeyPressed::FORWARD;
	else if (wParam == 'S')
		*keyState |= KeyPressed::BACKWARD;
	else if (wParam == 'A')
		*keyState |= KeyPressed::LEFT;
	else if (wParam == 'D')
		*keyState |= KeyPressed::RIGHT;
	else if (wParam == VK_SPACE)
		*keyState |= KeyPressed::UP;
	else if (wParam == VK_CONTROL)
		*keyState |= KeyPressed::DOWN;
}

void NoclipSettings::NoclipKeyStateOff(WPARAM wParam)
{
	auto* keyState = &quickPanel->keyState;

	if (wParam == 'W')
		*keyState &= ~KeyPressed::FORWARD;
	else if (wParam == 'S')
		*keyState &= ~KeyPressed::BACKWARD;
	else if (wParam == 'A')
		*keyState &= ~KeyPressed::LEFT;
	else if (wParam == 'D')
		*keyState &= ~KeyPressed::RIGHT;
	else if (wParam == VK_SPACE)
		*keyState &= ~KeyPressed::UP;
	else if (wParam == VK_CONTROL)
		*keyState &= ~KeyPressed::DOWN;
}

void NoclipSettings::NoclipLogic()
{

}