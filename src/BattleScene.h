#pragma once
#include "BattleMap.h"
#include "Scene.h"
#include "Point.h"
#include <stack>
#include "BattleMenu.h"
#include "BattleOperator.h"

class BattleScene : public Scene
{
public:
    BattleScene();
    BattleScene(int id);
    ~BattleScene();

    std::vector<Role*> battle_roles_;

    BattleMenu* battle_menu_;
    BattleOperator* battle_operator_;
    Head* head_;

    int battle_id_ = 0;
    BattleInfo* info_;
    void setID(int id);

    static const int COORD_COUNT = BATTLEMAP_COORD_COUNT;
    //����㣬�����㣬��ɫ�㣬ѡ��㣨��ֵΪ����ѡ��0����ֵΪ��ѡ��
    MapSquare earth_layer_, building_layer_, role_layer_, select_layer_, effect_layer_;

    int select_state_ = 0;  //0-������1-ѡ�ƶ�Ŀ�꣬2-ѡ�ж�Ŀ��

    int select_x_, select_y_;
    void setSelectPosition(int x, int y) { select_x_ = x; select_y_ = y; }


    virtual void draw() override;
    virtual void dealEvent(BP_Event& e) override;
    virtual void onEntrance();

    void setRoleInitState(Role* r);

    void sortRoles();
    static bool compareRole(Role* r1, Role* r2);


    int calRolePic(Role* r);

    void calSelectLayer(Role* r, int mode, int step);

    bool canSelect(int x, int y);

    void walk(Role* r, int x, int y, Towards t);

    virtual bool canWalk(int x, int y) override;
    bool isBuilding(int x, int y);
    bool isOutLine(int x, int y);
    bool isWater(int x, int y);
    bool isRole(int x, int y);
    bool isOutScreen(int x, int y);


    //"�Ƅ�", "��W", "�ö�", "�ⶾ", "�t��", "��Ʒ", "�ȴ�", "��B", "�Ԅ�", "�Y��"
    void actMove(Role* r);
    void actAttack(Role* r);
    void actUsePoison(Role* r);
    void actDetoxification(Role* r);
    void actMedcine(Role* r);
    void actUseItem(Role* r);
    void actWait(Role* r);
    void actStatus(Role* r);
    void actAuto(Role* r);
    void actRest(Role* r);

    int calHurt(Role* r1, Role* r2, Magic* magic, int magic_level);


    bool initBattleData();
    bool initBattleRoleState();

    int selectTeamMembers();
    void ShowMultiMenu(int max0, int menu);
    void showSlectMenu(std::string* str, int x);                               // ��ս������Ϣ
    void showBattleMenu(int x, int y);                                    // ս������

    void initMultiMenu();

    void getMousePosition(Point* point);

    //void menuCloseCallback(Ref* pSender);
    //void menuCloseCallback1(Ref* pSender);
    bool battle(int battlenum, int getexp, int mods, int id, int maternum, int enemyrnum);

    void calMoveAbility();
    void reArrangeBRole();
    void moveRole(int bnum);

    void moveAmination(int bnum);
    bool selectAim(int bnum, int step, int mods);
    //void Draw(float dt);
    void moveAminationStep(float dt);
    void attack(int bum);
};