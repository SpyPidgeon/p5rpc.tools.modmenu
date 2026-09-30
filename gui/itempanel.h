#pragma once
#include "panels.h"
#include "skillpanel.h"

class ItemPanel : Panel, Exportable
{
public:
    ItemPanel() { this->label = "Item Table"; }
    static ItemPanel* GetInstance() { static ItemPanel* instance = new ItemPanel(); return instance; }

    void RenderLogic() override;
    void InspectorLogic() override;
    void ScanValues() override;
    void ApplyChanges() override;
    void Refresh() override;
};
static ItemPanel* itemPanel = ItemPanel::GetInstance();