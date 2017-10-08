#include "GameUtil.h"

GameUtil GameUtil::game_util_;

GameUtil::GameUtil()
{
}

GameUtil::~GameUtil()
{
}

//ĳ���Ƿ����ʹ��ĳ��Ʒ
//ԭ���ࣺ0���飬1װ����2���ţ�3ҩƷ��4����
bool GameUtil::canUseItem(Role* r, Item* i)
{
    if (r == nullptr) { return false; }
    if (i == nullptr) { return true; }
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

}

//�Ƿ��������
bool GameUtil::canLevelUp(Role* r)
{
    return false;
}

//������Ʒ�����Ƿ��㹻
bool GameUtil::canLearnBook(Role* r)
{
    return false;
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
    r2->Poison += r1->UsePoison/3;
    GameUtil::limit2(r2->Poison, 0, MAX_POISON);
    return r2->Poison - temp;
}
