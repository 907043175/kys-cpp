#pragma once
#include <vector>
#include "Types.h"

enum
{
    MaxBRoleNum = 42,                       //ս���������
    BLayerCount = 2,                        //�����ļ��洢��ͼ���ݲ���
    BLayerCountNew = 8,                     //ս����Ҫ��ͼ����
    BSceneMaxX = 64,                        //ս�����X����
    BSceneMaxY = 64,                        //ս�����Y����
};

struct BattleInfo
{
    int16_t battleNum;
    char name[10];
    int16_t battleMap, exp, battleMusic; //9
    int16_t mate[12], autoMate[12], mate_x[12], mate_y[12]; //56
    int16_t enemy[30], enemy_x[30], enemy_y[30]; //146
    int16_t boutEvent, operationEvent;
    int16_t getKongFu[3], getItems[3];//154
    int16_t getMoney;
};

typedef int16_t BattleMapArray[BSceneMaxX * BSceneMaxY];

//short AddResourse[10], Connection[10];
struct BattleRole
{
    int RoleID, Team;
private:
    int X_, Y_;
public:
    int Face, Dead, Step, Acted;
    int Pic, ShowNumber, showgongji, showfangyu, szhaoshi, Progress, round, speed; //15
    int ExpGot, Auto, Show, Wait, frozen, killed, Knowledge, LifeAdd, Zhuanzhu, pozhao, wanfang; //24
    //31 lukeɾ������Ϊÿ�غ�˥��
    int zhuangtai[14];
    int lzhuangtai[10];
    int Address[51];
    Role* getRole() { return nullptr; }
    void setPosition(int x, int y) {}
    int X() { return X_; }
    int Y() { return Y_; }
private:
    BattleMapArray* role_layer_;
};

struct BattleSceneData
{
    short Data[BLayerCountNew][BSceneMaxX][BSceneMaxY];
    BattleMapArray Earth, Building;
};

class BattleData
{
public:
    BattleData();
    ~BattleData();

    std::vector<BattleRole> m_vcBattleRole;
    std::vector<BattleInfo> m_vcBattleInfo;
    std::vector<BattleSceneData> m_vcBattleSceneData;

    struct FactionBackup
    {
        int len, captain;
        int TMenber[10];
    };

    int* m_poffset;
    int m_nMaxBattleScene;

    static BattleData m_bBattle;
    static BattleData* getInstance()
    {
        return &m_bBattle;
    }

    bool isLoad();
    bool isInitSta(int currentBattle);
};

