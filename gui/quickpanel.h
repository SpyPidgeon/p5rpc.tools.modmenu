#pragma once
#include "panels.h"
#include "flowscriptpanel.h"
#include "vectormath.h"

struct NoclipSettings
{
	bool enabled = false;
	float speed = 10;

	void NoclipKeyStateOn(WPARAM wParam);
	void NoclipKeyStateOff(WPARAM wParam);
	void NoclipLogic();
};
IMGUI_REFLECT(NoclipSettings,enabled,speed);

enum KeyPressed : BYTE
{
	FORWARD = 1 << 0,
	BACKWARD = 1 << 1,
	LEFT = 1 << 2,
	RIGHT = 1 << 3,
	UP = 1 << 4,
	DOWN = 1 << 5
};

enum QuickSelection
{
	NOCLIP,
	TELEPORT
};

class QuickPanel : Panel
{
public:
	QuickPanel() { this->label = "Quick"; this->childLabel = "Options"; }
	static QuickPanel* GetInstance() { static QuickPanel* instance = new QuickPanel(); return instance; }

	void RenderLogic() override;
	void InspectorLogic() override;
	//void ScanValues() override;
	//void ApplyChanges() override;
	//void Refresh() override;

	NoclipSettings noclip;
	BYTE keyState;
	Vector3 teleport;

	void SavePosition();
	void Teleport(const Vector3& position);
};
static QuickPanel* quickPanel = QuickPanel::GetInstance();