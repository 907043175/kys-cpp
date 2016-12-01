#pragma once
#include "save.h"
#include "Head.h"
#include <direct.h>
#include <corecrt_io.h>

//#include "cocos2d.h"
//USING_NS_CC;
using namespace std;

class Operation
{
public:
	short num;
	vector <short> par;
};
class EventInstruct  //����ָ���ʵ��д����
{
public:
	void XXX();
};
class EventData
{
public:
	const vector<Operation>* getOperation();
	void setId(int num);
	bool checkId(int num);
	void arrByOperation(unsigned char *Data, int len);			//��ָ�������������;�Ժ����¼���֯��ص����ݾ������Ϊ����
	int getOperationLen(int num);	//��ȡָ�����ݳ���;

private:
	int _id;
	vector<Operation>_operations;
};

class EventManager
{
public:
	EventManager();
	virtual ~EventManager();
	static EventManager eventManager;
	static EventManager* getInstance()
	{
		return &eventManager;
	}
	bool initEventData();		//�����¼�����


	bool callEvent(int num);	//����ָ�������д����
	std::vector<EventData> eventData;

	int eventCount = 0;
};






