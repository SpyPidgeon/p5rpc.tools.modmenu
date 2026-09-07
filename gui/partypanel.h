#pragma once
#include "panels.h"
#include "skillpanel.h"

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