#pragma once

class config
{
public:
	config();
	~config();

	enum
	{
		_Rtypecount = 10,
		SLayerCount = 6,
		SceneMaxX = 64,
		SceneMaxY = 64,
		PerSceneMaxEvent = 400,							//����������¼���	
		MAXScene = 200,									//��󳡾���
		MAX_ITEM_AMOUNT = 400,							//�����Ʒ��
		MaxRole = 1000,									//���������
		Maxfaction = 200,								//���������
		MaxZhaoShi = 1000,								//�����ʽ��
		MaxMagic = 1000,								//����书��
		MaxTeamMember = 6,								//��������Ա��
		MaxEquipNum = 5,								//���װ������
		MaxEventNum = 3000,								//����¼���
		MaxEventFactor = 50,							//���¼���������
		EventFolderNum = 1,								//�¼��ļ�����	
		EventFileNum = 1								//���¼��ļ����¼��ļ���

	};

};

