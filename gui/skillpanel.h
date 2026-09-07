#pragma once
#include "panels.h"

enum class SkillTab
{
    ACTIVE,
    ELEMENT
};

class SkillPanel : SearchablePanel
{
public:
    SkillPanel() { this->label = "Skills"; }

    static SkillPanel* GetInstance()
    {
        static SkillPanel* instance = new SkillPanel();
        return instance;
    }

    void RenderLogic() override;
    void InspectorLogic() override;
    void ScanValues() override;
    void ApplyChanges() override;
    void Refresh() override;

    static constexpr uint16_t ACTIVE_SKILL_SIZE = 800;
    static constexpr uint16_t SKILL_ELEMENT_SIZE = 1056;

    std::array<ActiveSkill, ACTIVE_SKILL_SIZE> activeSkillArray;
    std::array<ActiveSkill, ACTIVE_SKILL_SIZE>* activeSkillsPTR;

    std::array<std::string, SKILL_ELEMENT_SIZE> skillNames;
    std::array<SkillElement, SKILL_ELEMENT_SIZE> skillElementArray;
    std::array<SkillElement, SKILL_ELEMENT_SIZE>* skillElementPtr;

private:
    SkillTab tab = SkillTab::ACTIVE;
};
static SkillPanel* skillPanel = SkillPanel::GetInstance();