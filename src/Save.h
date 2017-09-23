#pragma once
#include <vector>
#include "File.h"

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
    EventFileNum = 1,                                //���¼��ļ����¼��ļ���
    MaxMagicNum = 30
};


struct SceneMapData
{
	short Earth[SceneMaxX][SceneMaxY];
    short Earth[SceneMaxX][SceneMaxY];
    short Earth[SceneMaxX][SceneMaxY];
    short Earth[SceneMaxX][SceneMaxY];
    short Earth[SceneMaxX][SceneMaxY];
    short Earth[SceneMaxX][SceneMaxY];
};

struct TSceneEvent
{
	short CanWalk, Num, Event1, Event2, Event3, BeginPic1, EndPic, BeginPic2, PicDelay, XPos, YPos;
	short StartTime, Duration, Interval, DoneTime, IsActive, OutTime, OutEvent;
};

struct SceneEventData
{

	TSceneEvent Data[PerSceneMaxEvent];
};

class Save
{
public:
    Save();
    ~Save();

    int* Offset;
    unsigned char key = 156;
    unsigned char password;
    int Rgrplen;
    int Ridxlen = _Rtypecount * 4;
    unsigned char* GRPMD5_cal, *GRPMD5_load;
    int B_Count;                                        //������������
    int R_Count;                                        //��ɫ����
    int I_Count;                                        //��Ʒ����
    int S_Count;                                        //��������
    int M_Count;                                        //�书����
    int SP_Count;                                       //С���̵�����
    int Z_Count;                                        //��ʽ����
    int F_Count;                                        //��������
    static const int R_length = 436;                    //��ɫ���ݳ���

    bool LoadR(int num);
    bool SaveR(int num);

    static Save save;
    static Save* getInstance()
    {
        return &save;
    }

    void jiemi(unsigned char* Data, unsigned char key, int len);
    void encryption(std::string str, unsigned char key);

    //std::vector<BaoShop> m_Baoshop;
    //std::vector<BasicData> m_BasicData;
    //std::vector<Character> m_Character;
    //std::vector<Calendar> m_Calendar;
    //std::vector<Faction> m_Faction;
    //std::vector<Magic> m_Magic;
    //std::vector<SceneData> m_SceneData;
    //std::vector<ZhaoShi> m_ZhaoShi;
    //std::vector<Item> m_Item;
    std::vector<SceneMapData> m_SceneMapData;
    std::vector<SceneEventData> m_SceneEventData;
};

