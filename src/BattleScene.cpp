#include "BattleScene.h"
#include "MainScene.h"
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include "Save.h"
#include "Menu.h"
#include "others/libconvert.h"
#include "File.h"
#include "GameUtil.h"
#include "Random.h"
#include "UIStatus.h"
#include "Font.h"
#include "Util.h"
#include "ShowRoleDifference.h"

BattleScene::BattleScene()
{
    full_window_ = 1;
    earth_layer_ = new MapSquare(COORD_COUNT);
    building_layer_ = new MapSquare(COORD_COUNT);
    role_layer_ = new MapSquare(COORD_COUNT);
    select_layer_ = new MapSquare(COORD_COUNT);
    effect_layer_ = new MapSquare(COORD_COUNT);
    battle_menu_ = new BattleMenu();
    battle_menu_->setBattleScene(this);
    battle_menu_->setPosition(160, 200);
    head_self_ = new Head();
    addChild(head_self_);
    battle_cursor_ = new BattleCursor();
    battle_cursor_->setBattleScene(this);
    save_ = Save::getInstance();
}

BattleScene::BattleScene(int id) : BattleScene()
{
    setID(id);
}

BattleScene::~BattleScene()
{
    delete battle_menu_;
    delete battle_cursor_;
    Util::safe_delete({ &earth_layer_, &building_layer_, &role_layer_, &select_layer_, &effect_layer_ });
}

void BattleScene::setID(int id)
{
    battle_id_ = id;
    info_ = BattleMap::getInstance()->getBattleInfo(id);

    BattleMap::getInstance()->copyLayerData(info_->BattleFieldID, 0, &earth_layer_->data(0));
    BattleMap::getInstance()->copyLayerData(info_->BattleFieldID, 1, &building_layer_->data(0));

    role_layer_->setAll(-1);
    select_layer_->setAll(-1);
    effect_layer_->setAll(-1);
}

void BattleScene::draw()
{
    auto r0 = battle_roles_[0];  //��ǰ�����ж��еĽ�ɫ
    Engine::getInstance()->setRenderAssistTexture();
    Engine::getInstance()->fillColor({ 0, 0, 0, 255 }, 0, 0, render_center_x_ * 2, render_center_y_ * 2);
#ifndef _DEBUG0
    for (int sum = -view_sum_region_; sum <= view_sum_region_ + 15; sum++)
    {
        for (int i = -view_width_region_; i <= view_width_region_; i++)
        {
            int i1 = man_x_ + i + (sum / 2);
            int i2 = man_y_ - i + (sum - sum / 2);
            auto p = getPositionOnRender(i1, i2, man_x_, man_y_);
            p.x += x_;
            p.y += y_;
            if (!isOutLine(i1, i2))
            {
                int num = earth_layer_->data(i1, i2) / 2;
                BP_Color color = { 255, 255, 255, 255 };
                if (battle_cursor_->isRunning())
                {
                    if (select_layer_->data(i1, i2) < 0)
                    {
                        color = { 64, 64, 64, 255 };
                    }
                    else
                    {
                        color = { 128, 128, 128, 255 };
                    }
                    if (battle_cursor_->getMode() == BattleCursor::Action)
                    {
                        if (effect_layer_->data(i1, i2) >= 0)
                        {
                            if (select_layer_->data(i1, i2) < 0)
                            {
                                color = { 160, 160, 160, 255 };
                            }
                            else
                            {
                                color = { 192, 192, 192, 255 };
                            }
                        }
                    }
                    if (i1 == select_x_ && i2 == select_y_)
                    {
                        color = { 255, 255, 255, 255 };
                    }
                }

                if (num > 0)
                {
                    TextureManager::getInstance()->renderTexture("smap", num, p.x, p.y, color);
                }
            }
        }
    }
#endif
    for (int sum = -view_sum_region_; sum <= view_sum_region_ + 15; sum++)
    {
        for (int i = -view_width_region_; i <= view_width_region_; i++)
        {
            int i1 = man_x_ + i + (sum / 2);
            int i2 = man_y_ - i + (sum - sum / 2);
            auto p = getPositionOnRender(i1, i2, man_x_, man_y_);
            p.x += x_;
            p.y += y_;
            if (!isOutLine(i1, i2))
            {
                int num = building_layer_->data(i1, i2) / 2;
                if (num > 0)
                {
                    TextureManager::getInstance()->renderTexture("smap", num, p.x, p.y);
                }
                num = role_layer_->data(i1, i2);
                if (num >= 0)
                {
                    auto r = Save::getInstance()->getRole(num);
                    std::string path = convert::formatString("fight/fight%03d", r->HeadID);
                    BP_Color color = { 255, 255, 255, 255 };
                    uint8_t alpha = 255;
                    if (battle_cursor_->isRunning())
                    {
                        color = { 128, 128, 128, 255 };
                        if (effect_layer_->data(i1, i2) >= 0)
                        {
                            if (r0->ActTeam == 0 && battle_roles_[0]->Team == r->Team)
                            {
                                color = { 255, 255, 255, 255 };
                            }
                            else if (r0->ActTeam != 0 && battle_roles_[0]->Team != r->Team)
                            {
                                uint8_t r = uint8_t(127 + RandomClassical::rand(128));
                                color = { 255, 255, 255, 255 };
                            }
                        }
                    }
                    int pic;
                    if (r == r0)
                    {
                        pic = calRolePic(r, action_type_, action_frame_);
                    }
                    else
                    {
                        pic = calRolePic(r);
                    }
                    if (r->HP <= 0) { alpha = dead_alpha_; }
                    TextureManager::getInstance()->renderTexture(path, pic, p.x, p.y, color, alpha);
                }
                if (effect_id_ >= 0 && effect_layer_->data(i1, i2) >= 0)
                {
                    std::string path = convert::formatString("eft/eft%03d", effect_id_);
                    num = effect_frame_ + RandomClassical::rand(10) - RandomClassical::rand(10);
                    TextureManager::getInstance()->renderTexture(path, num, p.x, p.y, { 255, 255, 255, 255 }, 224);
                }
            }
        }
    }
    Engine::getInstance()->renderAssistTextureToWindow();
    //printf("Battle scene drawn\n");
}

void BattleScene::dealEvent(BP_Event& e)
{
    //ѡ��λ�����������еĵ�һ����
    auto r = battle_roles_[0];

    //����һ�����Ѿ��ж�����˵�������˶��ж��ˣ�������ж�״̬����������
    if (r->Acted != 0)
    {
        resetRolesAct();
        sortRoles();
    }

    man_x_ = r->X();
    man_y_ = r->Y();
    select_x_ = r->X();
    select_y_ = r->Y();
    head_self_->setRole(r);
    head_self_->setState(Element::Pass);

    int select_act = 0;

    //ע������ֻ�ж��Ƿ�Ϊ�Զ���
    if (r->Auto == 0)
    {
        select_act = battle_menu_->runAsRole(r);
    }
    else
    {
        //�˴�ӦдAI���֣�
    }

    switch (select_act)
    {
    case 0: actMove(r); break;
    case 1: actUseMagic(r); break;
    case 2: actUsePoison(r); break;
    case 3: actDetoxification(r); break;
    case 4: actMedcine(r); break;
    case 5: actUseItem(r); break;
    case 6: actWait(r); break;
    case 7: actStatus(r); break;
    case 8: actAuto(r); break;
    case 9: actRest(r); break;
    default:
        //Ĭ��ֵΪʲô������
        break;
    }

    //������˳ɹ��ж�������ŵ���β
    if (r->Acted)
    {
        r->Moved = 0;
        battle_roles_.erase(battle_roles_.begin());
        battle_roles_.push_back(r);
        poisonEffect(r);
    }
    //��������˵�����
    clearDead();

    //���ս�����
    int battle_result = checkResult();
    //�ҷ�ʤ
    if (battle_result >= 0)
    {
        result_ == battle_result;
        setExit(true);
    }
    if (battle_result == 0 || battle_result != 0 && fail_exp_)
    {
        calExpGot();
    }
}

void BattleScene::onEntrance()
{
    calViewRegion();

    //ע���ʱ���ܵõ����ڵĴ�С����������ͷ���λ��
    head_self_->setPosition(100, 100);

    //����ȫ����ɫ��λ�ò㣬���������
    for (auto r : Save::getInstance()->getRoles())
    {
        r->setPoitionLayer(role_layer_);
        r->Team = 2;  //��ȫ�����óɲ����ڵ���Ӫ
        r->Auto = 1;
    }

    //��������λ�ú���Ӫ�������ĺ���ͳһ����
    //����
    for (int i = 0; i < TEAMMATE_COUNT; i++)
    {
        auto r = Save::getInstance()->getRole(Save::getInstance()->Team[i]);
        if (r)
        {
            battle_roles_.push_back(r);
            r->setPosition(info_->TeamMateX[i], info_->TeamMateY[i]);
            r->Team = 0;
            r->Auto = 0;
        }
    }
    //�з�
    for (int i = 0; i < BATTLE_ENEMY_COUNT; i++)
    {
        auto r = Save::getInstance()->getRole(info_->Enemy[i]);
        if (r)
        {
            battle_roles_.push_back(r);
            r->setPosition(info_->EnemyX[i], info_->EnemyY[i]);
            r->Team = 1;
            r->Auto = 1;
        }
    }

    //��ʼ״̬
    for (auto r : battle_roles_)
    {
        setRoleInitState(r);
    }
    //����
    sortRoles();
}

void BattleScene::onExit()
{
    //���ȫ����ɫ��λ�ò�
    for (auto r : Save::getInstance()->getRoles())
    {
        r->setPoitionLayer(nullptr);
    }
}

void BattleScene::setRoleInitState(Role* r)
{
    r->Acted = 0;
    r->ExpGot = 0;
    r->ShowString = "";
    r->FightingFrame = 0;
    r->Auto = 0;

    //��ȡ����֡��
    bool frame_readed = false;
    //ע������жϲ�̫׼��Ӧ���ڹ��캯��������һ��������ĳ�ֵ
    /*for (int i = 0; i < 5; i++)
    {
        if (r->FightFrame[i] > 0)
        {
            frame_readed = true;
            break;
        }
    }*/
    if (!frame_readed)
    {
        readFightFrame(r);
    }

    //Ѱ�����Լ�����ĵз�����������
    int min_distance = COORD_COUNT * COORD_COUNT;
    Role* r_near;
    for (auto r1 : battle_roles_)
    {
        if (r->Team != r1->Team)
        {
            int dis = calDistance(r, r1);
            if (dis < min_distance)
            {
                r_near = r1;
                min_distance = dis;
            }
        }
    }

    r->FaceTowards = calTowards(r->X(), r->Y(), r_near->X(), r_near->Y());
    //r->FaceTowards = RandomClassical::rand(4);  //ûͷ��Ӭ����ѡ������
}

void BattleScene::readFightFrame(Role* r)
{
    for (int i = 0; i < 5; i++)
    {
        r->FightFrame[i] = 0;
    }
    std::string file = convert::formatString("../game/resource/fight/fight%03d/fightframe.txt", r->HeadID);
    std::string frame_txt = convert::readStringFromFile(file);
    std::vector<int> frames;
    convert::findNumbers(frame_txt, &frames);
    for (int i = 0; i < frames.size() / 2; i++)
    {
        r->FightFrame[frames[i * 2]] = frames[i * 2 + 1];
    }
}

//��ɫ����
void BattleScene::sortRoles()
{
    std::sort(battle_roles_.begin(), battle_roles_.end(), compareRole);
}

//��ɫ����Ĺ���
bool BattleScene::compareRole(Role* r1, Role* r2)
{
    return r1->Speed > r2->Speed;
}

void BattleScene::resetRolesAct()
{
    for (auto r : battle_roles_)
    {
        r->Acted = 0;
    }
}

//������ƶ�����(����װ��)
int BattleScene::calMoveStep(Role* r)
{
    int speed = r->Speed;
    if (r->Equip1 >= 0)
    {
        auto i = Save::getInstance()->getItem(r->Equip1);
        speed += i->AddSpeed;
    }
    if (r->Equip2 >= 0)
    {
        auto i = Save::getInstance()->getItem(r->Equip2);
        speed += i->AddSpeed;
    }
    return speed / 15 + 1;
}

//���ݶ���֡�������ɫ����ͼ���
int BattleScene::calRolePic(Role* r, int style, int frame)
{
    if (r->FightFrame[style] <= 0)
    {
        style = -1;
    }
    if (style == -1)
    {
        for (int i = 0; i < 5; i++)
        {
            if (r->FightFrame[i] > 0)
            {
                return r->FightFrame[i] * r->FaceTowards;
            }
        }
    }
    else
    {
        int total = 0;
        for (int i = 0; i < 5; i++)
        {
            if (i == style)
            {
                return total + r->FightFrame[style] * r->FaceTowards + frame;
            }
            total += r->FightFrame[i] * 4;
        }
    }
    return r->FaceTowards;
}

//������Ա�ѡ��ķ�Χ�����дѡ���
//mode���壺0-�ƶ����ܲ������ϰ�Ӱ�죻1�����ö�ҽ�ƵȽ��ܲ���Ӱ�죻2�鿴״̬��ȫ����ѡ��3����ѡֱ�ߵĸ���
void BattleScene::calSelectLayer(Role* r, int mode, int step)
{
    if (mode == 0)
    {
        select_layer_->setAll(-1);
        std::vector<Point> cal_stack;
        cal_stack.push_back({ r->X(), r->Y() });
        int count = 0;
        while (step >= 0)
        {
            std::vector<Point> cal_stack_next;
            for (auto p : cal_stack)
            {
                select_layer_->data(p.x, p.y) = step;
                auto check_next = [&](Point p1)->void
                {
                    //δ������ҿ����ߵĸ��Ӳ�����һ���ļ���
                    if (canWalk(p1.x, p1.y) && select_layer_->data(p1.x, p1.y) == -1)
                    {
                        cal_stack_next.push_back(p1);
                        count++;
                    }
                };
                //����Ƿ��ڵз����ԣ�������򿪴�ѡ��
                if (!isNearEnemy(r, p.x, p.y))
                {
                    //���4�����ڵ�
                    check_next({ p.x - 1, p.y });
                    check_next({ p.x + 1, p.y });
                    check_next({ p.x, p.y - 1 });
                    check_next({ p.x, p.y + 1 });
                }
                if (count >= COORD_COUNT * COORD_COUNT) { break; }  //�������������������
            }
            cal_stack = cal_stack_next;
            step--;
        }
    }
    else if (mode == 1)
    {
        for (int ix = 0; ix < COORD_COUNT; ix++)
        {
            for (int iy = 0; iy < COORD_COUNT; iy++)
            {
                select_layer_->data(ix, iy) = step - calDistance(ix, iy, r->X(), r->Y());
            }
        }
    }
    else if (mode == 2)
    {
        select_layer_->setAll(0);
    }
    else if (mode == 3)
    {
        for (int ix = 0; ix < COORD_COUNT; ix++)
        {
            for (int iy = 0; iy < COORD_COUNT; iy++)
            {
                int dx = abs(ix - r->X());
                int dy = abs(iy - r->Y());
                if (dx == 0 && dy <= step || dy == 0 && dx <= step)
                {
                    select_layer_->data(ix, iy) = 0;
                }
                else
                {
                    select_layer_->data(ix, iy) = -1;
                }
            }
        }
    }
}

void BattleScene::calEffectLayer(Role* r, Magic* m, int level_index)
{
    effect_layer_->setAll(-1);

    //��δָ����ѧ������Ϊֻѡ��һ����
    if (m == nullptr || m->AttackAreaType == 0)
    {
        effect_layer_->data(select_x_, select_y_) = 0;
        return;
    }

    level_index = Save::getInstance()->getRoleLearnedMagicLevelIndex(r, m);

    //�˴��Ƚ���׸����������
    if (m->AttackAreaType == 1)
    {
        int x = r->X(), y = r->Y();
        select_x_ = x;
        select_y_ = y;
        int dis = m->SelectDistance[level_index];
        for (int ix = x - dis; ix <= x + dis; ix++)
        {
            for (int iy = y - dis; iy <= y + dis; iy++)
            {
                if (!isOutLine(ix, iy) && (x == ix || y == iy) && calTowards(x, y, ix, iy) == towards_)
                {
                    effect_layer_->data(ix, iy) = 0;
                }
            }
        }
    }
    else if (m->AttackAreaType == 2)
    {
        int x = r->X(), y = r->Y();
        select_x_ = x;
        select_y_ = y;
        int dis = m->SelectDistance[level_index];
        for (int ix = x - dis; ix <= x + dis; ix++)
        {
            for (int iy = y - dis; iy <= y + dis; iy++)
            {
                if (!isOutLine(ix, iy) && (x == ix || y == iy))
                {
                    effect_layer_->data(ix, iy) = 0;
                }
            }
        }
    }
    else if (m->AttackAreaType == 3)
    {
        int x = select_x_, y = select_y_;
        //effect_layer_.setAll(-1);
        int dis = m->AttackDistance[level_index];
        for (int ix = x - dis; ix <= x + dis; ix++)
        {
            for (int iy = y - dis; iy <= y + dis; iy++)
            {
                if (!isOutLine(ix, iy))
                {
                    effect_layer_->data(ix, iy) = 0;
                }
            }
        }
    }
}

bool BattleScene::canSelect(int x, int y)
{
    return (!isOutLine(x, y) && select_layer_->data(x, y) >= 0);
}

void BattleScene::walk(Role* r, int x, int y, Towards t)
{
    if (canWalk(x, y))
    {
        r->setPosition(x, y);
    }
}

bool BattleScene::canWalk(int x, int y)
{
    if (isOutLine(x, y) || isBuilding(x, y) || isWater(x, y) || isRole(x, y))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool BattleScene::isBuilding(int x, int y)
{
    return building_layer_->data(x, y) > 0;
}

bool BattleScene::isOutLine(int x, int y)
{
    return (x < 0 || x >= COORD_COUNT || y < 0 || y >= COORD_COUNT);
}

bool BattleScene::isWater(int x, int y)
{
    int num = earth_layer_->data(x, y) / 2;
    if (num >= 179 && num <= 181
        || num == 261 || num == 511
        || num >= 662 && num <= 665
        || num == 674)
    {
        return true;
    }
    return false;
}

bool BattleScene::isRole(int x, int y)
{
    return role_layer_->data(x, y) > 0;
}

bool BattleScene::isOutScreen(int x, int y)
{
    return (abs(man_x_ - x) >= 16 || abs(man_y_ - y) >= 20);
}

bool BattleScene::isNearEnemy(Role* r, int x, int y)
{
    for (auto r1 : battle_roles_)
    {
        if (r->Team != r1->Team && calDistance(r1->X(), r1->Y(), x, y) <= 1)
        {
            return true;
        }
    }
    return false;
}

//��ȡǡ����ѡ���Ľ�ɫ
Role* BattleScene::getSelectedRole()
{
    int r = role_layer_->data(select_x_, select_y_);
    return Save::getInstance()->getRole(r);
}

void BattleScene::actMove(Role* r)
{
    int step = calMoveStep(r);
    calSelectLayer(r, 0, step);
    battle_cursor_->setRoleAndMagic(r);
    battle_cursor_->setMode(BattleCursor::Move);
    if (battle_cursor_->run() == 0)
    {
        r->setPrevPosition(r->X(), r->Y());
        moveAnimation(r, select_x_, select_y_);
        r->Moved = 1;
    }
}

void BattleScene::actUseMagic(Role* r)
{
    auto magic_menu = new MenuText();
    std::vector<std::string> magic_names;
    for (int i = 0; i < ROLE_MAGIC_COUNT; i++)
    {
        auto m = Save::getInstance()->getRoleLearnedMagic(r, i);
        if (m)
        {
            magic_names.push_back(convert::formatString("%s%7d", m->Name, r->MagicLevel[i]));
        }
    }
    magic_menu->setStrings(magic_names);
    magic_menu->setPosition(160, 200);

    while (true)
    {
        int select_magic = magic_menu->run();
        if (select_magic < 0) { break; }

        r->ActTeam = 1;
        auto magic = Save::getInstance()->getRoleLearnedMagic(r, select_magic);
        //level_index��ʾ��0��9����level��0��999
        int level_index = r->getRoleMagicLevelIndex(select_magic);
        //�����ѡ��ķ�Χ
        if (magic->AttackAreaType == 0 || magic->AttackAreaType == 3)
        {
            calSelectLayer(r, 1, magic->SelectDistance[level_index]);
        }
        else
        {
            calSelectLayer(r, 3, magic->SelectDistance[level_index]);
        }
        //ѡ��Ŀ��
        battle_cursor_->setMode(BattleCursor::Action);
        battle_cursor_->setRoleAndMagic(r, magic, level_index);
        towards_ = r->FaceTowards;
        calEffectLayer(r, magic, level_index);
        int selected = battle_cursor_->run();
        //ȡ��ѡ��Ŀ�������½���ѡ�书
        if (selected < 0)
        {
            continue;
        }
        else
        {
            //���Ź������棬�����˺�
            useMagicAnimation(r, magic);
            calAllHurt(r, magic);
            showNumberAnimation();
            r->Acted = 1;
            break;
        }
    }
    delete magic_menu;
}

void BattleScene::actUsePoison(Role* r)
{
    calSelectLayer(r, 1, r->UsePoison / 15 + 1);
    battle_cursor_->setMode(BattleCursor::Action);
    battle_cursor_->setRoleAndMagic(r);
    r->ActTeam = 1;
    calEffectLayer(r);
    int selected = battle_cursor_->run();
    if (selected >= 0)
    {
        auto r2 = getSelectedRole();
        if (r2)
        {
            int v = GameUtil::usePoison(r, r2);
            r2->ShowString = convert::formatString("%+d", v);
            r2->ShowColor = { 20, 255, 20, 255 };
        }
        r->PhysicalPower = GameUtil::limit(r->PhysicalPower - 3, 0, MAX_PHYSICAL_POWER);
        actionAnimation(r, 0, 30);
        showNumberAnimation();
        r->Acted = 1;
    }
}

void BattleScene::actDetoxification(Role* r)
{
    calSelectLayer(r, 1, r->Detoxification / 15 + 1);
    battle_cursor_->setMode(BattleCursor::Action);
    battle_cursor_->setRoleAndMagic(r);
    r->ActTeam = 0;
    calEffectLayer(r);
    int selected = battle_cursor_->run();
    if (selected >= 0)
    {
        auto r2 = getSelectedRole();
        if (r2)
        {
            int v = GameUtil::detoxification(r, r2);
            r2->ShowString = convert::formatString("-%d", -v);
            r2->ShowColor = { 20, 200, 255, 255 };
        }
        r->PhysicalPower = GameUtil::limit(r->PhysicalPower - 5, 0, MAX_PHYSICAL_POWER);
        actionAnimation(r, 0, 36);
        showNumberAnimation();
        r->Acted = 1;
    }
}

void BattleScene::actMedcine(Role* r)
{
    calSelectLayer(r, 1, r->Medcine / 15 + 1);
    battle_cursor_->setMode(BattleCursor::Action);
    battle_cursor_->setRoleAndMagic(r);
    r->ActTeam = 0;
    calEffectLayer(r);
    int selected = battle_cursor_->run();
    if (selected >= 0)
    {
        auto r2 = getSelectedRole();
        if (r2)
        {
            int v = GameUtil::medcine(r, r2);
            r2->ShowString = convert::formatString("%+d", v);
            r2->ShowColor = { 255, 255, 200, 255 };
        }
        r->PhysicalPower = GameUtil::limit(r->PhysicalPower - 5, 0, MAX_PHYSICAL_POWER);
        actionAnimation(r, 0, 0);
        showNumberAnimation();
        r->Acted = 1;
    }
}

void BattleScene::actUseItem(Role* r)
{

}

//�ȴ������Լ����뵽���һ��û�ж����˵ĺ���
void BattleScene::actWait(Role* r)
{
    for (int i = 1; i < battle_roles_.size(); i++)
    {
        if (battle_roles_[i]->Acted == 0)
        {
            battle_roles_.erase(battle_roles_.begin());
            battle_roles_.insert(battle_roles_.begin() + i, r);
        }
    }
}

void BattleScene::actStatus(Role* r)
{
    head_self_->setVisible(false);
    battle_cursor_->getHead()->setVisible(false);
    battle_cursor_->getUIStatus()->setVisible(true);

    calSelectLayer(r, 2, 0);
    battle_cursor_->setRoleAndMagic(r);
    battle_cursor_->setMode(BattleCursor::Check);
    battle_cursor_->run();

    head_self_->setVisible(true);
    battle_cursor_->getHead()->setVisible(true);
    battle_cursor_->getUIStatus()->setVisible(false);
}

void BattleScene::actAuto(Role* r)
{

}

void BattleScene::actRest(Role* r)
{
    r->PhysicalPower = GameUtil::limit(r->PhysicalPower + 5, 0, MAX_PHYSICAL_POWER);
    r->HP = GameUtil::limit(r->HP + 0.05 * r->MaxHP, 0, r->MaxHP);
    r->MP = GameUtil::limit(r->MP + 0.05 * r->MaxMP, 0, r->MaxMP);
    r->Acted = 1;
}

//�ƶ�����
void BattleScene::moveAnimation(Role* r, int x, int y)
{
    //��Ŀ��������ȷ��·��
    std::vector<Point> way;
    auto check_next = [&](Point p1, int step)->bool
    {
        if (canSelect(p1.x, p1.y) && select_layer_->data(p1.x, p1.y) == step)
        {
            way.push_back(p1);
            return true;
        }
        return false;
    };

    way.push_back({ x, y });
    for (int i = select_layer_->data(x, y); i < select_layer_->data(r->X(), r->Y()); i++)
    {
        int x1 = way.back().x, y1 = way.back().y;
        if (check_next({ x1 - 1, y1 }, i + 1)) { continue; }
        if (check_next({ x1 + 1, y1 }, i + 1)) { continue; }
        if (check_next({ x1, y1 - 1 }, i + 1)) { continue; }
        if (check_next({ x1, y1 + 1 }, i + 1)) { continue; }
    }

    for (int i = way.size() - 2; i >= 0; i--)
    {
        r->FaceTowards = calTowards(r->X(), r->Y(), way[i].x, way[i].y);
        r->setPosition(way[i].x, way[i].y);
        //setPosition(r->X(), r->Y());
        drawAndPresent(2);
    }
    r->setPosition(x, y);
    r->Moved = 1;
    select_layer_->setAll(-1);
}

//ʹ����ѧ����
void BattleScene::useMagicAnimation(Role* r, Magic* m)
{
    if (r && m)
    {
        actionAnimation(r, m->MagicType, m->EffectID);
    }
}

void BattleScene::actionAnimation(Role* r, int style, int effect_id, int shake /*= 0*/)
{
    if (r->X() != select_x_ || r->Y() != select_y_)
    {
        r->FaceTowards = calTowards(r->X(), r->Y(), select_x_, select_y_);
    }
    auto frame_count = r->FightFrame[style];
    action_type_ = style;
    for (action_frame_ = 0; action_frame_ < frame_count; action_frame_++)
    {
        drawAndPresent(animation_delay_);
    }
    action_frame_ = frame_count - 1;
    effect_id_ = effect_id;
    auto path = convert::formatString("eft/eft%03d", effect_id_);
    auto effect_count = TextureManager::getInstance()->getTextureGroupCount(path);
    for (effect_frame_ = 0; effect_frame_ < effect_count + 10; effect_frame_++)
    {
        if (shake > 0)
        {
            x_ = RandomClassical::rand(shake) - RandomClassical::rand(shake);
            y_ = RandomClassical::rand(shake) - RandomClassical::rand(shake);
        }
        drawAndPresent(animation_delay_);
    }
    action_frame_ = 0;
    action_type_ = -1;
    effect_frame_ = 0;
    effect_id_ = -1;
    x_ = 0;
    y_ = 0;
}

//r1ʹ���书magic����r2���˺������Ϊһ����
int BattleScene::calHurt(Role* r1, Role* r2, Magic* magic)
{
    int level_index = Save::getInstance()->getRoleLearnedMagicLevelIndex(r1, magic);

    int attack = r1->Attack + magic->Attack[level_index] / 3;
    int defence = r2->Defence;
    int v = attack - defence;
    v += RandomClassical::rand(10) - RandomClassical::rand(10);
    if (v < 1) { v = 1; }
    v = 999;  //������
    return v;
}

//����ȫ��������˺�
int BattleScene::calAllHurt(Role* r, Magic* m)
{
    int total = 0;
    for (auto r2 : battle_roles_)
    {
        //���ҷ��ұ����У�������λ�õ�Ч����Ǹ���
        if (r2->Team != r->Team && effect_layer_->data(r2->X(), r2->Y()) >= 0)
        {
            int hurt = calHurt(r, r2, m);
            r2->ShowString = convert::formatString("-%d", hurt);
            r2->ShowColor = { 255, 20, 20, 255 };
            r2->HP = GameUtil::limit(r2->HP - hurt, 0, r2->MaxHP);
            total += hurt;
        }
    }
    return total;
}

void BattleScene::showNumberAnimation()
{
    //�ж��Ƿ�����Ҫ��ʾ������
    bool need_show = false;
    for (auto r : battle_roles_)
    {
        if (!r->ShowString.empty())
        {
            need_show = true;
            break;
        }
    }
    if (!need_show) { return; }

    int size = 28;
    for (int i = 0; i <= 10; i++)
    {
        auto drawNumber = [&](void*)->void
        {
            for (auto r : battle_roles_)
            {
                if (!r->ShowString.empty())
                {
                    auto p = getPositionOnWindow(r->X(), r->Y(), man_x_, man_y_);
                    int x = p.x - size * r->ShowString.size() / 4;
                    int y = p.y - 75 - i * 2;
                    Font::getInstance()->draw(r->ShowString, size, x, y, r->ShowColor, 255 - 20 * i);
                }
            }
        };
        drawAndPresent(animation_delay_, drawNumber);
    }
    //��������˵���ʾ
    for (auto r : battle_roles_)
    {
        r->ShowString.clear();
    }
}

void BattleScene::clearDead()
{
    //�ж��Ƿ�����Ӧ�˳�
    bool found_dead = false;
    for (auto r : battle_roles_)
    {
        if (r->HP <= 0)
        {
            found_dead = true;
            break;
        }
    }
    if (!found_dead) { return; }

    //�˳���������������
    for (int i = 0; i <= 25; i++)
    {
        dead_alpha_ = 255 - i * 10;
        if (dead_alpha_ < 0) { dead_alpha_ = 0; }
        drawAndPresent(animation_delay_);
    }

    std::vector<Role*> alive;
    for (auto r : battle_roles_)
    {
        if (r->HP > 0)
        {
            alive.push_back(r);
        }
        else
        {
            r->setPosition(-1, -1);
        }
    }
    battle_roles_ = alive;
}

//�ж���Ч��
void BattleScene::poisonEffect(Role* r)
{
    if (r)
    {
        r->HP -= r->Poison / 3;
        //��Ϳ۵�1��
        if (r->HP < 1) { r->HP = 1; }
    }
}

int BattleScene::getTeamMateCount(int team)
{
    int count = 0;
    for (auto r : battle_roles_)
    {
        if (r->Team == team)
        {
            count++;
        }
    }
    return count;
}

//����Ƿ���һ��ȫ��
//���ظ�ֵ��ʾ������������طǸ���Ϊʤ������team���
//ʵ����ֻ�Ǽ���ҷ������뵱ǰ�������Ƿ���Ȼ���Ϊ0
//�����ӵ��ж���ʹ��set����map
int BattleScene::checkResult()
{
    int team0 = getTeamMateCount(0);
    if (team0 == battle_roles_.size()) { return 0; }
    if (team0 == 0) { return 1; }
    return -1;
}

void BattleScene::calExpGot()
{
    head_self_->setVisible(false);

    std::vector<Role*> alive_teammate;
    for (auto r : battle_roles_)
    {
        if (r->Team == 0)
        {
            alive_teammate.push_back(r);
        }
    }

    //���ڳ����˻�þ��飬����
    auto diff = new ShowRoleDifference();

    for (auto r : alive_teammate)
    {
        Role r0 = *r;  //���ڱȽϵ�״̬
        r->ExpGot += info_->Exp / alive_teammate.size();

        auto item = Save::getInstance()->getItem(r->PracticeItem);

        if (r->Level >= MAX_LEVEL)
        {
            //��������ȫ�ӵ���Ʒ����
            r->ExpForItem += r->ExpGot;
        }
        else if (item)
        {
            //δ������ƽ�־���
            r->Exp += r->ExpGot / 2;
            r->ExpForItem += r->ExpGot / 2;
        }
        else
        {
            //�������ȫ�ӵ����ﾭ��
            r->Exp += r->ExpGot;
        }

        //����Խ��
        if (r->Exp < r0.Exp) { r->Exp == MAX_EXP; }
        if (r->ExpForItem < r0.ExpForItem) { r->ExpForItem == MAX_EXP; }

        //����
        int change = 0;
        while (GameUtil::canLevelUp(r))
        {
            GameUtil::levelUp(r);
            change++;
        }
        if (change)
        {
            diff->setTwinRole(&r0, r);
            diff->setText("����");
            diff->run();
        }

        //��������
        if (item)
        {
            r0 = *r;
            change = 0;
            while (GameUtil::canFinishedItem(r))
            {
                GameUtil::useItem(r, item);
                change++;
            }
            if (change)
            {
                diff->setTwinRole(&r0, r);
                diff->setText(convert::formatString("�ޟ�%s�ɹ�", item->Name));
                diff->run();
            }
        }
    }
    delete diff;
}

