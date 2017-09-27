#pragma once
#include <cstdint>

enum
{
    MAX_SUBMAP_COORD = 64,
    MAX_MAINMAP_COORD = 480,
    MAX_SUBMAP_EVENT = 200,                         //����������¼���
    MAX_ITEM_COUNT = 200,                           //�����Ʒ��
    MAX_TEAMMATE_COUNT = 6,                         //��������Ա��
};

struct Role;
struct Item;
struct Magic;
struct SubMapRecord;
struct Shop;

//��Ա�������ǿ�ͷ��д���������»��ߣ������ֱ�ӷ��ʲ��޸�

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
    int16_t Attack, Speed, Defence, Medcine, UsePoison, MedcinePoi, DefencePoison, Fist, Sword, Knife, Unusual, HidWeapon;
    int16_t  Knowledge, Ethics, AttackPoison, AttackTwice, Repute, Aptitude, PracticeBook;
    uint16_t ExpForBook;
    int16_t MagicID[10], MagicLevel[10];
    int16_t TakingItem[4], TakingItemAmount[4];
    Magic* getLearnedMagic(int i);
};

struct Item
{
    int16_t ID;
    char Name[20], Name1[20];
    char Introduction[30];
    int16_t MagicID, AmiNum, User, EquipType, ShowIntro, ItemType, UnKnown5, UnKnown6, UnKnown7;
    int16_t AddCurrentHP, AddMaxHP, AddPoi, AddPhyPower, ChangeMPType, AddCurrentMP, AddMaxMP, AddAttack, AddSpeed;
    int16_t AddDefence, AddMedcine, AddUsePoi, AddMedPoison, AddDefPoi;
    int16_t AddFist, AddSword, AddKnife, AddUnusual, AddHidWeapon, AddKnowledge, AddEthics, AddAttTwice, AddAttPoi;
    int16_t OnlyPracRole, NeedMPType, NeedMP, NeedAttack, NeedSpeed, NeedUsePoi, NeedMedcine, NeedMedPoi;
    int16_t NeedFist, NeedSword, NeedKnife, NeedUnusual, NeedHidWeapon, NeedAptitude;
    int16_t NeedExp, NeedExpForItem, NeedMaterial;
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

struct SubMapData
{
    int16_t data[6][MAX_SUBMAP_COORD * MAX_SUBMAP_COORD];
};

struct SubMapEvent
{
    int16_t CannotWalk, ID, Event1, Event2, Event3, CurrentPic, EndPic, BeginPic, PicDelay;
private:
    int16_t X_, Y_;
public:
    int16_t X() { return X_; }
    int16_t Y() { return Y_; }
};

struct SubMapRecord
{
    int16_t ID;
    char Name[10];
    int16_t ExitMusic, EntranceMusic;
    int16_t JumpScence, EntranceCondition;
    int16_t MainEntranceX1, MainEntranceY1, MainEntranceX2, MainEntranceY2;
    int16_t EntranceX, EntranceY;
    int16_t ExitX[3], ExitY[3];
    int16_t JumpX1, JumpY1, JumpX2, JumpY2;

    int16_t& Earth(int x, int y);
    int16_t& Building(int x, int y);
    int16_t& Decoration(int x, int y);
    int16_t& EventIndex(int x, int y);
    int16_t& BuildingHeight(int x, int y);
    int16_t& EventHeight(int x, int y);
    SubMapEvent* Event(int x, int y);
    SubMapEvent* Event(int i);
};

struct Shop
{
    int16_t Item[5], Amount[5], Price[5];
};
