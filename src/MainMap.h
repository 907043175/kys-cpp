#pragma once

#include "Common.h"
#include "Save.h"

using namespace std;

class MainMap : public CommonScene
{
private:
	bool _readed = false;
	void ReadMap();
public:
	//RenderTexture* tex[8];
	int const static maxX = 480;
	int const static maxY = 480;

	typedef short MapArray[maxX][maxY];
	static MapArray Earth, Surface, Building, BuildX, BuildY, Entrance;
	//int walk[30][2];
	stack<MyPoint> wayQue;												//ջ(·��ջ)
									
	std::vector<Sprite*> EarthS, SurfaceS, BuildingS, CloudS;

	enum CloudTowards
	{
		Left = 0,
		Right = 1,
		Up = 2,
		Down = 3,
	};
	
	int cloudX,cloudY;
	int step = 0;
	int manPicture;
	int restTime = 0;					//ֹͣ������ʱ��
	int cloud_restTime = 0;				//����ʧ��ʱ��
	int const offset_manPic = 5001;		//��ʼ����ͼƫ����
	int const num_manPic = 7;				//��������ͼ����
	int const offset_restPic = 5029;		//������Ϣͼƫ����
	int const num_restPic = 6;			//������Ϣͼ����
	int const begin_restTime = 200;		//��ʼ��Ϣ��ʱ��
	int const each_pictrueTime = 15;		//��Ϣͼ�л����
	int const cloudSize = 240;				//�ƶ���
	int const static tag_mainLayer = 1;		//������ 
	int const static tag_wordLayer = 1;		//���ֲ���


	bool isEsc = false;					//�Ƿ��Ѵ�ϵͳ�˵�

	CloudTowards cloudTowards = Left;

	SceneData* curRScene;

	MainMap();
	~MainMap();

	virtual bool init();
	
	void Draw();

	void keyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void keyReleased(EventKeyboard::KeyCode keyCode, Event *event);
    void mouseDown(EventMouse eventMouse, Event *event);
    void mouseUp(EventMouse eventMouse, Event *event);
    void mouseScroll(EventMouse eventMouse, Event *event);
    void mouseMove(EventMouse eventMouse, Event *event);
    bool touchBegan(Touch *touch, Event *event);
    void touchEnded(Touch *touch, Event *event);
    void touchCancelled(Touch *touch, Event *event);
    void touchMoved(Touch *touch, Event *event);
	
	virtual void checkTimer2();
	void Walk(int x, int y, Towards t);
	void cloudMove();
	void getEntrance();
	void getMousePosition(Point *point);

	virtual bool checkIsBuilding(int x, int y);
	bool checkIsWater(int x, int y);
	virtual bool checkIsOutLine(int x, int y);
	bool checkIsOutScreen(int x, int y);
	bool canWalk(int x, int y);
	bool checkIsEntrance(int x, int y);
	virtual void FindWay(int Mx, int My, int Fx, int Fy);
	void stopFindWay();

	void menuCloseCallback(Ref* pSender);

	void test();

	CREATE_FUNC(MainMap);

	static Scene* createScene();
};


class Cloud : public Sprite
{
public:
	Point position;
	float speed;

	const int maxX = 17280;
	const int maxY = 8640;

	enum { numTexture = 10 };

	void initRand()
	{
		position.x = rand() % maxX;
		position.y = rand() % maxY;
		speed = 1 + rand() % 3;
		auto t = MyTexture2D::getSelfPointer(MyTexture2D::Cloud, rand() % numTexture);
		//this->setTexture(t->getTexture());
		t->setToSprite(this, Point(0, 0));
		this->setOpacity(128 + rand() % 128);
		this->setColor(Color3B(rand() % 256, rand() % 256, rand() % 256));
	}
	void setPositionOnScreen(int x, int y, int Center_X, int Center_Y)
	{
		this->setPosition(position.x - (-x * 18 + y * 18 + maxX / 2 - Center_X), -position.y + (x * 9 + y * 9 + 9 - Center_Y));
		//this->setPosition(324, 200);
	}
	void changePosition()
	{
		position.x += speed;
		if (position.x > maxX)
		{
			position.x = 0;
		}
	}

	static void initTextures()
	{
		//�Ƶ���ͼ
		char* path = "cloud";
		MyTexture2D::tex[MyTexture2D::Cloud][1].resize(numTexture);
		for (int i = 0; i < numTexture; i++)
		{
			MyTexture2D::addImage(path, MyTexture2D::Cloud, i, 0, 0, 1, true, true);
		}

	}
	CREATE_FUNC(Cloud);

};

