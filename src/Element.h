#pragma once
#include <vector>
#include "Engine.h"
#include "TextureManager.h"
#include <functional>

#define CONNECT(a,b) a##b

//��Ϸִ�кͻ��ƵĻ����࣬����Ҫ��ʾ������ߴ����¼��ģ����̳��Դ�
class Element
{
private:
    static std::vector<Element*> root_;   //������Ҫ���Ƶ����ݶ��洢�������̬������
    static int prev_present_ticks_;
    const int max_delay_ = 25;
protected:
    std::vector<Element*> childs_;
    bool visible_ = true;
    int result_ = -1;
    int full_window_ = 0;              //��Ϊ0ʱ��ʾ��ǰ����Ϊ��ʼ�㣬��ʱ���ڱ���Ľ�������ʾ����ʡ��Դ
    bool exit_ = true;                 //����Ĺ��������ֵΪtrue������ʾ��һ��ѭ�����˳�
protected:
    int x_ = 0;
    int y_ = 0;
    int w_ = 0;
    int h_ = 0;
public:
    Element() {}
    virtual ~Element();

    static void drawAll();

    static void addOnRootTop(Element* element) { root_.push_back(element); }
    static Element* removeFromRoot(Element* element);

    void addChild(Element* element);
    void addChild(Element* element, int x, int y);
    Element* getChild(int i) { return childs_[i]; }
    int getChildCount() { return childs_.size(); }
    void removeChild(Element* element);
    void clearChilds();

    void setPosition(int x, int y);
    void setSize(int w, int h) { w_ = w; h_ = h; }

    void getPosition(int& x, int& y) { x = x_; y = y_; }
    void getSize(int& w, int& h) { w = w_; h = h_; }

    bool inSide(int x, int y)
    {
        return x > x_ && x < x_ + w_ && y > y_ && y < y_ + h_;
    }

    int getResult() { return result_; }
    bool getVisible() { return visible_; }
    void setVisible(bool v) { visible_ = v; }

    //״̬
    enum State
    {
        Normal,
        Pass,
        Press,
    };

    int state_ = Normal;
    int getState() { return state_; }
    void setState(int s) { state_ = s; }

    static void clearEvent(BP_Event& e) { e.type = BP_FIRSTEVENT; }
    static Element* getCurrentTopDraw() { return root_.back(); }

    void setAllChildState(int s);
    //void setChildState(int i, int s);
    //int getChildState(int i);

    int findNextVisibleChild(int i0, int direct);

    void setExit(bool e) { exit_ = e; }
    bool isRunning() { return !exit_; }

    void exitWithResult(int r) { setExit(true); result_ = r; }


    //ͨ����˵������������޹ص��߼�����draw��dealEvent�����ⲻ�󣬵��ǽ���draw�н��л�ͼ��صĲ���

    virtual void backRun() {}                           //һֱ���У����Է����ܼ�����
    virtual void draw() {}                              //��λ�����
    virtual void dealEvent(BP_Event& e) {}              //ÿ��ѭ���д����¼�
    virtual void onEntrance() {}                        //���뱾����¼����������������
    virtual void onExit() {}                            //�뿪������¼������������

    virtual void pressedOK() {}                         //���»س������������¼�
    virtual void pressedCancel() {}                     //����esc������Ҽ����¼�

private:
    void drawSelfAndChilds();
    void checkStateAndEvent(BP_Event& e);
    void checkEventAndPresent(bool check_event = false);

public:
    int run(bool in_root = true);                       //ִ�б���
    int runAtPosition(int x = 0, int y = 0, bool in_root = true) { setPosition(x, y); return run(in_root); }
    int drawAndPresent(int times = 1, std::function<void(void*)> func = nullptr, void* data = nullptr);

    //��Ҫ��ͨ�˳����ܵ��ӽڵ㣬�븴����������ȥ�����˳�����ʽ��ͬ������ʵ�֣��ĳɺ�Ҳ��
    //ע�������������ܻ���ּ̳й�ϵ����������ٸ�д
    //virtual void pressedOK() override { exitWithResult(0); }
    //virtual void pressedCancel() override { exitWithResult(-1); }
};

