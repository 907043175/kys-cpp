#pragma once
#include "UI.h"

typedef std::function<void()> ButtonFunc;
#define BIND_FUNC(func) std::bind(&func, this)

/**
* @file      Button.h
* @brief     ��ť��
* @author    xiaowu
* @Remark    20170710 �޸ĵײ��ͼ����
             20170714 �ۣ�����һ�����д���кܶ����Ⱑ�����簴ť��״̬��Ӧ��Ӧ���Լ�ȥ��ɰ����������ò˵���ȥ��ɣ��˵�����ɵ�Ӧ�����Լ��Ķ���

*/

class Button : public UI
{
public:
    Button() {}
    Button(const std::string& path, int n1, int n2 = -1, int n3 = -1);

    enum ButtonState
    {
        Normal,
        Pass,
        Press,
    };

    virtual ~Button();

    //void InitMumber();
    void dealEvent(BP_Event& e) override;
    void draw();

    ButtonFunc func = nullptr;
    void setFunction(ButtonFunc func) { this->func = func; }
private:
    Texture* normal = nullptr, *pass = nullptr, *press = nullptr; //����״̬�İ�ťͼƬ
    int state_; //��ť״̬
public:
    void setState(ButtonState s) { state_ = s; }
};

