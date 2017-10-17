#pragma once
#include "Element.h"
#include "Types.h"
#include "Head.h"
#include "UIStatus.h"

class BattleScene;

//��Ϊս�������Ĳ�����Ϊ���������д��ԭ���Ƚ��鷳���ʵ����г�һ�����Բ������
//ע�⣬AIѡ��Ŀ�����ΪҲ��������
class BattleCursor : public Element
{
public:
    BattleCursor();
    ~BattleCursor();

    int* select_x_ = nullptr, *select_y_ = nullptr;
    MapSquare* select_layer_ = nullptr, *effect_layer_ = nullptr;

    Role* role_ = nullptr;
    Magic* magic_ = nullptr;
    int level_index_ = 0;
    void setRoleAndMagic(Role* r, Magic* m = nullptr, int l = 0);

    Head* head_selected_;
    //void setHead(Head* h) { head_selected_ = h; }
    Head* getHead() { return head_selected_; }

    UIStatus* ui_status_;
    UIStatus* getUIStatus() { return ui_status_; }

    int mode_ = Move;
    enum
    {
        Other = -1,
        Move,
        Action,
        Check,
    };
    void setMode(int m) { mode_ = m; }
    int getMode() { return mode_; }

    BattleScene* battle_scene_ = nullptr;
    void setBattleScene(BattleScene* b) { battle_scene_ = b; }

    void dealEvent(BP_Event& e) override;

    void dealMoveEvent(BP_Event& e);
    void dealActionEvent(BP_Event& e);

    void onEntrance() override;

    virtual void onPressedOK() override { exitWithResult(0); }
    virtual void onPressedCancel() override { exitWithResult(-1); }

};

