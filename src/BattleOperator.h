#pragma once
#include "Element.h"
#include "Types.h"
#include "Head.h"

//��Ϊս�������Ĳ�����Ϊ���������д��ԭ���Ƚ��鷳���ʵ����г�һ�����Բ���ѡ���ж�Ŀ��
class BattleOperator : public Element
{
public:
    BattleOperator();
    ~BattleOperator();

    int* select_x_ = nullptr, *select_y_ = nullptr;
    MapSquare* select_layer_ = nullptr, *effect_layer_ = nullptr;

    Role* role_ = nullptr;
    Magic* magic_ = nullptr;
    int level_index_ = 0;
    void setRoleAndMagic(Role* r, Magic* m = nullptr, int l = 0);

    Head* head_selected_;
    void setHead(Head* h) { head_selected_ = h; }
    Head* getHead() { return head_selected_; }

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

    Element* battle_scene_ = nullptr;
    void setBattleScene(Element* element) { battle_scene_ = element; }

    void dealEvent(BP_Event& e) override;

    void dealMoveEvent(BP_Event& e);
    void dealActionEvent(BP_Event& e);

    void onEntrance() override;

    virtual void pressedOK() override { exitWithResult(0); }
    virtual void pressedCancel() override { exitWithResult(-1); }

};

