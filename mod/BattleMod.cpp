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

#include <numeric>
#include <cassert>
#include <unordered_set>

using namespace BattleMod;


BattleModifier::BattleModifier() {
    printf("this is modified battle scene.\n");
    // ǿ�ư뼴ʱ
    semi_real_ = true;
}

void BattleModifier::setRoleInitState(Role* r)
{
    BattleScene::setRoleInitState(r);
    if (r->RealID == -1)
        r->RealID = r->ID;
    printf("ID %d realID %d Team %d\n", r->ID, r->RealID, r->Team);
	// TODO �޸�����޴�������
	conf.battleStatusManager[r->ID].initStatus(r, &conf.battleStatus);
}


void BattleMod::BattleModifier::actUseMagicSub(Role * r, Magic * magic)
{
    // ÿ�ι����������ߵĹ���̧��..��ʺ
    std::vector<decltype(atkNames_)> atk_namess;
    std::vector<Role::ActionShowInfo> atk_shows;
    // ÿ�ι�����ÿ���˵ķ�����������
    std::vector<std::vector<Role::ActionShowInfo>> defence_shows;
    // ÿ�ι�����ÿ���˵����ֶ�������
    std::vector<std::vector<Role::ActionShowInfo>> number_shows;

    // �������ж���Ҫ�ĵ�
    multiAtk_ = 0;
    for (int i = 0; i <= multiAtk_; i++)
    {
        int level_index = r->getMagicLevelIndex(magic->ID);
        //�����˺�
        r->PhysicalPower = GameUtil::limit(r->PhysicalPower - 3, 0, Role::getMaxValue()->PhysicalPower);
        r->MP = GameUtil::limit(r->MP - magic->calNeedMP(level_index), 0, r->MaxMP);
        calMagiclHurtAllEnemies(r, magic);

        // ���ﶯ���ǳ�����
        // ���ȣ������ߵ�̧�ֶ���������showNumberAnimation��ɣ����Թ����߱��������һ��show
        // Ȼ�󹥻���ϣ�ÿ�ǹ����ߵ����˺�����һ�������Ч
        // ������Ч���������˺���ʾ�ͽ���

        atk_namess.push_back(atkNames_);
        atkNames_.clear();

        r->Show.Effect = 10;
        r->addShowString("����");
        // ������Ҳ���Լ������ˣ���Ѫ��������������Effect������
        atk_shows.push_back(r->Show);
        r->Show.clearDisplayOnly();
        
        defence_shows.emplace_back();
        for (auto r2 : battle_roles_) 
        {
            if (r2->Show.BattleHurt != 0) {
                r2->Show.Effect = 6;
                r2->addShowString("������è������", { 255, 20, 20, 255 });
                r2->addShowString("�����޵�", { 160, 32, 240, 255 });
                r2->addShowString("����");
            }
            // ͬһ������Ϊ����ʹ�ü����仯����������Ҳ����ν
            defence_shows.back().push_back(r2->Show);
            r2->Show.clearDisplayOnly();
        }
        
        number_shows.emplace_back();
        for (auto r2 : battle_roles_)
        {
            if (r2->Show.BattleHurt != 0)
            {
                if (magic->HurtType == 0)
                {
                    r2->addShowString(convert::formatString("-%d", r2->Show.BattleHurt), { 255, 20, 20, 255 });
                }
                else if (magic->HurtType == 1)
                {
                    r2->addShowString(convert::formatString("-%d", r2->Show.BattleHurt), { 160, 32, 240, 255 });
                    // ����������������ʾ���鷳
                    r2->Show.BattleHurt = 0;
                }
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
            number_shows.back().push_back(r2->Show);
            r2->Show.clear();
        }

        //��ѧ�ȼ�����
        auto index = r->getMagicOfRoleIndex(magic);
        if (index >= 0)
        {
            r->MagicLevel[index] += 1 + rng_.rand_int(2);
            GameUtil::limit2(r->MagicLevel[index], 0, MAX_MAGIC_LEVEL);
        }
        printf("%s %s level is %d\n", PotConv::to_read(r->Name).c_str(), PotConv::to_read(magic->Name).c_str(), r->MagicLevel[index]);
    }
    r->Acted = 1;

    // ��Ҫ���ƣ���Ϊ�Ѿ��뿪��ջ
    actionAnimation_ = [this, r, magic, atk_namess, atk_shows, defence_shows, number_shows]() mutable
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
            showNumberAnimation(2, false);

            // ����Ч��������ֵ
            std::vector<std::pair<int&, int>> animated_changes;
            for (int j = 0; j < number_shows[i].size(); j++)
            {
                // ��ȡ��������ֶ�������
                battle_roles_[j]->Show = number_shows[i][j];
                // �󶨣�����ֵ���˺�ֵ
                animated_changes.emplace_back(battle_roles_[j]->HP, -battle_roles_[j]->Show.BattleHurt);
                // �ɰ�����������������鷳
            }
            showNumberAnimation(2, true, animated_changes);
            for (auto r2 : battle_roles_)
            {
                r2->clearShowStrings();
            }
        }
    };
}

//r1ʹ���书magic����r2���˺������Ϊһ����
int BattleModifier::calMagicHurt(Role* r1, Role* r2, Magic* magic)
{
    // simulation�Ļ��ƹ�ȥ������
    if (simulation_)
        return BattleScene::calMagicHurt(r1, r2, magic);

    assert(defEffectManager_.size() == 0);
    
    // ���￼����ô������ʾЧ��
    // �ȼ�����ط���Ч��ע��r2��������ʵ���ﴫ��magicҲ�У�Ч���������ǵ�
	conf.tryProcAndAddToManager(r2->RealID, conf.defRole, conf.defEffectManager, r2, r1, nullptr);
    
    // �ټ��밤���ߵ��书������Ч
    for (int i = 0; i < r2->getLearnedMagicCount(); i++) {
		conf.tryProcAndAddToManager(r2->MagicID[i], conf.defMagic, conf.defEffectManager, r2, r1, Save::getInstance()->getMagic(r2->MagicID[i]));
    }

	conf.tryProcAndAddToManager(conf.defAll, conf.defEffectManager, r2, r1, magic);

    // ǿ����Чֱ���ж�
    // ��Ч8 9
    // 8 �������ĵ��˵�
    conf.setStatusFromParams(conf.atkEffectManager.getAllEffectParams(8), r2);
    // 9 �������Լ�
    conf.applyStatusFromParams(conf.atkEffectManager.getAllEffectParams(9), r1);
    // Ȼ�󵹹��� 8 �������ĵ���
    conf.applyStatusFromParams(conf.defEffectManager.getAllEffectParams(8), r1);
    // 9 �������Լ�
    conf.applyStatusFromParams(conf.defEffectManager.getAllEffectParams(9), r2);

    // �����˺�������������������
    int progressHurt = 0;

    // ��Ч1 ����
    progressHurt += conf.atkEffectManager.getEffectParam0(1);
    // ��Ч2 ����
    progressHurt -= conf.defEffectManager.getEffectParam0(2);


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
        int attack = r1->Attack + (magic->Attack[level_index]+ conf.atkEffectManager.getEffectParam0(0)) / 4;

        int defence = r2->Defence;

        //װ����Ч��
        if (r1->Equip0 >= 0)
        {
            auto i = Save::getInstance()->getItem(r1->Equip0);
            attack += i->AddAttack;
        }
        if (r1->Equip1 >= 0)
        {
            auto i = Save::getInstance()->getItem(r1->Equip1);
            attack += i->AddAttack;
        }
        if (r2->Equip0 >= 0)
        {
            auto i = Save::getInstance()->getItem(r2->Equip0);
            defence += i->AddDefence;
        }
        if (r2->Equip1 >= 0)
        {
            auto i = Save::getInstance()->getItem(r2->Equip1);
            defence += i->AddDefence;
        }

        // �˺�̫�ߣ�����һ��
        int v = attack - defence * 2;

        //����˥��
        //�����Ӧ��Ҳ������..
        //˼������ô�ģ���ô��calRoleDistance���һ���������޸ı�������ָ��ǩ����ֻ��
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
        hurt = v;
    }

    // ��Ч12 �������Ӽ��������������� ������
    r2->Show.ProgressChange += conf.defEffectManager.getEffectParam0(12);

    // ��Ч6����Ч7 ��״̬
    // �����ӽ�
    conf.applyStatusFromParams(conf.atkEffectManager.getAllEffectParams(6), r2);
    conf.applyStatusFromParams(conf.atkEffectManager.getAllEffectParams(7), r1);
    // Ȼ�󵹹���
    conf.applyStatusFromParams(conf.defEffectManager.getAllEffectParams(7), r2);
    conf.applyStatusFromParams(conf.defEffectManager.getAllEffectParams(6), r1);

    // �����ӣ�ֻ����
    if (progressHurt > 0) {
        r2->Show.ProgressChange -= progressHurt;
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
    // ̧��ʱ������������Ч
    auto effects = conf.tryProcAndAddToManager(m->ID, conf.atkMagic, conf.atkEffectManager, r, nullptr, m);
    // �򵥵�������ʾ~ TODO �޺���
    for (const auto& effect : effects) {
        if (!effect.description.empty())
            atkNames_.push_back(std::cref(effect.description));
    }

    // �������������Ĺ�����Ч
    effects = conf.tryProcAndAddToManager(r->RealID, conf.atkRole, conf.atkEffectManager, r, nullptr, m);
    for (const auto& effect : effects) {
        if (!effect.description.empty())
            atkNames_.push_back(std::cref(effect.description));
    }

    // ���������
    effects = conf.tryProcAndAddToManager(conf.atkAll, conf.atkEffectManager, r, nullptr, m);
    for (const auto& effect : effects) {
        if (!effect.description.empty())
            atkNames_.push_back(std::cref(effect.description));
    }

    // ��Ч11 ����, �����ƾ���������
    multiAtk_ += conf.atkEffectManager.getEffectParam0(11);

    int total = 0;
	int targets = 0;
    for (auto r2 : battle_roles_)
    {
        //���ҷ��ұ����У�������λ�õ�Ч����Ǹ���
        if (r2->Team != r->Team && haveEffect(r2->X(), r2->Y()))
        {
            r2->Show.BattleHurt = calMagicHurt(r, r2, m);
            if (m->HurtType == 0)
            {
                // r2->addShowString(convert::formatString("-%d", hurt), { 255, 20, 20, 255 }, 30);
                int prevHP = r2->HP;
                r2->Show.BattleHurt = GameUtil::limit(r2->Show.BattleHurt, -(r2->MaxHP - r2->HP), r2->HP);
                // r2->HP = GameUtil::limit(r2->HP - r2->BattleHurt, 0, r2->MaxHP);
                int hurt1 = prevHP - r2->HP;
                r->ExpGot += hurt1;
                if (r2->HP <= 0)
                {
                    r->ExpGot += hurt1 / 2;
                }
                // r2->ProgressChange -= -hurt / 5;
            }
            else if (m->HurtType == 1)
            {
                // r2->addShowString(convert::formatString("-%d", hurt), { 160, 32, 240, 255 }, 30);
                int prevMP = r2->MP;
                r2->MP = GameUtil::limit(r2->MP - r2->Show.BattleHurt, 0, r2->MaxMP);
                r->MP = GameUtil::limit(r->MP + r2->Show.BattleHurt, 0, r->MaxMP);
                int hurt1 = prevMP - r2->MP;
                r->ExpGot += hurt1 / 2;
            }
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

        // ��Ч9 ǿ��
        conf.setStatusFromParams(conf.turnEffectManager.getAllEffectParams(9), role);

        // ��Ч7 ��״̬
        conf.applyStatusFromParams(conf.turnEffectManager.getAllEffectParams(7), role);

        // ��Ч12 �Ӽ���
        role->Show.ProgressChange += conf.turnEffectManager.getEffectParam0(12);

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
        showNumberAnimation();
        role->clearShowStrings();
        // ����غϽ������һЩ��Ч������˵��Ѫ���� ��һϵ��
        // ��������������

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
        if (result_ == 0 || result_ == 1 && fail_exp_)
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
        // ǿ��״̬ ��Ч9
        auto forceStat = conf.speedEffectManager.getAllEffectParams(9);
        conf.setStatusFromParams(forceStat, r);

        int progress = 0;
        
        // ����/��״̬�����Լ���������Ҳ���ǲ��У��ٸ��ѭ�����жϲ���һ�������
        // ��Ч7
        conf.applyStatusFromParams(conf.speedEffectManager.getAllEffectParams(7), r);

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
    int fontSize = 25;
    int stayFrame = 40;
    std::unique_ptr<TextBox> boxRoot = std::make_unique<TextBox>();
    int w, h;
    Engine::getInstance()->getWindowSize(w, h);
    boxRoot->setHaveBox(false);
    // ����Ҳ���ֱ��
    boxRoot->setText(hugeStr);
    boxRoot->setPosition(w/2.0 - (hugeStr.size()/4.0) * fontSize, 50);
    boxRoot->setFontSize(fontSize);
    boxRoot->setStayFrame(stayFrame);
    boxRoot->setAlphaBox({ 255, 165, 79, 255 }, { 0, 0, 0, 128 });
    // �����趨��ɫ�ɡ�����
    boxRoot->setTextColor({ 255, 165, 79, 255 });
    boxRoot->run();
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
    int hp_y = y - 63;
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
    int i = 4;
    for (auto& s : conf.battleStatus) {
        if (!s.hide) {
            int val = conf.battleStatusManager[r->ID].getBattleStatusVal(s.id);
            if (val == 0) continue;
            int actual_w = ((double)val / s.max) * hp_max_w;
            Engine::getInstance()->fillColor(outline_color, hp_x, hp_y + i, hp_max_w, 1);
            Engine::getInstance()->fillColor(s.color, hp_x + 1, hp_y + i, actual_w, 1);
            i += 1;
        }
    }
}


