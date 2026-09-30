#pragma once
#include "guistructs.h"
#include <filesystem>

class Exportable
{
public:

    void RenderButton();
    void RenderExplorer();
    std::vector<std::string> GetDirectories(const std::string& path);

    virtual void ExportFile(const std::string& directory) {}

    static std::string currentDirectory;
    static std::vector<std::string> directories;
    bool renderExplorer = false;

private:
};