#pragma once
#include <vector>
#include "Types.h"

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

