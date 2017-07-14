#pragma once
#include "UI.h"

typedef std::function<void()> ButtonFunc;
#define BIND_FUNC(func) std::bind(&func, this)

/**
* @file		 Button.h
* @brief	 ��ť��
* @author    xiaowu
* @Remark    20170710 �޸ĵײ��ͼ���� 
			 20170714 �ۣ�����һ�����д���кܶ����Ⱑ�����簴ť��״̬��Ӧ��Ӧ���Լ�ȥ��ɰ����������ò˵���ȥ��ɣ��˵�����ɵ�Ӧ�����Լ��Ķ���

*/



class Button : public UI
{
public:
    Button(const std::string& strNormalpath);
	Button(const std::string& strNormalpath, const std::string& strPasspath, const std::string& strPress);

    virtual ~Button();

	void InitMumber();
    void dealEvent(BP_Event& e) override;
	void draw();

    ButtonFunc func = nullptr;
    void setFunction(ButtonFunc func) { this->func = func; }
private:

	std::string m_strNormalpath, m_strPasspath, m_strPress; //����״̬�İ�ťͼƬ·��
    int nState; //��ť״̬
	enum ButtonState
	{
		Normal,
		Pass,
		Press,
	};

};

