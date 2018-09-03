#pragma once
#include "Save.h"
#include <string>

class RoleTranslate {
public:
	static std::string getVal(Role* r, const std::string& chn)
	{
		if (chn == "��̖")
		{
			return std::to_string(r->ID);
		}
		else if (chn == "�^��")
		{
			return std::to_string(r->HeadID);
		}
		else if (chn == "�������L")
		{
			return std::to_string(r->IncLife);
		}
		else if (chn == "�o��")
		{
			return std::to_string(r->UnUse);
		}
		else if (chn == "����")
		{
			return r->Name;
		}
		else if (chn == "��̖")
		{
			return r->Nick;
		}
		else if (chn == "�Ԅe")
		{
			return std::to_string(r->Sexual);
		}
		else if (chn == "�ȼ�")
		{
			return std::to_string(r->Level);
		}
		else if (chn == "���")
		{
			return std::to_string(r->Exp);
		}
		else if (chn == "����")
		{
			return std::to_string(r->HP);
		}
		else if (chn == "�������ֵ")
		{
			return std::to_string(r->MaxHP);
		}
		else if (chn == "�Ȃ�")
		{
			return std::to_string(r->Hurt);
		}
		else if (chn == "�ж�")
		{
			return std::to_string(r->Poison);
		}
		else if (chn == "�w��")
		{
			return std::to_string(r->PhysicalPower);
		}
		else if (chn == "��Ʒ�ޟ��c��")
		{
			return std::to_string(r->ExpForMakeItem);
		}
		else if (chn == "����")
		{
			return std::to_string(r->Equip0);
		}
		else if (chn == "����")
		{
			return std::to_string(r->Equip1);
		}
		else if (chn == "��������1")
		{
			return std::to_string(r->Frame[0]);
		}
		else if (chn == "��������2")
		{
			return std::to_string(r->Frame[1]);
		}
		else if (chn == "��������3")
		{
			return std::to_string(r->Frame[2]);
		}
		else if (chn == "��������4")
		{
			return std::to_string(r->Frame[3]);
		}
		else if (chn == "��������5")
		{
			return std::to_string(r->Frame[4]);
		}
		else if (chn == "��������6")
		{
			return std::to_string(r->Frame[5]);
		}
		else if (chn == "��������7")
		{
			return std::to_string(r->Frame[6]);
		}
		else if (chn == "��������8")
		{
			return std::to_string(r->Frame[7]);
		}
		else if (chn == "��������9")
		{
			return std::to_string(r->Frame[8]);
		}
		else if (chn == "��������10")
		{
			return std::to_string(r->Frame[9]);
		}
		else if (chn == "��������11")
		{
			return std::to_string(r->Frame[10]);
		}
		else if (chn == "��������12")
		{
			return std::to_string(r->Frame[11]);
		}
		else if (chn == "��������13")
		{
			return std::to_string(r->Frame[12]);
		}
		else if (chn == "��������14")
		{
			return std::to_string(r->Frame[13]);
		}
		else if (chn == "��������15")
		{
			return std::to_string(r->Frame[14]);
		}
		else if (chn == "�������|")
		{
			return std::to_string(r->MPType);
		}
		else if (chn == "����")
		{
			return std::to_string(r->MP);
		}
		else if (chn == "�������ֵ")
		{
			return std::to_string(r->MaxMP);
		}
		else if (chn == "������")
		{
			return std::to_string(r->Attack);
		}
		else if (chn == "�p��")
		{
			return std::to_string(r->Speed);
		}
		else if (chn == "���R��")
		{
			return std::to_string(r->Defence);
		}
		else if (chn == "�t��")
		{
			return std::to_string(r->Medicine);
		}
		else if (chn == "�ö�")
		{
			return std::to_string(r->UsePoison);
		}
		else if (chn == "�ⶾ")
		{
			return std::to_string(r->Detoxification);
		}
		else if (chn == "����")
		{
			return std::to_string(r->AntiPoison);
		}
		else if (chn == "ȭ��")
		{
			return std::to_string(r->Fist);
		}
		else if (chn == "����")
		{
			return std::to_string(r->Sword);
		}
		else if (chn == "ˣ��")
		{
			return std::to_string(r->Knife);
		}
		else if (chn == "����")
		{
			return std::to_string(r->Unusual);
		}
		else if (chn == "����")
		{
			return std::to_string(r->HiddenWeapon);
		}
		else if (chn == "��W���R")
		{
			return std::to_string(r->Knowledge);
		}
		else if (chn == "Ʒ��")
		{
			return std::to_string(r->Morality);
		}
		else if (chn == "���􎧶�")
		{
			return std::to_string(r->AttackWithPoison);
		}
		else if (chn == "���һ���")
		{
			return std::to_string(r->AttackTwice);
		}
		else if (chn == "��")
		{
			return std::to_string(r->Fame);
		}
		else if (chn == "�Y�|")
		{
			return std::to_string(r->IQ);
		}
		else if (chn == "�ޟ���Ʒ")
		{
			return std::to_string(r->PracticeItem);
		}
		else if (chn == "�ޟ��c��")
		{
			return std::to_string(r->ExpForItem);
		}
		else if (chn == "�����书1")
		{
			return std::to_string(r->MagicID[0]);
		}
		else if (chn == "�����书2")
		{
			return std::to_string(r->MagicID[1]);
		}
		else if (chn == "�����书3")
		{
			return std::to_string(r->MagicID[2]);
		}
		else if (chn == "�����书4")
		{
			return std::to_string(r->MagicID[3]);
		}
		else if (chn == "�����书5")
		{
			return std::to_string(r->MagicID[4]);
		}
		else if (chn == "�����书6")
		{
			return std::to_string(r->MagicID[5]);
		}
		else if (chn == "�����书7")
		{
			return std::to_string(r->MagicID[6]);
		}
		else if (chn == "�����书8")
		{
			return std::to_string(r->MagicID[7]);
		}
		else if (chn == "�����书9")
		{
			return std::to_string(r->MagicID[8]);
		}
		else if (chn == "�����书10")
		{
			return std::to_string(r->MagicID[9]);
		}
		else if (chn == "�书�ȼ�1")
		{
			return std::to_string(r->MagicLevel[0]);
		}
		else if (chn == "�书�ȼ�2")
		{
			return std::to_string(r->MagicLevel[1]);
		}
		else if (chn == "�书�ȼ�3")
		{
			return std::to_string(r->MagicLevel[2]);
		}
		else if (chn == "�书�ȼ�4")
		{
			return std::to_string(r->MagicLevel[3]);
		}
		else if (chn == "�书�ȼ�5")
		{
			return std::to_string(r->MagicLevel[4]);
		}
		else if (chn == "�书�ȼ�6")
		{
			return std::to_string(r->MagicLevel[5]);
		}
		else if (chn == "�书�ȼ�7")
		{
			return std::to_string(r->MagicLevel[6]);
		}
		else if (chn == "�书�ȼ�8")
		{
			return std::to_string(r->MagicLevel[7]);
		}
		else if (chn == "�书�ȼ�9")
		{
			return std::to_string(r->MagicLevel[8]);
		}
		else if (chn == "�书�ȼ�10")
		{
			return std::to_string(r->MagicLevel[9]);
		}
		else if (chn == "�y����Ʒ1")
		{
			return std::to_string(r->TakingItem[0]);
		}
		else if (chn == "�y����Ʒ2")
		{
			return std::to_string(r->TakingItem[1]);
		}
		else if (chn == "�y����Ʒ3")
		{
			return std::to_string(r->TakingItem[2]);
		}
		else if (chn == "�y����Ʒ4")
		{
			return std::to_string(r->TakingItem[3]);
		}
		else if (chn == "�y����Ʒ����1")
		{
			return std::to_string(r->TakingItemCount[0]);
		}
		else if (chn == "�y����Ʒ����2")
		{
			return std::to_string(r->TakingItemCount[1]);
		}
		else if (chn == "�y����Ʒ����3")
		{
			return std::to_string(r->TakingItemCount[2]);
		}
		else if (chn == "�y����Ʒ����4")
		{
			return std::to_string(r->TakingItemCount[3]);
		}
		return "";
	}
};