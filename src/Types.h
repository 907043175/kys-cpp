#pragma once
#include "Engine.h"
#include <cstdint>
#include <string>

using MAP_INT = int16_t;

#ifdef _MSC_VER
#define printf printf_s
//#define fopen fopen_s
#endif

template <typename T>
struct MapSquare
{
    MapSquare() {}
    MapSquare(int size) : MapSquare() { resize(size); }
    ~MapSquare()
    {
        if (data_)
        {
            delete[] data_;
        }
    }
    //���ᱣ��ԭʼ����
    void resize(int x)
    {
        if (data_)
        {
            delete[] data_;
        }
        data_ = new T[x * x];
        line_ = x;
    }

    T& data(int x, int y) { return data_[x + line_ * y]; }
    T& data(int x) { return data_[x]; }
    int size() { return line_; }
    int squareSize() { return line_ * line_; }
    void setAll(T v)
    {
        for (int i = 0; i < squareSize(); i++)
        {
            data_[i] = v;
        }
    }
    void copyTo(MapSquare* ms)
    {
        for (int i = 0; i < squareSize(); i++)
        {
            ms->data_[i] = data_[i];
        }
    }
    void copyFrom(MapSquare* ms)
    {
        for (int i = 0; i < squareSize(); i++)
        {
            data_[i] = ms->data_[i];
        }
    }

private:
    T* data_ = nullptr;
    int line_ = 0;
};

using MapSquareInt = MapSquare<MAP_INT>;

//ǰ������
struct Role;
struct Item;
struct Magic;
struct SubMapInfo;
struct Shop;
class Save;

enum
{
    SUBMAP_COORD_COUNT = 64,
    SUBMAP_LAYER_COUNT = 6,
    MAINMAP_COORD_COUNT = 480,
    SUBMAP_EVENT_COUNT = 200,    //����������¼���
    ITEM_IN_BAG_COUNT = 400,     //�����Ʒ��
    TEAMMATE_COUNT = 6,          //��������Ա��
};

enum
{
    ROLE_MAGIC_COUNT = 40,
    ROLE_TAKING_ITEM_COUNT = 4,

    MAX_MAGIC_LEVEL = 999,
    MAX_MAGIC_LEVEL_INDEX = 9,
};

enum
{
    SHOP_ITEM_COUNT = 36,
};

//��Ա�������ǿ�ͷ��д���������»��ߣ������ֱ�ӷ��ʲ��޸�

//�浵�еĽ�ɫ����
struct RoleSave
{
public:
    int ID;
    int HeadID, IncLife, Fuyuan;
    char Name[20], Nick[20];
    int Sexual;    //�Ա� 0-�� 1 Ů 2 ����
    int Level;
    int Exp;
    int HP, MaxHP, Hurt, Poison, PhysicalPower;
	int FightNum;
	//int ExpForMakeItem;
    int Equip[5];
	int Gongti;
	int TeamState;
	int Angry;
	int isRandomed;
	int Moveable, In_HeadNum, ZhanLueAI;
    int Impression, dtime, difficulty;  
	int Zhongcheng;
	int reHurt;
    int MPType, MP, MaxMP;
    int Attack, Speed, Defence, Medicine, UsePoison, Detoxification, AntiPoison, Fist, Sword, Knife, Unusual, HiddenWeapon;
    int Knowledge, Morality, AttackWithPoison, AttackTwice, Fame, IQ;
    int PracticeItem;
    int ExpForItem;
	int xiangxing, jiaoqing, Rtype, swq, pdq, xxq, jqq, MenPai, shifu, scsx, bssx;
	int Choushi[2];
	int weizhi, nweizhi, nfangxiang, OnStatus, lwq, msq, ldq, qtq, lsweizhi, lsnweizhi, lsfangxiang;
	int Sx, Sy, songshu, gongxian, unuse5;
	int unuse6, unuse7, unuse8, unuse9, btnum; //��¼����,�������� //98
    int MagicID[ROLE_MAGIC_COUNT], MagicLevel[ROLE_MAGIC_COUNT];
    int TakingItem[ROLE_TAKING_ITEM_COUNT], TakingItemCount[ROLE_TAKING_ITEM_COUNT];
	int JhMagic[10];
	int LZhaoshi[ROLE_MAGIC_COUNT];
	int MRevent;
	int AllEvent[8];
	int	LeaveTime, LeaveEvent;
	int LaoLian, QiangZhuang, NeiJia, QiangGong, JianGU, QingLing, QuanShi, JianKe, Daoke, YiBing, AnJian, YIShi, DuRen, HuiXue, HuiNei,
		HuiTI, BaoZao, PeiHe, WuXue, TuPo, LengJing, BaiBian, PoQi, ZhaoMen, BianHuan, FanGong, QiGong, YingGong, LingHuo, XingQi,
		ShenFa, FenFa, ZhanYi, JingZhun, JiSu, KuangBao, ShouFa, LianHuan, WaJie, GuShou; // 287 // ��fenfa��ʼ,��Ӧ����,����,�Ṧ,ȭ��,����,����,����,������Ǳ��
	int TianMing, XingXiu;
	int ZhuanChang[5];
	int TeXing[10];
	int unused[10];	//314

};

//ʵ�ʵĽ�ɫ���ݣ�����֮���ͨ����ս������
struct Role : public RoleSave
{
public:
    int Team;
    int FaceTowards, Dead, Step;
    int Pic, BattleSpeed;
    int ExpGot, Auto;
    int FightFrame[5] = { -1 };
    int FightingFrame;
    int Moved, Acted;
    int ActTeam;    //ѡ���ж���Ӫ 0-�ҷ���1-���ҷ�����Ч����ʱ��Ч

    int SelectedMagic;

    int Progress;

    struct ShowString
    {
        std::string Text;
        BP_Color Color;
        int Size;
    };
    //��ʾ����Ч��ʹ��
    struct ActionShowInfo
    {
        std::vector<ShowString> ShowStrings;
        int BattleHurt;
        int ProgressChange;
        int Effect;
        ActionShowInfo()
        {
            clear();
        }
        void clear()
        {
            ShowStrings.clear();
            BattleHurt = 0;
            ProgressChange = 0;
            Effect = -1;
        }
    };
    ActionShowInfo Show;

private:
    int X_, Y_;
    int prevX_, prevY_;

public:
    MapSquare<Role*>* position_layer_ = nullptr;
    void setRolePositionLayer(MapSquare<Role*>* l) { position_layer_ = l; }
    void setPosition(int x, int y);
    void setPositionOnly(int x, int y)
    {
        X_ = x;
        Y_ = y;
    }
    void setPrevPosition(int x, int y)
    {
        prevX_ = x;
        prevY_ = y;
    }
    void resetPosition() { setPosition(prevX_, prevY_); }
    int X() { return X_; }
    int Y() { return Y_; }

    //��role�ģ���ʾ����Ĳ����������书��
    int getRoleShowLearnedMagicLevel(int i);
    int getRoleMagicLevelIndex(int i);

    int getLearnedMagicCount();
    int getMagicLevelIndex(Magic* magic);
    int getMagicLevelIndex(int magic_id);
    int getMagicOfRoleIndex(Magic* magic);

    void limit();

    int learnMagic(Magic* magic);
    int learnMagic(int magic_id);

    bool isAuto() { return Auto != 0 || Team != 0; }

    void addShowString(std::string text, BP_Color color = { 255, 255, 255, 255 }, int size = 28) { Show.ShowStrings.push_back({ text, color, size }); }
    void clearShowStrings() { Show.ShowStrings.clear(); }

public:
    int AI_Action = 0;
    int AI_MoveX, AI_MoveY;
    int AI_ActionX, AI_ActionY;
    Magic* AI_Magic = nullptr;
    Item* AI_Item = nullptr;

public:
    int Network_Action;
    int Network_MoveX;
    int Network_MoveY;
    int Network_ActionX;
    int Network_ActionY;
    Magic* Network_Magic = nullptr;
    Item* Network_Item = nullptr;

public:
    int RealID = -1;
    bool Networked = false;
    bool Competing = false;

public:
    static Role* getMaxValue() { return &max_role_value_; }

private:
    static Role max_role_value_;
};

//�浵�е���Ʒ����
struct ItemSave
{
    int ID;
    char Name[40];
	int ExpofMagic;
	int SetNum, BattleBattleEffect, AddSign, needSex, rehurt, NeedEthics, NeedRepute;
	int AddQianli, BattleNum;
    char Introduction[60];
    int MagicID, HiddenWeaponEffectID, User, EquipType, ShowIntroduction;
    int ItemType;    //0���飬1װ����2���ţ�3ҩƷ��4����
    int Inventory, Price, EventNum;
    int AddHP, AddMaxHP, AddPoison, AddPhysicalPower, ChangeMPType, AddMP, AddMaxMP;
    int AddAttack, AddSpeed, AddDefence, AddMedicine, AddUsePoison, AddDetoxification, AddAntiPoison;
    int AddFist, AddSword, AddKnife, AddUnusual, AddHiddenWeapon, AddKnowledge, AddMorality, AddAttackTwice, AddAttackWithPoison;
    int OnlySuitableRole, NeedMPType, NeedMP, NeedAttack, NeedSpeed, NeedUsePoison, NeedMedicine, NeedDetoxification;
    int NeedFist, NeedSword, NeedKnife, NeedUnusual, NeedHiddenWeapon, NeedIQ;
    int NeedExp, NeedExpForMakeItem, NeedMaterial;
    int MakeItem[5], MakeItemCount[5];
	int AddIQ, AddFuyuan;
	int Unused[8];
};

//ʵ�ʵ���Ʒ����
struct Item : ItemSave
{
public:
    static int MoneyItemID;
    static int CompassItemID;

public:
    bool isCompass();
};

//�浵�е���ѧ���ݣ����ʺ϶�Ӧ���룬��������С˵�е���ѧ����ħ����������ˣ�
struct MagicSave
{
    int ID;
    char Name[20];
	int useness, miji, NeedHP, MinStep, bigami, EventNum;
    int SoundID;
    int MagicType;    //1-ȭ��2-����3-����4-����
    int EffectID;
    int HurtType;          //0-��ͨ��1-��ȡMP
    int AttackAreaType;    //0-�㣬1-�ߣ�2-ʮ�֣�3-��
    int NeedMP, WithPoison;
	int MinHurt, MaxHurt, HurtModulus, AttackModulus, MPModulus, SpeedModulus, WeaponModulus;
	int Ismichuan, AddMpScale, AddHpScale;
	int SelectDistance[10], AttackDistance[10];
	int AddHP[3], AddMP[3], AddAtt[3], AddDef[3], AddSpd[3];
	int MinPeg, MaxPeg, MinInjury, MaxInjury, AddMedcine, AddUsePoi, AddMedPoi, AddDefPoi;
	int AddFist, AddSword, AddKnife, AddUnusual, AddHidWeapon, BattleState;
	int NeedExp[3];
	int MaxLevel;
	char Introduction[120];
	int Zhaoshi[5];
	int Teshu[10], Teshumod[10], unused[10];
};

struct Magic : MagicSave
{
    int calNeedMP(int level_index) { return NeedMP * ((level_index + 2) / 2); }
    int calMaxLevelIndexByMP(int mp, int max_level);
};

//�浵�е��ӳ�������
//Լ����Scene��ʾ��Ϸ�����е�ĳ��Elementʵ������Map��ʾ�洢������
struct SubMapInfoSave
{
    int ID;
    char Name[20];
    int ExitMusic, EntranceMusic;
    int JumpSubMap, EntranceCondition;
    int MainEntranceX1, MainEntranceY1, MainEntranceX2, MainEntranceY2;
    int EntranceX, EntranceY;
    int ExitX[3], ExitY[3];
	int Mapmode, unuse, menpai, inbattle, zlwc, lwc, zcjg, cjg;
	int lwcx[5], lwcy[5], cjgx[5], cjgy[5];
	int bgskg, bgsx, bgsy, ldlkg, ldlx, ldly, bqckg, bqcx, bqcy, qizhix, qizhiy, ldjd, dzjd, fyjc, fyss;
	int addziyuan[10];
	int lianjie[10];
	int unused[10];
    //int JumpX, JumpY, JumpReturnX, JumpReturnY;
};

//�浵�е�ʱ������
struct TimeInfoSave
{
	int Jiazi;
	int Year;
	int Month;
	int Day;
	int Hour;


};

//��Ч����
struct Ttexiao
{
public:
	int Type;
	int Value;
};

//�浵�е���ʽ����
struct ZhaoshiInfoSave
{
	int daihao, congshu, shunwei;
	char Name[40];
	int ygongji, gongji, yfangyu, fangyu;
	char Introduction[90];
	Ttexiao texiao[24]; //89
};



//�浵�е���������
struct MenpaiInfoSave
{
	int num;
	char Name[40];
	int jvdian, zongduo, zmr, dizi, shengwang, shane;
	int ziyuan[10];
	int aziyuan[10];
	int neigong[20]; //57
	int guanxi[40]; //97
	int zhiwu[10]; //107
	int kzq, dzq, czsd, qizhi, mdizigrp, mdizipic, fdizigrp, fdizipic, sexy, identity, endevent;
	int tongmeng, israndomed, unuse2, unuse3, unuse4;
};

//�浵�еı�ǩ���
struct SignType
{
	int num;
	char name[40]; //10
	char Introduction[120]; //41
};

//�浵�еı�ǩ����
struct RSign
{
	int num;
	char Name[40]; //10
	int effert;
	int TypeNum;
	char Introduction[120]; //42
	int beiyong;
	int isshow; //44
	Ttexiao texiao[24]; //92
};



//�����¼�����
struct SubMapEvent
{
    //event1Ϊ����������event2Ϊ��Ʒ������event3Ϊ��������
    MAP_INT CannotWalk, Index, Event1, Event2, Event3, CurrentPic, EndPic, BeginPic, PicDelay;

private:
    MAP_INT X_, Y_;

public:
	MAP_INT BeginTime, DuringTime, RecurrentTime, ActiveTime, IsActive, OverdueTime, OvderdueEvent;

public:
    MAP_INT X() { return X_; }
    MAP_INT Y() { return Y_; }
    void setPosition(int x, int y, SubMapInfo* submap_record);
    void setPic(int pic)
    {
        BeginPic = pic;
        CurrentPic = pic;
        EndPic = pic;
    }
};

//ʵ�ʵĳ�������
struct SubMapInfo : public SubMapInfoSave
{
public:
    MAP_INT& LayerData(int layer, int x, int y)
    {
        return layer_data_[layer][x + y * SUBMAP_COORD_COUNT];
    }

    MAP_INT& Earth(int x, int y)
    {
        return LayerData(0, x, y);
    }

    MAP_INT& Building(int x, int y)
    {
        return LayerData(1, x, y);
    }

    MAP_INT& Decoration(int x, int y)
    {
        return LayerData(2, x, y);
    }

    MAP_INT& EventIndex(int x, int y)
    {
        return LayerData(3, x, y);
    }

    MAP_INT& BuildingHeight(int x, int y)
    {
        return LayerData(4, x, y);
    }

    MAP_INT& DecorationHeight(int x, int y)
    {
        return LayerData(5, x, y);
    }

    SubMapEvent* Event(int x, int y)
    {
        int i = EventIndex(x, y);
        return Event(i);
    }

    SubMapEvent* Event(int i)
    {
        if (i < 0 || i >= SUBMAP_EVENT_COUNT)
        {
            return nullptr;
        }
        return &events_[i];
    }

private:
    MAP_INT layer_data_[SUBMAP_LAYER_COUNT][SUBMAP_COORD_COUNT * SUBMAP_COORD_COUNT];
    SubMapEvent events_[SUBMAP_EVENT_COUNT];
};

//�浵�е��̵�����
struct ShopSave
{
    int ItemID[SHOP_ITEM_COUNT], ItermCount[SHOP_ITEM_COUNT];
};

//ʵ���̵�����
struct Shop : ShopSave
{
};