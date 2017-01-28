#pragma once
#include <vector>

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
    short battleNum;
    char name[10];
    short battleMap, exp, battleMusic; //9
    short mate[12], autoMate[12], mate_x[12], mate_y[12]; //56
    short enemy[30], enemy_x[30], enemy_y[30]; //146
    short boutEvent, operationEvent;
    short getKongFu[3], getItems[3];//154
    short getMoney;
};

//short AddResourse[10], Connection[10];
struct BattleRole
{
    int rnum, Team, Y, X, Face, Dead, Step, Acted;
    int Pic, ShowNumber, showgongji, showfangyu, szhaoshi, Progress, round, speed; //15
    int ExpGot, Auto, Show, Wait, frozen, killed, Knowledge, LifeAdd, Zhuanzhu, pozhao, wanfang; //24
    //31 lukeɾ������Ϊÿ�غ�˥��
    int zhuangtai[14];
    int lzhuangtai[10];
    int Address[51];
};

struct BattleSceneData
{
    short Data[BLayerCountNew][BSceneMaxX][BSceneMaxY];
};

class BattleData
{
public:
    BattleData();
    ~BattleData();

    std::vector<BattleRole> m_BattleRole;
    std::vector<BattleInfo> m_BattleInfo;
    std::vector<BattleSceneData> m_BattleSceneData;

    struct FactionBackup
    {
        int len, captain;
        int TMenber[10];
    };

    int* offset;
    int maxBattleScene;

    static BattleData bBattle;
    static BattleData* getInstance()
    {
        return &bBattle;
    }

    bool load();
    bool initSta(int currentBattle);
};

