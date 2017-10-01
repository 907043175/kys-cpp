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
    int16_t BattleFieldID, Exp, Music;
    int16_t TeamMate[6], AutoTeamMate[6], TeamMateX[6], TeamMateY[6];
    int16_t Enemy[20], EnemyX[20], EnemyY[20];
};

//���������ս��ǰ����
struct BattleFieldData2
{
    int16_t data[BATTLEMAP_SAVE_LAYER_COUNT][BATTLEMAP_COORD_COUNT*BATTLEMAP_COORD_COUNT];
};

//�����������ʼ����¼��û�����
class BattleSave
{
private:
    std::vector<BattleInfo> battle_infos_;
    std::vector<BattleFieldData2> battle_field_data2_;
    static BattleSave battle_data_;
public:
    BattleSave();
    ~BattleSave();

    static BattleSave* getInstance() { return &battle_data_; }
    BattleInfo* getBattleInfo(int i) { if (i < 0 || i >= battle_infos_.size()) { return nullptr; } return &battle_infos_[i]; }
    void copyLayerData(int battle_field_id, int layer, int16_t* out);

};

