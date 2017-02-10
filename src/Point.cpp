#include "Point.h"
#include <cmath>

Point::Point(int _x, int _y) :
    x(_x), y(_y)
{

}

Point::Point()
{
    x = y = step = g = h = f = Gx = Gy = 0;
    parent = nullptr;
    for (int i = 0; i < 4; i++)
    {
        child[i] = nullptr;
    }
    towards = LeftDown;
}

Point::~Point()
{
}

void Point::delTree(Point* root)
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

int Point::Heuristic(int Fx, int Fy)                        //manhattan���ۺ���
{
    h = (abs(x - Fx) + abs(y - Fy)) * 10;
    return h;
}