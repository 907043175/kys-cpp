#pragma once
#include "Base.h"
#include "Point.h"

//����ͼ���ӳ�����ս���������̳д���
class Scene : public Base
{
public:
    Scene();
    virtual ~Scene();
    virtual void draw() override {}
    virtual void dealEvent(BP_Event& e) override {}

    typedef enum
    {
        LeftUp = 0,
        RightUp = 1,
        LeftDown = 2,
        RightDown = 3,
    } Towards;

    static Towards towards;

    int screen_center_x_ = 0;
    int screen_center_y_ = 0;
    const int singleScene_X = 18;                               //Сͼ���СX
    const int singleScene_Y = 9;                            //Сͼ���СY
    const int singleMapScene_X = 18;                            //����Сͼ���СX
    const int singleMapScene_Y = 9;                         //����Сͼ���СY

    int minStep;                                                        //���(Mx,My),�յ�(Fx,Fy),�����ƶ�����minStep
    int Msx, Msy;

    int width_region_ = 0;
    int sum_region_ = 0;

    bool isMenuOn = 0;

    Point getPositionOnScreen(int x, int y, int CenterX, int CenterY);
    Point getMapPoint(int x, int y, int CenterX, int CenterY);
    int CallFace(int x1, int y1, int x2, int y2);

    int calBlockTurn(int x, int y, int layer)
    {
        return 4 * (128 * (x + y) + x) + layer;
    }

};


