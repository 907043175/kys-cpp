#pragma once
#include <stack>
#include <queue>
#include "Scene.h"
#include "Cloud.h"
#include "Types.h"

class MainMap : public Scene
{
public:
    MainMap();
    ~MainMap();

    static const int max_coord_ = MAINMAP_MAX_COORD;
    typedef int16_t MapArray[max_coord_ * max_coord_];
    static MapArray Earth_, Surface_, Building_, BuildX_, BuildY_, Entrance_;

    static int16_t& Earth(int x, int y) { return Earth_[x + y * max_coord_]; }
    static int16_t& Surface(int x, int y) { return Surface_[x + y * max_coord_]; }
    static int16_t& Building(int x, int y) { return Building_[x + y * max_coord_]; }
    static int16_t& BuildX(int x, int y) { return BuildX_[x + y * max_coord_]; }
    static int16_t& BuildY(int x, int y) { return BuildY_[x + y * max_coord_]; }

    static void divide2(MapArray& m);

    static bool _readed;

    int16_t& man_x_, &man_y_;
    int step_ = 0;
    int man_pic_;
    int rest_time_ = 0;                    //ֹͣ������ʱ��
    int man_pic0_ = 2501;                  //��ʼ����ͼƫ����
    int num_man_pic_ = 7;                  //��������ͼ����
    int rest_pic0_ = 2529;                 //������Ϣͼƫ����
    int num_rest_pic_ = 6;                 //������Ϣͼ����
    int ship_pic0_ = 3715;                 //��ʼ����ͼƫ����
    int num_ship_pic_ = 4;                 //��������ͼ����
    int begin_rest_time_ = 200;            //��ʼ��Ϣ��ʱ��
    int rest_interval_ = 15;               //��Ϣͼ�л����

    //todo: ��Ϣδ���

    Cloud::CloudTowards cloud_towards = Cloud::Left;
    std::vector<Cloud*> cloud_vector_;

    void draw() override;
    virtual void dealEvent(BP_Event& e) override;
    virtual void entrance() override;
    virtual void exit() override;

    void walk(int x, int y, Towards t);
    //void cloudMove();
    void getEntrance();
    virtual bool isBuilding(int x, int y);
    bool isWater(int x, int y);
    virtual bool isOutLine(int x, int y);
    bool isOutScreen(int x, int y);
    void getMousePosition(int _x, int _y);
    bool canWalk(int x, int y);
    bool checkEntrance(int x, int y);
    virtual void FindWay(int Mx, int My, int Fx, int Fy);
    void stopFindWay();
    std::stack<Point> way_que_;  //ջ(·��ջ)
};
