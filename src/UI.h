#pragma once
#include "Base.h"
//#include "Head.h"
//#include "UIStatus.h"
//#include "UISkill.h"
//#include "UIItem.h"
//#include "UISystem.h"

//ǰ�����������ٱ�������
class Head;
class UIStatus;
class UISkill;
class UIItem;
class UISystem;

class UI : public Base
{
private:
    UI();
    ~UI();
    //UI�˵��������ɣ������ظ�����
    static UI ui_;
public:
    virtual void entrance() override;
    virtual void draw() override;
    virtual void dealEvent(BP_Event& e) override;

    static UI* getInstance() { return &ui_; }

    std::vector<Head*> heads_;
    UIStatus* uistatus_ = nullptr;
    UISkill* uiskill_ = nullptr;
    UIItem* uiitem_ = nullptr;
    UISystem* uisystem_ = nullptr;
    int item_id_ = -1;
};

