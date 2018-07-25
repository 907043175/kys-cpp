#include "BattleMod.h"
#include "GameUtil.h"
#include "Save.h"
#include "Font.h"
#include "libconvert.h"
#include "PotConv.h"
#include <cassert>

using namespace BattleMod;

BattleMod::SpecialEffect::SpecialEffect(int id, const std::string & desc) :
    id_(id), description_(desc)
{
}

int BattleMod::SpecialEffect::getId() const
{
    return id_;
}

std::string BattleMod::SpecialEffect::getDescription() const
{
    return description_;
}


BattleMod::EffectParamPair::EffectParamPair(const SpecialEffect & effect, Param p, const std::string & desc) :
    effect(effect), description(desc)
{
    params_.push_back(p);
}

Param BattleMod::EffectParamPair::getParam0()
{
    return params_[0];
}

const Params & BattleMod::EffectParamPair::getParams()
{
    return params_;
}

EffectParamPair & BattleMod::EffectParamPair::operator+=(const EffectParamPair & rhs)
{
    // id ������ͬ
    if (effect.getId() != rhs.effect.getId() || params_.size() != rhs.params_.size()) {
        return *this;
    }
    for (std::size_t i = 0; i < params_.size(); i++) {
        params_[i] += rhs.params_[i];
    }
    return *this;
}

BattleMod::EffectSingle::EffectSingle(int p, EffectParamPair epp) : 
    percentProb_(p), effectPair_(epp)
{
}

EffectParamPair * BattleMod::EffectSingle::proc(RandomDouble & rand)
{
    // rand [0 1)
    // ����100��ȡ��������˵ʵ�ʷ�Χ��0-99
    if (rand.rand_int(100) < percentProb_) {
        return &effectPair_;
    }
    return nullptr;
}

EffectParamPair * BattleMod::EffectWeightedGroup::proc(RandomDouble & rand)
{
    printf("���Դ���\n");
    // [0 total)
    int t = rand.rand_int(total_);
    int c = 0;
    for (auto& p : group_) {
        c += p.first;
        if (t < c) {
            return &p.second;
        }
    }
    return nullptr;
}

BattleMod::EffectWeightedGroup::EffectWeightedGroup(int total) :
    total_(total)
{
}

void BattleMod::EffectWeightedGroup::addProbEPP(int weight, EffectParamPair epp)
{
    group_.emplace_back(weight, epp);
}

bool BattleMod::EffectManager::hasEffect(int eid)
{
    return epps_.find(eid) != epps_.end();
}

Param BattleMod::EffectManager::getEffectParam0(int eid)
{
    auto iter = epps_.find(eid);
    // ����0����Ӧ��û����ɡ���
    if (iter == epps_.end()) return 0;
    return iter->second.getParam0();
}

Params BattleMod::EffectManager::getAllEffectParams(int eid)
{
    auto iter = epps_.find(eid);
    if (iter == epps_.end()) return {};
    return iter->second.getParams();
}

EffectParamPair * BattleMod::EffectManager::getEPP(int eid)
{
    auto iter = epps_.find(eid);
    if (iter == epps_.end())
        return nullptr;
    return &(iter->second);
}

void BattleMod::EffectManager::unionEffects(const EffectManager & other)
{
    for (const auto& idPair : other.epps_) {
        auto myEpp = getEPP(idPair.first);
        if (myEpp) {
            *myEpp += idPair.second;
        }
        else {
            epps_.insert(idPair);
        }
    }
}

void BattleMod::EffectManager::addEPP(const EffectParamPair & ewp)
{
    epps_.insert({ ewp.effect.getId(), ewp });
}

std::size_t BattleMod::EffectManager::size()
{
    return epps_.size();
}

void BattleMod::EffectManager::clear()
{
    epps_.clear();
}



BattleModifier::BattleModifier() {
    printf("this is modified battle scene.\n");
    init();
}

BattleMod::BattleModifier::BattleModifier(int id) : BattleScene(id)
{
    init();
}

void BattleMod::BattleModifier::init()
{
    YAML::Node baseNode;
    // ������������try�������������Чȫ���
    try {
        YAML::Node baseNode = YAML::LoadFile(PATH);
    }
    catch (...) {
        printf("yaml config missing\n");
        return;
    }
    // ���������ȫ�����ҵ����ݽṹ��(��STL)
    // Ȼ�����д��validator֮���
    printf("��Ч���� %d\n", baseNode[u8"��Ч"].size());
    for (const auto& spNode : baseNode[u8"��Ч"]) {
        // ���밴˳��������Ϊ���������Կ��Ǹ�һ��
        assert(effects_.size() == spNode[u8"���"].as<int>());
        auto desc = PotConv::conv(spNode[u8"����"].as<std::string>(), "utf-8", "cp936");
        printf("%d %s\n", spNode[u8"���"].as<int>(), desc.c_str());
        effects_.emplace_back(spNode[u8"���"].as<int>(), desc);
    }

    if (baseNode[u8"�书"]) {
        for (const auto& magicNode : baseNode[u8"�书"]) {
            int wid = magicNode[u8"�书���"].as<int>();
            if (magicNode[u8"��������"]) {
                readIntoMapping(magicNode[u8"��������"], activeAtkMagic_[wid]);
            }
            if (magicNode[u8"��������"]) {
                readIntoMapping(magicNode[u8"��������"], passiveAtkMagic_[wid]);
            }
            if (magicNode[u8"��������"]) {
                readIntoMapping(magicNode[u8"��������"], passiveDefMagic_[wid]);
            }
            if (magicNode[u8"ȫ����Ч"]) {
                readIntoMapping(magicNode[u8"ȫ����Ч"], globalMagic_[wid]);
            }
        }
    }

    if (baseNode[u8"����"]) {
        for (const auto& personNode : baseNode[u8"����"]) {
            int pid = personNode[u8"������"].as<int>();
            if (personNode[u8"����"]) {
                readIntoMapping(personNode[u8"����"], atkRole_[pid]);
            }
            if (personNode[u8"����"]) {
                readIntoMapping(personNode[u8"����"], defRole_[pid]);
            }
            if (personNode[u8"ȫ��"]) {
                readIntoMapping(personNode[u8"ȫ��"], globalRole_[pid]);
            }
        }
    }
    printf("load yaml config complete\n");
}

EffectParamPair BattleModifier::readEffectParamPairs(const YAML::Node& node) {
    int id = node[u8"���"].as<int>();
    auto display = PotConv::conv(node[u8"��ʾ"].as<std::string>(), "utf-8", "cp936");
    printf("���� %s\n", display.c_str());
    // ����Ч�������Ժ�Ҫ������
    EffectParamPair epp(effects_[id], node[u8"Ч������"].as<int>(), display);
    return epp;
}


std::unique_ptr<ProccableEffect> BattleModifier::readProccableEffect(const YAML::Node& node) {
    int probType = node[u8"��������"].as<int>();
    ProcProbability prob = static_cast<ProcProbability>(probType);
    std::unique_ptr<ProccableEffect> pe;
    switch (prob) {
    case ProcProbability::random: {
        pe = std::make_unique<EffectSingle>(node[u8"��Ч"][u8"��������"].as<int>(), readEffectParamPairs(node[u8"��Ч"]));
        break;
    }
    case ProcProbability::distributed: {
        auto group = std::make_unique<EffectWeightedGroup>(node[u8"�ܱ���"].as<int>());
        for (auto& eNode : node[u8"��Ч"]) {
            group->addProbEPP(eNode[u8"��������"].as<int>(), readEffectParamPairs(eNode));
        }
        pe = std::move(group);
        break;
    }
    }
    return pe;
}

void BattleModifier::readIntoMapping(const YAML::Node& node, BattleMod::Effects& effects) {
    for (auto& spNode : node) {
        effects.push_back(std::move(readProccableEffect(spNode)));
    }
}

std::vector<std::string> BattleMod::BattleModifier::tryProcAndAddToManager(int id, const EffectsTable & table, EffectManager & manager)
{
    // ������ȫû�п�����Ч������ʾ
    // ��ô��ʾ������ʾʲô�����Ǹ�����
    // Ȼ������������Ч���������壿������Ҫ��ô��
    // �и��취���Ǵ��������Щȫ��return
    // ˭����˭����
    // TODO �������д�����Ч����
    std::vector<std::string> effectStrs;
    auto iter = table.find(id);
    if (iter != table.end()) {
        for (const auto& effect : iter->second) {
            if (auto epp = effect->proc(rand_)) {
                manager.addEPP(*epp);
                effectStrs.push_back(epp->description);
                printf("����Ч�� %s\n", epp->description.c_str());
            }
        }
    }
    return effectStrs;
}


void BattleModifier::setRoleInitState(Role* r)
{
    BattleScene::setRoleInitState(r);

    // �����ȫ����Ч����սʱ��Ҫ�ж��Ƿ񴥷�������
    // S/L�󷨣��޴������
    tryProcAndAddToManager(r->ID, globalRole_, globalEffectManagers_[r->ID]);

    // ��������书��ͬ�����Ŵ�������
    for (int i = 0; i < r->getLearnedMagicCount(); i++) {
        tryProcAndAddToManager(r->MagicID[i], globalMagic_, globalEffectManagers_[r->ID]);
    }
}

void BattleMod::BattleModifier::useMagic(Role * r, Magic * magic)
{
    int level_index = r->getMagicLevelIndex(magic->ID);
    for (int i = 0; i <= GameUtil::sign(r->AttackTwice); i++)
    {
        //���Ź������棬�����˺�
        showMagicName(magic->Name);
        calMagiclHurtAllEnemies(r, magic);
        r->PhysicalPower = GameUtil::limit(r->PhysicalPower - 3, 0, Role::getMaxValue()->PhysicalPower);
        r->MP = GameUtil::limit(r->MP - magic->calNeedMP(level_index), 0, r->MaxMP);
        useMagicAnimation(r, magic);
        showNumberAnimation();
        //��ѧ�ȼ�����
        auto index = r->getMagicOfRoleIndex(magic);
        if (index >= 0)
        {
            r->MagicLevel[index] += 1 + rand_.rand_int(2);
            GameUtil::limit2(r->MagicLevel[index], 0, MAX_MAGIC_LEVEL);
        }
        printf("%s %s level is %d\n", PotConv::to_read(r->Name).c_str(), PotConv::to_read(magic->Name).c_str(), r->MagicLevel[index]);
    }
    r->Acted = 1;
}

//r1ʹ���书magic����r2���˺������Ϊһ����
int BattleModifier::calMagicHurt(Role* r1, Role* r2, Magic* magic)
{
    // simulation�Ļ��ƹ�ȥ������
    if (simulation_)
        return BattleScene::calMagicHurt(r1, r2, magic);

    assert(defEffectManager_.size() == 0);
    
    // �ȼ�����ط���Ч
    tryProcAndAddToManager(r2->ID, defRole_, defEffectManager_);
    
    // �ټ��밤���ߵ��书������Ч
    for (int i = 0; i < r2->getLearnedMagicCount(); i++) {
        tryProcAndAddToManager(r2->MagicID[i], passiveDefMagic_, defEffectManager_);
    }

    // �����˺�������������������
    int progressHurt = 0;

    // ��Ч1 ����
    progressHurt += atkEffectManager_.getEffectParam0(1);
    // ��Ч2 ����
    progressHurt -= defEffectManager_.getEffectParam0(2);


    int hurt = 0;
    int level_index = Save::getInstance()->getRoleLearnedMagicLevelIndex(r1, magic);
    level_index = magic->calMaxLevelIndexByMP(r1->MP, level_index);
    if (magic->HurtType == 0)
    {
        if (r1->MP <= 10)
        {
            return 1 + rand_.rand_int(10);
        }
        int attack = r1->Attack + magic->Attack[level_index] / 3;
        // ��Ч0 �书��������
        attack += atkEffectManager_.getEffectParam0(0) / 3;
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

        int v = attack - defence;
        //����˥��
        int dis = calRoleDistance(r1, r2);
        v = v / exp((dis - 1) / 10);

        v += rand_.rand_int(10) - rand_.rand_int(10);
        if (v < 10)
        {
            v = 1 + rand_.rand_int(10);
        }
        hurt = v;
    }
    else if (magic->HurtType == 1)
    {
        int v = magic->HurtMP[level_index];
        v += rand_.rand_int(10) - rand_.rand_int(10);
        if (v < 10)
        {
            v = 1 + rand_.rand_int(10);
        }
        hurt = v;
    }

    // �����ӣ�ֻ����
    if (progressHurt > 0) {
        r2->ProgressChange -= progressHurt;
        printf("�����仯%d\n", r2->ProgressChange);
    }
    defEffectManager_.clear();
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

    assert(atkEffectManager_.size() == 0);

    // ����������������Ч�����ﱻ��Ҳ��ÿ�ι������ж�һ��
    for (int i = 0; i < r->getLearnedMagicCount(); i++) {
        tryProcAndAddToManager(r->MagicID[i], passiveAtkMagic_, atkEffectManager_);
    }

    // ̧��ʱ������������Ч
    auto strs = tryProcAndAddToManager(m->ID, activeAtkMagic_, atkEffectManager_);
    // �򵥵�������ʾ~
    for (const auto& str : strs) {
        showMagicName(str);
    }

    // �������������Ĺ�����Ч
    tryProcAndAddToManager(r->ID, atkRole_, atkEffectManager_);

    // ȫ����Ч�ϲ��������������ж�
    atkEffectManager_.unionEffects(globalEffectManagers_[r->ID]);

    int total = 0;
    for (auto r2 : battle_roles_)
    {
        //���ҷ��ұ����У�������λ�õ�Ч����Ǹ���
        if (r2->Team != r->Team && haveEffect(r2->X(), r2->Y()))
        {
            int hurt = calMagicHurt(r, r2, m);
            if (m->HurtType == 0)
            {
                r2->ShowString = convert::formatString("-%d", hurt);
                r2->ShowColor = { 255, 20, 20, 255 };
                int prevHP = r2->HP;
                r2->HP = GameUtil::limit(r2->HP - hurt, 0, r2->MaxHP);
                int hurt1 = prevHP - r2->HP;
                r->ExpGot += hurt1;
                if (r2->HP <= 0)
                {
                    r->ExpGot += hurt1 / 2;
                }
                r2->ProgressChange -= -hurt / 5;
            }
            else if (m->HurtType == 1)
            {
                r2->ShowString = convert::formatString("-%d", hurt);
                r2->ShowColor = { 160, 32, 240, 255 };
                int prevMP = r2->MP;
                r2->MP = GameUtil::limit(r2->MP - hurt, 0, r2->MaxMP);
                r->MP = GameUtil::limit(r->MP + hurt, 0, r->MaxMP);
                int hurt1 = prevMP - r2->MP;
                r->ExpGot += hurt1 / 2;
            }
        }
    }

    // �����ˣ���չ���Ч��
    atkEffectManager_.clear();
    return total;
}

void BattleModifier::showNumberAnimation()
{
    BattleScene::showNumberAnimation();
}

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
        r->Progress += r->Speed / 4;

        auto iter = globalEffectManagers_.find(r->ID);
        if (iter != globalEffectManagers_.end()) {
            // ��Ч3 ���Ӽ����ٶ�
            r->Progress += iter->second.getEffectParam0(3);
        }
    }
    return nullptr;
}