#pragma once
#include <stack>
#include "Scene.h"
#include "Cloud.h"

class MainMap : public Scene
{
public:
    MainMap();
    ~MainMap();
    //RenderTexture* tex[8];
    int const static maxX = 480;
    int const static maxY = 480;

    typedef short MapArray[maxX][maxY];
    static MapArray Earth, Surface, Building, BuildX, BuildY, Entrance;
    //int walk[30][2];
    std::stack<Point> wayQue;  //ջ(·��ջ)

    //std::vector<Sprite*> EarthS, SurfaceS, BuildingS, CloudS;

    static int Mx, My;


    int cloudX, cloudY;
    int step = 0;
    int manPicture;
    int restTime = 0;          //ֹͣ������ʱ��
    int cloud_restTime = 0;        //����ʧ��ʱ��
    int const offset_manPic = 5001;    //��ʼ����ͼƫ����
    int const num_manPic = 7;        //��������ͼ����
    int const offset_restPic = 5029;    //������Ϣͼƫ����
    int const num_restPic = 6;      //������Ϣͼ����
    int const begin_restTime = 200;    //��ʼ��Ϣ��ʱ��
    int const each_pictrueTime = 15;    //��Ϣͼ�л����
    int const cloudSize = 240;        //�ƶ���
    int const static tag_mainLayer = 1;  //������ 
    int const static tag_wordLayer = 1;  //���ֲ���


    bool isEsc = false;  //�Ƿ��Ѵ�ϵͳ�˵�

    Cloud::CloudTowards cloudTowards = Cloud::Left;

    std::vector<Cloud*> cloudVector;

    //SceneData* curRScene;
    void draw() override;

    bool _readed = false;
    void init() override;

    void dealEvent(BP_Event& e) override;
    void Walk(int x, int y, Towards t);
    void cloudMove();
    void getEntrance();

    virtual bool checkIsBuilding(int x, int y);
    bool checkIsWater(int x, int y);
    virtual bool checkIsOutLine(int x, int y);
    bool checkIsOutScreen(int x, int y);
    void getMousePosition(Point *point);
    bool canWalk(int x, int y);
    bool checkIsEntrance(int x, int y);
    virtual void FindWay(int Mx, int My, int Fx, int Fy);
    void stopFindWay();
};
