#pragma once
#include "Base.h"

class BattleOperator :
    public Base
{
public:
    BattleOperator();
    ~BattleOperator();

    Base* battle_scene_;  //�����ָ��BattleScene��ָ�룬��һ���ǲ���ֻ����ǰ����͹��ˣ�Ҫֱ����Ҫdynamic_cast

    void setBattleScene(Base* b) { battle_scene_ = b; }

};

