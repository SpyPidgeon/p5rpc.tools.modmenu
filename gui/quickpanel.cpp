#include "quickpanel.h"

void QuickPanel::RenderLogic()
{
	if (ImGui::Button("Noclip"))
	{
		selectedIndex = QuickSelection::NOCLIP;
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
	}
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