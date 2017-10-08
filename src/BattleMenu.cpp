#include "BattleMenu.h"
#include "Save.h"

BattleMenu::BattleMenu()
{
    setStrings({ "�Ƅ�", "��W", "�ö�", "�ⶾ", "�t��", "��Ʒ", "�ȴ�", "��B", "�Ԅ�", "�Y��" });
}

BattleMenu::~BattleMenu()
{
}

void BattleMenu::onEntrance()
{
    for (auto c : childs_)
    {
        c->setVisible(true);
    }

    //�ƶ����򲻿��ƶ�
    if (role_->Moved || role_->PhysicalPower < 10)
    {
        childs_[0]->setVisible(false);
    }
    //��ѧ
    if (role_->getLearnedMagicCount() <= 0 || role_->PhysicalPower < 20)
    {
        childs_[1]->setVisible(false);
    }
    //�ö�
    if (role_->UsePoison <= 0 || role_->PhysicalPower < 30)
    {
        childs_[2]->setVisible(false);
    }
    //�ⶾ
    if (role_->Detoxification <= 0 || role_->PhysicalPower < 30)
    {
        childs_[3]->setVisible(false);
    }
    //ҽ��
    if (role_->Medcine <= 0 || role_->PhysicalPower < 10)
    {
        childs_[4]->setVisible(false);
    }
    //���õȴ�
    childs_[6]->setVisible(false);
    setFontSize(20);
    arrange(0, 0, 0, 28);
}

int BattleMenu::runAsRole(Role* r)
{
    setRole(r);
    return run();
}

void BattleMenu::dealEvent(BP_Event& e)
{
    Menu::dealEvent(e);
    if (battle_scene_ == nullptr) { return; }
    if (role_)
    {
    }
}

