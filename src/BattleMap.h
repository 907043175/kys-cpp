#pragma once
#include <vector>
#include "Types.h"

enum
{
    BATTLE_ROLE_COUNT = 4096,                       //ս���������
    BATTLEMAP_SAVE_LAYER_COUNT = 2,                 //�����ļ��洢��ͼ���ݲ���
    BATTLEMAP_LAYER_COUNT = 8,                      //ս����Ҫ��ͼ����
    BATTLEMAP_COORD_COUNT = 64,                     //ս���������
    BATTLE_ENEMY_COUNT = 20,
};

//���������ս��ǰ����
struct BattleFieldData2
{
    MAP_INT data[BATTLEMAP_SAVE_LAYER_COUNT][BATTLEMAP_COORD_COUNT * BATTLEMAP_COORD_COUNT];
};

//�����������ʼ����¼��û�����
class BattleMap
{
private:
    std::vector<BattleInfo> battle_infos_;
    std::vector<BattleFieldData2> battle_field_data2_;
public:
    BattleMap();
    ~BattleMap();

    static BattleMap* getInstance() 
    {
        static BattleMap bm;
        return &bm;
    }
    BattleInfo* getBattleInfo(int i);
    void copyLayerData(int battle_field_id, int layer, MapSquareInt* out);

};

