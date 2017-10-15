#pragma once
#include "Menu.h"
#include "Head.h"
#include "UIItem.h"

class BattleScene;

//ע�⣬AIѡ���ж�����ΪҲ��������
class BattleActionMenu : public MenuText
{
public:
    BattleActionMenu();
    virtual ~BattleActionMenu();

    virtual void onEntrance() override;

    Role* role_ = nullptr;
    void setRole(Role* r) { role_ = r; }
    int runAsRole(Role* r) { setRole(r); return run(); }

    BattleScene* battle_scene_ = nullptr;
    void setBattleScene(BattleScene* b) { battle_scene_ = b; }

    void dealEvent(BP_Event& e) override;

    int autoSelect(Role* role);

    MapSquare* distance_layer_;

    void calDistanceLayer(int x, int y, int max_step = 64);

    struct AIAction
    {
        int Action;
        int MoveX, MoveY;
        int ActionX, ActionY;
        Magic* magic = nullptr;
        Item* item = nullptr;
        int point = 0;
    };

    void setAIActionToRole(AIAction& aa, Role* role)
    {
        role->AI_Action = aa.Action;
        role->AI_MoveX = aa.MoveX;
        role->AI_MoveY = aa.MoveY;
        role->AI_ActionX = aa.ActionX;
        role->AI_ActionY = aa.ActionY;
        role->AI_Magic = aa.magic;
        role->AI_Item = aa.item;
    }

    void getFarthestToAll(Role* role, std::vector<Role*> roles, int& x, int& y);
    void getNearestPosition(int x0, int y0, int& x, int& y);
    Role* getNearestRole(Role* role, std::vector<Role*> roles);
    void calAIActionNearest(Role* r2, AIAction& aa);
};

class BattleMagicMenu : public MenuText
{
public:
    BattleMagicMenu() {}
    virtual ~BattleMagicMenu() {}

    virtual void onEntrance() override;

    void dealEvent(BP_Event& e) override;

    Role* role_ = nullptr;
    Magic* magic_ = nullptr;
    void setRole(Role* r) { role_ = r; }
    int runAsRole(Role* r) { setRole(r); return run(); }

    Magic* getMagic() { return magic_; }

    virtual void onPressedOK() override;
    virtual void onPressedCancel() override { magic_ = nullptr; exitWithResult(-1); }

};


class BattleItemMenu : public UIItem
{
public:
    BattleItemMenu();
    virtual ~BattleItemMenu() {}
private:
    Role* role_ = nullptr;
public:
    virtual void dealEvent(BP_Event& e) override;

    void setRole(Role* r) { role_ = r; }
    Role* getRole() { return role_; }

    void addItem(Item* item, int count);
};


