#pragma once
#include "Menu.h"
#include "Head.h"

class TeamMenu : public Menu
{
public:
    TeamMenu();
    ~TeamMenu();

    std::vector<Head*> heads_;

    std::vector<int> selected_;

    virtual void entrance() override;

    int mode_;   //Ϊ0�ǵ�ѡ��Ϊ1�Ƕ�ѡ

};

