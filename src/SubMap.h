#pragma once
#include "Scene.h"
#include "Save.h"

class SubMap : public Scene
{
private:
    SubMap();
public:
    SubMap(int num);
    virtual ~SubMap();

    int view_x_ = 0, view_y_ = 0;
    int16_t& man_x_, &man_y_;
    int man_pic_;
    int step_ = 0;

    const int MAX_COORD = MAX_SUBMAP_COORD;

    int const MAN_PIC_0 = 2501;            //��ʼ��������ͼƫ����
    int const MAN_PIC_COUNT = 7;           //��������ͼ����
    int scene_id_;   //������

    SubMapRecord* record_;

public:
    SubMapRecord* getRecord() { return record_; }

    void setSceneNum(int num) { scene_id_ = num; }

    void setPosition(int x, int y) { setManPosition(x, y); setViewPosition(x, y); }
    //ע���ӽǺ����ǵ�λ�ÿ��ܲ�һ��
    void setManPosition(int x, int y) { man_x_ = x; man_y_ = y; }
    void setViewPosition(int x, int y) { view_x_ = x; view_y_ = y; }

    virtual void draw() override;
    virtual void dealEvent(BP_Event& e) override;
    virtual void backRun() override;

    void tryWalk(int x, int y, Towards t);

    bool checkEvent1(int x, int y, Towards t);
    bool checkEvent2(int x, int y, Towards t, Item* item);
    bool checkEvent3(int x, int y);
    void callEvent(int x, int y);

    virtual bool isBuilding(int x, int y);
    virtual bool isOutLine(int x, int y);
    bool isWater(int x, int y);
    bool isCanPassEvent(int x, int y);
    bool isCannotPassEvent(int x, int y);
    bool isFall(int x, int y);
    bool isExit(int x, int y);

    virtual bool isOutScreen(int x, int y) override;
    virtual bool canWalk(int x, int y) override;

    void getMousePosition(int _x, int _y);

    //�����¼���
    static SubMap* current_submap_;
    static Item* current_item_;
    static int event_x_, event_y_;

    SubMap* getCurrentSubmap() { return current_submap_; }
    Item* getCurrentItem() { return current_item_; }


};

