#pragma once
#include <vector>
#include "File.h"

enum
{
    _Rtypecount = 10,
    SceneMaxX = 64,
    SceneMaxY = 64,
    PerSceneMaxEvent = 400,                          //����������¼���
    MAXScene = 200,                                  //��󳡾���
    MAX_ITEM_COUNT = 400,                           //�����Ʒ��
    MaxRole = 1000,                                  //���������
    Maxfaction = 200,                                //���������
    MaxZhaoShi = 1000,                               //�����ʽ��
    MaxMagic = 1000,                                 //����书��
    MAX_TEAM_COUNT = 6,                               //��������Ա��
    MaxEquipNum = 5,                                 //���װ������
    MaxEventNum = 3000,                              //����¼���
    MaxEventFactor = 50,                             //���¼���������
    EventFolderNum = 1,                              //�¼��ļ�����
    EventFileNum = 1,                                //���¼��ļ����¼��ļ���
    MaxMagicNum = 30
};

struct ItemList { int16_t item, count; };

//�˴���Ա��������д������ֱ�ӷ���
struct GlobalData
{
    int16_t InShip, unused0, MainMapX, MainMapY, SubMapX, SubMapY, FaceTowards, ShipX, ShipY, ShipX1, ShipY1, ShipTowards;
    int16_t Team[MAX_TEAM_COUNT];
    ItemList ItemList[MAX_ITEM_COUNT];
    //short m_sDifficulty, m_sCheating, m_sBeiyong[4];
};

class Save;
struct Magic;

struct Role
{
    int16_t ID;
    int16_t HeadNum, IncLife, UnUse;
    char Name[10], Nick[10];
    int16_t Sexual, Level;
    uint16_t Exp;
    int16_t CurrentHP, MaxHP, Hurt, Poison, PhyPower;
    uint16_t ExpForItem;
    int16_t Equip1, Equip2;
    int16_t Frame[15];
    int16_t MPType, CurrentMP, MaxMP;
    int16_t Attack, Speed, Defence, Medcine, UsePoi, MedPoi, DefPoi, Fist, Sword, Knife, Unusual, HidWeapon;
    int16_t  Knowledge, Ethics, AttPoi, AttTwice, Repute, Aptitude, PracticeBook;
    uint16_t ExpForBook;
    int16_t MagicID[10], MagicLevel[10];
    int16_t TakingItem[4], TakingItemAmount[4];
    Magic* getLearnedMagic(int i) { return nullptr; }
};

struct Item
{
    int16_t ID;
    char Name[20], Name1[20];
    char Introduction[30]; //36
    int16_t Placeholder2, Magic, AmiNum, User, EquipType, ShowIntro, ItemType, Inventory, Price, EventNum; //46
    int16_t AddCurrentHP, AddMaxHP, AddPoi, AddPhyPower, ChangeMPType, AddCurrentMP, AddMaxMP, AddAttack, AddSpeed;
    int16_t AddDefence, AddMedcine, AddUsePoi, AddMedPoison, AddDefPoi; //60
    int16_t AddBoxing, AddFencing, AddKnife, AddSpecial, AddShader, AddMKnowledge, AddMorality, AddAttTwice, AddAttPoi; //69
    int16_t OnlyPracRole, NeedMPType, NeedMP, NeedAttack, NeedSpeed, NeedUsePoi, NeedMedcine, NeedMedPoi; //77
    int16_t NeedBoxing, NeedFencing, NeedKnife, NeedSpecial, NeedShader, NeedAptitude; //83
    int16_t NeedExp, Count, Rate; //86
    int16_t NeedItem[5], NeedItemAmount[5];
};

struct Magic
{
    int16_t ID;
    char Name[10];
    int16_t Unknown[5];
    int16_t SoundNum, MagicType, AmiNum, HurtType, AttAreaType, NeedMP, Poison;
    int16_t Attack[10], MoveDistance[10], AttDistance[10], AddMP[10], HurtMP[10];
};

struct SubMapRecord
{
    int16_t ID;
    char Name[10];
    int16_t ExitMusic, EntranceMusic;
    int16_t JumpScence, EnCondition;
    int16_t MainEntranceY1, MainEntranceX1, MainEntranceY2, MainEntranceX2;
    int16_t EntranceY, EntranceX;
    int16_t ExitY[3], ExitX[3];
    int16_t JumpY1, JumpX1, JumpY2, JumpX2;
};

struct SubMapData
{
    short Earth[SceneMaxX][SceneMaxY];
    short Building[SceneMaxX][SceneMaxY];
    short Decoration[SceneMaxX][SceneMaxY];
    short Event[SceneMaxX][SceneMaxY];
    short BuildingHeight[SceneMaxX][SceneMaxY];
    short EventHeight[SceneMaxX][SceneMaxY];
};

struct SubMapEvent
{
    int16_t CanWalk, Num, Event1, Event2, Event3, BeginPic1, EndPic, BeginPic2, PicDelay, XPos, YPos;
};

struct SceneEventData
{
    SubMapEvent Data[PerSceneMaxEvent];
};

struct Shop
{
   int16_t Item[5], Amount[5], Price[5];
};

class Save
{
public:
    Save();
    ~Save();

    int Rgrplen;
    int Ridxlen = _Rtypecount * 4;
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

    static Save save_;
    static Save* getInstance()
    {
        return &save_;
    }

    std::vector<int> offset, length;

    GlobalData global_data_;

    std::vector<Role> roles_;
    std::vector<Magic> magics_;
    std::vector<Item> items_;
    std::vector<SubMapRecord> submap_records_;
    std::vector<SubMapData> submap_data_;
    std::vector<Shop> shops_;
    std::vector<SceneEventData> m_SceneEventData;

    GlobalData* getGlobalData() { return&global_data_; }

    Role* getRole(int i) { return &roles_[i]; }
    Magic* getMagic(int i) { return &magics_[i]; }
    Item* getItem(int i) { return &items_[i]; }
    SubMapRecord* getSubMapRecord(int i) { return &submap_records_[i]; }

    void fromCP950ToCP936(char* s);

};

