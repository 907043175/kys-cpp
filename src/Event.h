#pragma once
#include "save.h"
#include "Head.h"
#include <direct.h>
#include <corecrt_io.h>
#include <functional>

//#include "cocos2d.h"
//USING_NS_CC;
using namespace std;

typedef function<int(int,int,int,int,int)> EventFunc;

class Operation
{
public:
    short num;
    vector <short> par;
};



//�ڲ�����ָ���������������ֵΪ��ǰָ���ָ�룬����ֵΪָ����Ҫ�ƶ���ֵ���ú�򻯴���
#define EVENT_FUNC(name) int name(int p1=-2,int p2=-2, int p3=-2, int p4=-2,int p5=-2)
class EventInstruct  //����ָ���ʵ��д����
{
public:
    static vector<EventFunc> funcs;
public:
    EventInstruct();
#define EVENT_FUNCS \
    EVENT_FUNC(clear_screen);\
    EVENT_FUNC(talk);\
	EVENT_FUNC(isZhangMen);

    EVENT_FUNCS;

    void XXX();
};
#undef EVENT_FUNC

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
    EventManager();
    virtual ~EventManager();
    static EventManager eventManager;
    static EventManager* getInstance()
    {
        return &eventManager;
    }
    bool initEventData();       //�����¼�����


    bool callEvent(int num);    //����ָ�������д����
    std::vector<EventData> eventData;

    int eventCount = 0;
};






