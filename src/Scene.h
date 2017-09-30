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

    //BP_Texture* earth_texture_ = nullptr;

    //int man_x_, man_y_;        //ע���������в�����������Ϊ�浵��ƺ�ĳЩָ������⣬����ʾ�Ƽ����ַ���
    static Towards towards_;     //���򣬹���һ������

    int screen_center_x_ = 0;
    int screen_center_y_ = 0;
    const int TILE_W = 18;  //Сͼ���СX
    const int TILE_H = 9;   //Сͼ���СY

    //ȷ����Ұʹ��
    int view_width_region_ = 0;
    int view_sum_region_ = 0;

    int total_step_ = 0;        //������·�ļ���
    BP_Keycode pre_pressed_;    //������·���ϴΰ���

    int step_ = 0;
    int man_pic_;
    void setManPic(int pic) { man_pic_ = pic; }

    void checkWalk(int x, int y, BP_Event& e);   //һЩ�������֣�δ���

    Point getPositionOnScreen(int x, int y, int CenterX, int CenterY);

    Towards CallFace(int x1, int y1, int x2, int y2);

    int calBlockTurn(int x, int y, int layer) { return 4 * (128 * (x + y) + x) + layer; }

    void getTowardsFromKey(BP_Keycode key);
    //��ȡ����һ�������
    void getTowardsPosition(int x0, int y0, Towards tw, int* x1, int* y1);

    virtual bool canWalk(int x, int y) { return false; }
    virtual bool isOutScreen(int x, int y) { return false; }

    std::vector<PointEx> way_que_;  //ջ(·��ջ)
    int minStep;                                                        //���(Mx,My),�յ�(Fx,Fy),�����ƶ�����minStep
    int mouse_x_, mouse_y_;
    void stopFindWay() { way_que_.clear();/*while (!way_que_.empty()) { way_que_.pop(); }*/ }
    void FindWay(int Mx, int My, int Fx, int Fy);

};


