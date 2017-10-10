#include "Types.h"
#include "GameUtil.h"

//�����������꣬������ֵΪ�����൱�ڴ���������
void Role::setPosition(int x, int y)
{
    if (position_layer_ == nullptr)
    {
        return;
    }
    if (X_ >= 0 && Y_ >= 0)
    {
        position_layer_->data(X_, Y_) = -1;
    }
    if (x >= 0 && y >= 0)
    {
        position_layer_->data(x, y) = ID;
    }
    X_ = x;
    Y_ = y;
}

//��ʾ�õģ����ڲ������õĶ�1
int Role::getRoleShowLearnedMagicLevel(int i)
{
    return getRoleMagicLevelIndex(i) + 1;
}

//��ȡ��ѧ�ȼ�������ֵ��0~9������ֱ�����������书������������
int Role::getRoleMagicLevelIndex(int i)
{
    int l = MagicLevel[i] / 100;
    if (l < 0) { l = 0; }
    if (l > 9) { l = 9; }
    return l;
}

//��ѧϰ��ѧ������
int Role::getLearnedMagicCount()
{
    int n = 0;
    for (int i = 0; i < ROLE_MAGIC_COUNT; i++)
    {
        if (MagicID[i] > 0) { n++; }
    }
    return n;
}

//������ѧָ���ȡ�ȼ���-1��ʾδѧ��
int Role::getMagicLevelIndex(Magic* magic)
{
    return getMagicLevelIndex(magic->ID);
}

int Role::getMagicLevelIndex(int magic_id)
{
    for (int i = 0; i < ROLE_MAGIC_COUNT; i++)
    {
        if (MagicID[i] == magic_id)
        {
            return getRoleMagicLevelIndex(i);
        }
    }
    return -1;
}

//�������������
void Role::limit()
{
    GameUtil::limit2(Level, 0, MAX_LEVEL);

    GameUtil::limit2(Exp, 0, MAX_EXP);
    GameUtil::limit2(ExpForItem, 0, MAX_EXP);
    GameUtil::limit2(ExpForMakeItem, 0, MAX_EXP);

    GameUtil::limit2(Poison, 0, MAX_POISON);

    GameUtil::limit2(MaxHP, 0, MAX_HP);
    GameUtil::limit2(MaxMP, 0, MAX_MP);
    GameUtil::limit2(HP, 0, MaxHP);
    GameUtil::limit2(MP, 0, MaxMP);
    GameUtil::limit2(PhysicalPower, 0, MAX_PHYSICAL_POWER);

    GameUtil::limit2(Attack, 0, MAX_ATTACK);
    GameUtil::limit2(Defence, 0, MAX_DEFENCE);
    GameUtil::limit2(Speed, 0, MAX_SPEED);

    GameUtil::limit2(Medcine, 0, MAX_MEDCINE);
    GameUtil::limit2(UsePoison, 0, MAX_USE_POISON);
    GameUtil::limit2(Detoxification, 0, MAX_DETOXIFICATION);
    GameUtil::limit2(AntiPoison, 0, MAX_ANTI_POISON);

    GameUtil::limit2(Fist, 0, MAX_FIST);
    GameUtil::limit2(Sword, 0, MAX_SWORD);
    GameUtil::limit2(Knife, 0, MAX_KNIFE);
    GameUtil::limit2(Unusual, 0, MAX_UNUSUAL);
    GameUtil::limit2(HiddenWeapon, 0, MAX_HIDDEN_WEAPON);

    GameUtil::limit2(Knowledge, 0, MAX_KNOWLEDGE);
    GameUtil::limit2(Morality, 0, MAX_MORALITY);
    GameUtil::limit2(AttackWithPoison, 0, MAX_ATTACK_WITH_POISON);
    GameUtil::limit2(Fame, 0, MAX_FAME);
    GameUtil::limit2(IQ, 0, MAX_IQ);

    for (int i = 0; i < ROLE_MAGIC_COUNT; i++)
    {
        GameUtil::limit2(MagicLevel[i], 0, MAX_MAGIC_LEVEL);
    }
}

int Role::learnMagic(Magic* magic)
{
    if (magic == nullptr || magic->ID <= 0) { return -1; }  //��ѧid����
    return learnMagic(magic->ID);
}

int Role::learnMagic(int magic_id)
{
    if (magic_id <= 0) { return -1; }
    //����Ƿ��Ѿ�ѧ��
    int index = -1;
    for (int i = 0; i < ROLE_MAGIC_COUNT; i++)
    {
        if (MagicID[i] == magic_id)
        {
            if (MagicLevel[i] / 100 < MAX_MAGIC_LEVEL_INDEX)
            {
                MagicLevel[i] += 100;
                return 0;
            }
            else
            {
                return -2;   //����
            }
        }
        if (MagicID[i] <= 0)
        {
            index = i;
        }
    }

    if (index < 0)
    {
        return -3;   //�����е���indexΪ������ʾ��ѧ������
    }
    else
    {
        //������ѧ
        MagicID[index] = magic_id;
        MagicLevel[index] = 0;
        return 0;
    }
}

//����ĳ���¼������꣬��һЩMOD���������д���
void SubMapEvent::setPosition(int x, int y, SubMapInfo* submap_record)
{
    if (x < 0) { x = X_; }
    if (y < 0) { y = Y_; }
    auto index = submap_record->EventIndex(X_, Y_);
    submap_record->EventIndex(X_, Y_) = -1;
    X_ = x;
    Y_ = y;
    submap_record->EventIndex(X_, Y_) = index;
}
