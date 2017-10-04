#pragma once
#include "Element.h"
#include "Types.h"

//��Ϊս�������Ĳ�����Ϊ���������д��ԭ���Ƚ��鷳���ʵ����г�һ��������Ӧ�¼�
class BattleOperator : public Element
{
public:
    BattleOperator();
    ~BattleOperator();

    int* select_x_ = nullptr, *select_y_ = nullptr;
    MapSquare* select_layer_ = nullptr, *effect_layer_ = nullptr;

    Role* role_ = nullptr;
    Magic* magic_ = nullptr;

    void setRoleAndMagic(Role* r, Magic* m = nullptr) { role_ = r; magic_ = m; }
    void dealEvent(BP_Event& e) override;

    int mode_ = Move;
    enum
    {
        Other = -1,
        Move,
        Action,
    };
    void setMode(int m) { mode_ = m; }
    int getMode() { return mode_; }

    Element* battle_scene_ = nullptr;
    void setBattleScene(Element* element) { battle_scene_ = element; }

};

