#pragma once
#include "panels.h"

struct FlowCategory
{
	void* categoryStart;
	uint16_t size;
};

struct FlowScript
{
	void (*Function)();
	uint8_t paramCount;
	const char* name;
};

static const std::array<const char*, 6> flowCategoryNames =
{
	"Common",
	"Field",
	"AI",
	"Social",
	"Facility",
	"Net"
};

class FlowScriptPanel : SearchablePanel
{
public:
	FlowScriptPanel() { this->label = "FlowScript"; }
	static FlowScriptPanel* GetInstance() { static FlowScriptPanel* instance = new FlowScriptPanel(); return instance; }

	void RenderLogic() override;
	void InspectorLogic() override;
	void ScanValues() override;
	//void ApplyChanges() override;
	//void Refresh() override;

	std::array<FlowCategory, 6>* flowCategories;
	std::vector<FlowScript> flowVector;

	int previouslySelected = -1;
};
static FlowScriptPanel *flowPanel = FlowScriptPanel::GetInstance();