#pragma once
#include "Menu.h"
#include "Head.h"

class BattleScene;

//ע�⣬AIѡ���ж�����ΪҲ��������
class BattleMenu : public MenuText
{
public:
    BattleMenu();
    virtual ~BattleMenu();

    virtual void onEntrance() override;

    Role* role_ = nullptr;
    void setRole(Role* r) { role_ = r; }
    int runAsRole(Role* r);

    BattleScene* battle_scene_ = nullptr;
    void setBattleScene(BattleScene* b) { battle_scene_ = b; }

    void dealEvent(BP_Event& e) override;

};



