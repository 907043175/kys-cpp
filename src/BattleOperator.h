#pragma once
#include "Element.h"

class BattleOperator :
    public Element
{
public:
    BattleOperator();
    ~BattleOperator();

    Element* battle_scene_;  //�����ָ��BattleScene��ָ�룬��һ���ǲ���ֻ����ǰ����͹��ˣ�Ҫֱ����Ҫdynamic_cast

    void setBattleScene(Element* b) { battle_scene_ = b; }

};

