#include "UI.h"
#include "Types.h"
#include "Save.h"
#include "Head.h"
#include "UIStatus.h"
#include "UISkill.h"
#include "UIItem.h"
#include "UISystem.h"

UI UI::ui_;

UI::UI()
{
    //ע�⣬�˴�Լ��childs_[0]Ϊ��UI�������ö�Ӧ��ָ�룬��Ҫ��ʾ�ĸ���ֵ��childs_[0]����
    ui_status_ = new UIStatus();
    ui_skill_ = new UISkill();
    ui_item_ = new UIItem();
    ui_system_ = new UISystem();
    ui_status_->setPosition(300, 0);
    ui_skill_->setPosition(300, 0);
    ui_item_->setPosition(300, 0);
    ui_system_->setPosition(300, 0);
    addChild(ui_status_);

    //ò�����ﲻ��ֱ�ӵ���������������̬���Ĵ���˳��ȷ��
    button_status_ = new Button("title", 122);
    button_skill_ = new Button("title", 123);
    button_item_ = new Button("title", 124);
    button_system_ = new Button("title", 125);
    addChild(button_status_, 10, 10);
    addChild(button_skill_, 90, 10);
    addChild(button_item_, 170, 10);
    addChild(button_system_, 250, 10);

    for (int i = 0; i < TEAMMATE_COUNT; i++)
    {
        auto h = new Head();
        addChild(h, 20, 60 + i * 90);
        heads_.push_back(h);
    }
    heads_[0]->setState(Pass);
    result_ = -1; //�Ǹ�����Ʒid������������������ٶ�
}


UI::~UI()
{
    childs_[0] = nullptr;
    delete ui_status_;
    delete ui_skill_;
    delete ui_item_;
    delete ui_system_;
}

void UI::onEntrance()
{
}

void UI::draw()
{
    Engine::getInstance()->fillColor({ 0, 0, 0, 128 }, 0, 0, -1, -1);
    for (int i = 0; i < TEAMMATE_COUNT; i++)
    {
        heads_[i]->setRole(Save::getInstance()->getTeamMate(i));
        if (heads_[i]->getState() != Normal)
        {
            auto role = heads_[i]->getRole();
            if (role)
            {
                ui_status_->setRole(role);
                ui_skill_->setRole(role);
            }
        }
    }
}

void UI::dealEvent(BP_Event& e)
{
    if (e.type == BP_MOUSEBUTTONUP && e.button.button == BP_BUTTON_LEFT)
    {
        //�������Ƿ�ʹ������Ʒ��������Ʒ��id
        if (childs_[0] == ui_item_)
        {
            result_ = ui_item_->getResult();
            setExit(true);
        }
        if (button_status_->getState() == Press) { childs_[0] = ui_status_; }
        if (button_skill_->getState() == Press) { childs_[0] = ui_skill_; }
        if (button_item_->getState() == Press) { childs_[0] = ui_item_; }
        if (button_system_->getState() == Press) { childs_[0] = ui_system_; }
    }
    if (e.type == BP_KEYUP && e.key.keysym.sym == BPK_ESCAPE
        || e.type == BP_MOUSEBUTTONUP && e.button.button == BP_BUTTON_RIGHT)
    {
        setExit(true);
    }
}
