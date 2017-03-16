#pragma once

#include "Scene.h"
#include <stack>

class SubScene : public Scene
{
public:
    SubScene();
    SubScene(int num) : SubScene() { setSceneNum(num); }
    virtual ~SubScene();

    int Sx, Sy;
    int manPicture;
    int step = 0;
    int const offset_manPic = 5001;  //��ʼ��������ͼƫ����
    int const num_manPic = 7;  //��������ͼ����
    int sceneNum;   //������
    //std::vector<Sprite*> EarthS, BuildS, AirS, EventS;
    std::stack<Point> wayQue;  //ջ(·��ջ)

    void setSceneNum(int num) { sceneNum = num; }

    void init() override;
	void setPosition(int x, int y);
    void draw() override;
    void dealEvent(BP_Event& e) override;

    void walk(int x, int y, Towards t);

    void callEvent(int x, int y);
    bool canWalk(int x, int y);
    virtual bool checkIsBuilding(int x, int y);
    virtual bool checkIsOutLine(int x, int y);
    bool checkIsHinder(int x, int y);
    bool checkIsEvent(int x, int y);
    bool checkIsFall(int x, int y);
    bool checkIsExit(int x, int y);
    bool checkIsOutScreen(int x, int y);
    void stopFindWay();

    void getMousePosition(int _x, int _y);
    virtual void FindWay(int Mx, int My, int Fx, int Fy);

    inline int calBlockTurn(int x, int y, int layer)
    {
        return 4 * (128 * (x + y) + x) + layer;
    }

};

