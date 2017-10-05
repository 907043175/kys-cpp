#pragma once
#include <vector>
#include "Types.h"
#include <map>

struct ItemList { SAVE_INT item_id, count; };

class Save
{
public:
    //�˴�Ϊȫ�����ݣ�����ͱ���ʹ�ã���������࿪ͷ������˳�򣬷����Լ����Ű�
    SAVE_INT InShip, InSubmap, MainMapX, MainMapY, SubMapX, SubMapY, FaceTowards, ShipX, ShipY, ShipX1, ShipY1, Encode;
    SAVE_INT Team[TEAMMATE_COUNT];
    ItemList Items[ITEM_IN_BAG_COUNT];
private:
    //��������������
    SAVE_INT buffer_[100];

    const int MONEY_ITEM_ID = 174;
    const int COMPASS_ITEM_ID = 182;

    int sdata_length_ = sizeof(SAVE_INT) * SUBMAP_LAYER_COUNT * SUBMAP_COORD_COUNT * SUBMAP_COORD_COUNT;
    int ddata_length_ = sizeof(SubMapEvent) * SUBMAP_EVENT_COUNT;

public:
    Save();
    ~Save();

    bool LoadR(int num);
    bool SaveR(int num);

    static Save save_;
    static Save* getInstance()
    {
        return &save_;
    }

    static std::string getFilename(int i, char c);

    //ע���ڶ�ȡ֮��offset��lengthβ�����һ��Ԫ�أ���ֵ���ܳ���
    std::vector<int> offset_, length_;

    //����ʵ�ʱ�����������
    std::vector<Role> roles_;
    std::vector<Magic> magics_;
    std::vector<Item> items_;
    std::vector<SubMapInfo> submap_infos_;
    //std::vector<SubMapLayerData> submap_data_;
    std::vector<Shop> shops_;
    //std::vector<SubMapEvent> submap_event_;

    std::map<std::string, Role*> roles_by_name_;
    std::map<std::string, Item*> items_by_name_;
    std::map<std::string, Magic*> magics_by_name_;
    std::map<std::string, SubMapInfo*> submap_infos_by_name_;

    Role* getRole(int i) { if (i < 0 || i >= roles_.size()) { return nullptr; } return &roles_[i]; }
    Magic* getMagic(int i) { if (i <= 0 || i >= magics_.size()) { return nullptr; } return &magics_[i]; }  //0���书��Ч
    Item* getItem(int i) { if (i < 0 || i >= items_.size()) { return nullptr; } return &items_[i]; }
    SubMapInfo* getSubMapInfo(int i) { if (i < 0 || i >= submap_infos_.size()) { return nullptr; } return &submap_infos_[i]; }

    Role* getTeamMate(int i);
    int getTeamMateID(int i) { return Team[i]; }

    Item* getItemByBagIndex(int i);
    SAVE_INT getItemCountByBagIndex(int i);
    SAVE_INT getItemCountInBag(Item* item);

    int getItemCountInBag(int item_id);
    int getMoneyCountInBag() { return getItemCountInBag(MONEY_ITEM_ID); }

    void makeMaps();

    Role* getRoleByName(std::string name) { return roles_by_name_[name]; }
    Magic* getMagicByName(std::string name) { return magics_by_name_[name]; }
    Item* getItemByName(std::string name) { return items_by_name_[name]; }
    SubMapInfo* getSubMapRecordByName(std::string name) { return submap_infos_by_name_[name]; }

    Magic* getRoleLearnedMagic(Role* r, int i);
    int getRoleLearnedMagicLevelIndex(Role* r, Magic* m);

    static char* getIdxContent(std::string filename_idx, std::string filename_grp, std::vector<int>* offset, std::vector<int>* length);

    template <class T> void setSavePointer(std::vector<T>& v, int size)
    {
        for (auto& i : v)
        {
            i.save_ = this;
        }
    }
};


