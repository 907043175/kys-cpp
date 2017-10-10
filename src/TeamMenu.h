#pragma once
#include "Menu.h"
#include "Head.h"

//����ѡ������еĽ�ɫ�����Դ���һ��item��Ϊ���ˣ�Ϊ�ջ���ʾ������
class TeamMenu : public Menu
{
public:
    TeamMenu();
    ~TeamMenu();

private:
    std::vector<Head*> heads_;
    std::vector<int> selected_;
    Role* role_ = nullptr;
    Item* item_ = nullptr;
    int mode_ = 0;   //Ϊ0�ǵ�ѡ��Ϊ1�Ƕ�ѡ

public:
    void setItem(Item* item) { item_ = item; }
    void setMode(int m) { mode_ = m; }

    virtual void onEntrance() override;
    virtual void draw() override;
    virtual void pressedOK() override;

    Role* getRole();
    std::vector<Role*> getRoles();
};

