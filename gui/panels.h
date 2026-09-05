#pragma once
#include <vector>
#include <functional>
#include "filestructs.h"
#include "battlestructs.h"
#include "skillstructs.h"

std::string GetNameFromBinary(const uint32_t currentIndex, const uintptr_t nameAddress);

typedef DatUnit* (__stdcall* GetDatUnitByID)(uint16_t ID);
extern GetDatUnitByID GetDatUnit;

constexpr ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

struct Panel
{
    Panel();
    Panel(std::string label) : label(label) {}

    std::string label;
    const char* childLabel = "Inspector";
    bool open = false;
    int selectedIndex = 0;
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
    static bool TextMatch(std::string search, std::string match);
    void RenderLogic() override;

    template<typename T,std::size_t S,std::size_t NS>
    void RenderList(std::array<T, S>* array,std::array<std::string,NS>* names);
};

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

enum class PartyTab
{
    Members,
    Personas
};

class PartyPanel : Panel
{
public:
    PartyPanel() { this->label = "Party"; }
    static PartyPanel* GetInstance() { static PartyPanel* instance = new PartyPanel(); return instance; }

    void RenderLogic() override;
    void InspectorLogic() override;
    void ScanValues() override;
    void ApplyChanges() override;
    void Refresh() override;

    static constexpr uint8_t PARTY_MAX = 10;
    static constexpr uint16_t PERSONA_LIST_SIZE = 464;

    std::array<std::pair<DatUnit, std::string>, PARTY_MAX> partyMembers;
    std::array<DatUnit*, PARTY_MAX> partyMemberPTRs;
    std::array<std::string, PERSONA_LIST_SIZE> personaNames;

    int selectedPersona = 0;

private:
    PartyTab tab = PartyTab::Members;
};
static PartyPanel* partyPanel = PartyPanel::GetInstance();