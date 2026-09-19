#include "gamehooks.h"
#include "flowscriptpanel.h"

GetDatUnitByID GetDatUnit;
FlowScriptIntCheck oFlowScriptIntThunk;

std::string GetNameFromBinary(const uint32_t currentIndex, const uintptr_t nameAddress)
{
	unsigned int j = 0;
	unsigned int nameOffset = 0;

	while (j < currentIndex)
	{
		if (*reinterpret_cast<BYTE*>(nameAddress + nameOffset) == 0x00)
		{
			j++;
		}
		nameOffset++;
	}

	std::string binaryName;

	while (*reinterpret_cast<BYTE*>(nameAddress + nameOffset) != 0x00)
	{
		binaryName.push_back((char)*reinterpret_cast<char*>(nameAddress + nameOffset));
		nameOffset++;
	}

	return binaryName;
}

MouseState oMouseState;
extern bool fetchContext;
void MouseStateHook()
{
	if (fetchContext)
		return;

	oMouseState();
}

// No inline to avoid stack corruption.
__declspec(noinline) void FlowScriptFloatToInt(int parameter)
{
	if (!flowPanel->runByModMenu)
		return;

	int arrayParam = 15 - (parameter * 2);

	// Bithack go brrrr
	float* data = &modMenuFlowScript->parameters.at(arrayParam);
	int newData = (int)*data;
	std::memcpy(data, &newData, sizeof(float));
}

int __fastcall FlowScriptIntDetour(int parameter)
{
	FlowScriptFloatToInt(parameter);
	return oFlowScriptIntThunk(parameter);
}