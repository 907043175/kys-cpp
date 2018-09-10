#include "BattleMod.h"
#include "GameUtil.h"
#include "Save.h"
#include "Font.h"
#include "libconvert.h"
#include "PotConv.h"
#include "Event.h"
#include "DrawableOnCall.h"
#include "TeamMenu.h"
#include "BattleConfig.h"
#include "ShowExp.h"
#include "MagicEffectDrawable.h"

#include <numeric>
#include <cassert>
#include <unordered_set>

using namespace BattleMod;


BattleModifier::BattleModifier() {
    printf("this is modified battle scene.\n");
    // ǿ�ư뼴ʱ
    semi_real_ = true;
}

void BattleMod::BattleModifier::setID(int id)
{
    BattleScene::rng_.set_seed(Save::getInstance()->Seed + id);
    BattleScene::setID(id);
}

void BattleModifier::setRoleInitState(Role* r)
{
    BattleScene::setRoleInitState(r);
    if (r->RealID == -1)
        r->RealID = r->ID;
    printf("ID %d realID %d Team %d\n", r->ID, r->RealID, r->Team);
    // TODO �޸�����޴�������
    conf.battleStatusManager[r->ID].initStatus(r);

    // ���r��ʼ�H�H���S�޸Ġ�B��ǿ��)
    EffectManager startMang;
    conf.tryProcAndAddToManager(conf.startAll, startMang, r, nullptr, nullptr);
}

void BattleMod::BattleModifier::addAtkAnim(Role * r, BP_Color color, const std::vector<EffectIntsPair> & eips)
{
    std::string showStrs;
    for (const auto& eip : eips) {
        if (!eip.description.empty()) {
            if (eip.position == EffectDisplayPosition::on_top) {
                atkNames_.push_back(std::cref(eip.description));
            }
            else if (eip.position == EffectDisplayPosition::on_person) {
                if (showStrs.empty()) {
                    showStrs = eip.description;
                }
                else {
                    showStrs += " + " + eip.description;
                }
            }
            // ֱ�Ӹ���?
            if (r->Show.Effect == -1 && eip.getAnimation() != -1) {
                r->Show.Effect = eip.getAnimation();
            }
        }
    }
    if (!showStrs.empty()) {
        r->addShowString(showStrs, color);
    }
}

void BattleMod::BattleModifier::addDefAnim(Role * r, BP_Color color, const std::vector<EffectIntsPair>& eips)
{
    std::string showStrs;
    for (const auto& eip : eips) {
        if (!eip.description.empty() && eip.position != EffectDisplayPosition::no) {
            if (showStrs.empty()) {
                showStrs = eip.description;
            }
            else {
                showStrs += " + " + eip.description;
            }
        }
        if (r->Show.Effect == -1 && eip.getAnimation() != -1) {
            r->Show.Effect = eip.getAnimation();
        }
    }
    if (!showStrs.empty()) {
        r->addShowString(showStrs, color);
    }
}

void BattleMod::BattleModifier::actRest(Role * r)
{
    r->PhysicalPower = GameUtil::limit(r->PhysicalPower + 5, 0, Role::getMaxValue()->PhysicalPower);
    r->HP = GameUtil::limit(r->HP + 0.05 * r->MaxHP, 0, r->MaxHP);
    r->MP = GameUtil::limit(r->MP + 0.05 * r->MaxMP, 0, r->MaxMP);
    r->Acted = 1;
}

void BattleMod::BattleModifier::actUseMagic(Role * r)
{
    BattleMagicMenu magic_menu;
    Role * enemy = r;
    for (auto role : battle_roles_) {
        if (role->Team != r->Team) {
            enemy = role;
            break;
        }
    }
    MagicEffectDrawable med(conf, r, enemy, 420, 120);
    magic_menu.drawable = &med;
    while (true)
    {
        Magic* magic = nullptr;
        if (r->Networked)
        {
            magic = r->Network_Magic;
        }
        else
        {
            magic_menu.setStartItem(r->SelectedMagic);
            magic_menu.runAsRole(r);
            magic = magic_menu.getMagic();
            r->SelectedMagic = magic_menu.getResult();
        }
        if (magic == nullptr)
        {
            r->Network_Action = -1;
            break;
        }    //�������˳���Ϸ��������û��ѡ�书
        r->ActTeam = 1;
        //level_index��ʾ��0��9����level��0��999
        int level_index = r->getMagicLevelIndex(magic->ID);
        calSelectLayerByMagic(r->X(), r->Y(), r->Team, magic, level_index);
        //ѡ��Ŀ��
        battle_cursor_->setMode(BattleCursor::Action);
        battle_cursor_->setRoleAndMagic(r, magic, level_index);
        int selected = battle_cursor_->run();
        //ȡ��ѡ��Ŀ�������½���ѡ�书
        if (selected < 0)
        {
            continue;
        }
        else
        {
            r->Network_ActionX = select_x_;
            r->Network_ActionY = select_y_;
            r->Network_Magic = magic;
            actUseMagicSub(r, magic);
            break;
        }
    }
}

void BattleMod::BattleModifier::actUseMagicSub(Role * r, Magic * magic)
{
    // ÿ�ι����������ߵĹ���̧��..��ʺ
    std::vector<decltype(atkNames_)> atk_namess;
    std::vector<Role::ActionShowInfo> atk_shows;
    std::vector<Role::ActionShowInfo> atk_post_shows;
    // ÿ�ι�����ÿ���˵ķ�����������
    std::vector<std::vector<Role::ActionShowInfo>> defence_shows;
    // ÿ�ι�����ÿ���˵����ֶ�������
    std::vector<std::vector<Role::ActionShowInfo>> number_shows;

    // �������ж���Ҫ�ĵ�
    multiAtk_ = 0;
    for (int i = 0; i <= multiAtk_; i++)
    {
        r->Show.BattleHurt = 0;
        int magic_index = r->getMagicOfRoleIndex(magic);
        int level_index = r->getMagicLevelIndex(magic->ID);

        // �w�� Ĭ�J-3 TODO ��status
        // r->PhysicalPower = GameUtil::limit(r->PhysicalPower - 3, 0, Role::getMaxValue()->PhysicalPower);
        // �w����2�������������Y�挑
        conf.applyStatusFromParams({0, -3}, r);
        
        // �ׂ��书���������p�루���ǟoЧ��
        int mpNeeded = magic->calNeedMP(level_index);
        if (magic_index == 0 && r->RealID != 0)
        {
            mpNeeded /= 2;
        }
        r->Show.MPHurt = mpNeeded;
        calMagiclHurtAllEnemies(r, magic);

        // ���ﶯ���ǳ�����
        // ���ȣ������ߵ�̧�ֶ���������showNumberAnimation��ɣ����Թ����߱��������һ��show
        // Ȼ�󹥻���ϣ�ÿ�ǹ����ߵ����˺�����һ�������Ч
        // ������Ч���������˺���ʾ�ͽ���

        atk_namess.push_back(atkNames_);
        atkNames_.clear();

        // atk_shows ��ʾʲô�������ȣ�״̬����ʾ
        atk_shows.push_back(r->Show);
        r->Show.clearDisplayOnly();

        defence_shows.emplace_back();
        for (auto r2 : battle_roles_)
        {
            defence_shows.back().push_back(r2->Show);
            r2->Show.clearDisplayOnly();
        }

        number_shows.emplace_back();
        // �����ߵĻ�����������...
        for (auto r2 : battle_roles_)
        {
            if (r2->Show.BattleHurt != 0)
            {
                char sign = '-';
                if (r2->Show.BattleHurt < 0) sign = '+';
                r2->addShowString(convert::formatString("%c%d", sign, r2->Show.BattleHurt), { 255, 20, 20, 255 });
            }
            if (r2->Show.MPHurt != 0)
            {
                char sign = '-';
                if (r2->Show.MPHurt < 0) sign = '+';
                r2->addShowString(convert::formatString("%c%d", sign, r2->Show.MPHurt), { 72,209,204, 255 });
            }
            // ������ʾ����Ч
            auto result = conf.battleStatusManager[r2->ID].materialize();
            for (auto const& p : result)
            {
                if (!p.first.hide)
                {
                    r2->addShowString(convert::formatString("%s %d", p.first.display.c_str(), p.second), p.first.color);
                }
            }
            if (r2 != r) {
                number_shows.back().push_back(r2->Show);
            }
            else {
                atk_post_shows.push_back(r->Show);
                number_shows.back().emplace_back();     // ����
            }
            r2->Show.clear();
        }

    }
    r->Acted = 1;
    // �������󣬲�Ҫ����
    r->Progress -= 1000;
    // ��Ҫ���ƣ���Ϊ�Ѿ��뿪��ջ
    actionAnimation_ = [this, r, magic, atk_namess, atk_shows, defence_shows, number_shows, atk_post_shows]() mutable
    {
        for (int i = 0; i < atk_shows.size(); i++)
        {
            // ���Ź�������
            showMagicNames(atk_namess[i]);
            r->Show = atk_shows[i];
            useMagicAnimation(r, magic);

            // �Ȼ��壬����ʾ�˺�������׶���ʾ�������仯
            std::vector<std::pair<int&, int>> progress_changes;
            for (int j = 0; j < defence_shows[i].size(); j++)
            {
                // ��ȡ��������ֶ�������
                battle_roles_[j]->Show = defence_shows[i][j];
                progress_changes.emplace_back(battle_roles_[j]->Progress, battle_roles_[j]->Show.ProgressChange);
            }
            showNumberAnimation(3, false, progress_changes);

            // ����Ч��������ֵ
            std::vector<std::pair<int&, int>> animated_changes;
            for (int j = 0; j < number_shows[i].size(); j++)
            {
                // ��ȡ��������ֶ�������
                battle_roles_[j]->Show = number_shows[i][j];
                // �󶨣�����ֵ���˺�ֵ
                animated_changes.emplace_back(battle_roles_[j]->HP, -battle_roles_[j]->Show.BattleHurt);
                animated_changes.emplace_back(battle_roles_[j]->MP, -battle_roles_[j]->Show.MPHurt);
                // �ɰ�����������������鷳
            }
            showNumberAnimation(3, true, animated_changes);
            for (auto r2 : battle_roles_)
            {
                r2->clearShowStrings();
            }

            // �������
            std::vector<std::pair<int&, int>> post_changes;
            r->Show = atk_post_shows[i];
            post_changes.emplace_back(r->HP, -r->Show.BattleHurt);
            post_changes.emplace_back(r->MP, -r->Show.MPHurt);
            showNumberAnimation(2, true, post_changes);
            r->Show.clear();
        }
        // �ӻ���
        r->Progress += 1000;
    };
}

void BattleMod::BattleModifier::calExpGot()
{
    // �Ƿ񷢹�������
    if (info_->Exp != 0 || network_) {
        return;
    }

    int exp = 0;
    for (int i = 0; i < BATTLE_ENEMY_COUNT; i++)
    {
        auto r = Save::getInstance()->getRole(info_->Enemy[i]);
        if (r == nullptr) continue;
        // 10��
        exp += r->Level * 10;
    }
    for (auto r : friends_) {
        r->ExpGot = exp;
        r->Exp += exp;
    }

    ShowExp showExp;
    showExp.setRoles(friends_);
    showExp.run();

    for (auto r : friends_) {
        r->ExpGot = 0;
    }

    info_->Exp = 1;
}

//r1ʹ���书magic����r2���˺������Ϊһ����
int BattleModifier::calMagicHurt(Role* r1, Role* r2, Magic* magic)
{
    // simulation�Ļ��ƹ�ȥ������
    if (simulation_)
        return BattleScene::calMagicHurt(r1, r2, magic);

    assert(defEffectManager_.size() == 0);

    // ǿ�ƣ��@������@�Y�Д�
    conf.applyStatusFromParams(conf.atkEffectManager.getAllEffectParams(8), r2);

    // ������ط���Ч��ע��r2����
    auto effects = conf.tryProcAndAddToManager(r2->RealID, conf.defRole, conf.defEffectManager, r2, r1, magic);
    addDefAnim(r2, { 255,0,0 }, effects);

    // ���밤���ߵ��书������Ч
    for (int i = 0; i < r2->getLearnedMagicCount(); i++) {
        auto effects = conf.tryProcAndAddToManager(r2->MagicID[i], conf.defMagic,
            conf.defEffectManager, r2, r1, Save::getInstance()->getMagic(r2->MagicID[i]));
        addDefAnim(r2, { 255,215,0 }, effects);
    }

    effects = conf.tryProcAndAddToManager(conf.defAll, conf.defEffectManager, r2, r1, magic);
    addDefAnim(r2, { 238, 232, 170 }, effects);

    // ��Ч6����Ч7 ��״̬
    // �����ӽ�
    conf.applyStatusFromParams(conf.atkEffectManager.getAllEffectParams(6), r2);
    conf.applyStatusFromParams(conf.atkEffectManager.getAllEffectParams(7), r1);
    // Ȼ�󵹹���
    conf.applyStatusFromParams(conf.defEffectManager.getAllEffectParams(7), r2);
    conf.applyStatusFromParams(conf.defEffectManager.getAllEffectParams(6), r1);

    // �����˺�������������������
    int progressHurt = 0;

    // ��Ч1 ����
    progressHurt += conf.atkEffectManager.getEffectParam0(1);

    // ��Ч16, �⹥�ٷֱ�����
    double progressScale = 100;
    progressScale += conf.atkEffectManager.getEffectParam0(16);
    progressScale += conf.defEffectManager.getEffectParam0(16);
    progressHurt *= (progressScale / 100.0);

    // ��Ч2 ����
    double defProgress = conf.defEffectManager.getEffectParam0(2);
    double defScale = 100;
    // ��Ч17������ٷֱ�����
    defScale += conf.atkEffectManager.getEffectParam0(17);
    defScale += conf.defEffectManager.getEffectParam0(17);
    defProgress *= (defScale / 100.0);

    progressHurt -= defProgress;

    // ��Ч18 ��K����
    double finalScale = 100;
    finalScale += conf.atkEffectManager.getEffectParam0(18);
    finalScale += conf.defEffectManager.getEffectParam0(18);
    progressHurt *= (finalScale / 100.0);

    int hurt = 0;
    int level_index = Save::getInstance()->getRoleLearnedMagicLevelIndex(r1, magic);
    level_index = magic->calMaxLevelIndexByMP(r1->MP, level_index);
    if (magic->HurtType == 0)
    {
        if (r1->MP <= 10)
        {
            return 1 + rng_.rand_int(10);
        }

        // ��Ч0 �书�������ӣ���ʵ������Ҳ����
        int attack = GameUtil::getAtk(r1) + (magic->Attack[level_index] + conf.atkEffectManager.getEffectParam0(0)) / 4;
        int defence = GameUtil::getDef(r2);

        // �˺�̫�ߣ�����һ��
        int v = attack - defence * 1.5;
        v = std::max(v, attack / 7);

        //����˥��
        //�����Ӧ��Ҳ������..
        //˼������ô�ģ���ô��calRoleDistance���һ������
        int dis = calRoleDistance(r1, r2);
        v = v / exp((dis - 1) / 10);

        v += rng_.rand_int(10) - rng_.rand_int(10);

        // ��Ч4 ����
        double amplify = 100;
        amplify += conf.atkEffectManager.getEffectParam0(4);
        amplify += conf.defEffectManager.getEffectParam0(4);
        v = int(v * (amplify / 100));

        // ��Ч5 ֱ�Ӽ��˺�
        v += conf.atkEffectManager.getEffectParam0(5) + conf.defEffectManager.getEffectParam0(5);

        // ��Ч15 �ٷֱȷ���
        int reflectPerc = conf.defEffectManager.getEffectParam0(15);
        // �Լ����������ؓ������Ѫ���Ԅӵ���������
        reflectPerc += conf.atkEffectManager.getEffectParam0(15);
        r1->Show.BattleHurt += (reflectPerc / 100.0) * hurt;
        
        // ��Ч19
        int reflect = conf.defEffectManager.getEffectParam0(19);
        reflect += conf.atkEffectManager.getEffectParam0(19);

        // �������
        if (v < 10)
        {
            v = 1 + rng_.rand_int(10);
        }
        hurt = v;
    }
    else if (magic->HurtType == 1)
    {
        int v = magic->HurtMP[level_index];
        v += rng_.rand_int(10) - rng_.rand_int(10);
        if (v < 10)
        {
            v = 1 + rng_.rand_int(10);
        }
        r2->Show.MPHurt += v;
    }

    // ��Ч13 ����ֱ�ӱ仯��ʵ���ϼӵ�BattleHurt
    r2->Show.BattleHurt -= conf.defEffectManager.getEffectParam0(13);


    // ��Ч14 �����仯
    r2->Show.MPHurt -= conf.defEffectManager.getEffectParam0(14);

    // ��Ч12 �������Ӽ��������������� ������
    r2->Show.ProgressChange += conf.defEffectManager.getEffectParam0(12);


    // ��B10 ��������
    if (conf.battleStatusManager[r2->ID].getBattleStatusVal(10) > 0)
    {
        if (r2->Show.BattleHurt >= r2->HP) {
            r2->Show.BattleHurt = r2->HP - 1;
            conf.battleStatusManager[r2->ID].incrementBattleStatusVal(10, -1);
        }
        // progressHurt = 0;
        r2->Show.ProgressChange += 500;
    }

    // �����ӣ�ֻ����
    if (progressHurt > 0) {
        r2->Show.ProgressChange -= progressHurt;
        // ������򸺼���������������������ʾ
        r2->Show.ProgressChange = std::max(-r2->Progress, r2->Show.ProgressChange);
        printf("�����仯%d\n", r2->Show.ProgressChange);
    }

    conf.defEffectManager.clear();
    return hurt;
}

int BattleModifier::calMagiclHurtAllEnemies(Role* r, Magic* m, bool simulation)
{
    // simulation�Ҿͼ�װ��֪�����ٺ�
    // ����ԭ���벻�ع�һ�£��Ѹ�
    // ������BattleScene�ǻ���˭��calMagicHurt
    // Ӧ�û���override��ģ��Ӹ�simulation_�ƹ�ȥ����
    if (simulation) {
        simulation_ = true;
        return BattleScene::calMagiclHurtAllEnemies(r, m, true);
    }
    else {
        simulation_ = false;
    }

    assert(conf.atkEffectManager.size() == 0);

    // ����������������Ч�����ﱻ��Ҳ��ÿ�ι������ж�һ��
    // ������Ϊʲô�ѱ�������Ч����ȡ���ˡ�����Ŷ����������ӵ�ȫ���﹥�����水�����ж���
    /*
    for (int i = 0; i < r->getLearnedMagicCount(); i++) {
        tryProcAndAddToManager(r->MagicID[i], atkMagic_, atkEffectManager_);
    }
    */

    std::string mName(m->Name);
    atkNames_.push_back(mName);


    // �������������Ĺ�����Ч��ǿ����ЧҪ������Ч..
    auto effects = conf.tryProcAndAddToManager(r->RealID, conf.atkRole, conf.atkEffectManager, r, nullptr, m);
    // ��ɫ
    addAtkAnim(r, { 255,0,0 }, effects);

    // ̧��ʱ������������Ч
    effects = conf.tryProcAndAddToManager(m->ID, conf.atkMagic, conf.atkEffectManager, r, nullptr, m);
    // �书����ɫ��
    addAtkAnim(r, { 255,215,0 }, effects);

    // ��������ģ���ɫ
    effects = conf.tryProcAndAddToManager(conf.atkAll, conf.atkEffectManager, r, nullptr, m);
    addAtkAnim(r, { 238, 232, 170 }, effects);

    // ��Ч11 ����, �����ƾ���������
    multiAtk_ += conf.atkEffectManager.getEffectParam0(11);

    int total = 0;
    int targets = 0;
    for (auto r2 : battle_roles_)
    {
        //���ҷ��ұ����У�������λ�õ�Ч����Ǹ���
        if (r2->Team != r->Team && haveEffect(r2->X(), r2->Y()))
        {
            r2->Show.BattleHurt += calMagicHurt(r, r2, m);
            if (r2->HP > 0)
            {
                targets += 1;
            }
        }
    }
    // û���ˣ���ֹ����
    if (targets == 0)
    {
        multiAtk_ = 0;
    }

    if (targets > 0) {
        // ��Ч13 ����ֱ�ӱ仯��ʵ���ϼӵ�BattleHurt
        // ò�ƴ���һ������߀����������r��������
        r->Show.BattleHurt -= conf.atkEffectManager.getEffectParam0(13);
        // ��Ч14 �����仯
        r->Show.MPHurt -= conf.atkEffectManager.getEffectParam0(14);
    }

    // ������������
    for (auto r2 : battle_roles_)
    {
        r2->Show.BattleHurt = GameUtil::limit(r2->Show.BattleHurt, -(r2->MaxHP - r2->HP), r2->HP);
        r2->Show.MPHurt = GameUtil::limit(r2->Show.MPHurt, -(r2->MaxMP - r2->MP), r2->MP);
    }

    // ����Ҫ�ú���һ����ʾЧ����ô��
    // ��Ч12 �Ӽ���
    r->Show.ProgressChange += conf.atkEffectManager.getEffectParam0(12);

    // �����ˣ���չ���Ч��
    conf.atkEffectManager.clear();
    return total;
}

void BattleModifier::dealEvent(BP_Event& e)
{
    if (battle_roles_.empty())
    {
        exitWithResult(0);
    }

    Role* role = nullptr;
    if (semi_real_ == 0)
    {
        //ѡ��λ�����������еĵ�һ����
        role = battle_roles_[0];

        //����һ�����Ѿ��ж�����˵�������˶��ж��ˣ�������ж�״̬����������
        if (role->Acted != 0)
        {
            resetRolesAct();
            sortRoles();
            role = battle_roles_[0];
        }
    }
    else
    {
        role = semiRealPickOrTick();
        if (role == nullptr) return;
    }

    acting_role_ = role;

    //��λ
    man_x_ = role->X();
    man_y_ = role->Y();
    select_x_ = role->X();
    select_y_ = role->Y();
    head_self_->setRole(role);
    head_self_->setState(Element::Pass);

    //�ж�
    action(role);

    //������˳ɹ��ж�������ŵ���β
    if (role->Acted)
    {
        // �ж������������
        // �书�����ж���Ч
        for (int i = 0; i < role->getLearnedMagicCount(); i++) {
            conf.tryProcAndAddToManager(role->MagicID[i], conf.turnMagic, conf.turnEffectManager, role, nullptr, Save::getInstance()->getMagic(role->MagicID[i]));
        }
        conf.tryProcAndAddToManager(role->RealID, conf.turnRole, conf.turnEffectManager, role, nullptr, nullptr);
        conf.tryProcAndAddToManager(conf.turnAll, conf.turnEffectManager, role, nullptr, nullptr);

        // ��Ч7 ��״̬
        conf.applyStatusFromParams(conf.turnEffectManager.getAllEffectParams(7), role);

        // ��Ч12 �Ӽ���
        role->Show.ProgressChange += conf.turnEffectManager.getEffectParam0(12);

        std::vector<std::pair<int &, int>> animated_changes;

        // ��Ч13 ����ֱ�ӱ仯
        int hp = conf.turnEffectManager.getEffectParam0(13);
        hp = GameUtil::limit(role->HP + hp, 0, role->MaxHP) - role->HP;
        if (hp != 0) {
            role->addShowString(convert::formatString("���� %d", hp), { 255, 20, 20, 255 });
            animated_changes.emplace_back(role->HP, hp);
        }
            
        // ��Ч14 �����仯
        int mp = conf.turnEffectManager.getEffectParam0(14);
        mp = GameUtil::limit(role->MP + mp, 0, role->MaxMP) - role->MP;
        if (mp != 0) {
            role->addShowString(convert::formatString("���� %d", mp), { 255, 20, 20, 255 });
            animated_changes.emplace_back(role->MP, mp);
        }
            

        if (semi_real_ == 0)
        {
            battle_roles_.erase(battle_roles_.begin());
            battle_roles_.push_back(role);
        }
        else
        {
            role->Progress -= 1000;
            resetRolesAct();
        }

        // �ж��� ����Ц����������������ЧȫȨ�ӹ��ˣ�����ʲô��
        // ����.. TODO �ӹ�
        poisonEffect(role);

        // ��������ν��
        auto const& result = conf.battleStatusManager[role->ID].materialize();
        for (auto const& p : result) {
            printf("%d�Լ���״̬%s %d %d\n", role->ID, p.first.display.c_str(), p.first.id, p.second);
            if (!p.first.hide)
                role->addShowString(convert::formatString("%s %d", p.first.display.c_str(), p.second), p.first.color);
        }
        showNumberAnimation(2, true, animated_changes);
        role->Show.clear();

        conf.turnEffectManager.clear();
    }

    //��������˵�����
    clearDead();

    //���ս�����
    int battle_result = checkResult();

    //�ҷ�ʤ
    if (battle_result >= 0)
    {
        result_ = battle_result;
        if (result_ == 0)
        {
            calExpGot();
        }
        setExit(true);
    }
}

void BattleMod::BattleModifier::setupRolePosition(Role * r, int team, int x, int y)
{
    if (r == nullptr) return;
    r->setPosition(x, y);
    r->Team = team;
    readFightFrame(r);
    r->FaceTowards = rng_.rand_int(4);
    battle_roles_.push_back(r);
}

// ����������
Role* BattleModifier::semiRealPickOrTick() {
    //������ͼѡ��һ��
    for (auto r : battle_roles_)
    {
        if (r->Progress > 1000)
        {
            return r;
        }
    }

    //�޷�ѡ���ˣ����������˽�����������
    for (auto r : battle_roles_)
    {
        // �����Ǹ�ʲô��������

        assert(speedEffectManager_.size() == 0);

        // ����ȫ��Ч��
        conf.tryProcAndAddToManager(conf.speedAll, conf.speedEffectManager, r, nullptr, nullptr);
        // �Լ���Ч��
        conf.tryProcAndAddToManager(r->RealID, conf.speedRole, conf.speedEffectManager, r, nullptr, nullptr);
        // �Լ��书��Ч����ÿ�μ�����ô��һ�� ��ſ��
        for (int i = 0; i < r->getLearnedMagicCount(); i++) {
            conf.tryProcAndAddToManager(r->MagicID[i], conf.speedMagic, conf.speedEffectManager, r, nullptr, Save::getInstance()->getMagic(r->MagicID[i]));
        }

        int progress = 0;

        // ����/��״̬�����Լ���������Ҳ���ǲ��У��ٸ��ѭ�����жϲ���һ�������
        // ��Ч7
        conf.applyStatusFromParams(conf.speedEffectManager.getAllEffectParams(7), r);

        // ��Ч13 ����ֱ�ӱ仯
        int hp = conf.speedEffectManager.getEffectParam0(13);
        hp = GameUtil::limit(r->HP + hp, 0, r->MaxHP) - r->HP;
        r->HP += hp;

        // ��Ч14 �����仯
        int mp = conf.speedEffectManager.getEffectParam0(14);
        mp = GameUtil::limit(r->MP + mp, 0, r->MaxMP) - r->MP;
        r->MP += mp;

        // ��Ч3 �����ٶ�
        progress = conf.speedEffectManager.getEffectParam0(3);
        // printf("���������ٶ�%d\n", progress);
        // printf("%d�����ӳ� %d%%\n", r->ID, speedEffectManager_.getEffectParam0(10));
        // ��Ч10 �����ٶȰٷֱ�����
        progress = int((conf.speedEffectManager.getEffectParam0(10) / 100.0) * progress) + progress;

        // �������У��ֶ�б��
        // progress = progress < 0 ? 0 : progress;

        r->Progress += progress;

        conf.battleStatusManager[r->ID].materialize();
        conf.speedEffectManager.clear();
    }
    return nullptr;
}

void BattleMod::BattleModifier::showMagicNames(const std::vector<std::string>& names)
{
    // UI����д�����㲻����������
    if (names.empty()) return;

    std::string hugeStr = std::accumulate(std::next(names.begin()), names.end(), names[0],
        [](std::string a, const std::string& b) {
        return a + " - " + b;
    });
    int w, h;
    int fontSize = 25;
    Engine::getInstance()->getWindowSize(w, h);
    TextBox tb;
    tb.setText(hugeStr);
    tb.setPosition(w / 2.0 - (hugeStr.size() / 4.0) * fontSize, 50);
    tb.setFontSize(fontSize);
    tb.setStayFrame(40);
    tb.run();
}

void BattleMod::BattleModifier::renderExtraRoleInfo(Role * r, int x, int y)
{
    if (r == nullptr || r->HP <= 0)
    {
        return;
    }
    // ����Ѫ��
    BP_Color outline_color = { 0, 0, 0, 128 };
    BP_Color background_color = { 0, 255, 0, 128 };    // �ҷ���ɫ
    if (r->Team == 1)
    {
        // �з���ɫ
        background_color = { 255, 0, 0, 128 };
    }
    int hp_x = x - 20;
    int hp_y = y - 70;
    int hp_max_w = 40;
    int hp_h = 3;
    double perc = ((double)r->HP / r->MaxHP);
    if (perc < 0)
    {
        perc = 0;
    }
    BP_Rect r1 = { hp_x, hp_y, perc * hp_max_w, hp_h };

    Engine::getInstance()->fillColor(background_color, hp_x, hp_y, perc * hp_max_w, hp_h);
    // �Ͻ��²ۣ������
    Engine::getInstance()->fillColor(outline_color, hp_x, hp_y, hp_max_w, 1);
    Engine::getInstance()->fillColor(outline_color, hp_x, hp_y + hp_h, hp_max_w, 1);
    Engine::getInstance()->fillColor(outline_color, hp_x, hp_y, 1, hp_h);
    Engine::getInstance()->fillColor(outline_color, hp_x + hp_max_w, hp_y, 1, hp_h);

    perc = ((double)r->MP / r->MaxMP);
    hp_y += 4;
    Engine::getInstance()->fillColor({ 72,209,204, 255 }, hp_x, hp_y, perc * hp_max_w, 2);
    Engine::getInstance()->fillColor(outline_color, hp_x, hp_y, hp_max_w, 1);
    Engine::getInstance()->fillColor(outline_color, hp_x, hp_y + hp_h, hp_max_w, 1);
    Engine::getInstance()->fillColor(outline_color, hp_x, hp_y, 1, hp_h);
    Engine::getInstance()->fillColor(outline_color, hp_x + hp_max_w, hp_y, 1, hp_h);

    hp_y += 4;
    int i = 0;
    for (auto& s : conf.battleStatus) {
        // �ټ���һ����״̬��ʾ��ǿ�в���ʾ����...
        if (!s.hide && s.id!=0) {
            int val = conf.battleStatusManager[r->ID].getBattleStatusVal(s.id);
            if (val == 0) continue;
            int actual_w = ((double)val / s.max) * hp_max_w;
            Engine::getInstance()->fillColor(outline_color, hp_x, hp_y + i, hp_max_w, 2);
            Engine::getInstance()->fillColor(s.color, hp_x + 1, hp_y + i, actual_w, 2);
            Engine::getInstance()->fillColor(outline_color, hp_x + 1, hp_y + i + 2, hp_max_w, 1);
            i += 3;
        }
    }
}


