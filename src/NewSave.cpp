#include "NewSave.h"
#include "PotConv.h"
#include "csv.h"
#include <fstream>
#include <iostream>

// ����
void NewSave::SaveCSVBaseInfo(Save::BaseInfo* data, int length, int record)
{
    std::ofstream fout("../game/save/csv/" + std::to_string(record) + "_����.csv");
    fout << "�˴�";
    fout << ",";
    fout << "�ӳ�����";
    fout << ",";
    fout << "����ͼX";
    fout << ",";
    fout << "����ͼY";
    fout << ",";
    fout << "�ӳ���X";
    fout << ",";
    fout << "�ӳ���Y";
    fout << ",";
    fout << "�泯����";
    fout << ",";
    fout << "��X";
    fout << ",";
    fout << "��Y";
    fout << ",";
    fout << "��X1";
    fout << ",";
    fout << "��Y1";
    fout << ",";
    fout << "�ڲ�����";
    fout << ",";
    fout << "����1";
    fout << ",";
    fout << "����2";
    fout << ",";
    fout << "����3";
    fout << ",";
    fout << "����4";
    fout << ",";
    fout << "����5";
    fout << ",";
    fout << "����6";
    fout << std::endl;
    for (int i = 0; i < length; i++)
    {
        fout << data[i].InShip;
        fout << ",";
        fout << data[i].InSubMap;
        fout << ",";
        fout << data[i].MainMapX;
        fout << ",";
        fout << data[i].MainMapY;
        fout << ",";
        fout << data[i].SubMapX;
        fout << ",";
        fout << data[i].SubMapY;
        fout << ",";
        fout << data[i].FaceTowards;
        fout << ",";
        fout << data[i].ShipX;
        fout << ",";
        fout << data[i].ShipY;
        fout << ",";
        fout << data[i].TimeCount;
        fout << ",";
        fout << data[i].TimeEvent;
        fout << ",";
        fout << data[i].RandomEvent;
        fout << ",";
        for (int j = 0; j < 6; j++)
        {
            fout << data[i].Team[j];
            if (j != 6 - 1)
            {
                fout << ",";
            }
        }
        fout << std::endl;
    }
}
// ����
void NewSave::SaveCSVItemList(ItemList* data, int length, int record)
{
    std::ofstream fout("../game/save/csv/" + std::to_string(record) + "_����.csv");
    fout << "��Ʒ���";
    fout << ",";
    fout << "��Ʒ����";
    fout << std::endl;
    for (int i = 0; i < length; i++)
    {
        fout << data[i].item_id;
        fout << ",";
        fout << data[i].count;
        fout << std::endl;
    }
}
// ����
void NewSave::SaveCSVRoleSave(const std::vector<Role>& data, int record)
{
    std::ofstream fout("../game/save/csv/" + std::to_string(record) + "_����.csv");
    fout << "���";
    fout << ",";
    fout << "ͷ��";
    fout << ",";
    fout << "�����ɳ�";
    fout << ",";
    fout << "����";
    fout << ",";
    fout << "����";
    fout << ",";
    fout << "���";
    fout << ",";
    fout << "�Ա�";
    fout << ",";
    fout << "�ȼ�";
    fout << ",";
    fout << "����";
    fout << ",";
    fout << "����";
    fout << ",";
    fout << "�������ֵ";
    fout << ",";
    fout << "����";
    fout << ",";
    fout << "�ж�";
    fout << ",";
    fout << "����";
    fout << ",";
    fout << "��Ʒ��������";
    fout << ",";
    fout << "����";
    fout << ",";
    fout << "����";
	fout << ",";
	fout << "Ь��";
	fout << ",";
	fout << "��Ʒ";

    fout << ",";
    fout << "��������";
    fout << ",";
    fout << "����";
    fout << ",";
    fout << "�������ֵ";
    fout << ",";
    fout << "������";
    fout << ",";
    fout << "�Ṧ";
    fout << ",";
    fout << "������";
    fout << ",";
    fout << "ҽ��";
    fout << ",";
    fout << "�ö�";
    fout << ",";
    fout << "�ⶾ";
    fout << ",";
    fout << "����";
    fout << ",";
    fout << "ȭ��";
    fout << ",";
    fout << "����";
    fout << ",";
    fout << "ˣ��";
    fout << ",";
    fout << "����";
    fout << ",";
    fout << "����";
    fout << ",";
    fout << "��ѧ��ʶ";
    fout << ",";
    fout << "Ʒ��";
    fout << ",";
    fout << "��������";
    fout << ",";
    fout << "���һ���";
    fout << ",";
    fout << "����";
    fout << ",";
    fout << "����";
    fout << ",";
    fout << "������Ʒ";
    fout << ",";
    fout << "��������";
    fout << ",";
    fout << "�����书1";
    fout << ",";
    fout << "�����书2";
    fout << ",";
    fout << "�����书3";
    fout << ",";
    fout << "�����书4";
    fout << ",";
    fout << "�����书5";
    fout << ",";
    fout << "�����书6";
    fout << ",";
    fout << "�����书7";
    fout << ",";
    fout << "�����书8";
    fout << ",";
    fout << "�����书9";
    fout << ",";
    fout << "�����书10";
    fout << ",";
    fout << "�书�ȼ�1";
    fout << ",";
    fout << "�书�ȼ�2";
    fout << ",";
    fout << "�书�ȼ�3";
    fout << ",";
    fout << "�书�ȼ�4";
    fout << ",";
    fout << "�书�ȼ�5";
    fout << ",";
    fout << "�书�ȼ�6";
    fout << ",";
    fout << "�书�ȼ�7";
    fout << ",";
    fout << "�书�ȼ�8";
    fout << ",";
    fout << "�书�ȼ�9";
    fout << ",";
    fout << "�书�ȼ�10";
    fout << ",";
    fout << "Я����Ʒ1";
    fout << ",";
    fout << "Я����Ʒ2";
    fout << ",";
    fout << "Я����Ʒ3";
    fout << ",";
    fout << "Я����Ʒ4";
    fout << ",";
    fout << "Я����Ʒ����1";
    fout << ",";
    fout << "Я����Ʒ����2";
    fout << ",";
    fout << "Я����Ʒ����3";
    fout << ",";
    fout << "Я����Ʒ����4";
    fout << std::endl;
    int length = data.size();
    for (int i = 0; i < length; i++)
    {
        fout << data[i].ID;
        fout << ",";
        fout << data[i].HeadID;
        fout << ",";
        fout << data[i].IncLife;
        fout << ",";
        fout << data[i].Fuyuan;
        fout << ",";
        fout << '"' << data[i].Name << '"';
        fout << ",";
        fout << '"' << data[i].Nick << '"';
        fout << ",";
        fout << data[i].Sexual;
        fout << ",";
        fout << data[i].Level;
        fout << ",";
        fout << data[i].Exp;
        fout << ",";
        fout << data[i].HP;
        fout << ",";
        fout << data[i].MaxHP;
        fout << ",";
        fout << data[i].Hurt;
        fout << ",";
        fout << data[i].Poison;
        fout << ",";
        fout << data[i].PhysicalPower;
        fout << ",";

		fout << data[i].Equip[0];
        fout << ",";
        fout << data[i].Equip[1];
        fout << ",";
		fout << data[i].Equip[2];
		fout << ",";
		fout << data[i].Equip[3];
		fout << ",";

        fout << data[i].MPType;
        fout << ",";
        fout << data[i].MP;
        fout << ",";
        fout << data[i].MaxMP;
        fout << ",";
        fout << data[i].Attack;
        fout << ",";
        fout << data[i].Speed;
        fout << ",";
        fout << data[i].Defence;
        fout << ",";
        fout << data[i].Medicine;
        fout << ",";
        fout << data[i].UsePoison;
        fout << ",";
        fout << data[i].Detoxification;
        fout << ",";
        fout << data[i].AntiPoison;
        fout << ",";
        fout << data[i].Fist;
        fout << ",";
        fout << data[i].Sword;
        fout << ",";
        fout << data[i].Knife;
        fout << ",";
        fout << data[i].Unusual;
        fout << ",";
        fout << data[i].HiddenWeapon;
        fout << ",";
        fout << data[i].Knowledge;
        fout << ",";
        fout << data[i].Morality;
        fout << ",";
        fout << data[i].AttackWithPoison;
        fout << ",";
        fout << data[i].AttackTwice;
        fout << ",";
        fout << data[i].Fame;
        fout << ",";
        fout << data[i].IQ;
        fout << ",";
        fout << data[i].PracticeItem;
        fout << ",";
        fout << data[i].ExpForItem;
        fout << ",";
        for (int j = 0; j < 10; j++)
        {
            fout << data[i].MagicID[j];
            if (j != 10 - 1)
            {
                fout << ",";
            }
        }
        fout << ",";
        for (int j = 0; j < 10; j++)
        {
            fout << data[i].MagicLevel[j];
            if (j != 10 - 1)
            {
                fout << ",";
            }
        }
        fout << ",";
        for (int j = 0; j < 4; j++)
        {
            fout << data[i].TakingItem[j];
            if (j != 4 - 1)
            {
                fout << ",";
            }
        }
        fout << ",";
        for (int j = 0; j < 4; j++)
        {
            fout << data[i].TakingItemCount[j];
            if (j != 4 - 1)
            {
                fout << ",";
            }
        }
        fout << std::endl;
    }
}
// ��Ʒ
void NewSave::SaveCSVItemSave(const std::vector<Item>& data, int record)
{
    std::ofstream fout("../game/save/csv/" + std::to_string(record) + "_��Ʒ.csv");
    fout << "���";
    fout << ",";
    fout << "��Ʒ��";
    fout << ",";
    fout << "��Ʒ������1";
    fout << ",";
    fout << "��Ʒ������2";
    fout << ",";
    fout << "��Ʒ������3";
    fout << ",";
    fout << "��Ʒ������4";
    fout << ",";
    fout << "��Ʒ������5";
    fout << ",";
    fout << "��Ʒ������6";
    fout << ",";
    fout << "��Ʒ������7";
    fout << ",";
    fout << "��Ʒ������8";
    fout << ",";
    fout << "��Ʒ������9";
    fout << ",";
    fout << "��Ʒ������10";
    fout << ",";
    fout << "��Ʒ˵��";
    fout << ",";
    fout << "�����书";
    fout << ",";
    fout << "�����������";
    fout << ",";
    fout << "ʹ����";
    fout << ",";
    fout << "װ������";
    fout << ",";
    fout << "��ʾ��Ʒ˵��";
    fout << ",";
    fout << "��Ʒ����";
    fout << ",";
    fout << "δ֪5";
    fout << ",";
    fout << "δ֪6";
    fout << ",";
    fout << "δ֪7";
    fout << ",";
    fout << "������";
    fout << ",";
    fout << "���������ֵ";
    fout << ",";
    fout << "���ж��ⶾ";
    fout << ",";
    fout << "������";
    fout << ",";
    fout << "�ı���������";
    fout << ",";
    fout << "������";
    fout << ",";
    fout << "���������ֵ";
    fout << ",";
    fout << "�ӹ�����";
    fout << ",";
    fout << "���Ṧ";
    fout << ",";
    fout << "�ӷ�����";
    fout << ",";
    fout << "��ҽ��";
    fout << ",";
    fout << "��ʹ��";
    fout << ",";
    fout << "�ӽⶾ";
    fout << ",";
    fout << "�ӿ���";
    fout << ",";
    fout << "��ȭ��";
    fout << ",";
    fout << "������";
    fout << ",";
    fout << "��ˣ��";
    fout << ",";
    fout << "���������";
    fout << ",";
    fout << "�Ӱ�������";
    fout << ",";
    fout << "����ѧ��ʶ";
    fout << ",";
    fout << "��Ʒ��";
    fout << ",";
    fout << "�����һ���";
    fout << ",";
    fout << "�ӹ�������";
    fout << ",";
    fout << "����������";
    fout << ",";
    fout << "����������";
    fout << ",";
    fout << "������";
    fout << ",";
    fout << "�蹥����";
    fout << ",";
    fout << "���Ṧ";
    fout << ",";
    fout << "���ö�";
    fout << ",";
    fout << "��ҽ��";
    fout << ",";
    fout << "��ⶾ";
    fout << ",";
    fout << "��ȭ��";
    fout << ",";
    fout << "������";
    fout << ",";
    fout << "��ˣ��";
    fout << ",";
    fout << "���������";
    fout << ",";
    fout << "�谵��";
    fout << ",";
    fout << "������";
    fout << ",";
    fout << "�辭��";
    fout << ",";
    fout << "������Ʒ�辭��";
    fout << ",";
    fout << "�����";
    fout << ",";
    fout << "������Ʒ1";
    fout << ",";
    fout << "������Ʒ2";
    fout << ",";
    fout << "������Ʒ3";
    fout << ",";
    fout << "������Ʒ4";
    fout << ",";
    fout << "������Ʒ5";
    fout << ",";
    fout << "������Ʒ����1";
    fout << ",";
    fout << "������Ʒ����2";
    fout << ",";
    fout << "������Ʒ����3";
    fout << ",";
    fout << "������Ʒ����4";
    fout << ",";
    fout << "������Ʒ����5";
    fout << std::endl;
    int length = data.size();
    for (int i = 0; i < length; i++)
    {
        fout << data[i].ID;
        fout << ",";
        fout << '"' << data[i].Name << '"';
        fout << ",";
		fout << '"' << data[i].ExpofMagic << '"';
		fout << ",";
		fout << '"' << data[i].SetNum << '"';
		fout << ",";
		fout << '"' << data[i].BattleBattleEffect << '"';
		fout << ",";
		fout << '"' << data[i].AddSign << '"';
		fout << ",";
		fout << '"' << data[i].needSex << '"';
		fout << ",";
		fout << '"' << data[i].rehurt << '"';
		fout << ",";
		fout << '"' << data[i].NeedEthics << '"';
		fout << ",";
		fout << '"' << data[i].NeedRepute << '"';
		fout << ",";
		fout << '"' << data[i].AddQianli << '"';
		fout << ",";
		fout << '"' << data[i].BattleNum << '"';
		fout << ",";
        fout << '"' << data[i].Introduction << '"';
        fout << ",";
        fout << data[i].MagicID;
        fout << ",";
        fout << data[i].HiddenWeaponEffectID;
        fout << ",";
        fout << data[i].User;
        fout << ",";
        fout << data[i].EquipType;
        fout << ",";
        fout << data[i].ShowIntroduction;
        fout << ",";
        fout << data[i].ItemType;
        fout << ",";
        fout << data[i].Inventory;
        fout << ",";
        fout << data[i].Price;
        fout << ",";
        fout << data[i].EventNum;
        fout << ",";
        fout << data[i].AddHP;
        fout << ",";
        fout << data[i].AddMaxHP;
        fout << ",";
        fout << data[i].AddPoison;
        fout << ",";
        fout << data[i].AddPhysicalPower;
        fout << ",";
        fout << data[i].ChangeMPType;
        fout << ",";
        fout << data[i].AddMP;
        fout << ",";
        fout << data[i].AddMaxMP;
        fout << ",";
        fout << data[i].AddAttack;
        fout << ",";
        fout << data[i].AddSpeed;
        fout << ",";
        fout << data[i].AddDefence;
        fout << ",";
        fout << data[i].AddMedicine;
        fout << ",";
        fout << data[i].AddUsePoison;
        fout << ",";
        fout << data[i].AddDetoxification;
        fout << ",";
        fout << data[i].AddAntiPoison;
        fout << ",";
        fout << data[i].AddFist;
        fout << ",";
        fout << data[i].AddSword;
        fout << ",";
        fout << data[i].AddKnife;
        fout << ",";
        fout << data[i].AddUnusual;
        fout << ",";
        fout << data[i].AddHiddenWeapon;
        fout << ",";
        fout << data[i].AddKnowledge;
        fout << ",";
        fout << data[i].AddMorality;
        fout << ",";
        fout << data[i].AddAttackTwice;
        fout << ",";
        fout << data[i].AddAttackWithPoison;
        fout << ",";
        fout << data[i].OnlySuitableRole;
        fout << ",";
        fout << data[i].NeedMPType;
        fout << ",";
        fout << data[i].NeedMP;
        fout << ",";
        fout << data[i].NeedAttack;
        fout << ",";
        fout << data[i].NeedSpeed;
        fout << ",";
        fout << data[i].NeedUsePoison;
        fout << ",";
        fout << data[i].NeedMedicine;
        fout << ",";
        fout << data[i].NeedDetoxification;
        fout << ",";
        fout << data[i].NeedFist;
        fout << ",";
        fout << data[i].NeedSword;
        fout << ",";
        fout << data[i].NeedKnife;
        fout << ",";
        fout << data[i].NeedUnusual;
        fout << ",";
        fout << data[i].NeedHiddenWeapon;
        fout << ",";
        fout << data[i].NeedIQ;
        fout << ",";
        fout << data[i].NeedExp;
        fout << ",";
        fout << data[i].NeedExpForMakeItem;
        fout << ",";
        fout << data[i].NeedMaterial;
        fout << ",";
        for (int j = 0; j < 5; j++)
        {
            fout << data[i].MakeItem[j];
            if (j != 5 - 1)
            {
                fout << ",";
            }
        }
        fout << ",";
        for (int j = 0; j < 5; j++)
        {
            fout << data[i].MakeItemCount[j];
            if (j != 5 - 1)
            {
                fout << ",";
            }
        }
        fout << std::endl;
    }
}
// ����
void NewSave::SaveCSVSubMapInfoSave(const std::vector<SubMapInfo>& data, int record)
{
    std::ofstream fout("../game/save/csv/" + std::to_string(record) + "_����.csv");
    fout << "���";
    fout << ",";
    fout << "����";
    fout << ",";
    fout << "��������";
    fout << ",";
    fout << "��������";
    fout << ",";
    fout << "��ת����";
    fout << ",";
    fout << "��������";
    fout << ",";
    fout << "�⾰���X1";
    fout << ",";
    fout << "�⾰���Y1";
    fout << ",";
    fout << "�⾰���X2";
    fout << ",";
    fout << "�⾰���Y2";
    fout << ",";
    fout << "���X";
    fout << ",";
    fout << "���Y";
    fout << ",";
    fout << "����X1";
    fout << ",";
    fout << "����X2";
    fout << ",";
    fout << "����X3";
    fout << ",";
    fout << "����Y1";
    fout << ",";
    fout << "����Y2";
    fout << ",";
    fout << "����Y3";
    fout << ",";
    fout << "��תX";
    fout << ",";
    fout << "��תY";
    fout << ",";
    fout << "��ת����X";
    fout << ",";
    fout << "��ת����Y";
    fout << std::endl;
    int length = data.size();
    for (int i = 0; i < length; i++)
    {
        fout << data[i].ID;
        fout << ",";
        fout << '"' << data[i].Name << '"';
        fout << ",";
        fout << data[i].ExitMusic;
        fout << ",";
        fout << data[i].EntranceMusic;
        fout << ",";
        fout << data[i].JumpSubMap;
        fout << ",";
        fout << data[i].EntranceCondition;
        fout << ",";
        fout << data[i].MainEntranceX1;
        fout << ",";
        fout << data[i].MainEntranceY1;
        fout << ",";
        fout << data[i].MainEntranceX2;
        fout << ",";
        fout << data[i].MainEntranceY2;
        fout << ",";
        fout << data[i].EntranceX;
        fout << ",";
        fout << data[i].EntranceY;
        fout << ",";
        for (int j = 0; j < 3; j++)
        {
            fout << data[i].ExitX[j];
            if (j != 3 - 1)
            {
                fout << ",";
            }
        }
        fout << ",";
        for (int j = 0; j < 3; j++)
        {
            fout << data[i].ExitY[j];
            if (j != 3 - 1)
            {
                fout << ",";
            }
        }


        fout << std::endl;
    }
}
// �书
void NewSave::SaveCSVMagicSave(const std::vector<Magic>& data, int record)
{
    std::ofstream fout("../game/save/csv/" + std::to_string(record) + "_�书.csv");
    fout << "���";
    fout << ",";
    fout << "����";
    fout << ",";
    fout << "δ֪1";
    fout << ",";
    fout << "δ֪2";
    fout << ",";
    fout << "δ֪3";
    fout << ",";
    fout << "δ֪4";
    fout << ",";
    fout << "δ֪5";
    fout << ",";
    fout << "������Ч";
    fout << ",";
    fout << "�书����";
    fout << ",";
    fout << "�书����";
    fout << ",";
    fout << "�˺�����";
    fout << ",";
    fout << "������Χ����";
    fout << ",";
    fout << "��������";
    fout << ",";
    fout << "�����ж�";
    fout << ",";
    fout << "����1";
    fout << ",";
    fout << "����2";
    fout << ",";
    fout << "����3";
    fout << ",";
    fout << "����4";
    fout << ",";
    fout << "����5";
    fout << ",";
    fout << "����6";
    fout << ",";
    fout << "����7";
    fout << ",";
    fout << "����8";
    fout << ",";
    fout << "����9";
    fout << ",";
    fout << "����10";
    fout << ",";
    fout << "�ƶ���Χ1";
    fout << ",";
    fout << "�ƶ���Χ2";
    fout << ",";
    fout << "�ƶ���Χ3";
    fout << ",";
    fout << "�ƶ���Χ4";
    fout << ",";
    fout << "�ƶ���Χ5";
    fout << ",";
    fout << "�ƶ���Χ6";
    fout << ",";
    fout << "�ƶ���Χ7";
    fout << ",";
    fout << "�ƶ���Χ8";
    fout << ",";
    fout << "�ƶ���Χ9";
    fout << ",";
    fout << "�ƶ���Χ10";
    fout << ",";
    fout << "ɱ�˷�Χ1";
    fout << ",";
    fout << "ɱ�˷�Χ2";
    fout << ",";
    fout << "ɱ�˷�Χ3";
    fout << ",";
    fout << "ɱ�˷�Χ4";
    fout << ",";
    fout << "ɱ�˷�Χ5";
    fout << ",";
    fout << "ɱ�˷�Χ6";
    fout << ",";
    fout << "ɱ�˷�Χ7";
    fout << ",";
    fout << "ɱ�˷�Χ8";
    fout << ",";
    fout << "ɱ�˷�Χ9";
    fout << ",";
    fout << "ɱ�˷�Χ10";
    fout << ",";
    fout << "������1";
    fout << ",";
    fout << "������2";
    fout << ",";
    fout << "������3";
    fout << ",";
    fout << "������4";
    fout << ",";
    fout << "������5";
    fout << ",";
    fout << "������6";
    fout << ",";
    fout << "������7";
    fout << ",";
    fout << "������8";
    fout << ",";
    fout << "������9";
    fout << ",";
    fout << "������10";
    fout << ",";
    fout << "ɱ������1";
    fout << ",";
    fout << "ɱ������2";
    fout << ",";
    fout << "ɱ������3";
    fout << ",";
    fout << "ɱ������4";
    fout << ",";
    fout << "ɱ������5";
    fout << ",";
    fout << "ɱ������6";
    fout << ",";
    fout << "ɱ������7";
    fout << ",";
    fout << "ɱ������8";
    fout << ",";
    fout << "ɱ������9";
    fout << ",";
    fout << "ɱ������10";
    fout << std::endl;
    int length = data.size();
    for (int i = 0; i < length; i++)
    {
        fout << data[i].ID;
        fout << ",";
        fout << '"' << data[i].Name << '"';
        fout << ",";

        fout << ",";
        fout << data[i].SoundID;
        fout << ",";
        fout << data[i].MagicType;
        fout << ",";
        fout << data[i].EffectID;
        fout << ",";
        fout << data[i].HurtType;
        fout << ",";
        fout << data[i].AttackAreaType;
        fout << ",";
        fout << data[i].NeedMP;
        fout << ",";
        fout << data[i].WithPoison;
        fout << ",";

        fout << ",";
        for (int j = 0; j < 10; j++)
        {
            fout << data[i].SelectDistance[j];
            if (j != 10 - 1)
            {
                fout << ",";
            }
        }
        fout << ",";
        for (int j = 0; j < 10; j++)
        {
            fout << data[i].AttackDistance[j];
            if (j != 10 - 1)
            {
                fout << ",";
            }
        }
        fout << ",";
        for (int j = 0; j < 10; j++)
        {
            fout << data[i].AddMP[j];
            if (j != 10 - 1)
            {
                fout << ",";
            }
        }
        fout << ",";

        fout << std::endl;
    }
}
// �̵�
void NewSave::SaveCSVShopSave(const std::vector<Shop>& data, int record)
{
    std::ofstream fout("../game/save/csv/" + std::to_string(record) + "_�̵�.csv");
    fout << "��Ʒ���1";
    fout << ",";
    fout << "��Ʒ���2";
    fout << ",";
    fout << "��Ʒ���3";
    fout << ",";
    fout << "��Ʒ���4";
    fout << ",";
    fout << "��Ʒ���5";
    fout << ",";
    fout << "��Ʒ����1";
    fout << ",";
    fout << "��Ʒ����2";
    fout << ",";
    fout << "��Ʒ����3";
    fout << ",";
    fout << "��Ʒ����4";
    fout << ",";
    fout << "��Ʒ����5";
    fout << ",";
    fout << "��Ʒ�۸�1";
    fout << ",";
    fout << "��Ʒ�۸�2";
    fout << ",";
    fout << "��Ʒ�۸�3";
    fout << ",";
    fout << "��Ʒ�۸�4";
    fout << ",";
    fout << "��Ʒ�۸�5";
    fout << std::endl;
    int length = data.size();
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            fout << data[i].ItemID[j];
            if (j != 5 - 1)
            {
                fout << ",";
            }
        }
        fout << ",";
        for (int j = 0; j < 5; j++)
        {
            fout << data[i].ItermCount[j];
            if (j != 5 - 1)
            {
                fout << ",";
            }
        }

        fout << std::endl;
    }
}
// ����
void NewSave::LoadCSVBaseInfo(Save::BaseInfo* data, int length, int record)
{
    io::CSVReader<21, io::trim_chars<>, io::double_quote_escape<',', '\"'>> in("../game/save/csv/" + std::to_string(record) + "_����.csv");
    in.read_header(io::ignore_missing_column | io::ignore_extra_column,
        "�˴�",
		"����",
		"��X",
		"��Y",
		"�Ȉ�������X",
		"�Ȉ�������Y",
		"���挦����",
		"��X",
		"��Y",
		"Ӌ�r",
		"���r�¼�",
		"�S�C�¼�",
		"�Ȉ�������",
		"���挦����",
		"����˔�",
		"���",
		"���1",
		"���2",
		"���3",
		"���4",
		"���5");
    auto getDefault = []()
    {
        Save::BaseInfo nextLineData;
        nextLineData.InShip = 0;
        nextLineData.InSubMap = 0;
        nextLineData.MainMapX = 0;
        nextLineData.MainMapY = 0;
        nextLineData.SubMapX = 0;
        nextLineData.SubMapY = 0;
        nextLineData.FaceTowards = 0;
        nextLineData.ShipX = 0;
        nextLineData.ShipY = 0;
        nextLineData.TimeCount = 0; 
        nextLineData.TimeEvent = 0;
        nextLineData.RandomEvent = 0;
		nextLineData.SubmapTowards = 0;
		nextLineData.ShipTowards = 0;
		nextLineData.TeamCount = 0;
        for (int j = 0; j < 6; j++)
        {
            nextLineData.Team[j] = -1;
        }
        return nextLineData;
    };
    int lines = 0;
    auto nextLineData = getDefault();
	while (in.read_row(
		nextLineData.InShip,
		nextLineData.InSubMap,
		nextLineData.MainMapX,
		nextLineData.MainMapY,
		nextLineData.SubMapX,
		nextLineData.SubMapY,
		nextLineData.FaceTowards,
		nextLineData.ShipX,
		nextLineData.ShipY,
		nextLineData.TimeCount,
		nextLineData.TimeEvent,
		nextLineData.RandomEvent,
		nextLineData.SubmapTowards,
		nextLineData.ShipTowards,
		nextLineData.TeamCount,
        nextLineData.Team[0],
        nextLineData.Team[1],
        nextLineData.Team[2],
        nextLineData.Team[3],
        nextLineData.Team[4],
        nextLineData.Team[5]))
    {
        data[lines] = nextLineData;
        if (lines + 1 == length)
        {
            break;
        }
        lines++;
        nextLineData = getDefault();
    }
}
// ����
void NewSave::LoadCSVItemList(ItemList* data, int length, int record)
{
    io::CSVReader<2, io::trim_chars<>, io::double_quote_escape<',', '\"'>> in("../game/save/csv/" + std::to_string(record) + "_����.csv");
    in.read_header(io::ignore_missing_column | io::ignore_extra_column,
        "��Ʒ���",
        "��Ʒ����");
    auto getDefault = []()
    {
        ItemList nextLineData;
        nextLineData.item_id = -1;
        nextLineData.count = 0;
        return nextLineData;
    };
    int lines = 0;
    auto nextLineData = getDefault();
    while (in.read_row(
        nextLineData.item_id,
        nextLineData.count))
    {
        data[lines] = nextLineData;
        if (lines + 1 == length)
        {
            break;
        }
        lines++;
        nextLineData = getDefault();
    }
}
// ����
void NewSave::LoadCSVRoleSave(std::vector<Role>& data, int record)
{
	
    data.clear();
    io::CSVReader<305, io::trim_chars<>, io::double_quote_escape<',', '\"'>> in("../game/save/csv/" + std::to_string(record) + "_����.csv");
    in.read_header(io::ignore_missing_column | io::ignore_extra_column,
		"���",
		"�^��/�𶷴�̖",
		"�������L",
		"����",
		"����",
		"��̖",
		"�Ԅe",
		"�ȼ�",
		"���ֵ",
		"����",
		"�������ֵ",
		"�܂��̶�",
		"�ж��̶�",
		"�w��",
		"�𶷈D��̖",
		"����",
		"����",
		"�^��",
		"�_��",
		"�Ʒ",
		"���w",
		"����B",
		"��ŭֵ",
		"���Ҙ�ӛ",
		"�Є�����",
		"�����c",
		"����AI��B",
		"���^",
		"�Єӕr�g",
		"�y��",
		"���\��",
		"ˎ��",
		"�������|",
		"����",
		"�������ֵ",
		"������",
		"�p��",
		"������",
		"�t��",
		"��ȱ",
		"��ˇ",
		"����",
		"ȭ��",
		"����",
		"ˣ��",
		"�������",
		"��������",
		"��W���R",
		"Ʒ��",
		"���g",
		"���һ���",
		"��",
		"�Y�|",
		"�޾���Ʒ",
		"�ޟ��c��",
		"����",
		"����",
		"����e",
		"���A��",
		"Ʒ�A��",
		"���ԃA��",
		"����A��",
		"�����T��",
		"����",
		"������λ",
		"�ݎ����",
		"��ҕ�T��",
		"��ҕ�T��1",
		"��ǰλ��",
		"�Ȳ�λ��",
		"�Ȳ�����1",
		"�����B",
		"����A��",
		"ڤ˼�A��",
		"�ڄӃA��",
		"�����A��",
		"�R�rλ��",
		"�Ȳ��R�rλ��",
		"�Ȳ�����2",
		"����X����",
		"����Y����",
		"�͕���ӛ",
		"�ٸ�ؕ�I",
		"����",
		"���g",
		"δ��1",
		"δ��2",
		"δ��3",
		"����ID",
		"�����书",
		"�����书1",
		"�����书2",
		"�����书3",
		"�����书4",
		"�����书5",
		"�����书6",
		"�����书7",
		"�����书8",
		"�����书9",
		"�����书10",
		"�����书11",
		"�����书12",
		"�����书13",
		"�����书14",
		"�����书15",
		"�����书16",
		"�����书17",
		"�����书18",
		"�����书19",
		"�����书20",
		"�����书21",
		"�����书22",
		"�����书23",
		"�����书24",
		"�����书25",
		"�����书26",
		"�����书27",
		"�����书28",
		"�����书29",
		"�����书30",
		"�����书31",
		"�����书32",
		"�����书33",
		"�����书34",
		"�����书35",
		"�����书36",
		"�����书37",
		"�����书38",
		"�����书39",
		"�����书�ȼ�",
		"�����书�ȼ�1",
		"�����书�ȼ�2",
		"�����书�ȼ�3",
		"�����书�ȼ�4",
		"�����书�ȼ�5",
		"�����书�ȼ�6",
		"�����书�ȼ�7",
		"�����书�ȼ�8",
		"�����书�ȼ�9",
		"�����书�ȼ�10",
		"�����书�ȼ�11",
		"�����书�ȼ�12",
		"�����书�ȼ�13",
		"�����书�ȼ�14",
		"�����书�ȼ�15",
		"�����书�ȼ�16",
		"�����书�ȼ�17",
		"�����书�ȼ�18",
		"�����书�ȼ�19",
		"�����书�ȼ�20",
		"�����书�ȼ�21",
		"�����书�ȼ�22",
		"�����书�ȼ�23",
		"�����书�ȼ�24",
		"�����书�ȼ�25",
		"�����书�ȼ�26",
		"�����书�ȼ�27",
		"�����书�ȼ�28",
		"�����书�ȼ�29",
		"�����书�ȼ�30",
		"�����书�ȼ�31",
		"�����书�ȼ�32",
		"�����书�ȼ�33",
		"�����书�ȼ�34",
		"�����书�ȼ�35",
		"�����书�ȼ�36",
		"�����书�ȼ�37",
		"�����书�ȼ�38",
		"�����书�ȼ�39",
		"�y����Ʒ1",
		"�y����Ʒ2",
		"�y����Ʒ3",
		"�y����Ʒ4",
		"�y����Ʒ1����",
		"�y����Ʒ2����",
		"�y����Ʒ3����",
		"�y����Ʒ4����",
		"�����书",
		"�����书1",
		"�����书2",
		"�����书3",
		"�����书4",
		"�����书5",
		"�����书6",
		"�����书7",
		"�����书8",
		"�����书9",
		"������ʽ",
		"������ʽ1",
		"������ʽ2",
		"������ʽ3",
		"������ʽ4",
		"������ʽ5",
		"������ʽ6",
		"������ʽ7",
		"������ʽ8",
		"������ʽ9",
		"������ʽ10",
		"������ʽ11",
		"������ʽ12",
		"������ʽ13",
		"������ʽ14",
		"������ʽ15",
		"������ʽ16",
		"������ʽ17",
		"������ʽ18",
		"������ʽ19",
		"������ʽ20",
		"������ʽ21",
		"������ʽ22",
		"������ʽ23",
		"������ʽ24",
		"������ʽ25",
		"������ʽ26",
		"������ʽ27",
		"������ʽ28",
		"������ʽ29",
		"������ʽ30",
		"������ʽ31",
		"������ʽ32",
		"������ʽ33",
		"������ʽ34",
		"������ʽ35",
		"������ʽ36",
		"������ʽ37",
		"������ʽ38",
		"������ʽ39",
		"��Ԓ�ˆ��_�P",
		"��Ԓ�¼�",
		"��B�¼�",
		"����¼�",
		"�д��¼�",
		"�W���¼�",
		"�¼���1",
		"�¼���2",
		"�¼���3",
		"�x�����",
		"�x��¼�",
		"�S�Cֵ1",
		"�S�Cֵ2",
		"�y����Ʒ5",
		"�y����Ʒ6",
		"�y����Ʒ7",
		"�y����Ʒ8",
		"�y����Ʒ5����",
		"�y����Ʒ6����",
		"�y����Ʒ7����",
		"�y����Ʒ8����",
		"����",
		"�t��",
		"�b���ؼ�",
		"��Ѫ",
		"�؃�",
		"���w",
		"����",
		"���",
		"��W",
		"ͻ��",
		"���o",
		"��׃",
		"�ƚ�",
		"���T",
		"׃��",
		"����",
		"�⹦",
		"Ӳ��",
		"�`��",
		"�К�",
		"��",
		"��������",
		"���R����",
		"�p������",
		"ȭ�Ɲ���",
		"��������",
		"ˣ������",
		"���T����",
		"��������",
		"����",
		"����",
		"����",
		"���L",
		"���L1",
		"���L2",
		"���L3",
		"���L4",
		"����",
		"����1",
		"����2",
		"����3",
		"����4",
		"����5",
		"����6",
		"����7",
		"����8",
		"����9",
		"�T��ؕ�I",
		"δʹ��",
		"δʹ��1",
		"δʹ��2",
		"δʹ��3",
		"δʹ��4",
		"δʹ��5",
		"δʹ��6",
		"δʹ��7",
		"δʹ��8");
    auto getDefault = []()
    {
        Role nextLineData;
        nextLineData.ID = 0;
        nextLineData.HeadID = 0;
        nextLineData.IncLife = 0;
        nextLineData.Fuyuan = 0;
        memset(nextLineData.Name, '\0', sizeof(nextLineData.Name));
        memset(nextLineData.Nick, '\0', sizeof(nextLineData.Nick));
        nextLineData.Sexual = 0;
        nextLineData.Level = 0;
        nextLineData.Exp = 0;
        nextLineData.HP = 0;
        nextLineData.MaxHP = 0;
        nextLineData.Hurt = 0;
        nextLineData.Poison = 0;
        nextLineData.PhysicalPower = 0;
		nextLineData.FightNum = 0;
		for (int j = 0; j < 5; j++)
		{
			nextLineData.Equip[j] = 0;
		}
		nextLineData.Gongti = 0;
		nextLineData.TeamState = 0;
		nextLineData.Angry = 0;
		nextLineData.isRandomed = 0;
		nextLineData.Moveable = 0;
		nextLineData.In_HeadNum = 0;
		nextLineData.ZhanLueAI = 0;
		nextLineData.Impression = 0; 
		nextLineData.dtime = 0; 
		nextLineData.difficulty = 0;
		nextLineData.Zhongcheng = 0;
		nextLineData.reHurt = 0;
		nextLineData.MPType = 0;
		nextLineData.MP = 0;
		nextLineData.MaxMP = 0;
		nextLineData.Attack = 0;
		nextLineData.Speed = 0;
		nextLineData.Defence = 0;
		nextLineData.Medicine = 0;
		nextLineData.UsePoison = 0;
		nextLineData.Detoxification = 0;
		nextLineData.AntiPoison = 0; 
		nextLineData.Fist = 0; 
		nextLineData.Sword = 0;
		nextLineData.Knife = 0;
		nextLineData.Unusual = 0;
		nextLineData.HiddenWeapon = 0;
		nextLineData.Knowledge = 0; 
		nextLineData.Morality = 0;
		nextLineData.AttackWithPoison = 0;
		nextLineData.AttackTwice = 0;
		nextLineData.Fame = 0;
		nextLineData.IQ = 0;
		nextLineData.PracticeItem = 0;
		nextLineData.ExpForItem = 0;
		nextLineData.xiangxing = 0;
		nextLineData.jiaoqing = 0;
		nextLineData.Rtype = 0;
		nextLineData.swq = 0;
		nextLineData.pdq = 0;
		nextLineData.xxq = 0;
		nextLineData.jqq = 0;
		nextLineData.MenPai = 0;
		nextLineData.shifu = 0;
		nextLineData.scsx = 0;
		nextLineData.bssx = 0;
		nextLineData.Choushi[0] = 0;
		nextLineData.Choushi[1] = 0;
		nextLineData.weizhi = 0;
		nextLineData.nweizhi = 0;
		nextLineData.nfangxiang = 0;
		nextLineData.OnStatus = 0;
		nextLineData.lwq = 0;
		nextLineData.msq = 0;
		nextLineData.ldq = 0;
		nextLineData.qtq = 0; 
		nextLineData.lsweizhi = 0;
		nextLineData.lsnweizhi = 0;
		nextLineData.lsfangxiang = 0;
		nextLineData.Sx = 0;
		nextLineData.Sy = 0;
		nextLineData.songshu = 0;
		nextLineData.gongxian = 0;
		nextLineData.unuse5 = 0;
		nextLineData.unuse6 = 0;
		nextLineData.unuse7 = 0;
		nextLineData.unuse8 = 0;
		nextLineData.unuse9 = 0;
		nextLineData.btnum = 0; //��¼����,�������� //98
		for (int j = 0; j < ROLE_MAGIC_COUNT; j++)
		{
			nextLineData.MagicID[j] = 0;
		}
		for (int j = 0; j < ROLE_MAGIC_COUNT; j++)
		{
			nextLineData.MagicLevel[j] = 0;
		}
		for (int j = 0; j < ROLE_TAKING_ITEM_COUNT; j++)
		{
			nextLineData.TakingItem[j] = 0;
		}
		for (int j = 0; j < ROLE_TAKING_ITEM_COUNT; j++)
		{
			nextLineData.TakingItemCount[j] = 0;
		}
		for (int j = 0; j < 10; j++)
		{
			nextLineData.JhMagic[j] = 0;
		}
		for (int j = 0; j < ROLE_MAGIC_COUNT; j++)
		{
			nextLineData.LZhaoshi[j] = 0;
		}
		nextLineData.MRevent = 0;
		for (int j = 0; j < 8; j++)
		{
			nextLineData.AllEvent[j] = 0;
		}
		nextLineData.LeaveTime = 0;
		nextLineData.LeaveEvent = 0;
		nextLineData.LaoLian = 0;
		nextLineData.QiangZhuang = 0;
		nextLineData.NeiJia = 0;
		nextLineData.QiangGong = 0;
		nextLineData.JianGU = 0;
		nextLineData.QingLing = 0;
		nextLineData.QuanShi = 0;
		nextLineData.JianKe = 0;
		nextLineData.Daoke = 0;
		nextLineData.YiBing = 0;
		nextLineData.AnJian = 0;
		nextLineData.YIShi = 0;
		nextLineData.DuRen = 0;
		nextLineData.HuiXue = 0;
		nextLineData.HuiNei = 0;
		nextLineData.HuiTI = 0;
		nextLineData.BaoZao = 0;
		nextLineData.PeiHe = 0;
		nextLineData.WuXue = 0;
		nextLineData.TuPo = 0;
		nextLineData.LengJing = 0;
		nextLineData.BaiBian = 0;
		nextLineData.PoQi = 0;
		nextLineData.ZhaoMen = 0;
		nextLineData.BianHuan = 0;
		nextLineData.FanGong = 0;
		nextLineData.QiGong = 0;
		nextLineData.YingGong = 0;
		nextLineData.LingHuo = 0;
		nextLineData.XingQi = 0;
		nextLineData.ShenFa = 0;
		nextLineData.FenFa = 0;
		nextLineData.ZhanYi = 0;
		nextLineData.JingZhun = 0;
		nextLineData.JiSu = 0;
		nextLineData.KuangBao = 0;
		nextLineData.ShouFa = 0; 
		nextLineData.LianHuan = 0;
		nextLineData.WaJie = 0;
		nextLineData.GuShou = 0; 
		nextLineData.TianMing = 0;
		nextLineData.XingXiu = 0;
		for (int j = 0; j < 5; j++)
		{
			nextLineData.ZhuanChang[j] = 0;
		}
		for (int j = 0; j < 10; j++)
		{
			nextLineData.TeXing[j] = 0;
		}
		for (int j = 0; j < 10; j++)
		{
			nextLineData.unused[j] = 0;
		}
        return nextLineData;
    };
    char* Name__;
    char* Nick__;
    int lines = 0;
    auto nextLineData = getDefault();
    while (in.read_row(
        nextLineData.ID,
        nextLineData.HeadID,
        nextLineData.IncLife,
        nextLineData.Fuyuan,
        Name__,
        Nick__,
        nextLineData.Sexual,
        nextLineData.Level,
        nextLineData.Exp,
        nextLineData.HP,
        nextLineData.MaxHP,
        nextLineData.Hurt,
        nextLineData.Poison,
        nextLineData.PhysicalPower,
		nextLineData.FightNum,
        nextLineData.Equip[0],
        nextLineData.Equip[1],
		nextLineData.Equip[2],
		nextLineData.Equip[3],
		nextLineData.Equip[4],
		nextLineData.Gongti,
		nextLineData.TeamState,
		nextLineData.Angry,
		nextLineData.isRandomed,
		nextLineData.Moveable,
		nextLineData.In_HeadNum,
		nextLineData.ZhanLueAI,
		nextLineData.Impression,
		nextLineData.dtime,
		nextLineData.difficulty,
		nextLineData.Zhongcheng,
		nextLineData.reHurt,
		nextLineData.MPType,
		nextLineData.MP,
		nextLineData.MaxMP,
		nextLineData.Attack,
		nextLineData.Speed,
		nextLineData.Defence,
		nextLineData.Medicine,
		nextLineData.UsePoison,
		nextLineData.Detoxification,
		nextLineData.AntiPoison,
		nextLineData.Fist,
		nextLineData.Sword,
		nextLineData.Knife,
		nextLineData.Unusual,
		nextLineData.HiddenWeapon,
		nextLineData.Knowledge,
		nextLineData.Morality,
		nextLineData.AttackWithPoison,
		nextLineData.AttackTwice,
		nextLineData.Fame,
		nextLineData.IQ,
		nextLineData.PracticeItem,
		nextLineData.ExpForItem,
		nextLineData.xiangxing,
		nextLineData.jiaoqing,
		nextLineData.Rtype,
		nextLineData.swq,
		nextLineData.pdq,
		nextLineData.xxq,
		nextLineData.jqq,
		nextLineData.MenPai,
		nextLineData.shifu,
		nextLineData.scsx,
		nextLineData.bssx,
		nextLineData.Choushi[0],
		nextLineData.Choushi[1],
		nextLineData.weizhi,
		nextLineData.nweizhi,
		nextLineData.nfangxiang,
		nextLineData.OnStatus,
		nextLineData.lwq,
		nextLineData.msq,
		nextLineData.ldq,
		nextLineData.qtq,
		nextLineData.lsweizhi,
		nextLineData.lsnweizhi,
		nextLineData.lsfangxiang,
		nextLineData.Sx,
		nextLineData.Sy,
		nextLineData.songshu,
		nextLineData.gongxian,
		nextLineData.unuse5,
		nextLineData.unuse6,
		nextLineData.unuse7,
		nextLineData.unuse8,
		nextLineData.unuse9,
		nextLineData.btnum, //��¼����,�������� //98
		nextLineData.MagicID[0],
		nextLineData.MagicID[1],
		nextLineData.MagicID[2],
		nextLineData.MagicID[3],
		nextLineData.MagicID[4],
		nextLineData.MagicID[5],
		nextLineData.MagicID[6],
		nextLineData.MagicID[7],
		nextLineData.MagicID[8],
		nextLineData.MagicID[9],
		nextLineData.MagicID[10],
		nextLineData.MagicID[11],
			nextLineData.MagicID[12],
			nextLineData.MagicID[13],
			nextLineData.MagicID[14],
			nextLineData.MagicID[15],
			nextLineData.MagicID[16],
			nextLineData.MagicID[17],
			nextLineData.MagicID[18],
			nextLineData.MagicID[19],
			nextLineData.MagicID[20],
			nextLineData.MagicID[21],
			nextLineData.MagicID[22],
			nextLineData.MagicID[23],
			nextLineData.MagicID[24],
			nextLineData.MagicID[25],
			nextLineData.MagicID[26],
			nextLineData.MagicID[27],
			nextLineData.MagicID[28],
			nextLineData.MagicID[29],
			nextLineData.MagicID[30],
			nextLineData.MagicID[31],
			nextLineData.MagicID[32],
			nextLineData.MagicID[33],
			nextLineData.MagicID[34],
			nextLineData.MagicID[35],
			nextLineData.MagicID[36],
			nextLineData.MagicID[37],
			nextLineData.MagicID[38],
			nextLineData.MagicID[39],
			nextLineData.MagicLevel[0],
			nextLineData.MagicLevel[1],
			nextLineData.MagicLevel[2],
			nextLineData.MagicLevel[3],
			nextLineData.MagicLevel[4],
			nextLineData.MagicLevel[5],
			nextLineData.MagicLevel[6],
			nextLineData.MagicLevel[7],
			nextLineData.MagicLevel[8],
			nextLineData.MagicLevel[9],
			nextLineData.MagicLevel[10],
			nextLineData.MagicLevel[11],
			nextLineData.MagicLevel[12],
			nextLineData.MagicLevel[13],
			nextLineData.MagicLevel[14],
			nextLineData.MagicLevel[15],
			nextLineData.MagicLevel[16],
			nextLineData.MagicLevel[17],
			nextLineData.MagicLevel[18],
			nextLineData.MagicLevel[19],
			nextLineData.MagicLevel[20],
			nextLineData.MagicLevel[21],
			nextLineData.MagicLevel[22],
			nextLineData.MagicLevel[23],
			nextLineData.MagicLevel[24],
			nextLineData.MagicLevel[25],
			nextLineData.MagicLevel[26],
			nextLineData.MagicLevel[27],
			nextLineData.MagicLevel[28],
			nextLineData.MagicLevel[29],
			nextLineData.MagicLevel[30],
			nextLineData.MagicLevel[31],
			nextLineData.MagicLevel[32],
			nextLineData.MagicLevel[33],
			nextLineData.MagicLevel[34],
			nextLineData.MagicLevel[35],
			nextLineData.MagicLevel[36],
			nextLineData.MagicLevel[37],
			nextLineData.MagicLevel[38],
			nextLineData.MagicLevel[39],
			nextLineData.TakingItem[0],
			nextLineData.TakingItem[1],
			nextLineData.TakingItem[2],
			nextLineData.TakingItem[3],
			nextLineData.TakingItemCount[0],
			nextLineData.TakingItemCount[1],
			nextLineData.TakingItemCount[2],
			nextLineData.TakingItemCount[3],
			nextLineData.JhMagic[0],
			nextLineData.JhMagic[1],
			nextLineData.JhMagic[2],
			nextLineData.JhMagic[3],
			nextLineData.JhMagic[4],
			nextLineData.JhMagic[5],
			nextLineData.JhMagic[6],
			nextLineData.JhMagic[7],
			nextLineData.JhMagic[8],
			nextLineData.JhMagic[9],
			nextLineData.LZhaoshi[0],
			nextLineData.LZhaoshi[1],
			nextLineData.LZhaoshi[2],
			nextLineData.LZhaoshi[3],
			nextLineData.LZhaoshi[4],
			nextLineData.LZhaoshi[5],
			nextLineData.LZhaoshi[6],
			nextLineData.LZhaoshi[7],
			nextLineData.LZhaoshi[8],
			nextLineData.LZhaoshi[9],
			nextLineData.LZhaoshi[10],
			nextLineData.LZhaoshi[11],
			nextLineData.LZhaoshi[12],
			nextLineData.LZhaoshi[13],
			nextLineData.LZhaoshi[14],
			nextLineData.LZhaoshi[15],
			nextLineData.LZhaoshi[16],
			nextLineData.LZhaoshi[17],
			nextLineData.LZhaoshi[18],
			nextLineData.LZhaoshi[19],
			nextLineData.LZhaoshi[20],
			nextLineData.LZhaoshi[21],
			nextLineData.LZhaoshi[22],
			nextLineData.LZhaoshi[23],
			nextLineData.LZhaoshi[24],
			nextLineData.LZhaoshi[25],
			nextLineData.LZhaoshi[26],
			nextLineData.LZhaoshi[27],
			nextLineData.LZhaoshi[28],
			nextLineData.LZhaoshi[29],
			nextLineData.LZhaoshi[30],
			nextLineData.LZhaoshi[31],
			nextLineData.LZhaoshi[32],
			nextLineData.LZhaoshi[33],
			nextLineData.LZhaoshi[34],
			nextLineData.LZhaoshi[35],
			nextLineData.LZhaoshi[36],
			nextLineData.LZhaoshi[37],
			nextLineData.LZhaoshi[38],
			nextLineData.LZhaoshi[39],
			nextLineData.MRevent,
			nextLineData.AllEvent[0],
			nextLineData.AllEvent[1],
			nextLineData.AllEvent[2],
			nextLineData.AllEvent[3],
			nextLineData.AllEvent[4],
			nextLineData.AllEvent[5],
			nextLineData.AllEvent[6],
			nextLineData.AllEvent[7],
		nextLineData.LeaveTime,
		nextLineData.LeaveEvent,
		nextLineData.LaoLian,
		nextLineData.QiangZhuang,
		nextLineData.NeiJia,
		nextLineData.QiangGong,
		nextLineData.JianGU,
		nextLineData.QingLing,
		nextLineData.QuanShi,
		nextLineData.JianKe,
		nextLineData.Daoke,
		nextLineData.YiBing,
		nextLineData.AnJian,
		nextLineData.YIShi,
		nextLineData.DuRen,
		nextLineData.HuiXue,
		nextLineData.HuiNei,
		nextLineData.HuiTI,
		nextLineData.BaoZao,
		nextLineData.PeiHe,
		nextLineData.WuXue,
		nextLineData.TuPo,
		nextLineData.LengJing,
		nextLineData.BaiBian,
		nextLineData.PoQi,
		nextLineData.ZhaoMen,
		nextLineData.BianHuan,
		nextLineData.FanGong,
		nextLineData.QiGong,
		nextLineData.YingGong,
		nextLineData.LingHuo,
		nextLineData.XingQi,
		nextLineData.ShenFa,
		nextLineData.FenFa,
		nextLineData.ZhanYi,
		nextLineData.JingZhun,
		nextLineData.JiSu,
		nextLineData.KuangBao,
		nextLineData.ShouFa,
		nextLineData.LianHuan,
		nextLineData.WaJie,
		nextLineData.GuShou,
		nextLineData.TianMing,
		nextLineData.XingXiu,
		nextLineData.ZhuanChang[0],
			nextLineData.ZhuanChang[1],
			nextLineData.ZhuanChang[2],
			nextLineData.ZhuanChang[3],
			nextLineData.ZhuanChang[4],
				nextLineData.TeXing[0],
				nextLineData.TeXing[1],
				nextLineData.TeXing[2],
				nextLineData.TeXing[3],
				nextLineData.TeXing[4],
				nextLineData.TeXing[5],
				nextLineData.TeXing[6],
				nextLineData.TeXing[7],
				nextLineData.TeXing[8],
				nextLineData.TeXing[9],
				nextLineData.unused[0],
				nextLineData.unused[1],
				nextLineData.unused[2],
				nextLineData.unused[3],
				nextLineData.unused[4],
				nextLineData.unused[5],
				nextLineData.unused[6],
				nextLineData.unused[7],
				nextLineData.unused[8],
				nextLineData.unused[9]))
    {
        strncpy(nextLineData.Name, Name__, sizeof(nextLineData.Name) - 1);
        strncpy(nextLineData.Nick, Nick__, sizeof(nextLineData.Nick) - 1);
        data.push_back(nextLineData);
        lines++;
        nextLineData = getDefault();
    }
	
}
// ��Ʒ
void NewSave::LoadCSVItemSave(std::vector<Item>& data, int record)
{
    data.clear();
    io::CSVReader<82, io::trim_chars<>, io::double_quote_escape<',', '\"'>> in("../game/save/csv/" + std::to_string(record) + "_��Ʒ.csv");
    in.read_header(io::ignore_missing_column | io::ignore_extra_column,
		"���",
		"��Ʒ��",
		"��Ʒ�书���",
		"���b̖",
		"����Ч",
		"���Ә˺�",
		"Ҫ���Ԅe",
		"�֏͂���",
		"��Ʒ��",
		"����",
		"���ӝ���ֵ",
		"����̖",
		"��Ʒ�f��",
		"�����书",
		"�����Ӯ���̖",
		"ʹ����",
		"�b�����",
		"�@ʾ��Ʒ�f��",
		"���",
		"�̵���",
		"�ۃr",
		"�{���¼�",
		"������",
		"���������ֵ",
		"���ж��ⶾ",
		"���w��",
		"��׃�������|",
		"�Ӄ���",
		"�Ӄ������ֵ",
		"�ӹ�����",
		"���p��",
		"�ӷ�����",
		"���t��",
		"��ʹ��",
		"�Ӽ�ˇ",
		"�ӿ���",
		"��ȭ��",
		"������",
		"��ˣ��",
		"���������",
		"�Ӱ�������",
		"����W���R",
		"��Ʒ��",
		"������",
		"�ӹ��򎧶�",
		"�H�ޟ�����",
		"��������|",
		"�����",
		"�蹥����",
		"���p��",
		"�趾�g",
		"���t��",
		"�輼ˇ",
		"��ȭ��",
		"������",
		"��ˣ��",
		"���������",
		"�谵��",
		"���Y�|",
		"�轛�",
		"����",
		"ϡ�ж�",
		"������Ʒ1",
		"������Ʒ2",
		"������Ʒ3",
		"������Ʒ4",
		"������Ʒ5",
		"��Ҫ��Ʒ1����",
		"��Ҫ��Ʒ2����",
		"��Ҫ��Ʒ3����",
		"��Ҫ��Ʒ4����",
		"��Ҫ��Ʒ5����",
		"���Y�|",
		"�Ӹ�Դ",
		"δʹ��",
		"δʹ��1",
		"δʹ��2",
		"δʹ��3",
		"δʹ��4",
		"δʹ��5",
		"δʹ��6",
		"δʹ��7");
    auto getDefault = []()
    {
        Item nextLineData;
        nextLineData.ID = 0;
        memset(nextLineData.Name, '\0', sizeof(nextLineData.Name));
		nextLineData.ExpofMagic = 0;
		nextLineData.SetNum = 0;
		nextLineData.BattleBattleEffect = 0;
		nextLineData.AddSign = 0;
		nextLineData.needSex = 0;
		nextLineData.rehurt = 0;
		nextLineData.NeedEthics = 0;
		nextLineData.NeedRepute = 0;
		nextLineData.AddQianli = 0;
		nextLineData.BattleNum = 0;
        memset(nextLineData.Introduction, '\0', sizeof(nextLineData.Introduction));
        nextLineData.MagicID = -1;
        nextLineData.HiddenWeaponEffectID = -1;
        nextLineData.User = -1;
        nextLineData.EquipType = -1;
        nextLineData.ShowIntroduction = 0;
        nextLineData.ItemType = 0;
        nextLineData.Inventory = 0; 
        nextLineData.Price = 0;
        nextLineData.EventNum = 0;
        nextLineData.AddHP = 0;
        nextLineData.AddMaxHP = 0;
        nextLineData.AddPoison = 0;
        nextLineData.AddPhysicalPower = 0;
        nextLineData.ChangeMPType = -1;
        nextLineData.AddMP = 0;
        nextLineData.AddMaxMP = 0;
        nextLineData.AddAttack = 0;
        nextLineData.AddSpeed = 0;
        nextLineData.AddDefence = 0;
        nextLineData.AddMedicine = 0;
        nextLineData.AddUsePoison = 0;
        nextLineData.AddDetoxification = 0;
        nextLineData.AddAntiPoison = 0;
        nextLineData.AddFist = 0;
        nextLineData.AddSword = 0;
        nextLineData.AddKnife = 0;
        nextLineData.AddUnusual = 0;
        nextLineData.AddHiddenWeapon = 0;
        nextLineData.AddKnowledge = 0;
        nextLineData.AddMorality = 0;
        nextLineData.AddAttackTwice = 0;
        nextLineData.AddAttackWithPoison = 0;
        nextLineData.OnlySuitableRole = -1;
        nextLineData.NeedMPType = 0;
        nextLineData.NeedMP = 0;
        nextLineData.NeedAttack = 0;
        nextLineData.NeedSpeed = 0;
        nextLineData.NeedUsePoison = 0;
        nextLineData.NeedMedicine = 0;
        nextLineData.NeedDetoxification = 0;
        nextLineData.NeedFist = 0;
        nextLineData.NeedSword = 0;
        nextLineData.NeedKnife = 0;
        nextLineData.NeedUnusual = 0;
        nextLineData.NeedHiddenWeapon = 0;
        nextLineData.NeedIQ = 0;
        nextLineData.NeedExp = 0;
        nextLineData.NeedExpForMakeItem = 0;
        nextLineData.NeedMaterial = -1;
        for (int j = 0; j < 5; j++)
        {
            nextLineData.MakeItem[j] = -1;
        }
        for (int j = 0; j < 5; j++)
        {
            nextLineData.MakeItemCount[j] = 0;
        }
		nextLineData.AddIQ = 0;
		nextLineData.AddFuyuan = 0;
		for (int j = 0; j < 8; j++)
		{
			nextLineData.Unused[j] = 0;
		}
        return nextLineData;
    };
    char* Name__;
    char* Introduction__;
    int lines = 0;
    auto nextLineData = getDefault();
    while (in.read_row(
        nextLineData.ID,
        Name__,
		nextLineData.ExpofMagic ,
	nextLineData.SetNum ,
	nextLineData.BattleBattleEffect ,
	nextLineData.AddSign ,
	nextLineData.needSex ,
	nextLineData.rehurt ,
	nextLineData.NeedEthics ,
	nextLineData.NeedRepute ,
	nextLineData.AddQianli ,
	nextLineData.BattleNum ,
        Introduction__,
        nextLineData.MagicID,
        nextLineData.HiddenWeaponEffectID,
        nextLineData.User,
        nextLineData.EquipType,
        nextLineData.ShowIntroduction,
        nextLineData.ItemType,
		nextLineData.Inventory,
	nextLineData.Price,
	nextLineData.EventNum,
        nextLineData.AddHP,
        nextLineData.AddMaxHP,
        nextLineData.AddPoison,
        nextLineData.AddPhysicalPower,
        nextLineData.ChangeMPType,
        nextLineData.AddMP,
        nextLineData.AddMaxMP,
        nextLineData.AddAttack,
        nextLineData.AddSpeed,
        nextLineData.AddDefence,
        nextLineData.AddMedicine,
        nextLineData.AddUsePoison,
        nextLineData.AddDetoxification,
        nextLineData.AddAntiPoison,
        nextLineData.AddFist,
        nextLineData.AddSword,
        nextLineData.AddKnife,
        nextLineData.AddUnusual,
        nextLineData.AddHiddenWeapon,
        nextLineData.AddKnowledge,
        nextLineData.AddMorality,
        nextLineData.AddAttackTwice,
        nextLineData.AddAttackWithPoison,
        nextLineData.OnlySuitableRole,
        nextLineData.NeedMPType,
        nextLineData.NeedMP,
        nextLineData.NeedAttack,
        nextLineData.NeedSpeed,
        nextLineData.NeedUsePoison,
        nextLineData.NeedMedicine,
        nextLineData.NeedDetoxification,
        nextLineData.NeedFist,
        nextLineData.NeedSword,
        nextLineData.NeedKnife,
        nextLineData.NeedUnusual,
        nextLineData.NeedHiddenWeapon,
        nextLineData.NeedIQ,
        nextLineData.NeedExp,
        nextLineData.NeedExpForMakeItem,
        nextLineData.NeedMaterial,
        nextLineData.MakeItem[0],
        nextLineData.MakeItem[1],
        nextLineData.MakeItem[2],
        nextLineData.MakeItem[3],
        nextLineData.MakeItem[4],
        nextLineData.MakeItemCount[0],
        nextLineData.MakeItemCount[1],
        nextLineData.MakeItemCount[2],
        nextLineData.MakeItemCount[3],
        nextLineData.MakeItemCount[4],
		nextLineData.AddIQ,
		nextLineData.AddFuyuan,
		nextLineData.Unused[0],
		nextLineData.Unused[1],
		nextLineData.Unused[2],
		nextLineData.Unused[3],
		nextLineData.Unused[4],
		nextLineData.Unused[5],
		nextLineData.Unused[6],
		nextLineData.Unused[7]))
    {
        strncpy(nextLineData.Introduction, Introduction__, sizeof(nextLineData.Introduction) - 1);
        strncpy(nextLineData.Name, Name__, sizeof(nextLineData.Name) - 1);
        data.push_back(nextLineData);
        lines++;
        nextLineData = getDefault();
    }
	
}
// ����
void NewSave::LoadCSVSubMapInfoSave(std::vector<SubMapInfo>& data, int record)
{
    data.clear();
    io::CSVReader<91, io::trim_chars<>, io::double_quote_escape<',', '\"'>> in("../game/save/csv/" + std::to_string(record) + "_����.csv");
    in.read_header(io::ignore_missing_column | io::ignore_extra_column,
		"���",
		"���Q",
		"���T����",
		"�M�T����",
		"�����{ɫ��",
		"�M��l��",
		"�⾰���X1",
		"�⾰���Y1",
		"�⾰���X2",
		"�⾰���Y2",
		"���X",
		"���Y",
		"����X1",
		"����X2",
		"����X3",
		"����Y1",
		"����Y2",
		"����Y3",
		"�h��",
		"δ��",
		"�����T��",
		"����",
		"���������",
		"�������",
		"���ؽ��w��",
		"�ؽ��w��",
		"�����X",
		"�����X1",
		"�����X2",
		"�����X3",
		"�����X4",
		"�����Y",
		"�����Y1",
		"�����Y2",
		"�����Y3",
		"�����Y4",
		"�ؽ��wX",
		"�ؽ��wX1",
		"�ؽ��wX2",
		"�ؽ��wX3",
		"�ؽ��wX4",
		"�ؽ��wY",
		"�ؽ��wY1",
		"�ؽ��wY2",
		"�ؽ��wY3",
		"�ؽ��wY4",
		"�]�P���_�P",
		"�]�P��X",
		"�]�P��Y",
		"�����t�_�P",
		"�����tX",
		"�����tY",
		"�������_�P",
		"������X",
		"������Y",
		"���X",
		"���Y",
		"�����M��",
		"����M��",
		"�����ӳ�",
		"�����Oʩ",
		"�F�V",
		"ʯ��",
		"ľ��",
		"ʳ��",
		"��̿",
		"��ˎ",
		"��ľ",
		"����",
		"ϡ��",
		"���F",
		"�B��",
		"�B��1",
		"�B��2",
		"�B��3",
		"�B��4",
		"�B��5",
		"�B��6",
		"�B��7",
		"�B��8",
		"�B��9",
		"δʹ��",
		"δʹ��1",
		"δʹ��2",
		"δʹ��3",
		"δʹ��4",
		"δʹ��5",
		"δʹ��6",
		"δʹ��7",
		"δʹ��8",
		"δʹ��9");
    auto getDefault = []()
    {
        SubMapInfo nextLineData;
        nextLineData.ID = 0;
        memset(nextLineData.Name, '\0', sizeof(nextLineData.Name));
        nextLineData.ExitMusic = 0;
        nextLineData.EntranceMusic = -1;
        nextLineData.JumpSubMap = -1;
        nextLineData.EntranceCondition = 0;
        nextLineData.MainEntranceX1 = 0;
        nextLineData.MainEntranceY1 = 0;
        nextLineData.MainEntranceX2 = 0;
        nextLineData.MainEntranceY2 = 0;
        nextLineData.EntranceX = 0;
        nextLineData.EntranceY = 0;
        for (int j = 0; j < 3; j++)
        {
            nextLineData.ExitX[j] = -1;
        }
        for (int j = 0; j < 3; j++)
        {
            nextLineData.ExitY[j] = -1;
        }
		nextLineData.Mapmode = 0;
			nextLineData.unuse = 0; 
			nextLineData.menpai = 0;
			nextLineData.inbattle = 0;
			nextLineData.zlwc = 0; 
			nextLineData.lwc = 0; 
			nextLineData.zcjg = 0; 
			nextLineData.cjg = 0;
			nextLineData.lwcx[0] = 0;
			nextLineData.lwcx[1] = 0;
			nextLineData.lwcx[2] = 0;
			nextLineData.lwcx[3] = 0;
			nextLineData.lwcx[4] = 0;
			nextLineData.lwcy[0] = 0;
			nextLineData.lwcy[1] = 0;
			nextLineData.lwcy[2] = 0;
			nextLineData.lwcy[3] = 0;
			nextLineData.lwcy[4] = 0;
			nextLineData.cjgx[0] = 0;
			nextLineData.cjgx[1] = 0;
			nextLineData.cjgx[2] = 0;
			nextLineData.cjgx[3] = 0;
			nextLineData.cjgx[4] = 0;
			nextLineData.cjgy[0] = 0;
			nextLineData.cjgy[1] = 0;
			nextLineData.cjgy[2] = 0;
			nextLineData.cjgy[3] = 0;
			nextLineData.cjgy[4] = 0;
			nextLineData.bgskg = 0;
			nextLineData.bgsx = 0;
			nextLineData.bgsy = 0;
			nextLineData.ldlkg = 0;
			nextLineData.ldlx = 0; 
			nextLineData.ldly = 0;
			nextLineData.bqckg = 0;
			nextLineData.bqcx = 0;
			nextLineData.bqcy = 0;
			nextLineData.qizhix = 0;
			nextLineData.qizhiy = 0;
			nextLineData.ldjd = 0;
			nextLineData.dzjd = 0;
			nextLineData.fyjc = 0;
			nextLineData.fyss = 0;
			nextLineData.addziyuan[0] = 0;
			nextLineData.addziyuan[1] = 0;
			nextLineData.addziyuan[2] = 0;
			nextLineData.addziyuan[3] = 0;
			nextLineData.addziyuan[4] = 0;
			nextLineData.addziyuan[5] = 0;
			nextLineData.addziyuan[6] = 0;
			nextLineData.addziyuan[7] = 0;
			nextLineData.addziyuan[8] = 0;
			nextLineData.addziyuan[9] = 0;
			nextLineData.lianjie[0] = 0;
			nextLineData.lianjie[1] = 0;
			nextLineData.lianjie[2] = 0;
			nextLineData.lianjie[3] = 0;
			nextLineData.lianjie[4] = 0;
			nextLineData.lianjie[5] = 0;
			nextLineData.lianjie[6] = 0;
			nextLineData.lianjie[7] = 0;
			nextLineData.lianjie[8] = 0;
			nextLineData.lianjie[9] = 0;
			nextLineData.unused[0] = 0;
			nextLineData.unused[1] = 0;
			nextLineData.unused[2] = 0;
			nextLineData.unused[3] = 0;
			nextLineData.unused[4] = 0;
			nextLineData.unused[5] = 0;
			nextLineData.unused[6] = 0;
			nextLineData.unused[7] = 0;
			nextLineData.unused[8] = 0;
			nextLineData.unused[9] = 0;
        return nextLineData;
    };
    char* Name__;
    int lines = 0;
    auto nextLineData = getDefault();
    while (in.read_row(
        nextLineData.ID,
        Name__,
        nextLineData.ExitMusic,
        nextLineData.EntranceMusic,
        nextLineData.JumpSubMap,
        nextLineData.EntranceCondition,
        nextLineData.MainEntranceX1,
        nextLineData.MainEntranceY1,
        nextLineData.MainEntranceX2,
        nextLineData.MainEntranceY2,
        nextLineData.EntranceX,
        nextLineData.EntranceY,
        nextLineData.ExitX[0],
        nextLineData.ExitX[1],
        nextLineData.ExitX[2],
        nextLineData.ExitY[0],
        nextLineData.ExitY[1],
        nextLineData.ExitY[2],
		nextLineData.Mapmode,
		nextLineData.unuse,
		nextLineData.menpai,
		nextLineData.inbattle,
		nextLineData.zlwc,
		nextLineData.lwc,
		nextLineData.zcjg,
		nextLineData.cjg,
		nextLineData.lwcx[0],
		nextLineData.lwcx[1],
		nextLineData.lwcx[2],
		nextLineData.lwcx[3],
		nextLineData.lwcx[4],
		nextLineData.lwcy[0],
		nextLineData.lwcy[1],
		nextLineData.lwcy[2],
		nextLineData.lwcy[3],
		nextLineData.lwcy[4],
		nextLineData.cjgx[0],
		nextLineData.cjgx[1],
		nextLineData.cjgx[2],
		nextLineData.cjgx[3],
		nextLineData.cjgx[4],
		nextLineData.cjgy[0],
		nextLineData.cjgy[1],
		nextLineData.cjgy[2],
		nextLineData.cjgy[3],
		nextLineData.cjgy[4],
		nextLineData.bgskg,
		nextLineData.bgsx,
		nextLineData.bgsy,
		nextLineData.ldlkg,
		nextLineData.ldlx,
		nextLineData.ldly,
		nextLineData.bqckg,
		nextLineData.bqcx,
		nextLineData.bqcy,
		nextLineData.qizhix,
		nextLineData.qizhiy,
		nextLineData.ldjd,
		nextLineData.dzjd,
		nextLineData.fyjc,
		nextLineData.fyss,
		nextLineData.addziyuan[0],
		nextLineData.addziyuan[1],
		nextLineData.addziyuan[2],
		nextLineData.addziyuan[3],
		nextLineData.addziyuan[4],
		nextLineData.addziyuan[5],
		nextLineData.addziyuan[6],
		nextLineData.addziyuan[7],
		nextLineData.addziyuan[8],
		nextLineData.addziyuan[9],
		nextLineData.lianjie[0],
		nextLineData.lianjie[1],
		nextLineData.lianjie[2],
		nextLineData.lianjie[3],
		nextLineData.lianjie[4],
		nextLineData.lianjie[5],
		nextLineData.lianjie[6],
		nextLineData.lianjie[7],
		nextLineData.lianjie[8],
		nextLineData.lianjie[9],
		nextLineData.unused[0],
		nextLineData.unused[1],
		nextLineData.unused[2],
		nextLineData.unused[3],
		nextLineData.unused[4],
		nextLineData.unused[5],
		nextLineData.unused[6],
		nextLineData.unused[7],
		nextLineData.unused[8],
		nextLineData.unused[9]))
    {
        strncpy(nextLineData.Name, Name__, sizeof(nextLineData.Name) - 1);
        data.push_back(nextLineData);
        lines++;
        nextLineData = getDefault();
    }
}
// �书
void NewSave::LoadCSVMagicSave(std::vector<Magic>& data, int record)
{
    data.clear();
    io::CSVReader<114, io::trim_chars<>, io::double_quote_escape<',', '\"'>> in("../game/save/csv/" + std::to_string(record) + "_�书.csv");
    in.read_header(io::ignore_missing_column | io::ignore_extra_column,
		"���",
		"���Q",
		"�o��",
		"����",
		"��Ҫ����",
		"��С���x",
		"�Ƿ�ΈD��Ч",
		"�¼�",
		"������Ч",
		"�书���",
		"�书�Ӯ�&��Ч",
		"�������",
		"��������",
		"���ă����c��",
		"�����ж��c��",
		"��С������",
		"��󹥓���",
		"����ϵ��",
		"����������",
		"��������",
		"�p������",
		"����ֵ����",
		"�Ƿ��؂�",
		"�Ӄ�������",
		"����������",
		"1���Ƅӷ���",
		"2���Ƅӷ���",
		"3���Ƅӷ���",
		"4���Ƅӷ���",
		"5���Ƅӷ���",
		"6���Ƅӷ���",
		"7���Ƅӷ���",
		"8���Ƅӷ���",
		"9���Ƅӷ���",
		"10���Ƅӷ���",
		"1����������",
		"2����������",
		"3����������",
		"4����������",
		"5����������",
		"6����������",
		"7����������",
		"8����������",
		"9����������",
		"10����������",
		"1��������",
		"2��������",
		"3��������",
		"1���Ӄ���",
		"2���Ӄ���",
		"3���Ӄ���",
		"1���ӹ���",
		"2���ӹ���",
		"3���ӹ���",
		"1���ӷ���",
		"2���ӷ���",
		"3���ӷ���",
		"1�����p��",
		"2�����p��",
		"3�����p��",
		"��С��Ѩ����",
		"����Ѩ����",
		"��С�Ȃ�����",
		"���Ȃ�����",
		"�����t��",
		"���Ӷ��g",
		"���Ӽ�ˇ",
		"���ӿ���",
		"����ȭ��",
		"��������",
		"����ˣ��",
		"��������",
		"���Ӱ���",
		"��B",
		"1���轛�",
		"2���轛�",
		"3���轛�",
		"��ߵȼ�",
		"�f��",
		"��ʽ",
		"��ʽ1",
		"��ʽ2",
		"��ʽ3",
		"��ʽ4",
		"����",
		"����1",
		"����2",
		"����3",
		"����4",
		"����5",
		"����6",
		"����7",
		"����8",
		"����9",
		"�������",
		"�������1",
		"�������2",
		"�������3",
		"�������4",
		"�������5",
		"�������6",
		"�������7",
		"�������8",
		"�������9",
		"��Ҫؕ�I",
		"δʹ��",
		"δʹ��1",
		"δʹ��2",
		"δʹ��3",
		"δʹ��4",
		"δʹ��5",
		"δʹ��6",
		"δʹ��7",
		"δʹ��8");
    auto getDefault = []()
    {
        Magic nextLineData;
        nextLineData.ID = 0;
        memset(nextLineData.Name, '\0', sizeof(nextLineData.Name));
		nextLineData.useness = 0;
			nextLineData.miji = 0;
			nextLineData.NeedHP = 0;
			nextLineData.MinStep = 0;
			nextLineData.bigami = 0;
			nextLineData.EventNum = 0;
        nextLineData.SoundID = 0;
        nextLineData.MagicType = 0;
        nextLineData.EffectID = 0;
        nextLineData.HurtType = 0;
        nextLineData.AttackAreaType = 0;
        nextLineData.NeedMP = 0;
        nextLineData.WithPoison = 0;
		nextLineData.MinHurt = 0;
			nextLineData.MaxHurt = 0;
			nextLineData.HurtModulus = 0;
			nextLineData.AttackModulus = 0;
			nextLineData.MPModulus = 0;
			nextLineData.SpeedModulus = 0;
			nextLineData.WeaponModulus = 0;
		nextLineData.Ismichuan = 0;
			nextLineData.AddMpScale = 0;
			nextLineData.AddHpScale = 0;

        for (int j = 0; j < 10; j++)
        {
            nextLineData.SelectDistance[j] = 0;
        }
        for (int j = 0; j < 10; j++)
        {
            nextLineData.AttackDistance[j] = 0;
        }
        for (int j = 0; j < 3; j++)
        {
            nextLineData.AddHP[j] = 0;
        }
        for (int j = 0; j < 3; j++)
        {
            nextLineData.AddMP[j] = 0;
        }
		for (int j = 0; j < 3; j++)
		{
			nextLineData.AddAtt[j] = 0;
		}
		for (int j = 0; j < 3; j++)
		{
			nextLineData.AddDef[j] = 0;
		}
		for (int j = 0; j < 3; j++)
		{
			nextLineData.AddSpd[j] = 0;
		}
		nextLineData.MinPeg = 0; 
			nextLineData.MaxPeg = 0; 
			nextLineData.MinInjury = 0; 
			nextLineData.MaxInjury = 0; 
			nextLineData.AddMedcine = 0; 
			nextLineData.AddUsePoi = 0; 
			nextLineData.AddMedPoi = 0; 
			nextLineData.AddDefPoi = 0;
		nextLineData.AddFist = 0; 
			nextLineData.AddSword = 0; 
			nextLineData.AddKnife = 0; 
			nextLineData.AddUnusual = 0; 
			nextLineData.AddHidWeapon = 0; 
			nextLineData.BattleState = 0;
			for (int j = 0; j < 3; j++)
			{
				nextLineData.NeedExp[j] = 0;
			}
		nextLineData.MaxLevel = 0;
		memset(nextLineData.Introduction, '\0', sizeof(nextLineData.Introduction));
		nextLineData.Zhaoshi[5] = 0;
		for (int j = 0; j < 10; j++)
		{
			nextLineData.Teshu[j] = 0;
		}
		for (int j = 0; j < 10; j++)
		{
			nextLineData.Teshumod[j] = 0;
		}
		for (int j = 0; j < 10; j++)
		{
			nextLineData.unused[j] = 0;
		}

        return nextLineData;
    };
    char* Name__;
	char* Introduction__;
    int lines = 0;
    auto nextLineData = getDefault();
    while (in.read_row(
        nextLineData.ID,
        Name__,
		nextLineData.useness,
		nextLineData.miji,
		nextLineData.NeedHP,
		nextLineData.MinStep,
		nextLineData.bigami,
		nextLineData.EventNum,
        nextLineData.SoundID,
        nextLineData.MagicType,
        nextLineData.EffectID,
        nextLineData.HurtType,
        nextLineData.AttackAreaType,
        nextLineData.NeedMP,
        nextLineData.WithPoison,
		nextLineData.MinHurt, 
		nextLineData.MaxHurt,
		nextLineData.HurtModulus,
		nextLineData.AttackModulus,
		nextLineData.MPModulus,
		nextLineData.SpeedModulus,
		nextLineData.WeaponModulus,
		nextLineData.Ismichuan,
		nextLineData.AddMpScale,
		nextLineData.AddHpScale,
        nextLineData.SelectDistance[0],
        nextLineData.SelectDistance[1],
        nextLineData.SelectDistance[2],
        nextLineData.SelectDistance[3],
        nextLineData.SelectDistance[4],
        nextLineData.SelectDistance[5],
        nextLineData.SelectDistance[6],
        nextLineData.SelectDistance[7],
        nextLineData.SelectDistance[8],
        nextLineData.SelectDistance[9],
        nextLineData.AttackDistance[0],
        nextLineData.AttackDistance[1],
        nextLineData.AttackDistance[2],
        nextLineData.AttackDistance[3],
        nextLineData.AttackDistance[4],
        nextLineData.AttackDistance[5],
        nextLineData.AttackDistance[6],
        nextLineData.AttackDistance[7],
        nextLineData.AttackDistance[8],
        nextLineData.AttackDistance[9],
        nextLineData.AddHP[0],
        nextLineData.AddHP[1],
        nextLineData.AddHP[2],
        nextLineData.AddMP[0],
        nextLineData.AddMP[1],
        nextLineData.AddMP[2],
		nextLineData.AddAtt[0],
		nextLineData.AddAtt[1],
		nextLineData.AddAtt[2],
		nextLineData.AddDef[0],
		nextLineData.AddDef[1],
		nextLineData.AddDef[2],
		nextLineData.AddSpd[0],
		nextLineData.AddSpd[1],
		nextLineData.AddSpd[2],
		nextLineData.MinPeg,
		nextLineData.MaxPeg,
		nextLineData.MinInjury,
		nextLineData.MaxInjury,
		nextLineData.AddMedcine,
		nextLineData.AddUsePoi,
		nextLineData.AddMedPoi,
		nextLineData.AddDefPoi,
		nextLineData.AddFist,
		nextLineData.AddSword,
		nextLineData.AddKnife,
		nextLineData.AddUnusual,
		nextLineData.AddHidWeapon,
		nextLineData.BattleState,
		nextLineData.NeedExp[0],
		nextLineData.NeedExp[1],
		nextLineData.NeedExp[2],
		nextLineData.MaxLevel,
		Introduction__,
		nextLineData.Zhaoshi[0],
		nextLineData.Zhaoshi[1],
		nextLineData.Zhaoshi[2],
		nextLineData.Zhaoshi[3],
		nextLineData.Zhaoshi[4],
		nextLineData.Teshu[0],
		nextLineData.Teshu[1],
		nextLineData.Teshu[2],
		nextLineData.Teshu[3],
		nextLineData.Teshu[4],
		nextLineData.Teshu[5],
		nextLineData.Teshu[6],
		nextLineData.Teshu[7],
		nextLineData.Teshu[8],
		nextLineData.Teshu[9],
		nextLineData.Teshumod[0],
		nextLineData.Teshumod[1],
		nextLineData.Teshumod[2],
		nextLineData.Teshumod[3],
		nextLineData.Teshumod[4],
		nextLineData.Teshumod[5],
		nextLineData.Teshumod[6],
		nextLineData.Teshumod[7],
		nextLineData.Teshumod[8],
		nextLineData.Teshumod[9],
		nextLineData.unused[0],
		nextLineData.unused[1],
		nextLineData.unused[2],
		nextLineData.unused[3],
		nextLineData.unused[4],
		nextLineData.unused[5],
		nextLineData.unused[6],
		nextLineData.unused[7],
		nextLineData.unused[8],
		nextLineData.unused[9]))
    {
		strncpy(nextLineData.Introduction, Introduction__, sizeof(nextLineData.Introduction) - 1);
        strncpy(nextLineData.Name, Name__, sizeof(nextLineData.Name) - 1);
        data.push_back(nextLineData);
        lines++;
        nextLineData = getDefault();
    }
}
// �̵�
void NewSave::LoadCSVShopSave(std::vector<Shop>& data, int record)
{
    data.clear();
    io::CSVReader<72, io::trim_chars<>, io::double_quote_escape<',', '\"'>> in("../game/save/csv/" + std::to_string(record) + "_�̵�.csv");
    in.read_header(io::ignore_missing_column | io::ignore_extra_column,
		"��Ʒ",
		"��Ʒ����",
		"��Ʒ1",
		"��Ʒ����1",
		"��Ʒ2",
		"��Ʒ����2",
		"��Ʒ3",
		"��Ʒ����3",
		"��Ʒ4",
		"��Ʒ����4",
		"��Ʒ5",
		"��Ʒ����5",
		"��Ʒ6",
		"��Ʒ����6",
		"��Ʒ7",
		"��Ʒ����7",
		"��Ʒ8",
		"��Ʒ����8",
		"��Ʒ9",
		"��Ʒ����9",
		"��Ʒ10",
		"��Ʒ����10",
		"��Ʒ11",
		"��Ʒ����11",
		"��Ʒ12",
		"��Ʒ����12",
		"��Ʒ13",
		"��Ʒ����13",
		"��Ʒ14",
		"��Ʒ����14",
		"��Ʒ15",
		"��Ʒ����15",
		"��Ʒ16",
		"��Ʒ����16",
		"��Ʒ17",
		"��Ʒ����17",
		"��Ʒ18",
		"��Ʒ����18",
		"��Ʒ19",
		"��Ʒ����19",
		"��Ʒ20",
		"��Ʒ����20",
		"��Ʒ21",
		"��Ʒ����21",
		"��Ʒ22",
		"��Ʒ����22",
		"��Ʒ23",
		"��Ʒ����23",
		"��Ʒ24",
		"��Ʒ����24",
		"��Ʒ25",
		"��Ʒ����25",
		"��Ʒ26",
		"��Ʒ����26",
		"��Ʒ27",
		"��Ʒ����27",
		"��Ʒ28",
		"��Ʒ����28",
		"��Ʒ29",
		"��Ʒ����29",
		"��Ʒ30",
		"��Ʒ����30",
		"��Ʒ31",
		"��Ʒ����31",
		"��Ʒ32",
		"��Ʒ����32",
		"��Ʒ33",
		"��Ʒ����33",
		"��Ʒ34",
		"��Ʒ����34",
		"��Ʒ35",
		"��Ʒ����35");
    auto getDefault = []()
    {
        Shop nextLineData;
        for (int j = 0; j < 36; j++)
        {
            nextLineData.ItemID[j] = -1;
			nextLineData.ItermCount[j] = -1;
        }
        return nextLineData;
    };
    int lines = 0;
    auto nextLineData = getDefault();
    while (in.read_row(
        nextLineData.ItemID[0],
		nextLineData.ItermCount[0],
		nextLineData.ItemID[1],
		nextLineData.ItermCount[1],
		nextLineData.ItemID[2],
		nextLineData.ItermCount[2],
		nextLineData.ItemID[3],
		nextLineData.ItermCount[3],
		nextLineData.ItemID[4],
		nextLineData.ItermCount[4],
		nextLineData.ItemID[5],
		nextLineData.ItermCount[5],
		nextLineData.ItemID[6],
		nextLineData.ItermCount[6],
		nextLineData.ItemID[7],
		nextLineData.ItermCount[7],
		nextLineData.ItemID[8],
		nextLineData.ItermCount[8],
		nextLineData.ItemID[9],
		nextLineData.ItermCount[9],
		nextLineData.ItemID[10],
		nextLineData.ItermCount[10],
		nextLineData.ItemID[11],
		nextLineData.ItermCount[11],
		nextLineData.ItemID[12],
		nextLineData.ItermCount[12],
		nextLineData.ItemID[13],
		nextLineData.ItermCount[13],
		nextLineData.ItemID[14],
		nextLineData.ItermCount[14],
		nextLineData.ItemID[15],
		nextLineData.ItermCount[15],
		nextLineData.ItemID[16],
		nextLineData.ItermCount[16],
		nextLineData.ItemID[17],
		nextLineData.ItermCount[17],
		nextLineData.ItemID[18],
		nextLineData.ItermCount[18],
		nextLineData.ItemID[19],
		nextLineData.ItermCount[19],
		nextLineData.ItemID[20],
		nextLineData.ItermCount[20],
		nextLineData.ItemID[21],
		nextLineData.ItermCount[21],
		nextLineData.ItemID[22],
		nextLineData.ItermCount[22],
		nextLineData.ItemID[23],
		nextLineData.ItermCount[23],
		nextLineData.ItemID[24],
		nextLineData.ItermCount[24],
		nextLineData.ItemID[25],
		nextLineData.ItermCount[25],
		nextLineData.ItemID[26],
		nextLineData.ItermCount[26],
		nextLineData.ItemID[27],
		nextLineData.ItermCount[27],
		nextLineData.ItemID[28],
		nextLineData.ItermCount[28],
		nextLineData.ItemID[29],
		nextLineData.ItermCount[29],
		nextLineData.ItemID[30],
		nextLineData.ItermCount[30],
		nextLineData.ItemID[31],
		nextLineData.ItermCount[31],
		nextLineData.ItemID[32],
		nextLineData.ItermCount[32],
		nextLineData.ItemID[33],
		nextLineData.ItermCount[33],
		nextLineData.ItemID[34],
		nextLineData.ItermCount[34],
		nextLineData.ItemID[35],
		nextLineData.ItermCount[35]))
    {
        data.push_back(nextLineData);
        lines++;
        nextLineData = getDefault();
    }
}

void NewSave::LoadCSVTimeSave(std::vector<TimeInfoSave>& data, int record)
{
	data.clear();
	io::CSVReader<5, io::trim_chars<>, io::double_quote_escape<',', '\"'>> in("../game/save/csv/" + std::to_string(record) + "_����.csv");
	in.read_header(io::ignore_missing_column | io::ignore_extra_column,
		"����",
		"��",
		"��",
		"��",
		"ʱ");
	auto getDefault = []()
	{
		TimeInfoSave nextLineData;
		nextLineData.Jiazi = -1;
		nextLineData.Year = -1;
		nextLineData.Month = -1;
		nextLineData.Day = -1;
		nextLineData.Hour = -1;
		return nextLineData;
	};
	int lines = 0;
	auto nextLineData = getDefault();
	while (in.read_row(
		nextLineData.Jiazi,
		nextLineData.Year,
		nextLineData.Month,
		nextLineData.Day,
		nextLineData.Hour))
	{
		data.push_back(nextLineData);
		lines++;
		nextLineData = getDefault();
	}
}

void NewSave::LoadCSVZhaoshiSave(std::vector<ZhaoshiInfoSave>& data, int record)
{
	data.clear();
	io::CSVReader<57, io::trim_chars<>, io::double_quote_escape<',', '\"'>> in("../game/save/csv/" + std::to_string(record) + "_��ʽ.csv");
	in.read_header(io::ignore_missing_column | io::ignore_extra_column,
		"���",
		"�Č�",
		"�λ",
		"���Q",
		"�Ƿ񹥓�",
		"�����ӳ�",
		"�Ƿ����",
		"�����ӳ�",
		"�f��",
		"��Ч���",
		"��Ч����",
		"��Ч���1",
		"��Ч����1",
		"��Ч���2",
		"��Ч����2",
		"��Ч���3",
		"��Ч����3",
		"��Ч���4",
		"��Ч����4",
		"��Ч���5",
		"��Ч����5",
		"��Ч���6",
		"��Ч����6",
		"��Ч���7",
		"��Ч����7",
		"��Ч���8",
		"��Ч����8",
		"��Ч���9",
		"��Ч����9",
		"��Ч���10",
		"��Ч����10",
		"��Ч���11",
		"��Ч����11",
		"��Ч���12",
		"��Ч����12",
		"��Ч���13",
		"��Ч����13",
		"��Ч���14",
		"��Ч����14",
		"��Ч���15",
		"��Ч����15",
		"��Ч���16",
		"��Ч����16",
		"��Ч���17",
		"��Ч����17",
		"��Ч���18",
		"��Ч����18",
		"��Ч���19",
		"��Ч����19",
		"��Ч���20",
		"��Ч����20",
		"��Ч���21",
		"��Ч����21",
		"��Ч���22",
		"��Ч����22",
		"��Ч���23",
		"��Ч����23");
	auto getDefault = []()
	{
		ZhaoshiInfoSave nextLineData;
		nextLineData.daihao = -1;
			nextLineData.congshu = -1;
			nextLineData.shunwei = -1;
		memset(nextLineData.Name, '\0', sizeof(nextLineData.Name));
		nextLineData.ygongji = -1;
		nextLineData.gongji = -1;
		nextLineData.yfangyu = -1;
			nextLineData.fangyu = -1;
		memset(nextLineData.Introduction, '\0', sizeof(nextLineData.Introduction));
		for (int j = 0; j < 24; j++) {
			nextLineData.texiao[j].Type = -1;
			nextLineData.texiao[j].Value = -1;
		}

		return nextLineData;
	};
	int lines = 0;
	char* Name__;
	char* Introduction__;
	auto nextLineData = getDefault();
	while (in.read_row(
		nextLineData.daihao,
		nextLineData.congshu,
	nextLineData.shunwei,
	Name__,
	nextLineData.ygongji,
	nextLineData.gongji,
	nextLineData.yfangyu,
	nextLineData.fangyu,
		Introduction__,
		nextLineData.texiao[0].Type,
		nextLineData.texiao[0].Value,
		nextLineData.texiao[1].Type,
		nextLineData.texiao[1].Value,
		nextLineData.texiao[2].Type,
		nextLineData.texiao[2].Value,
		nextLineData.texiao[3].Type,
		nextLineData.texiao[3].Value,
		nextLineData.texiao[4].Type,
		nextLineData.texiao[4].Value,
		nextLineData.texiao[5].Type,
		nextLineData.texiao[5].Value,
		nextLineData.texiao[6].Type,
		nextLineData.texiao[6].Value,
		nextLineData.texiao[7].Type,
		nextLineData.texiao[7].Value,
		nextLineData.texiao[8].Type,
		nextLineData.texiao[8].Value,
		nextLineData.texiao[9].Type,
		nextLineData.texiao[9].Value,
		nextLineData.texiao[10].Type,
		nextLineData.texiao[10].Value,
		nextLineData.texiao[11].Type,
		nextLineData.texiao[11].Value,
		nextLineData.texiao[12].Type,
		nextLineData.texiao[12].Value,
		nextLineData.texiao[13].Type,
		nextLineData.texiao[13].Value,
		nextLineData.texiao[14].Type,
		nextLineData.texiao[14].Value,
		nextLineData.texiao[15].Type,
		nextLineData.texiao[15].Value,
		nextLineData.texiao[16].Type,
		nextLineData.texiao[16].Value,
		nextLineData.texiao[17].Type,
		nextLineData.texiao[17].Value,
		nextLineData.texiao[18].Type,
		nextLineData.texiao[18].Value,
		nextLineData.texiao[19].Type,
		nextLineData.texiao[19].Value,
		nextLineData.texiao[20].Type,
		nextLineData.texiao[20].Value,
		nextLineData.texiao[21].Type,
		nextLineData.texiao[21].Value,
		nextLineData.texiao[22].Type,
		nextLineData.texiao[22].Value,
		nextLineData.texiao[23].Type,
		nextLineData.texiao[23].Value))
	{
		strncpy(nextLineData.Introduction, Introduction__, sizeof(nextLineData.Introduction) - 1);
		strncpy(nextLineData.Name, Name__, sizeof(nextLineData.Name) - 1);
		data.push_back(nextLineData);
		lines++;
		nextLineData = getDefault();
	}
}


void NewSave::LoadCSVMenpaiSave(std::vector<MenpaiInfoSave>& data, int record)
{
	data.clear();
	io::CSVReader<114, io::trim_chars<>, io::double_quote_escape<',', '\"'>> in("../game/save/csv/" + std::to_string(record) + "_����.csv");
	in.read_header(io::ignore_missing_column | io::ignore_extra_column,
		"���",
		"���Q",
		"���c����",
		"����",
		"���T��",
		"���ӂ���",
		"�T����",
		"�T���Ɛ�",
		"�F�V",
		"ʯ��",
		"ľ��",
		"ʳ��",
		"��̿",
		"��ˎ",
		"��ľ",
		"����",
		"ϡ��",
		"���F",
		"�F�V+",
		"ʯ��+",
		"ľ��+",
		"ʳ��+",
		"��̿+",
		"��ˎ+",
		"��ľ+",
		"����+",
		"ϡ��+",
		"���F+",
		"�T�Ƀȹ�",
		"�T�Ƀȹ�1",
		"�T�Ƀȹ�2",
		"�T�Ƀȹ�3",
		"�T�Ƀȹ�4",
		"�T�Ƀȹ�5",
		"�T�Ƀȹ�6",
		"�T�Ƀȹ�7",
		"�T�Ƀȹ�8",
		"�T�Ƀȹ�9",
		"�T�Ƀȹ�10",
		"�T�Ƀȹ�11",
		"�T�Ƀȹ�12",
		"�T�Ƀȹ�13",
		"�T�Ƀȹ�14",
		"�T�Ƀȹ�15",
		"�T�Ƀȹ�16",
		"�T�Ƀȹ�17",
		"�T�Ƀȹ�18",
		"�T�Ƀȹ�19",
		"�o",
		"���R",
		"���",
		"�䮔",
		"����",
		"ȫ��",
		"��ü",
		"����",
		"���",
		"��ɽ",
		"�Aɽ",
		"��ɽ",
		"̩ɽ",
		"��ɽ",
		"Ѫ��",
		"�F��",
		"ؤ��",
		"�嶾",
		"����",
		"����",
		"ѩɽ",
		"���o",
		"���o1",
		"���o2",
		"���o3",
		"���o4",
		"���b",
		"����",
		"�L��",
		"�R��",
		"��ϼ",
		"�˘O",
		"��ţ",
		"�o��",
		"Ұ��",
		"Ұ�R",
		"����",
		"�ۄ�",
		"����",
		"����",
		"�T����",
		"�T����1",
		"�T����2",
		"�T����3",
		"�T����4",
		"�T����5",
		"�T����6",
		"�T����7",
		"�T����8",
		"�T����9",
		"�U���A��",
		"�е��ӃA��",
		"���ӳ��L�ٶ�",
		"���",
		"�е������D",
		"�е����^��",
		"Ů�������D",
		"Ů�����^��",
		"�����Ԅe",
		"�������",
		"���T�¼�",
		"ͬ��",
		"���Ҙ�ӛ",
		"δ���x2",
		"δ���x3",
		"δ���x4");
	auto getDefault = []()
	{
		MenpaiInfoSave nextLineData;
		nextLineData.num = -1;
		memset(nextLineData.Name, '\0', sizeof(nextLineData.Name));
		nextLineData.jvdian = -1;
			nextLineData.zongduo = -1;
			nextLineData.zmr = -1;
			nextLineData.dizi = -1;
			nextLineData.shengwang = -1;
			nextLineData.shane = -1;
			for (int j = 0; j < 10; j++) {
				nextLineData.ziyuan[j] = -1;
			};
		for (int j = 0; j < 10; j++) {
			nextLineData.aziyuan[j] = -1;
		};
		for (int j = 0; j < 20; j++) {
			nextLineData.neigong[j] = -1;
		};
		for (int j = 0; j < 40; j++) {
			nextLineData.guanxi[j] = -1;
		};
		for (int j = 0; j < 10; j++) {
			nextLineData.zhiwu[j] = -1;
		};
		nextLineData.kzq = -1; 
			nextLineData.dzq = -1;
			nextLineData.czsd = -1;
			nextLineData.qizhi = -1;
			nextLineData.mdizigrp = -1;
			nextLineData.mdizipic = -1;
			nextLineData.fdizigrp = -1;
			nextLineData.fdizipic = -1;
			nextLineData.sexy = -1;
			nextLineData.identity = -1;
			nextLineData.endevent = -1;
			nextLineData.tongmeng = -1;
			nextLineData.israndomed = -1;
			nextLineData.unuse2 = -1;
			nextLineData.unuse3 = -1;
			nextLineData.unuse4 = -1;
		return nextLineData;
	};
	int lines = 0;
	char* Name__;
	auto nextLineData = getDefault();
	while (in.read_row(
		nextLineData.num,
		Name__,
		nextLineData.jvdian,
		nextLineData.zongduo,
		nextLineData.zmr,
		nextLineData.dizi,
		nextLineData.shengwang,
		nextLineData.shane,
		nextLineData.ziyuan[0],
		nextLineData.ziyuan[1],
		nextLineData.ziyuan[2],
		nextLineData.ziyuan[3],
		nextLineData.ziyuan[4],
		nextLineData.ziyuan[5],
		nextLineData.ziyuan[6],
		nextLineData.ziyuan[7],
		nextLineData.ziyuan[8],
		nextLineData.ziyuan[9],
		nextLineData.aziyuan[0],
		nextLineData.aziyuan[1],
		nextLineData.aziyuan[2],
		nextLineData.aziyuan[3],
		nextLineData.aziyuan[4],
		nextLineData.aziyuan[5],
		nextLineData.aziyuan[6],
		nextLineData.aziyuan[7],
		nextLineData.aziyuan[8],
		nextLineData.aziyuan[9],
		nextLineData.neigong[0],
		nextLineData.neigong[1],
		nextLineData.neigong[2],
		nextLineData.neigong[3],
		nextLineData.neigong[4],
		nextLineData.neigong[5],
		nextLineData.neigong[6],
		nextLineData.neigong[7],
		nextLineData.neigong[8],
		nextLineData.neigong[9],
		nextLineData.neigong[10],
		nextLineData.neigong[11],
		nextLineData.neigong[12],
		nextLineData.neigong[13],
		nextLineData.neigong[14],
		nextLineData.neigong[15],
		nextLineData.neigong[16],
		nextLineData.neigong[17],
		nextLineData.neigong[18],
		nextLineData.neigong[19],
		nextLineData.guanxi[0],
		nextLineData.guanxi[1],
		nextLineData.guanxi[2],
		nextLineData.guanxi[3],
		nextLineData.guanxi[4],
		nextLineData.guanxi[5],
		nextLineData.guanxi[6],
		nextLineData.guanxi[7],
		nextLineData.guanxi[8],
		nextLineData.guanxi[9],
		nextLineData.guanxi[10],
		nextLineData.guanxi[11],
		nextLineData.guanxi[12],
		nextLineData.guanxi[13],
		nextLineData.guanxi[14],
		nextLineData.guanxi[15],
		nextLineData.guanxi[16],
		nextLineData.guanxi[17],
		nextLineData.guanxi[18],
		nextLineData.guanxi[19],
		nextLineData.guanxi[20],
		nextLineData.guanxi[21],
		nextLineData.guanxi[22],
		nextLineData.guanxi[23],
		nextLineData.guanxi[24],
		nextLineData.guanxi[25],
		nextLineData.guanxi[26],
		nextLineData.guanxi[27],
		nextLineData.guanxi[28],
		nextLineData.guanxi[29],
		nextLineData.guanxi[30],
		nextLineData.guanxi[31],
		nextLineData.guanxi[32],
		nextLineData.guanxi[33],
		nextLineData.guanxi[34],
		nextLineData.guanxi[35],
		nextLineData.guanxi[36],
		nextLineData.guanxi[37],
		nextLineData.guanxi[38],
		nextLineData.guanxi[39],
		nextLineData.zhiwu[0],
		nextLineData.zhiwu[1],
		nextLineData.zhiwu[2],
		nextLineData.zhiwu[3],
		nextLineData.zhiwu[4],
		nextLineData.zhiwu[5],
		nextLineData.zhiwu[6],
		nextLineData.zhiwu[7],
		nextLineData.zhiwu[8],
		nextLineData.zhiwu[9],
		nextLineData.kzq,
		nextLineData.dzq,
		nextLineData.czsd,
		nextLineData.qizhi,
		nextLineData.mdizigrp,
		nextLineData.mdizipic,
		nextLineData.fdizigrp,
		nextLineData.fdizipic,
		nextLineData.sexy,
		nextLineData.identity,
		nextLineData.endevent,
		nextLineData.tongmeng,
		nextLineData.israndomed,
		nextLineData.unuse2,
		nextLineData.unuse3,
		nextLineData.unuse4))
	{
		strncpy(nextLineData.Name, Name__, sizeof(nextLineData.Name) - 1);
		data.push_back(nextLineData);
		lines++;
		nextLineData = getDefault();
	}
}


void NewSave::LoadCSVRSignSave(std::vector<RSign>& data, int record)
{
	data.clear();
	io::CSVReader<55, io::trim_chars<>, io::double_quote_escape<',', '\"'>> in("../game/save/csv/" + std::to_string(record) + "_��ʽ.csv");
	in.read_header(io::ignore_missing_column | io::ignore_extra_column,
		"��̖",
		"���Q",
		"Ч��",
		"e",
		"�f��",
		"�f��",
		"�Ƿ��[��",
		"��Ч���",
		"��Ч����",
		"��Ч���1",
		"��Ч����1",
		"��Ч���2",
		"��Ч����2",
		"��Ч���3",
		"��Ч����3",
		"��Ч���4",
		"��Ч����4",
		"��Ч���5",
		"��Ч����5",
		"��Ч���6",
		"��Ч����6",
		"��Ч���7",
		"��Ч����7",
		"��Ч���8",
		"��Ч����8",
		"��Ч���9",
		"��Ч����9",
		"��Ч���10",
		"��Ч����10",
		"��Ч���11",
		"��Ч����11",
		"��Ч���12",
		"��Ч����12",
		"��Ч���13",
		"��Ч����13",
		"��Ч���14",
		"��Ч����14",
		"��Ч���15",
		"��Ч����15",
		"��Ч���16",
		"��Ч����16",
		"��Ч���17",
		"��Ч����17",
		"��Ч���18",
		"��Ч����18",
		"��Ч���19",
		"��Ч����19",
		"��Ч���20",
		"��Ч����20",
		"��Ч���21",
		"��Ч����21",
		"��Ч���22",
		"��Ч����22",
		"��Ч���23",
		"��Ч����23");
	auto getDefault = []()
	{
		RSign nextLineData;
		nextLineData.num = -1;
		memset(nextLineData.Name, '\0', sizeof(nextLineData.Name));
		nextLineData.effert = -1;
		nextLineData.TypeNum = -1;
		memset(nextLineData.Introduction, '\0', sizeof(nextLineData.Introduction));
		nextLineData.beiyong = -1;
		nextLineData.isshow = -1;
		for (int j = 0; j < 24; j++) {
			nextLineData.texiao[j].Type = -1;
			nextLineData.texiao[j].Value = -1;
		}

		return nextLineData;
	};
	int lines = 0;
	char* Name__;
	char* Introduction__;
	auto nextLineData = getDefault();
	while (in.read_row(
		nextLineData.num,
		Name__,
		nextLineData.effert,
		nextLineData.TypeNum,
		Introduction__,
		nextLineData.beiyong,
			nextLineData.isshow, //44
		nextLineData.texiao[0].Type,
		nextLineData.texiao[0].Value,
		nextLineData.texiao[1].Type,
		nextLineData.texiao[1].Value,
		nextLineData.texiao[2].Type,
		nextLineData.texiao[2].Value,
		nextLineData.texiao[3].Type,
		nextLineData.texiao[3].Value,
		nextLineData.texiao[4].Type,
		nextLineData.texiao[4].Value,
		nextLineData.texiao[5].Type,
		nextLineData.texiao[5].Value,
		nextLineData.texiao[6].Type,
		nextLineData.texiao[6].Value,
		nextLineData.texiao[7].Type,
		nextLineData.texiao[7].Value,
		nextLineData.texiao[8].Type,
		nextLineData.texiao[8].Value,
		nextLineData.texiao[9].Type,
		nextLineData.texiao[9].Value,
		nextLineData.texiao[10].Type,
		nextLineData.texiao[10].Value,
		nextLineData.texiao[11].Type,
		nextLineData.texiao[11].Value,
		nextLineData.texiao[12].Type,
		nextLineData.texiao[12].Value,
		nextLineData.texiao[13].Type,
		nextLineData.texiao[13].Value,
		nextLineData.texiao[14].Type,
		nextLineData.texiao[14].Value,
		nextLineData.texiao[15].Type,
		nextLineData.texiao[15].Value,
		nextLineData.texiao[16].Type,
		nextLineData.texiao[16].Value,
		nextLineData.texiao[17].Type,
		nextLineData.texiao[17].Value,
		nextLineData.texiao[18].Type,
		nextLineData.texiao[18].Value,
		nextLineData.texiao[19].Type,
		nextLineData.texiao[19].Value,
		nextLineData.texiao[20].Type,
		nextLineData.texiao[20].Value,
		nextLineData.texiao[21].Type,
		nextLineData.texiao[21].Value,
		nextLineData.texiao[22].Type,
		nextLineData.texiao[22].Value,
		nextLineData.texiao[23].Type,
		nextLineData.texiao[23].Value))
	{
		strncpy(nextLineData.Introduction, Introduction__, sizeof(nextLineData.Introduction) - 1);
		strncpy(nextLineData.Name, Name__, sizeof(nextLineData.Name) - 1);
		data.push_back(nextLineData);
		lines++;
		nextLineData = getDefault();
	}
}


void NewSave::InsertRoleAt(std::vector<Role>& data, int idx)
{
    auto newCopy = data[idx];
    data.insert(data.begin() + idx, newCopy);
    for (int i = 0; i < data.size(); i++)
    {
        data[i].ID = i;
    }
    Save::getInstance()->updateAllPtrVector();
    for (int i = 0; i < 1; i++)
    {
        auto p = Save::getInstance();
        if (p->Team[0] >= idx)
        {
            p->Team[0] += 1;
        }
        if (p->Team[1] >= idx)
        {
            p->Team[1] += 1;
        }
        if (p->Team[2] >= idx)
        {
            p->Team[2] += 1;
        }
        if (p->Team[3] >= idx)
        {
            p->Team[3] += 1;
        }
        if (p->Team[4] >= idx)
        {
            p->Team[4] += 1;
        }
        if (p->Team[5] >= idx)
        {
            p->Team[5] += 1;
        }
    }
    for (auto& p : Save::getInstance()->getItems())
    {
        if (p->User >= idx)
        {
            p->User += 1;
        }
        if (p->OnlySuitableRole >= idx)
        {
            p->OnlySuitableRole += 1;
        }
    }
}


void NewSave::InsertItemAt(std::vector<Item>& data, int idx)
{
    auto newCopy = data[idx];
    data.insert(data.begin() + idx, newCopy);
    for (int i = 0; i < data.size(); i++)
    {
        data[i].ID = i;
    }
    Save::getInstance()->updateAllPtrVector();
    for (int i = 0; i < ITEM_IN_BAG_COUNT; i++)
    {
        auto* p = &(Save::getInstance()->Items[i]);
        if (p->item_id >= idx)
        {
            p->item_id += 1;
        }
    }
    for (auto& p : Save::getInstance()->getRoles())
    {
        if (p->Equip[0] >= idx)
        {
            p->Equip[0] += 1;
        }
        if (p->Equip[1] >= idx)
        {
            p->Equip[1] += 1;
        }
		if (p->Equip[2] >= idx)
		{
			p->Equip[2] += 1;
		}
		if (p->Equip[3] >= idx)
		{
			p->Equip[3] += 1;
		}
        if (p->PracticeItem >= idx)
        {
            p->PracticeItem += 1;
        }
        if (p->TakingItem[0] >= idx)
        {
            p->TakingItem[0] += 1;
        }
        if (p->TakingItem[1] >= idx)
        {
            p->TakingItem[1] += 1;
        }
        if (p->TakingItem[2] >= idx)
        {
            p->TakingItem[2] += 1;
        }
        if (p->TakingItem[3] >= idx)
        {
            p->TakingItem[3] += 1;
        }
    }
    for (auto& p : Save::getInstance()->getItems())
    {
        if (p->NeedMaterial >= idx)
        {
            p->NeedMaterial += 1;
        }
        if (p->MakeItem[0] >= idx)
        {
            p->MakeItem[0] += 1;
        }
        if (p->MakeItem[1] >= idx)
        {
            p->MakeItem[1] += 1;
        }
        if (p->MakeItem[2] >= idx)
        {
            p->MakeItem[2] += 1;
        }
        if (p->MakeItem[3] >= idx)
        {
            p->MakeItem[3] += 1;
        }
        if (p->MakeItem[4] >= idx)
        {
            p->MakeItem[4] += 1;
        }
    }
    for (auto& p : Save::getInstance()->getShops())
    {
        if (p->ItemID[0] >= idx)
        {
            p->ItemID[0] += 1;
        }
        if (p->ItemID[1] >= idx)
        {
            p->ItemID[1] += 1;
        }
        if (p->ItemID[2] >= idx)
        {
            p->ItemID[2] += 1;
        }
        if (p->ItemID[3] >= idx)
        {
            p->ItemID[3] += 1;
        }
        if (p->ItemID[4] >= idx)
        {
            p->ItemID[4] += 1;
        }
    }
}
void NewSave::InsertSubMapInfoAt(std::vector<SubMapInfo>& data, int idx)
{
    auto newCopy = data[idx];
    data.insert(data.begin() + idx, newCopy);
    for (int i = 0; i < data.size(); i++)
    {
        data[i].ID = i;
    }
    Save::getInstance()->updateAllPtrVector();
}
void NewSave::InsertMagicAt(std::vector<Magic>& data, int idx)
{
    auto newCopy = data[idx];
    data.insert(data.begin() + idx, newCopy);
    for (int i = 0; i < data.size(); i++)
    {
        data[i].ID = i;
    }
    Save::getInstance()->updateAllPtrVector();
    for (auto& p : Save::getInstance()->getRoles())
    {
        if (p->MagicID[0] >= idx)
        {
            p->MagicID[0] += 1;
        }
        if (p->MagicID[1] >= idx)
        {
            p->MagicID[1] += 1;
        }
        if (p->MagicID[2] >= idx)
        {
            p->MagicID[2] += 1;
        }
        if (p->MagicID[3] >= idx)
        {
            p->MagicID[3] += 1;
        }
        if (p->MagicID[4] >= idx)
        {
            p->MagicID[4] += 1;
        }
        if (p->MagicID[5] >= idx)
        {
            p->MagicID[5] += 1;
        }
        if (p->MagicID[6] >= idx)
        {
            p->MagicID[6] += 1;
        }
        if (p->MagicID[7] >= idx)
        {
            p->MagicID[7] += 1;
        }
        if (p->MagicID[8] >= idx)
        {
            p->MagicID[8] += 1;
        }
        if (p->MagicID[9] >= idx)
        {
            p->MagicID[9] += 1;
        }
    }
    for (auto& p : Save::getInstance()->getItems())
    {
        if (p->MagicID >= idx)
        {
            p->MagicID += 1;
        }
    }
}
void NewSave::InsertShopAt(std::vector<Shop>& data, int idx)
{
    auto newCopy = data[idx];
    data.insert(data.begin() + idx, newCopy);
    for (int i = 0; i < data.size(); i++)
    {
        // data[i].ID = i;
    }
    Save::getInstance()->updateAllPtrVector();
}

NewSave NewSave::new_save_;

#define GET_OFFSET(field) (int((char*)(&(a.field)) - (char*)(&a)))
#define BIND_FIELD_INT(key, field) FieldInfo(key, 0, GET_OFFSET(field), sizeof(a.field))
#define BIND_FIELD_TEXT(key, field) FieldInfo(key, 1, GET_OFFSET(field), sizeof(a.field))

void NewSave::initDBFieldInfo()
{
    if (new_save_.base_.size() == 0)
    {
        Save::BaseInfo a;
        new_save_.base_ =
        {
            BIND_FIELD_INT("�˴�", InShip),
            BIND_FIELD_INT("�ӳ�����", InSubMap),
            BIND_FIELD_INT("����ͼX", MainMapX),
            BIND_FIELD_INT("����ͼY", MainMapY),
            BIND_FIELD_INT("�ӳ���X", SubMapX),
            BIND_FIELD_INT("�ӳ���Y", SubMapY),
            BIND_FIELD_INT("�泯����", FaceTowards),
            BIND_FIELD_INT("��X", ShipX),
            BIND_FIELD_INT("��Y", ShipY),
			BIND_FIELD_INT("��X1",TimeCount),       
			BIND_FIELD_INT("��Y1", TimeEvent),
            BIND_FIELD_INT("�ڲ�����", RandomEvent),
            BIND_FIELD_INT("����1", Team[0]),
            BIND_FIELD_INT("����2", Team[1]),
            BIND_FIELD_INT("����3", Team[2]),
            BIND_FIELD_INT("����4", Team[3]),
            BIND_FIELD_INT("����5", Team[4]),
            BIND_FIELD_INT("����6", Team[5]),
        };
    }
    if (new_save_.item_list_.size() == 0)
    {
        ItemList a;
        new_save_.item_list_ =
        {
            BIND_FIELD_INT("��Ʒ���", item_id),
            BIND_FIELD_INT("��Ʒ����", count),
        };
    }
    if (new_save_.role_.size() == 0)
    {
        Role a;
        new_save_.role_ =
        {
            BIND_FIELD_INT("���", ID),
            BIND_FIELD_INT("ͷ��", HeadID),
            BIND_FIELD_INT("�����ɳ�", IncLife),
            BIND_FIELD_INT("��Դ", Fuyuan),
            BIND_FIELD_TEXT("����", Name),
            BIND_FIELD_TEXT("���", Nick),
            BIND_FIELD_INT("�Ա�", Sexual),
            BIND_FIELD_INT("�ȼ�", Level),
            BIND_FIELD_INT("����", Exp),
            BIND_FIELD_INT("����", HP),
            BIND_FIELD_INT("�������ֵ", MaxHP),
            BIND_FIELD_INT("����", Hurt),
            BIND_FIELD_INT("�ж�", Poison),
            BIND_FIELD_INT("����", PhysicalPower),
            BIND_FIELD_INT("����", Equip[0]),
            BIND_FIELD_INT("����", Equip[1]),
			BIND_FIELD_INT("Ь��", Equip[3]),
			BIND_FIELD_INT("��Ʒ", Equip[3]),

            BIND_FIELD_INT("��������", MPType),
            BIND_FIELD_INT("����", MP),
            BIND_FIELD_INT("�������ֵ", MaxMP),
            BIND_FIELD_INT("������", Attack),
            BIND_FIELD_INT("�Ṧ", Speed),
            BIND_FIELD_INT("������", Defence),
            BIND_FIELD_INT("ҽ��", Medicine),
            BIND_FIELD_INT("�ö�", UsePoison),
            BIND_FIELD_INT("�ⶾ", Detoxification),
            BIND_FIELD_INT("����", AntiPoison),
            BIND_FIELD_INT("ȭ��", Fist),
            BIND_FIELD_INT("����", Sword),
            BIND_FIELD_INT("ˣ��", Knife),
            BIND_FIELD_INT("����", Unusual),
            BIND_FIELD_INT("����", HiddenWeapon),
            BIND_FIELD_INT("��ѧ��ʶ", Knowledge),
            BIND_FIELD_INT("Ʒ��", Morality),
            BIND_FIELD_INT("��������", AttackWithPoison),
            BIND_FIELD_INT("���һ���", AttackTwice),
            BIND_FIELD_INT("����", Fame),
            BIND_FIELD_INT("����", IQ),
            BIND_FIELD_INT("������Ʒ", PracticeItem),
            BIND_FIELD_INT("��������", ExpForItem),
            BIND_FIELD_INT("�����书1", MagicID[0]),
            BIND_FIELD_INT("�����书2", MagicID[1]),
            BIND_FIELD_INT("�����书3", MagicID[2]),
            BIND_FIELD_INT("�����书4", MagicID[3]),
            BIND_FIELD_INT("�����书5", MagicID[4]),
            BIND_FIELD_INT("�����书6", MagicID[5]),
            BIND_FIELD_INT("�����书7", MagicID[6]),
            BIND_FIELD_INT("�����书8", MagicID[7]),
            BIND_FIELD_INT("�����书9", MagicID[8]),
            BIND_FIELD_INT("�����书10", MagicID[9]),
            BIND_FIELD_INT("�书�ȼ�1", MagicLevel[0]),
            BIND_FIELD_INT("�书�ȼ�2", MagicLevel[1]),
            BIND_FIELD_INT("�书�ȼ�3", MagicLevel[2]),
            BIND_FIELD_INT("�书�ȼ�4", MagicLevel[3]),
            BIND_FIELD_INT("�书�ȼ�5", MagicLevel[4]),
            BIND_FIELD_INT("�书�ȼ�6", MagicLevel[5]),
            BIND_FIELD_INT("�书�ȼ�7", MagicLevel[6]),
            BIND_FIELD_INT("�书�ȼ�8", MagicLevel[7]),
            BIND_FIELD_INT("�书�ȼ�9", MagicLevel[8]),
            BIND_FIELD_INT("�书�ȼ�10", MagicLevel[9]),
            BIND_FIELD_INT("Я����Ʒ1", TakingItem[0]),
            BIND_FIELD_INT("Я����Ʒ2", TakingItem[1]),
            BIND_FIELD_INT("Я����Ʒ3", TakingItem[2]),
            BIND_FIELD_INT("Я����Ʒ4", TakingItem[3]),
            BIND_FIELD_INT("Я����Ʒ����1", TakingItemCount[0]),
            BIND_FIELD_INT("Я����Ʒ����2", TakingItemCount[1]),
            BIND_FIELD_INT("Я����Ʒ����3", TakingItemCount[2]),
            BIND_FIELD_INT("Я����Ʒ����4", TakingItemCount[3]),
        };
    }
    if (new_save_.item_.size() == 0)
    {
        Item a;
        new_save_.item_ =
        {
            BIND_FIELD_INT("���", ID),
            BIND_FIELD_TEXT("��Ʒ��", Name),


            BIND_FIELD_TEXT("��Ʒ˵��", Introduction),
            BIND_FIELD_INT("�����书", MagicID),
            BIND_FIELD_INT("�����������", HiddenWeaponEffectID),
            BIND_FIELD_INT("ʹ����", User),
            BIND_FIELD_INT("װ������", EquipType),
            BIND_FIELD_INT("��ʾ��Ʒ˵��", ShowIntroduction),
            BIND_FIELD_INT("��Ʒ����", ItemType),

			
			BIND_FIELD_INT("������", AddHP),
            BIND_FIELD_INT("���������ֵ", AddMaxHP),
            BIND_FIELD_INT("���ж��ⶾ", AddPoison),
            BIND_FIELD_INT("������", AddPhysicalPower),
            BIND_FIELD_INT("�ı���������", ChangeMPType),
            BIND_FIELD_INT("������", AddMP),
            BIND_FIELD_INT("���������ֵ", AddMaxMP),
            BIND_FIELD_INT("�ӹ�����", AddAttack),
            BIND_FIELD_INT("���Ṧ", AddSpeed),
            BIND_FIELD_INT("�ӷ�����", AddDefence),
            BIND_FIELD_INT("��ҽ��", AddMedicine),
            BIND_FIELD_INT("��ʹ��", AddUsePoison),
            BIND_FIELD_INT("�ӽⶾ", AddDetoxification),
            BIND_FIELD_INT("�ӿ���", AddAntiPoison),
            BIND_FIELD_INT("��ȭ��", AddFist),
            BIND_FIELD_INT("������", AddSword),
            BIND_FIELD_INT("��ˣ��", AddKnife),
            BIND_FIELD_INT("���������", AddUnusual),
            BIND_FIELD_INT("�Ӱ�������", AddHiddenWeapon),
            BIND_FIELD_INT("����ѧ��ʶ", AddKnowledge),
            BIND_FIELD_INT("��Ʒ��", AddMorality),
            BIND_FIELD_INT("�����һ���", AddAttackTwice),
            BIND_FIELD_INT("�ӹ�������", AddAttackWithPoison),
            BIND_FIELD_INT("����������", OnlySuitableRole),
            BIND_FIELD_INT("����������", NeedMPType),
            BIND_FIELD_INT("������", NeedMP),
            BIND_FIELD_INT("�蹥����", NeedAttack),
            BIND_FIELD_INT("���Ṧ", NeedSpeed),
            BIND_FIELD_INT("���ö�", NeedUsePoison),
            BIND_FIELD_INT("��ҽ��", NeedMedicine),
            BIND_FIELD_INT("��ⶾ", NeedDetoxification),
            BIND_FIELD_INT("��ȭ��", NeedFist),
            BIND_FIELD_INT("������", NeedSword),
            BIND_FIELD_INT("��ˣ��", NeedKnife),
            BIND_FIELD_INT("���������", NeedUnusual),
            BIND_FIELD_INT("�谵��", NeedHiddenWeapon),
            BIND_FIELD_INT("������", NeedIQ),
            BIND_FIELD_INT("�辭��", NeedExp),
            BIND_FIELD_INT("������Ʒ�辭��", NeedExpForMakeItem),
            BIND_FIELD_INT("�����", NeedMaterial),
            BIND_FIELD_INT("������Ʒ1", MakeItem[0]),
            BIND_FIELD_INT("������Ʒ2", MakeItem[1]),
            BIND_FIELD_INT("������Ʒ3", MakeItem[2]),
            BIND_FIELD_INT("������Ʒ4", MakeItem[3]),
            BIND_FIELD_INT("������Ʒ5", MakeItem[4]),
            BIND_FIELD_INT("������Ʒ����1", MakeItemCount[0]),
            BIND_FIELD_INT("������Ʒ����2", MakeItemCount[1]),
            BIND_FIELD_INT("������Ʒ����3", MakeItemCount[2]),
            BIND_FIELD_INT("������Ʒ����4", MakeItemCount[3]),
            BIND_FIELD_INT("������Ʒ����5", MakeItemCount[4]),
        };
    }
    if (new_save_.submap_.size() == 0)
    {
        SubMapInfo a;
        new_save_.submap_ =
        {
            BIND_FIELD_INT("���", ID),
            BIND_FIELD_TEXT("����", Name),
            BIND_FIELD_INT("��������", ExitMusic),
            BIND_FIELD_INT("��������", EntranceMusic),
            BIND_FIELD_INT("��ת����", JumpSubMap),
            BIND_FIELD_INT("��������", EntranceCondition),
            BIND_FIELD_INT("�⾰���X1", MainEntranceX1),
            BIND_FIELD_INT("�⾰���Y1", MainEntranceY1),
            BIND_FIELD_INT("�⾰���X2", MainEntranceX2),
            BIND_FIELD_INT("�⾰���Y2", MainEntranceY2),
            BIND_FIELD_INT("���X", EntranceX),
            BIND_FIELD_INT("���Y", EntranceY),
            BIND_FIELD_INT("����X1", ExitX[0]),
            BIND_FIELD_INT("����X2", ExitX[1]),
            BIND_FIELD_INT("����X3", ExitX[2]),
            BIND_FIELD_INT("����Y1", ExitY[0]),
            BIND_FIELD_INT("����Y2", ExitY[1]),
            BIND_FIELD_INT("����Y3", ExitY[2]),

        };
    }
    if (new_save_.magic_.size() == 0)
    {
        Magic a;
        new_save_.magic_ =
        {
            BIND_FIELD_INT("���", ID),
            BIND_FIELD_TEXT("����", Name),

            BIND_FIELD_INT("������Ч", SoundID),
            BIND_FIELD_INT("�书����", MagicType),
            BIND_FIELD_INT("�书����", EffectID),
            BIND_FIELD_INT("�˺�����", HurtType),
            BIND_FIELD_INT("������Χ����", AttackAreaType),
            BIND_FIELD_INT("��������", NeedMP),
            BIND_FIELD_INT("�����ж�", WithPoison),

            BIND_FIELD_INT("�ƶ���Χ1", SelectDistance[0]),
            BIND_FIELD_INT("�ƶ���Χ2", SelectDistance[1]),
            BIND_FIELD_INT("�ƶ���Χ3", SelectDistance[2]),
            BIND_FIELD_INT("�ƶ���Χ4", SelectDistance[3]),
            BIND_FIELD_INT("�ƶ���Χ5", SelectDistance[4]),
            BIND_FIELD_INT("�ƶ���Χ6", SelectDistance[5]),
            BIND_FIELD_INT("�ƶ���Χ7", SelectDistance[6]),
            BIND_FIELD_INT("�ƶ���Χ8", SelectDistance[7]),
            BIND_FIELD_INT("�ƶ���Χ9", SelectDistance[8]),
            BIND_FIELD_INT("�ƶ���Χ10", SelectDistance[9]),
            BIND_FIELD_INT("ɱ�˷�Χ1", AttackDistance[0]),
            BIND_FIELD_INT("ɱ�˷�Χ2", AttackDistance[1]),
            BIND_FIELD_INT("ɱ�˷�Χ3", AttackDistance[2]),
            BIND_FIELD_INT("ɱ�˷�Χ4", AttackDistance[3]),
            BIND_FIELD_INT("ɱ�˷�Χ5", AttackDistance[4]),
            BIND_FIELD_INT("ɱ�˷�Χ6", AttackDistance[5]),
            BIND_FIELD_INT("ɱ�˷�Χ7", AttackDistance[6]),
            BIND_FIELD_INT("ɱ�˷�Χ8", AttackDistance[7]),
            BIND_FIELD_INT("ɱ�˷�Χ9", AttackDistance[8]),
            BIND_FIELD_INT("ɱ�˷�Χ10", AttackDistance[9]),
            BIND_FIELD_INT("������1", AddMP[0]),
            BIND_FIELD_INT("������2", AddMP[1]),
            BIND_FIELD_INT("������3", AddMP[2]),
            BIND_FIELD_INT("������4", AddMP[3]),
            BIND_FIELD_INT("������5", AddMP[4]),
            BIND_FIELD_INT("������6", AddMP[5]),
            BIND_FIELD_INT("������7", AddMP[6]),
            BIND_FIELD_INT("������8", AddMP[7]),
            BIND_FIELD_INT("������9", AddMP[8]),
            BIND_FIELD_INT("������10", AddMP[9]),

        };
    }
    if (new_save_.shop_.size() == 0)
    {
        Shop a;
        new_save_.shop_ =
        {
            BIND_FIELD_INT("��Ʒ���1", ItemID[0]),
            BIND_FIELD_INT("��Ʒ���2", ItemID[1]),
            BIND_FIELD_INT("��Ʒ���3", ItemID[2]),
            BIND_FIELD_INT("��Ʒ���4", ItemID[3]),
            BIND_FIELD_INT("��Ʒ���5", ItemID[4]),

        };
    }
}

void NewSave::SaveDBBaseInfo(sqlite3* db, Save::BaseInfo* data, int length)
{
    sqlite3_exec(db, "delete from base", nullptr, nullptr, nullptr);
    std::string cmd = "insert into base values(";
    for (auto& info : new_save_.base_)
    {
        cmd += std::to_string(*(int*)((char*)data + info.offset)) + ",";
    }
    cmd.pop_back();
    cmd += ")";
    sqlite3_exec(db, cmd.c_str(), nullptr, nullptr, nullptr);
}

void NewSave::LoadDBBaseInfo(sqlite3* db, Save::BaseInfo* data, int length)
{
    std::vector<Save::BaseInfo> datas;
    readValues(db, "base", new_save_.base_, datas);
    *data = datas[0];
}

void NewSave::SaveDBItemList(sqlite3* db, ItemList* data, int length)
{
    std::vector<ItemList> itemlist(length);
    for (int i = 0; i < length; i++)
    {
        itemlist[i] = data[i];
    }
    writeValues(db, "bag", new_save_.item_list_, itemlist);
}

void NewSave::LoadDBItemList(sqlite3* db, ItemList* data, int length)
{
    std::vector<ItemList> itemlist;
    readValues(db, "bag", new_save_.item_list_, itemlist);
    for (int i = 0; i < length; i++)
    {
        data[i] = itemlist[i];
    }
}

void NewSave::SaveDBRoleSave(sqlite3* db, const std::vector<Role>& data)
{
    writeValues(db, "role", new_save_.role_, data);
}

void NewSave::LoadDBRoleSave(sqlite3* db, std::vector<Role>& data)
{
    readValues(db, "role", new_save_.role_, data);
}

void NewSave::SaveDBItemSave(sqlite3* db, const std::vector<Item>& data)
{
    writeValues(db, "item", new_save_.item_, data);
}

void NewSave::LoadDBItemSave(sqlite3* db, std::vector<Item>& data)
{
    readValues(db, "item", new_save_.item_, data);
}

void NewSave::SaveDBSubMapInfoSave(sqlite3* db, const std::vector<SubMapInfo>& data)
{
    writeValues(db, "submap", new_save_.submap_, data);
}

void NewSave::LoadDBSubMapInfoSave(sqlite3* db, std::vector<SubMapInfo>& data)
{
    readValues(db, "submap", new_save_.submap_, data);
}

void NewSave::SaveDBMagicSave(sqlite3* db, const std::vector<Magic>& data)
{
    writeValues(db, "magic", new_save_.magic_, data);
}

void NewSave::LoadDBMagicSave(sqlite3* db, std::vector<Magic>& data)
{
	readValues(db, "magic", new_save_.magic_, data);
}

void NewSave::SaveDBShopSave(sqlite3* db, const std::vector<Shop>& data)
{
    writeValues(db, "shop", new_save_.shop_, data);
}

void NewSave::LoadDBShopSave(sqlite3* db, std::vector<Shop>& data)
{
    readValues(db, "shop", new_save_.shop_, data);
}
