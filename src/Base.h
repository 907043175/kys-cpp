#pragma once
#include <vector>
#include "Engine.h"
#include "TextureManager.h"

#define CONNECT(a,b) a##b

struct auto_ptr
{

};

class Base      //��Ϸ���ƻ����࣬����Ҫ��ʾ����ģ����̳��Դ�
{
public:
    static std::vector<Base*> base_vector_;   //������Ҫ���Ƶ����ݶ��洢��m_vcBase��
    bool visible_ = true;
public:
    Base();
    virtual ~Base();

    virtual void run() {}
    virtual void draw() {}
    virtual void dealEvent(BP_Event& e) {}
    virtual void init() {}

    void LOG(const char* format, ...);
    template <class T> void safe_delete(T*& pointer)
    {
        if (pointer)
        { delete pointer; }
        pointer = nullptr;
    }

    

    void push(Base* b) { base_vector_.push_back(b); b->init(); }
    void pop() { base_vector_.pop_back(); }
    static Base* getCurentBase() { return base_vector_.at(0); }

    int x_ = 0;
    int y_ = 0;
    int w_ = 0;
    int h_ = 0;
    void setPosition(int x, int y) { x_ = x; y_ = y; }
    void setSize(int w, int h) { w_ = w; h_ = h; }
    bool inSide(int x, int y);

    int full_window_ = 0;  //��Ϊ0ʱ��ʾ��ǰ����Ϊ��ʼ�㣬���ڱ�����Ĳ㽫������ʾ

};

