#pragma once
#include <vector>
#include "Types.h"

enum
{
    BATTLE_ROLE_COUNT = 4096,                       //ս���������
    BATTLEMAP_SAVE_LAYER_COUNT = 2,                        //�����ļ��洢��ͼ���ݲ���
    BATTLEMAP_LAYER_COUNT = 8,                     //ս����Ҫ��ͼ����
    BATTLEMAP_COORD_COUNT = 64,                        //ս���������
};

struct BattleInfo
{
    int16_t ID;
    char Name[10];
    int16_t BattleMapSaveLayerID, Exp, Music;
    int16_t TeamMate[6], AutoTeamMate[6], TeamMateX[6], TeamMateY[6];
    int16_t Enemy[20], EnemyX[20], EnemyY[20];
};

//���������ս��ǰ����
struct BattleMapSaveLayerData
{
    int16_t Data[BATTLEMAP_SAVE_LAYER_COUNT][BATTLEMAP_COORD_COUNT][BATTLEMAP_COORD_COUNT];
};

//�����������ȡ��¼��û�����
class BattleSave
{
private:
    std::vector<BattleInfo> battle_infos_;
    std::vector<BattleMapSaveLayerData> battle_map_save_layer_data_;
    static BattleSave battle_data_;
public:
    BattleSave();
    ~BattleSave();

    static BattleSave* getInstance() { return &battle_data_; }
    BattleInfo* getBattleInfo() {}

};

