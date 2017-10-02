#pragma once
#include "Scene.h"
#include "Cloud.h"
#include "Types.h"

class MainScene : public Scene
{
private:
    static MainScene main_map_;
    MainScene();
    ~MainScene();

public:
    static MainScene* getIntance() { return &main_map_; }

    static const int COORD_COUNT = MAINMAP_COORD_COUNT;
    MapSquare earth_layer_ , surface_layer_, building_layer_, build_x_layer_, build_y_layer_, entrance_layer_;
    bool data_readed_ = false;

    void divide2(MapSquare& m);

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
    virtual void onEntrance() override;
    virtual void onExit() override;

    void tryWalk(int x, int y, Towards t);
    //void cloudMove();
    void getEntrance();

    virtual bool isBuilding(int x, int y);
    bool isWater(int x, int y);
    virtual bool isOutLine(int x, int y);

    virtual bool isOutScreen(int x, int y) override;
    virtual bool canWalk(int x, int y) override;

    bool checkEntrance(int x, int y);    //����ͼ��Ҫ�Ǽ�����
};
