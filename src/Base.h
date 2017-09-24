#pragma once
#include <vector>
#include "Engine.h"
#include "TextureManager.h"

#define CONNECT(a,b) a##b

//��Ϸ���ƻ����࣬����Ҫ��ʾ����ģ����̳��Դ�
class Base
{
public:
    static std::vector<Base*> base_root_;   //������Ҫ���Ƶ����ݶ��洢�����������
    std::vector<Base*> childs_;
    bool visible_ = true;
    protected:
    int result_ = -1;
public:
    Base() {}
    virtual ~Base();

    static void LOG(const char* format, ...);
    template <class T> void safe_delete(T*& pointer)
    {
        if (pointer)
        { delete pointer; }
        pointer = nullptr;
    }

    static void drawAll();
    static void push(Base* b) { base_root_.push_back(b); }
    static Base* pop();
    static Base* getCurentBase() { return base_root_.at(0); }

    int x_ = 0;
    int y_ = 0;
    int w_ = 0;
    int h_ = 0;
    void setPosition(int x, int y);
    void setSize(int w, int h) { w_ = w; h_ = h; }
    bool inSide(int x, int y);

    int full_window_ = 0;                               //��Ϊ0ʱ��ʾ��ǰ����Ϊ��ʼ�㣬���ڱ�����Ĳ㽫������ʾ

    bool loop_ = true;
    int run();                                         //ִ�б���

    virtual void backRun() {}                           //һֱ���У����Է����ܼ�����
    virtual void draw() {}                              //��λ�����
    virtual void dealEvent(BP_Event& e) {}              //ÿ��ѭ���д����¼�
    virtual void enter() {}                          //���뱾����¼����������������
    virtual void exit() {}                              //�뿪������¼������������
    //virtual void init() {}                              //��ʼ�����㣬�������һЩָ�룬��ֵ���趨
    int getResult() { return result_; }
    void drawSelfAndChilds();
    void addChild(Base* b, int x, int y);
};

