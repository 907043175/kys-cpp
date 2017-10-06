#include "Point.h"
#include <cmath>

PointEx::PointEx()
{
    parent = nullptr;
    for (int i = 0; i < 4; i++)
    {
        child[i] = nullptr;
    }
    towards = Towards_LeftDown;
}

void PointEx::delTree(PointEx* root)
{
    if (root == nullptr)                // ��������ֱ�ӷ���
    {
        return;
    }
    else                            // �ǿ�����
    {
        delTree(root->child[0]);    // ɾ������
        delTree(root->child[1]);
        delTree(root->child[2]);
        delTree(root->child[3]);
        delete (root);                // �ͷŸ��ڵ�
    }
}

int PointEx::Heuristic(int Fx, int Fy)                        //manhattan���ۺ���
{
    h = (abs(x - Fx) + abs(y - Fy)) * 10;
    return h;
}