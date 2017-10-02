#pragma once
#include <vector>
#include "Engine.h"
#include "TextureManager.h"

#define CONNECT(a,b) a##b

//��Ϸ���ƻ����࣬����Ҫ��ʾ����ģ����̳��Դ�
class Base
{
private:
    static std::vector<Base*> root_;   //������Ҫ���Ƶ����ݶ��洢�����������
    //static std::set<Base*> collector_;
    int prev_present_ticks_;
protected:
    std::vector<Base*> childs_;
    bool visible_ = true;
    int result_ = -1;
    int full_window_ = 0;              //��Ϊ0ʱ��ʾ��ǰ����Ϊ��ʼ�㣬���ڱ�����Ĳ㽫������ʾ
    bool exit_ = false;                //����Ĺ��������ֵΪtrue������ʾ�˳�
protected:
    int x_ = 0;
    int y_ = 0;
    int w_ = 0;
    int h_ = 0;
public:
    Base() {}
    virtual ~Base();

    static void drawAll();

    static void addOnRootTop(Base* b) { root_.push_back(b); }
    static Base* removeFromRoot(Base* b);

    //static Base* getCurentBase() { return root_.at(0); }

    void addChild(Base* b);
    void addChild(Base* b, int x, int y);
    void removeChild(Base* b);
    void clearChilds();   //���Ƽ�

    void setPosition(int x, int y);
    void setSize(int w, int h) { w_ = w; h_ = h; }

    bool inSide(int x, int y)
    {
        return x > x_ && x < x_ + w_ && y > y_ && y < y_ + h_;
    }

    int run(bool in_root = true);                       //ִ�б���

    virtual void backRun() {}                           //һֱ���У����Է����ܼ�����
    virtual void draw() {}                              //��λ�����
    virtual void dealEvent(BP_Event& e) {}              //ÿ��ѭ���д����¼�
    virtual void onEntrance() {}                          //���뱾����¼����������������
    virtual void onExit() {}                              //�뿪������¼������������

    int getResult() { return result_; }
    void drawSelfAndChilds();

    bool getVisible() { return visible_; }
    void setVisible(bool v) { visible_ = v; }

    enum State
    {
        Normal,
        Pass,
        Press,
    };

    State state_ = Normal;   //״̬
    State getState() { return state_; }
    void setState(State s) { state_ = s; }
    void checkStateAndEvent(BP_Event& e);

    void oneFrame(bool check_event = false);

    static void clearEvent(BP_Event& e) { e.type = BP_FIRSTEVENT; }
    static Base* getCurrentTopDraw() { return root_.back(); }

    void setAllChildState(State s);
    void setChildState(int i, State s);

    void setExit(bool e) { exit_ = e; }
};

