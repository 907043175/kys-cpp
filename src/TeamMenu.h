#pragma once
#include "Menu.h"
#include "Head.h"

//����ѡ������еĽ�ɫ�����Դ���һ��item��Ϊ���ˣ�Ϊ�ջ���ʾ������
class TeamMenu : public Menu
{
public:
    TeamMenu();
    ~TeamMenu();

    std::vector<Head*> heads_;

    std::vector<int> selected_;

    Item* item = nullptr;

    virtual void onEntrance() override;

    int mode_;   //Ϊ0�ǵ�ѡ��Ϊ1�Ƕ�ѡ

};

