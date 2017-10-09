#include "GameUtil.h"
#include "others/libconvert.h"
#include "Save.h"
#include "Random.h"

GameUtil GameUtil::game_util_;

GameUtil::GameUtil()
{
    auto str = convert::readStringFromFile("../game/list/levelup.txt");
    convert::findNumbers(str, &level_up_list_);
    if (level_up_list_.size() < MAX_LEVEL)
    {
        level_up_list_.resize(MAX_LEVEL, 60000);
    }
}

GameUtil::~GameUtil()
{
}

//ĳ���Ƿ����ʹ��ĳ��Ʒ
//ԭ���ࣺ0���飬1װ����2���ţ�3ҩƷ��4����
bool GameUtil::canUseItem(Role* r, Item* i)
{
    if (r == nullptr) { return false; }
    if (i == nullptr) { return false; }
    if (i->ItemType == 0)
    {
        //���������˿���ʹ��
        return false;
    }
    else if (i->ItemType == 1 || i->ItemType == 2)
    {
        if (i->ItemType == 2)
        {
            //���������ж�
            if ((r->MPType == 0 || r->MPType == 1) && (i->NeedMPType == 0 || i->NeedMPType == 1))
            {
                if (r->MPType != i->NeedMPType)
                {
                    return false;
                }
            }
            //�н��ʺ����ֱ���ж�
            if (i->OnlySuitableRole >= 0)
            {
                return i->OnlySuitableRole == r->ID;
            }
        }

        //���������ѧ��������Ϊ�٣�δ����Ϊ��
        //�˴�ע�⣬����п��Ƴ���Ʒ���ؼ�������ѧ����֮�󲻻�����ҩ�ˣ��뾡����������������
        if (i->MagicID > 0)
        {
            int level = r->getMagicLevelIndex(i->MagicID);
            if (level >= 0 && level < MAX_MAGIC_LEVEL_INDEX) { return true; }
            if (level == MAX_MAGIC_LEVEL_INDEX) { return false; }
        }

        //�ж�ĳ�������Ƿ��ʺ�
        auto test = [](SAVE_INT v, SAVE_INT v_need)->bool
        {
            if (v_need > 0 && v < v_need) { return false; }
            if (v_need < 0 && v > -v_need) { return false; }
            return true;
        };

        //������ж�δȷ�������������ж���
        return test(r->Attack, i->NeedAttack) && test(r->Speed, i->NeedSpeed)
            && test(r->Medcine, i->NeedMedcine)
            && test(r->UsePoison, i->NeedUsePoison) && test(r->Detoxification, i->NeedDetoxification)
            && test(r->Fist, i->NeedFist) && test(r->Sword, i->NeedSword)
            && test(r->Knife, i->NeedKnife) && test(r->Unusual, i->NeedUnusual)
            && test(r->HiddenWeapon, i->NeedHiddenWeapon)
            && test(r->MP, i->NeedMP)
            && test(r->IQ, i->NeedIQ);
    }
    else if (i->ItemType == 3)
    {
        //ҩƷ�������˿���ʹ��
        return true;
    }
    else if (i->ItemType == 4)
    {
        //�����಻����ʹ��
        return false;
    }
    return false;
}

//ʹ����Ʒʱ���Ա仯
void GameUtil::useItem(Role* r, Item* i)
{

}

//���������Ա仯
void GameUtil::levelUp(Role* r)
{
    if (r == nullptr) { return; }

    r->Exp -= game_util_.level_up_list_[r->Level - 1];
    r->Level++;

    r->PhysicalPower = MAX_PHYSICAL_POWER;
    r->MaxHP += r->IncLife * 3 + RandomClassical::rand(6);
    r->HP = r->MaxHP;
    r->MaxMP += 20 + RandomClassical::rand(6);
    r->MP = r->MaxMP;

    r->Hurt = 0;
    r->Poison = 0;

    r->Attack += RandomClassical::rand(7);
    r->Speed += RandomClassical::rand(7);
    r->Defence += RandomClassical::rand(7);

    auto check_up = [&](SAVE_INT & value, int limit, int max_inc)->void
    {
        if (value > limit)
        {
            value += 1 + RandomClassical::rand(max_inc);
        }
    };

    check_up(r->Medcine, 0, 3);
    check_up(r->Detoxification, 0, 3);
    check_up(r->UsePoison, 0, 3);

    check_up(r->Fist, 10, 3);
    check_up(r->Sword, 10, 3);
    check_up(r->Knife, 10, 3);
    check_up(r->Unusual, 10, 3);
    check_up(r->HiddenWeapon, 10, 3);

    r->limit();
}

//�Ƿ��������
bool GameUtil::canLevelUp(Role* r)
{
    if (r->Level >= 1 && r->Level <= MAX_LEVEL)
    {
        if (r->Exp >= game_util_.level_up_list_[r->Level - 1])
        {
            return true;
        }
    }
    return false;
}

//��Ʒ����ֵ�Ƿ��㹻
bool GameUtil::canFinishedItem(Role* r)
{
    auto item = Save::getInstance()->getItem(r->PracticeBook);
    if (r->ExpForItem >= getFinishedExpForItem(r, item))
    {
        return true;
    }
    return false;
}

//������Ʒ���辭��
int GameUtil::getFinishedExpForItem(Role* r, Item* i)
{
    //�޾����趨��Ʒ��������
    if (i == nullptr || i->NeedExp <= 0)
    {
        return INT_MAX;
    }

    int multiple = 7 - r->IQ / 15;
    if (multiple <= 0) { multiple = 1; }

    //�й�����ѧ�ģ����������򲻿�����
    if (i->MagicID > 0)
    {
        int magic_level_index = r->getMagicLevelIndex(i->MagicID);
        if (magic_level_index == MAX_MAGIC_LEVEL_INDEX)
        {
            return INT_MAX;
        }
        //���������ʹ�1������2������һ����
        if (MAX_MAGIC_LEVEL_INDEX > 0)
        {
            multiple *= magic_level_index;
        }
    }
    return i->NeedExp * multiple;
}

//ҽ�Ƶ�Ч��
int GameUtil::medcine(Role* r1, Role* r2)
{
    auto temp = r2->HP;
    r2->HP += r1->Medcine;
    GameUtil::limit2(r2->HP, 0, r2->MaxHP);
    return r2->HP - temp;
}

//�ⶾ
//ע���������ֵͨ��ӦΪ��
int GameUtil::detoxification(Role* r1, Role* r2)
{
    auto temp = r2->Poison;
    r2->Poison -= r1->Detoxification / 3;
    GameUtil::limit2(r2->Poison, 0, MAX_POISON);
    return r2->Poison - temp;
}

//�ö�
int GameUtil::usePoison(Role* r1, Role* r2)
{
    auto temp = r2->Poison;
    r2->Poison += r1->UsePoison / 3;
    GameUtil::limit2(r2->Poison, 0, MAX_POISON);
    return r2->Poison - temp;
}
