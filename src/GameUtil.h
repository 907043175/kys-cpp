#pragma once
#include "Types.h"

//��������һЩ��Ϸ�еĹ�ʽ������ʹ����Ʒ��Ч�����˺���ʽ��
//ͨ����˵Ӧ��ȫ���Ǿ�̬����
class GameUtil
{
private:
    GameUtil();
    ~GameUtil();
public:
    static int limit(int current, int min_value, int max_value)
    {
        if (current < min_value) { (current = min_value); }
        if (current > max_value) { (current = max_value); }
        return current;
    }

    static bool canUseItem(Role* r, Item* i) { return false; }
    static bool useItem(Role* r, Item* i) { return false; }
};

