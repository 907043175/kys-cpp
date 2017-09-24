#pragma once
#include <vector>
#include "Engine.h"
#include "TextureManager.h"

#define CONNECT(a,b) a##b

//��Ϸ���ƻ����࣬����Ҫ��ʾ����ģ����̳��Դ�
class Base
{
public:
    static std::vector<Base*> base_need_draw_;   //������Ҫ���Ƶ����ݶ��洢�����������
    bool visible_ = true;
public:
    Base() {}
    virtual ~Base() {}

    void LOG(const char* format, ...);
    template <class T> void safe_delete(T*& pointer)
    {
        if (pointer)
        { delete pointer; }
        pointer = nullptr;
    }

    static void drawAll();
    static void push(Base* b) { base_need_draw_.push_back(b); }
    static Base* pop();
    static Base* getCurentBase() { return base_need_draw_.at(0); }

    int x_ = 0;
    int y_ = 0;
    int w_ = 0;
    int h_ = 0;
    void setPosition(int x, int y) { x_ = x; y_ = y; }
    void setSize(int w, int h) { w_ = w; h_ = h; }
    bool inSide(int x, int y);

    int full_window_ = 0;                               //��Ϊ0ʱ��ʾ��ǰ����Ϊ��ʼ�㣬���ڱ�����Ĳ㽫������ʾ

    bool loop_ = true;
    void run();                                         //ִ�б���

    virtual void backRun() {}                           //һֱ���У����Է����ܼ�����
    virtual void draw() {}                              //��λ�����
    virtual void dealEvent(BP_Event& e) {}              //ÿ��ѭ���д����¼�
    virtual void entrance() {}                          //���뱾����¼����������������
    virtual void exit() {}                              //�뿪������¼������������
    virtual void init() {}                              //��ʼ�����㣬�������һЩָ�룬��ֵ���趨

};

