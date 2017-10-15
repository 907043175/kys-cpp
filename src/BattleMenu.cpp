#include "BattleMenu.h"
#include "Save.h"
#include "Random.h"
#include "BattleScene.h"
#include "others\libconvert.h"
#include "Event.h"

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

    childs_text_["�ȴ�"]->setVisible(false);  //���õȴ�

    setFontSize(20);
    arrange(0, 0, 0, 28);
    pass_child_ = findFristVisibleChild();
    forcePassChild();
    if (!role_->Moved) { role_->AI_Action = -1; }  //����Ϊδ�����ai���ж�
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

    //aiΪÿ���ж�����
    std::vector<AIAction> ai_action;

    if (role->AI_Action == -1)
    {
        //��ʼ���㱾�ֵĲ���
        role->AI_Action == getResultFromString("�Y��");
        role->AI_MoveX = role->X();
        role->AI_MoveY = role->Y();
        role->AI_ActionX = role->X();
        role->AI_ActionY = role->Y();
        role->AI_Magic = nullptr;
        role->AI_Item = nullptr;

        //��������ƶ���λ��
        battle_scene_->calSelectLayer(role, 0, battle_scene_->calMoveStep(role));

        //���ǳ�ҩ

        std::string action_text = "ˎƷ";
        if (childs_text_[action_text]->getVisible() &&
            (role->HP < 0.2 * role->MaxHP || role->MP < 0.2 * role->MaxMP || role_->PhysicalPower < 0.2 * MAX_PHYSICAL_POWER))
        {
            AIAction aa;
            aa.Action = getResultFromString(action_text);
            auto item_menu = new BattleItemMenu();
            item_menu->setRole(role);
            item_menu->setForceItemType(2);
            item_menu->run();
            aa.item = item_menu->getCurrentItem();
            delete item_menu;
            if (aa.item)
            {
                //�������Ϲ���
                aa.point = std::max(aa.item->AddHP, aa.item->AddMP) + role->MaxHP - role->HP;
                getFarthestToAll(role, enemies, aa.MoveX, aa.MoveY);
                ai_action.push_back(aa);
            }
        }

        //�ⶾ��ҽ�ƣ��ö�����Ϊ��������
        if (role->Morality > 50)
        {
            action_text = "�ⶾ";
            //��ⶾ�ģ��������������ж������ߣ��ӽ����ⶾ
            if (childs_text_[action_text]->getVisible())
            {
                for (auto r2 : friends)
                {
                    if (r2->Poison > 50)
                    {
                        int action_dis = battle_scene_->calMoveStep(role) + battle_scene_->calActionStep(role->Detoxification);
                        int dis = battle_scene_->calDistance(role, r2);
                        if (action_dis >= dis)
                        {
                            AIAction aa;
                            aa.Action = getResultFromString(action_text);
                            calAIActionNearest(r2, aa);
                            aa.point = r2->Poison;
                            ai_action.push_back(aa);
                        }
                    }
                }
            }
            action_text = "�t��";
            if (childs_text_[action_text]->getVisible())
            {
                for (auto r2 : friends)
                {
                    if (r2->HP < 0.2 * r2->MaxHP)
                    {
                        int action_dis = battle_scene_->calMoveStep(role) + battle_scene_->calActionStep(role->Medcine);
                        int dis = battle_scene_->calDistance(role, r2);
                        if (action_dis >= dis)
                        {
                            AIAction aa;
                            aa.Action = getResultFromString(action_text);
                            calAIActionNearest(r2, aa);
                            aa.point = role->Medcine;
                            ai_action.push_back(aa);
                        }
                    }
                }
            }
        }
        else
        {
            //�����ö�
            action_text = "�ö�";
            if (childs_text_[action_text]->getVisible())
            {
                auto r2 = getNearestRole(role, enemies);
                int action_dis = battle_scene_->calMoveStep(role) + battle_scene_->calActionStep(role->UsePoison);
                int dis = battle_scene_->calDistance(role, r2);
                if (action_dis >= dis)
                {
                    AIAction aa;
                    aa.Action = getResultFromString(action_text);
                    calAIActionNearest(r2, aa);
                    aa.point = std::min(MAX_POISON - r2->Poison, role->UsePoison);
                    ai_action.push_back(aa);
                }
            }
        }

        //ʹ�ð���
        action_text = "����";
        if (childs_text_[action_text]->getVisible())
        {
            auto r2 = getNearestRole(role, enemies);
            int action_dis = battle_scene_->calMoveStep(role) + battle_scene_->calActionStep(role->HiddenWeapon);
            int dis = battle_scene_->calDistance(role, r2);
            if (action_dis >= dis)
            {
                auto item_menu = new BattleItemMenu();
                item_menu->setRole(role);
                item_menu->setForceItemType(3);
                item_menu->run();
                auto item = item_menu->getCurrentItem();
                delete item_menu;
                if (item)
                {
                    AIAction aa;
                    aa.Action = getResultFromString(action_text);
                    calAIActionNearest(r2, aa);
                    aa.point = -item->AddHP;
                    aa.item = item;
                    ai_action.push_back(aa);
                }
            }
        }

        //ʹ����ѧ
        action_text = "��W";
        if (childs_text_[action_text]->getVisible())
        {
            AIAction aa;
            aa.Action = getResultFromString(action_text);
            auto r2 = getNearestRole(role, enemies);
            calAIActionNearest(r2, aa);
            //������ѧ
            int max_hurt = -1;
            for (int i = 0; i < ROLE_MAGIC_COUNT; i++)
            {
                auto magic = Save::getInstance()->getRoleLearnedMagic(role, i);
                if (magic == nullptr) { continue; }
                int level_index = role->getRoleMagicLevelIndex(i);

                battle_scene_->calSelectLayerByMagic(aa.MoveX, aa.MoveY, role->Team, magic, level_index);
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
                                aa.magic = magic;
                                aa.ActionX = ix;
                                aa.ActionY = iy;
                            }
                            printf("AI %s use %s to attack (%d, %d) will get hurt: %d\n", role->Name, magic->Name, ix, iy, total_hurt);
                        }
                    }
                }
            }
            aa.point = max_hurt / 2;
            ai_action.push_back(aa);
        }

        //����������ֵ��ж�
        int point = -1;
        for (auto aa : ai_action)
        {
            printf("%s: %d\n", getStringFromResult(aa.Action).c_str(), aa.point);
            if (aa.point >= point)
            {
                point = aa.point;
                setAIActionToRole(aa, role);
            }
        }
    }

    if (!role->Moved)
    {
        //δ�ƶ��򷵻��ƶ�
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

void BattleActionMenu::getFarthestToAll(Role* role, std::vector<Role*> roles, int& x, int& y)
{
    Random<double> rand;   //÷ɭ��ת�������
    rand.set_seed();
    //ѡ�������ез���������ĵ�
    int max_dis = 0;
    int k = 2;  //������ʼ��㷽���ǳ���ָ����ͬ�ĵ�ʱ��ѡ���ĸ�����ͬ
    for (int ix = 0; ix < BATTLEMAP_COORD_COUNT; ix++)
    {
        for (int iy = 0; iy < BATTLEMAP_COORD_COUNT; iy++)
        {
            if (battle_scene_->canSelect(ix, iy))
            {
                int cur_dis = 0;
                for (auto r2 : roles)
                {
                    cur_dis += battle_scene_->calDistance(role, r2);
                }
                if (cur_dis > max_dis || (cur_dis == max_dis && rand.rand() < 1.0 / (k++)))
                {
                    max_dis = cur_dis;
                    x = ix;
                    y = iy;
                }
            }
        }
    }
}

void BattleActionMenu::getNearestPosition(int x0, int y0, int& x, int& y)
{
    Random<double> rand;   //÷ɭ��ת�������
    rand.set_seed();
    calDistanceLayer(x0, y0);
    printf("%d %d %d\n", x0, y0, battle_scene_->select_layer_->data(x0,y0));
    int min_dis = BATTLEMAP_COORD_COUNT * BATTLEMAP_COORD_COUNT;
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
                    x = ix;
                    y = iy;
                }
            }
        }
    }
}

Role* BattleActionMenu::getNearestRole(Role* role, std::vector<Role*> roles)
{
    int min_dis = 4096;
    Role* r2 = nullptr;
    //ѡ���������ĵ���
    for (auto r : roles)
    {
        auto cur_dis = battle_scene_->calDistance(role, r);
        if (cur_dis < min_dis)
        {
            r2 = r;
            min_dis = cur_dis;
        }
    }
    return r2;
}

//�����ȼ���ÿ����ƶ��ķ�Χ
void BattleActionMenu::calAIActionNearest(Role* r2, AIAction& aa)
{
    getNearestPosition(r2->X(), r2->Y(), aa.MoveX, aa.MoveY);
    aa.ActionX = r2->X();
    aa.ActionY = r2->Y();
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

void BattleItemMenu::dealEvent(BP_Event& e)
{
    if (role_ == nullptr) { return; }
    if (role_->isAuto())
    {
        if (role_->AI_Item)
        {
            current_item_ = role_->AI_Item;
            setExit(true);
            return;
        }
        std::vector<Item*> items;
        //ѡ����Ʒ�б�
        if (role_->Team == 0)
        {
            geItemsByType(force_item_type_);
        }
        else
        {
            available_items_.clear();
            for (int i = 0; i < ROLE_TAKING_ITEM_COUNT; i++)
            {
                auto item = Save::getInstance()->getItem(role_->TakingItem[i]);
                if (getItemDetailType(item) == force_item_type_)
                {
                    available_items_.push_back(item);
                }
            }
        }
        //���ѡһ��
        current_item_ = getAvailableItem(RandomClassical::rand(available_items_.size()));
        setExit(true);
    }
    else
    {
        UIItem::dealEvent(e);
    }
}

void BattleItemMenu::addItem(Item* item, int count)
{
    if (role_->Team == 0)
    {
        Event::getInstance()->addItemWithoutHint(item->ID, count);
    }
    else
    {
        Event::getInstance()->roleAddItem(role_->ID, item->ID, count);
    }
}
