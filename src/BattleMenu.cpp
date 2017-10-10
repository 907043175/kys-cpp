#include "BattleMenu.h"
#include "Save.h"
#include "Random.h"

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
        c->setState(Normal);
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
    childs_[findNextVisibleChild(getChildCount() - 1, 1)]->setState(Pass);
}

int BattleMenu::runAsRole(Role* r)
{
    setRole(r);
    return run();
}

void BattleMenu::dealEvent(BP_Event& e)
{

    if (battle_scene_ == nullptr) { return; }
    if (role_->Auto)
    {
        setResult(autoSelect(role_));
    }
    else
    {
        Menu::dealEvent(e);
    }
}

//"0�Ƅ�", "1��W", "2�ö�", "3�ⶾ", "4�t��", "5��Ʒ", "6�ȴ�"
int BattleMenu::autoSelect(Role* r)
{
    Random<double> rand;   //÷ɭ��ת�������
    rand.set_seed();

    std::vector<int> points(10);
    //aiΪÿ���ж����֣���ѧ���ö����ⶾ��ҽ��

    //��������������20%��0.8���ʿ��ǳ�ҩ
    if (r->HP < 0.2*r->MaxHP)
    {
        points[5] = 0;
    }

    if (r->MP < 0.2*r->MaxMP)
    {
        points[5] = 0;
    }

    if (r->Morality > 50)
    {
        //��ⶾ�ģ��������������ж������ߣ��ӽ����ⶾ
        if (childs_[3]->getVisible())
        {
            points[3] == 0;
        }

        if (childs_[4]->getVisible())
        {
            points[4] == 0;
        }
    }
    else
    {
        //�����ö�
        if (childs_[2]->getVisible())
        {
            points[2] == 0;
        }
    }

    if (childs_[1]->getVisible())
    {
        points[1] = 0;
    }

    return 0;
}

