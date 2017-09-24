#pragma once

#include "Scene.h"
#include <stack>
#include "Save.h"

class SubMap : public Scene
{
private:
    SubMap();
public:
    SubMap(int num);
    virtual ~SubMap();

    int Cx=0, Cy=0;
    int manPicture;
    int step = 0;

    const int MaxSceneCoord = 63;

    int const offset_manPic = 2501;  //��ʼ��������ͼƫ����
    int const num_manPic = 7;  //��������ͼ����
    int scene_id_;   //������

    SubMapRecord* current_submap_;

    std::stack<Point> wayQue;  //ջ(·��ջ)

    void setSceneNum(int num) { scene_id_ = num; }

	void setPosition(int x, int y);
    void draw() override;
    void dealEvent(BP_Event& e) override;
    virtual void backRun() override;

    void walk(int x, int y, Towards t);

    void callEvent(int x, int y);
    bool canWalk(int x, int y);
    virtual bool isBuilding(int x, int y);
    virtual bool isOutLine(int x, int y);
    bool isWater(int x, int y);
    bool isEvent(int x, int y);
    bool isFall(int x, int y);
    bool isExit(int x, int y);
    bool isOutScreen(int x, int y);
    void stopFindWay();

    void getMousePosition(int _x, int _y);
    virtual void FindWay(int Mx, int My, int Fx, int Fy);
	void ReSetEventPosition(int &x, int &y); //add by xiaowu �����¼�����

};

