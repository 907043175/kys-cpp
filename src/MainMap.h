#pragma once
#include "Scene.h"
#include "Cloud.h"
#include "Types.h"

class MainMap : public Scene
{
public:
    MainMap();
    ~MainMap();

    static const int MAX_COORD = MAX_MAINMAP_COORD;
    typedef int16_t MapArray[MAX_COORD * MAX_COORD];
    static MapArray Earth_, Surface_, Building_, BuildX_, BuildY_, Entrance_;

    static int16_t& Earth(int x, int y) { return Earth_[x + y * MAX_COORD]; }
    static int16_t& Surface(int x, int y) { return Surface_[x + y * MAX_COORD]; }
    static int16_t& Building(int x, int y) { return Building_[x + y * MAX_COORD]; }
    static int16_t& BuildX(int x, int y) { return BuildX_[x + y * MAX_COORD]; }
    static int16_t& BuildY(int x, int y) { return BuildY_[x + y * MAX_COORD]; }

    static void divide2(MapArray& m);

    static bool data_readed_;

    int16_t& man_x_, &man_y_;
    int step_ = 0;
    int man_pic_;
    int rest_time_ = 0;                     //ֹͣ������ʱ��
    
    int MAN_PIC_0 = 2501;                   //��ʼ����ͼƫ����
    int MAN_PIC_COUNT = 7;                  //��������ͼ����
    int REST_PIC_0 = 2529;                  //������Ϣͼƫ����
    int REST_PIC_COUNT = 6;                 //������Ϣͼ����
    int SHIP_PIC_0 = 3715;                  //��ʼ����ͼƫ����
    int SHIP_PIC_COUNT = 4;                 //��������ͼ����
    int BEGIN_REST_TIME = 200;              //��ʼ��Ϣ��ʱ��
    int REST_INTERVAL = 15;                 //��Ϣͼ�л����

    //todo: ��Ϣδ���

    Cloud::CloudTowards cloud_towards = Cloud::Left;
    std::vector<Cloud*> cloud_vector_;

    void draw() override;
    virtual void dealEvent(BP_Event& e) override;
    virtual void entrance() override;
    virtual void exit() override;

    void tryWalk(int x, int y, Towards t);
    //void cloudMove();
    void getEntrance();
    
    virtual bool isBuilding(int x, int y);
    bool isWater(int x, int y);
    virtual bool isOutLine(int x, int y);
    
    virtual bool isOutScreen(int x, int y) override;
    virtual bool canWalk(int x, int y) override;
    
    bool checkEntrance(int x, int y);
    void getMousePosition(int _x, int _y);
};
