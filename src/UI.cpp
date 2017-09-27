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
    //ע�⣬�˴�Լ��ǰMAX_TEAMMATE_COUNT������ΪСͷ�񣬺�������4��Ϊ�л��õİ�ť
    for (int i = 0; i < MAX_TEAMMATE_COUNT; i++)
    {
        auto h = new Head();
        addChild(h, 10, i * 80);
        h->setSize(200, 80);
        heads_.push_back(h);
    }
    //�˴������ö�Ӧ��ָ�룬��Ҫ��ʾ�ĸ��ͽ�childs_ĩβ��ָ���滻����
    uistatus_ = new UIStatus();
    uiskill_ = new UISkill();
    uiitem_ = new UIItem();
    uisystem_ = new UISystem();
    addChild(uistatus_, 200, 0);
    heads_[0]->setState(Pass);
    instance_ = true;
}


UI::~UI()
{
}

void UI::entrance()
{

}

void UI::draw()
{
    Engine::getInstance()->fillColor({ 0, 0, 0, 128 }, 0, 0, -1, -1);
    for (int i = 0; i < MAX_TEAMMATE_COUNT; i++)
    {
        heads_[i]->setRole(Save::getInstance()->getTeamMate(i));
        if (heads_[i]->getState() != Normal)
        {
            uistatus_->setRole(heads_[i]->getRole());
            uiskill_->setRole(heads_[i]->getRole());
        }
    }
}

void UI::dealEvent(BP_Event& e)
{
    if (e.type == BP_KEYUP)
    {
        if (e.key.keysym.sym == BPK_ESCAPE)
        {
            loop_ = false;
        }
    }
}
