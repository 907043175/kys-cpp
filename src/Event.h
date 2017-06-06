#pragma once
#include "save.h"
#include "Head.h"
#include <direct.h>
#include <corecrt_io.h>
#include <functional>

//#include "cocos2d.h"
//USING_NS_CC;
using namespace std;

//typedef function<int(int,int,int,int,int)> EventFunc;

class Operation
{
public:
    short num;
    vector <short> par;
};



//�ڲ�����ָ���������������ֵΪ��ǰָ���ָ�룬����ֵΪָ����Ҫ�ƶ���ֵ���ú�򻯴���
//#define EVENT_FUNC(name) int name(int p1=-2,int p2=-2, int p3=-2, int p4=-2,int p5=-2)




class EventData
{
public:
    const vector<Operation>* getOperation();
    void setId(int num);
    bool checkId(int num);
    void arrByOperation(unsigned char* Data, int len);          //��ָ�������������;�Ժ����¼���֯��ص����ݾ������Ϊ����
    int getOperationLen(int num);   //��ȡָ�����ݳ���;

private:
    int _id;
    vector<Operation>_operations;
};

class EventManager
{
public:
	EventManager()
	{};
	virtual ~EventManager();
    static EventManager* getInstance()
    {
		if (m_EventManager == NULL)
			m_EventManager = new EventManager();
        return m_EventManager;
    }
    bool initEventData();       //�����¼�����
    bool callEvent(int num);    //����ָ�������д����
	void iniEventRun();
	void runEvent(const std::vector<Operation>* operation);
    std::vector<EventData> eventData;
    int eventCount = 0;
	

	void clear_0();
	void talk_1();
	void getItem_2(short tnum, short amount, short rnum = 0);
	void getJueSe(short* rnum);
	void editEvent3(short snum, short ednum, short CanWalk, short Num, short Event1, short Event2, short Event3, short BeginPic1, short EndPic, short BeginPic2, short  PicDelay, short  XPos, short  YPos, short StartTime, short  Duration, short Interval, short  DoneTime, short  IsActive, short  OutTime, short  OutEvent);
	int judgeItem_4(short inum,short jump1,short jump2);
	int isFight_5(short jump1,short jump2);

	int isAdd_8(short jump1, short jump2);
	int getGongtiLevel(int rnum, int gongti);
	int getRoleSpeed(int rnum, bool equip);
	int getRoleDefence(int rnum, bool equip);
	int getRoleAttack(int rnum, bool equip);
	int getRoleBoxing(int rnum, bool equip);
	int getRoleFencing(int rnum, bool equip);
	int getRoleKnife(int rnum, bool equip);
	int getRoleSpecial(int rnum, bool equip);
	int getRoleShader(int rnum, bool equip);
	int getRoleDefpoi(int rnum, bool equip);
	int getRoleAttpoi(int rnum, bool equip);
	int getRoleUsepoi(int rnum, bool equip);
	int getRoleMedpoi(int rnum, bool equip);
	int getRoleMedicine(int rnum, bool equip);
	int GetItemCount(int inum);
	void StudyMagic(int rnum, int magicnum, int newmagicnum, int level, int dismode);
	void JumpScene(int snum, int x, int y);

private:
	static EventManager *m_EventManager;
	static int NowEenWu;
	static bool isTry;
	static bool TryGo;
	static int TryEventTmpI;
	static int EventEndCount;

};






