#pragma once
#include "ImReflect.hpp"
#include <vector>
#include <functional>
#include "skillstructs.h"

constexpr uint8_t PARTY_MAX = 10;
constexpr uint16_t PERSONA_LIST_SIZE = 464;
constexpr uint16_t FILE_ARRAY_SIZE = 512;

constexpr ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

std::string GetNameFromBinary(const uint32_t currentIndex, const uintptr_t nameAddress);

struct Panel
{
    Panel();
    Panel(std::string label) : label(label) {}

    std::string label;
    const char* childLabel = "Inspector";
    bool open = false;
    void RenderPanel();

    virtual void RenderLogic() {}
    virtual void InspectorLogic() {}
    virtual void ScanValues() {}
    virtual void ApplyChanges() {}
    virtual void Refresh() {}
};

extern std::vector<Panel*> panels;

struct SearchablePanel : Panel
{
    SearchablePanel() {}

    char searchText[256] = "";
    int selectedIndex = 0;
    bool TextMatch(std::string search, std::string match);
    void RenderLogic() override;

    template<typename T,std::size_t S,std::size_t NS>
    void RenderList(std::array<T, S>* array,std::array<std::string,NS>* names);
};

enum class SkillTab
{
    ACTIVE,
    ELEMENT
};

struct SkillPanel : SearchablePanel
{
    SkillPanel() { this->label = "Skills"; }

    static SkillPanel* GetInstance()
    {
        static SkillPanel* instance = new SkillPanel();
        return instance;
    }

    static constexpr uint16_t ACTIVE_SKILL_SIZE = 800;
    static constexpr uint16_t SKILL_ELEMENT_SIZE = 1056;

    std::array<ActiveSkill, ACTIVE_SKILL_SIZE> activeSkillArray;
    std::array<ActiveSkill, ACTIVE_SKILL_SIZE>* activeSkillsPTR;

    std::array<std::string, SKILL_ELEMENT_SIZE> skillNames;
    std::array<SkillElement, SKILL_ELEMENT_SIZE> skillElementArray;
    std::array<SkillElement, SKILL_ELEMENT_SIZE>* skillElementPtr;

    SkillTab tab = SkillTab::ACTIVE;

    void RenderLogic() override;
    void InspectorLogic() override;
    void ScanValues() override;
    void ApplyChanges() override;
    void Refresh() override;

private:
};
static SkillPanel* skillPanel = SkillPanel::GetInstance();