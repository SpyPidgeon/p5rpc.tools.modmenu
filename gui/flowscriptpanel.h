#pragma once
#include "panels.h"

struct FlowCategory
{
	void* categoryStart;
	uint16_t size;
};

struct FlowFileFunction
{
	char label[0x2C];
	int maxParams = 8;
	std::array<BYTE,42> data1;
	std::array<int, 16> parameters;
	std::array<BYTE, 0x224> data2;

	static FlowFileFunction* GetInstance()
	{
		static FlowFileFunction* instance = new FlowFileFunction();
		const char* label = "MOD_MENU_FLOWSCRIPT";
		strcpy_s(instance->label, 20, label);

		return instance;
	}
};
static FlowFileFunction* modMenuFlowScript = FlowFileFunction::GetInstance();

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
	void RunFunction();

	std::array<FlowCategory, 6>* flowCategories;
	std::vector<FlowScript> flowVector;
	std::vector<float> currentParams;
	FlowFileFunction** flowFunction;

	int previouslySelected = -1;
};
static FlowScriptPanel *flowPanel = FlowScriptPanel::GetInstance();