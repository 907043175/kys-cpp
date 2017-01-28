#pragma once

struct config
{
    enum
    {
        _Rtypecount = 10,
        SLayerCount = 6,
        SceneMaxX = 64,
        SceneMaxY = 64,
        PerSceneMaxEvent = 400,                          //����������¼���
        MAXScene = 200,                                  //��󳡾���
        MAX_ITEM_AMOUNT = 400,                           //�����Ʒ��
        MaxRole = 1000,                                  //���������
        Maxfaction = 200,                                //���������
        MaxZhaoShi = 1000,                               //�����ʽ��
        MaxMagic = 1000,                                 //����书��
        MaxTeamMember = 6,                               //��������Ա��
        MaxEquipNum = 5,                                 //���װ������
        MaxEventNum = 3000,                              //����¼���
        MaxEventFactor = 50,                             //���¼���������
        EventFolderNum = 1,                              //�¼��ļ�����
        EventFileNum = 1                                 //���¼��ļ����¼��ļ���
    };
};

struct SceneMapData
{
    short Data[config::SLayerCount][config::SceneMaxX][config::SceneMaxY];
};

struct SceneData
{
    short ListNum;
    char Name[10];
    short Placeholder1, ExitMusic, EntranceMusic, Pallet, EnterCondition; //10
    short MainEntranceY1, MainEntranceX1, MainEntranceY2, MainEntranceX2, EntranceY, EntranceX, ExitY[3], ExitX[3]; //22
    short MapMode, Unuse, Faction, IsBattle, MaxPraFieldAmount, PraFieldAmount, MaxStudyAmount, StudyAmount; //30
    short PraFieldX[5], PraFieldY[5], StudyX[5], StudyY[5]; //50
    short IsMeditation, MeditationX, MeditationY, IsAlchemy, AlchemyX, AlchemyY, IsFactory, FactoryX, FactoryY, FlagX, FlagY, AlchemyPro, MeditationPro, DefBuff, DefBuild; //65
    short AddResourse[10], Connection[10];
};

struct SceneEventData
{
    struct TSceneEvent
    {
        short CanWalk, Num, Event1, Event2, Event3, BeginPic1, EndPic, BeginPic2, PicDelay, XPos, YPos, StartTime, Duration, Interval, DoneTime,
              IsActive, OutTime, OutEvent;
    };
    TSceneEvent Data[config::PerSceneMaxEvent];
};

