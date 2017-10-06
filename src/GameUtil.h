#pragma once
#include "Types.h"
#include <cmath>

//��������һЩ��Ϸ�еĹ�ʽ������ʹ����Ʒ��Ч�����˺���ʽ��
//ͨ����˵Ӧ��ȫ���Ǿ�̬����
class GameUtil
{
private:
    GameUtil();
    ~GameUtil();
public:
    //��������ֵ
    static int limit(int current, int min_value, int max_value)
    {
        if (current < min_value) { current = min_value; }
        if (current > max_value) { current = max_value; }
        return current;
    }

    //limit2��ֱ���޸�����ֵ������������
    static void limit2(int& current, int min_value, int max_value)
    {
        current = limit(current, min_value, max_value);
    }

    static void limit2(int16_t& current, int min_value, int max_value)
    {
        current = limit(current, min_value, max_value);
    }

    //����ĳ����ֵ��λ��
    static int digit(int x)
    {
        int n = floor(log10(0.5 + abs(x)));
        if (x >= 0)
        {
            return n;
        }
        else
        {
            return n + 1;
        }
    }

    static bool canUseItem(Role* r, Item* i) { return false; }
    static bool useItem(Role* r, Item* i) { return false; }
};

