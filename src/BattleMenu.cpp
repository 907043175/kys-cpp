#include "BattleMenu.h"
#include "Save.h"
#include "Random.h"
#include "BattleScene.h"
#include "others\libconvert.h"

BattleActionMenu::BattleActionMenu()
{
    setStrings({ "�Ƅ�", "��W", "�ö�", "�ⶾ", "�t��", "����", "ˎƷ", "�ȴ�", "��B", "�Ԅ�", "�Y��" });
    distance_layer_ = new MapSquare();
    distance_layer_->resize(BATTLEMAP_COORD_COUNT);
}

BattleActionMenu::~BattleActionMenu()
{
    delete distance_layer_;
}

void BattleActionMenu::onEntrance()
{
    setVisible(true);
    for (auto c : childs_)
    {
        c->setVisible(true);
        c->setState(Normal);
    }

    //�ƶ����򲻿��ƶ�
    if (role_->Moved || role_->PhysicalPower < 10)
    {
        childs_text_["�Ƅ�"]->setVisible(false);
    }
    if (role_->getLearnedMagicCount() <= 0 || role_->PhysicalPower < 20)
    {
        childs_text_["��W"]->setVisible(false);
    }
    if (role_->UsePoison <= 0 || role_->PhysicalPower < 30)
    {
        childs_text_["�ö�"]->setVisible(false);
    }
    if (role_->Detoxification <= 0 || role_->PhysicalPower < 30)
    {
        childs_text_["�ⶾ"]->setVisible(false);
    }
    if (role_->Medcine <= 0 || role_->PhysicalPower < 10)
    {
        childs_text_["�t��"]->setVisible(false);
    }
    if (role_->HiddenWeapon <= 15 || role_->PhysicalPower < 10)
    {
        childs_text_["����"]->setVisible(false);
    }

    //���õȴ�
    childs_text_["�ȴ�"]->setVisible(false);

    setFontSize(20);
    arrange(0, 0, 0, 28);
    pass_child_ = findFristVisibleChild();
    forcePassChild();
}

void BattleActionMenu::dealEvent(BP_Event& e)
{
    if (battle_scene_ == nullptr) { return; }
    if (role_->isAuto())
    {
        int act = autoSelect(role_);
        setResult(act);
        setAllChildState(Normal);
        childs_[act]->setState(Press);
        setExit(true);
        setVisible(false);  //AI�����˵��ˣ�̫��
    }
    else
    {
        Menu::dealEvent(e);
    }
}

//"0�Ƅ�", "1��W", "2�ö�", "3�ⶾ", "4�t��", "5����", "6ˎƷ", "7�ȴ�", "8��B", "9�Ԅ�", "10�Y��"
int BattleActionMenu::autoSelect(Role* role)
{
    Random<double> rand;   //÷ɭ��ת�������
    rand.set_seed();

    std::vector<int> points(10);
    std::vector<Role*> friends, enemies;

    for (auto r : battle_scene_->battle_roles_)
    {
        if (r->Team == role->Team)
        {
            friends.push_back(r);
        }
        else
        {
            enemies.push_back(r);
        }
    }

    //aiΪÿ���ж����֣���ѧ���ö����ⶾ��ҽ�� -- ��δʹ��

    int move_step = 0;
    if (!role->Moved)
    {
        //�����û���ƶ���������㱾�ֵĲ���
        //����
        battle_scene_->calSelectLayer(role, 0, battle_scene_->calMoveStep(role));


        //��������������20%��0.8���ʿ��ǳ�ҩ
        if (role->HP < 0.2 * role->MaxHP)
        {
            //points[5] = 0;
        }

        if (role->MP < 0.2 * role->MaxMP)
        {
            //points[5] = 0;
        }

        if (role->Morality > 50)
        {
            //��ⶾ�ģ��������������ж������ߣ��ӽ����ⶾ
            if (childs_text_["�ⶾ"]->getVisible())
            {
                for (auto r : friends)
                {
                    if (r->Poison > 50)
                    {

                    }
                }


                //points[3] == 0;
            }

            if (childs_text_["�t��"]->getVisible())
            {
                for (auto r : friends)
                {
                    if (r->HP < 0.2 * r->MaxHP)
                    {

                    }
                }
                //points[4] == 0;
            }
        }
        else
        {
            //�����ö�
            if (childs_text_["�ö�"]->getVisible())
            {
                //points[2] == 0;
            }
        }

        //ʹ����ѧ
        if (childs_text_["��W"]->getVisible())
        {
            Role* r2 = nullptr;
            int min_dis = 4096;
            for (auto r : enemies)
            {
                auto cur_dis = battle_scene_->calDistance(role, r);
                if (cur_dis < min_dis)
                {
                    r2 = r;
                    min_dis = cur_dis;
                }
            }
            role->AI_ActionX = r2->X();
            role->AI_ActionY = r2->Y();
            calDistanceLayer(role->AI_ActionX, role->AI_ActionY);

            //ѡ����Ŀ�������ĵص�

            min_dis = 4096;
            int k = 2;
            for (int ix = 0; ix < BATTLEMAP_COORD_COUNT; ix++)
            {
                for (int iy = 0; iy < BATTLEMAP_COORD_COUNT; iy++)
                {
                    if (battle_scene_->canSelect(ix, iy))
                    {
                        int cur_dis = distance_layer_->data(ix, iy);
                        if (cur_dis < min_dis || (cur_dis == min_dis && rand.rand() < 1.0 / (k++)))
                        {
                            min_dis = cur_dis;
                            role->AI_MoveX = ix;
                            role->AI_MoveY = iy;
                        }
                    }
                }
            }




            //������ѧ
            int max_hurt = -1;
            for (int i = 0; i < ROLE_MAGIC_COUNT; i++)
            {
                auto magic = Save::getInstance()->getRoleLearnedMagic(role, i);
                if (magic == nullptr) { continue; }
                int level_index = role->getRoleMagicLevelIndex(i);

                battle_scene_->calSelectLayerByMagic(role->AI_MoveX, role->AI_MoveY, role->Team, magic, level_index);

                //��������ѡ���ĵ���ԣ���������
                for (int ix = 0; ix < BATTLEMAP_COORD_COUNT; ix++)
                {
                    for (int iy = 0; iy < BATTLEMAP_COORD_COUNT; iy++)
                    {
                        int total_hurt = 0;
                        if (battle_scene_->canSelect(ix, iy))
                        {

                            battle_scene_->calEffectLayer(role->X(), role->Y(), ix, iy, magic, level_index);
                            total_hurt = battle_scene_->calAllHurt(role, magic, true);
                            if (total_hurt > max_hurt)
                            {
                                max_hurt = total_hurt;
                                role->AI_Magic = magic;
                                role->AI_ActionX = ix;
                                role->AI_ActionY = iy;
                            }
                            printf("AI %s use %s to attack (%d, %d) will get hurt: %d\n", role->Name, magic->Name, ix, iy, total_hurt);
                        }

                    }
                }
            }
            //points[1] = 0;
            role->AI_Action = getResultFromString("��W");
        }
        //�״αض������ƶ�
        return getResultFromString("�Ƅ�");
    }
    else
    {
        return role->AI_Action;
    }
}

//�������
void BattleActionMenu::calDistanceLayer(int x, int y, int max_step/*=64*/)
{
    distance_layer_->setAll(max_step + 1);
    std::vector<Point> cal_stack;
    distance_layer_->data(x, y) = 0;
    cal_stack.push_back({ x, y });
    int count = 0;
    int step = 0;
    while (step <= 64)
    {
        std::vector<Point> cal_stack_next;
        auto check_next = [&](Point p1)->void
        {
            //δ������ҿ����ߵĸ��Ӳ�����һ���ļ���
            if (distance_layer_->data(p1.x, p1.y) == max_step + 1 && battle_scene_->canWalk(p1.x, p1.y))
            {
                distance_layer_->data(p1.x, p1.y) = step + 1;
                cal_stack_next.push_back(p1);
                count++;
            }
        };
        for (auto p : cal_stack)
        {
            distance_layer_->data(p.x, p.y) = step;
            check_next({ p.x - 1, p.y });
            check_next({ p.x + 1, p.y });
            check_next({ p.x, p.y - 1 });
            check_next({ p.x, p.y + 1 });
            if (count >= distance_layer_->squareSize()) { break; }  //�������������������
        }
        if (cal_stack_next.size() == 0) { break; }  //���µĵ㣬����
        cal_stack = cal_stack_next;
        step++;
    }
}

void BattleMagicMenu::onEntrance()
{
    setVisible(true);
    std::vector<std::string> magic_names;
    for (int i = 0; i < ROLE_MAGIC_COUNT; i++)
    {
        auto m = Save::getInstance()->getRoleLearnedMagic(role_, i);
        if (m)
        {
            magic_names.push_back(convert::formatString("%s%7d", m->Name, role_->getRoleShowLearnedMagicLevel(i)));
        }
    }
    setStrings(magic_names);
    setPosition(160, 200);
}

void BattleMagicMenu::dealEvent(BP_Event& e)
{
    if (role_ == nullptr) { return; }
    if (role_->isAuto())
    {
        magic_ = role_->AI_Magic;
        setAllChildState(Normal);
        setResult(0);
        setExit(true);
        setVisible(false);
    }
    else
    {
        Menu::dealEvent(e);
    }
}

void BattleMagicMenu::onPressedOK()
{
    magic_ = Save::getInstance()->getRoleLearnedMagic(role_, result_);
    setExit(true);
}

BattleItemMenu::BattleItemMenu()
{
    setSelectUser(false);
}
