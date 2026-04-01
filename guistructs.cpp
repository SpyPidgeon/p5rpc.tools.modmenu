#include "guistructs.h"

//--------------------------------------------------
// Texture
//--------------------------------------------------
std::string GetDLLPath(const std::string& path)
{
	char dllPath[MAX_PATH] = { 0 };
	GetModuleFileNameA(dll_handle, dllPath, MAX_PATH);

	std::string fullPath(dllPath);

	size_t lastSlash = fullPath.find_last_of("\\/");
	std::string baseDirectory = (lastSlash != std::string::npos) ? fullPath.substr(0, lastSlash + 1) : "";

	std::ostringstream ss;
	ss << baseDirectory << path;

	return ss.str();
}