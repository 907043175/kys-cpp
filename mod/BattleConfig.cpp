#include "BattleConfig.h"
#include "BattleMod.h"

#include "GameUtil.h"
#include "PotConv.h"
#include <unordered_set>
#include <iostream>
#include <cassert>

using namespace BattleMod;

BattleMod::SpecialEffect::SpecialEffect(int id, const std::string & desc) :
    id(id), description(desc)
{
}

void BattleMod::SpecialEffect::print(std::ostream & os) const
{
    os << description;
}

BattleMod::EffectIntsPair::EffectIntsPair(const SpecialEffect & effect, const std::string & desc, EffectDisplayPosition displayOnPerson, int animationEffect) :
    effect(effect), description(desc), position(displayOnPerson), animationEffect_(animationEffect)
{
}

int BattleMod::EffectIntsPair::getParam0()
{
    return params_[0];
}

const std::vector<int> & BattleMod::EffectIntsPair::getParams()
{
    return params_;
}

int BattleMod::EffectIntsPair::getAnimation() const
{
    return animationEffect_;
}

void BattleMod::EffectIntsPair::addParam(int p)
{
    params_.push_back(p);
}


EffectIntsPair & BattleMod::EffectIntsPair::operator+=(const EffectIntsPair & rhs)
{
    // id ������ͬ
    if (effect.id != rhs.effect.id) {
        return *this;
    }

    // ��״̬��ʱ�򣬲���������
    // ��ô�����أ���Ҳ��֪������ô���
    // ˵ʵ��ǿ��״̬���ܻ�����ʽ��min/max֮��� ����������
    if (effect.id == 6 || effect.id == 7 || effect.id == 8 || effect.id == 9) {
        std::unordered_map<int, int> statusStrMap;
        // ����ÿ��һ���Ǳ�ţ��ڶ���ǿ��
        for (std::size_t i = 0; i < rhs.params_.size() / 2; i += 2) {
            statusStrMap[rhs.params_[i]] = rhs.params_[i + 1];
        }
        for (std::size_t i = 0; i < params_.size() / 2; i += 2) {
            statusStrMap[params_[i]] += params_[i + 1];
        }
        params_.clear();
        for (const auto& p : statusStrMap) {
            params_.push_back(p.first);
            params_.push_back(p.second);
        }
        return *this;
    }

    if (params_.size() != rhs.params_.size()) {
        return *this;
    }

    // һ��ֱ�Ӽ�����
    for (std::size_t i = 0; i < params_.size(); i++) {
        params_[i] += rhs.params_[i];
    }
    return *this;
}

void BattleMod::EffectIntsPair::print(std::ostream & os) const
{
    os << description;
}

BattleMod::FlatValue::FlatValue(int val) : val_(val)
{
}

int BattleMod::FlatValue::getVal(BattleConfManager& conf, Role * attacker, Role * defender, const Magic * wg) const
{
	return val_;
}

void BattleMod::FlatValue::print(std::ostream & os) const
{
    os << val_;
}

BattleMod::DynamicVariable::DynamicVariable(DynamicVarEnum dynamicCode, VarTarget target) : dynamicCode_(dynamicCode), target_(target)
{
}

int BattleMod::DynamicVariable::getVal(BattleConfManager& conf, Role * attacker, Role * defender, const Magic * wg) const
{
	Role * c = attacker;
	if (target_ == VarTarget::Other) {
		c = defender;
	}
#define ATTR( attribute ) { if (c == nullptr) return 0; return c->attribute; }
	switch (dynamicCode_) {
	case DynamicVarEnum::var_char_sex: ATTR(Sexual);
	case DynamicVarEnum::var_char_level: ATTR(Level);
	case DynamicVarEnum::var_char_exp: ATTR(Exp);
	case DynamicVarEnum::var_char_hp: ATTR(HP);
	case DynamicVarEnum::var_char_maxhp: ATTR(MaxHP);
	case DynamicVarEnum::var_char_equip0: ATTR(Equip0);
	case DynamicVarEnum::var_char_equip1: ATTR(Equip1);
	case DynamicVarEnum::var_char_mptype: ATTR(MPType);
	case DynamicVarEnum::var_char_mp: ATTR(MP);
	case DynamicVarEnum::var_char_maxmp: ATTR(MaxMP);
	case DynamicVarEnum::var_char_attack: ATTR(Attack);
	case DynamicVarEnum::var_char_speed: ATTR(Speed);
	case DynamicVarEnum::var_char_defence: ATTR(Defence);
	case DynamicVarEnum::var_char_medicine: ATTR(Medicine);
	case DynamicVarEnum::var_char_usepoison: ATTR(UsePoison);
	case DynamicVarEnum::var_char_detoxification: ATTR(Detoxification);
	case DynamicVarEnum::var_char_antipoison: ATTR(AntiPoison);
	case DynamicVarEnum::var_char_fist: ATTR(Fist);
	case DynamicVarEnum::var_char_sword: ATTR(Sword);
	case DynamicVarEnum::var_char_blade: ATTR(Knife);
	case DynamicVarEnum::var_char_unusual: ATTR(Unusual);
	case DynamicVarEnum::var_char_hiddenweapon: ATTR(HiddenWeapon);
	case DynamicVarEnum::var_char_knowledge: ATTR(Knowledge);
	case DynamicVarEnum::var_char_morality: ATTR(Morality);
	case DynamicVarEnum::var_char_attackwithpoison: ATTR(AttackWithPoison);
	case DynamicVarEnum::var_char_attacktwice: ATTR(AttackTwice);
	case DynamicVarEnum::var_char_fame: ATTR(Fame);
	case DynamicVarEnum::var_char_iq: ATTR(IQ);
	case DynamicVarEnum::var_using_char: ATTR(ID);
	case DynamicVarEnum::var_books: {
		// Ӳ���룬д�鱾id
		int books = 0;
		for (int i = 144; i < 144 + 14; i++)
			books += Save::getInstance()->getItemCountInBag(i);

		if (c->Team != 0) return 0;
		return books;
	}
	case DynamicVarEnum::var_cur_wg_level: {
		// getMagicOfRoleIndex ���Ǹ�const���Һܷ�
		if (c == nullptr || wg == nullptr) return 0;
		for (int i = 0; i < ROLE_MAGIC_COUNT; i++)
		{
			if (c->MagicID[i] == wg->ID)
			{
				return c->MagicLevel[i];
			}
		}
		return 0;
	}
	case DynamicVarEnum::var_wg_level: {
		if (params_.size() < 1)
		{
			printf("var_wg_level incorrect params\n");
			return 0;
		}
		// ��ȡ�������
		int wgID = params_[0];
		if (c == nullptr) return 0;
		for (int i = 0; i < ROLE_MAGIC_COUNT; i++)
		{
			if (c->MagicID[i] == wgID)
			{
				return c->MagicLevel[i];
			}
		}
		return 0;
	}
	case DynamicVarEnum::var_count_item: {
		if (params_.size() < 1)
		{
			printf("var_count_item incorrect params\n");
			return 0;
		}
		// ��ȡ�������
		int itemID = params_[0];
		int num = Save::getInstance()->getItemCountInBag(itemID);
		if (c->Team != 0) return 0;
		return num;
	}
	case DynamicVarEnum::var_has_wg: {
		std::unordered_set<int> ids;
		for (int id : params_) {
			ids.insert(id);
		}
		if (c == nullptr) return 0;
		int count = 0;
		for (int i = 0; i < ROLE_MAGIC_COUNT; i++)
		{
			if (ids.find(c->MagicID[i]) != ids.end())
				count++;
		}
		if (count == ids.size())
			return 1;
		return 0;
	}
	case DynamicVarEnum::var_wg_type: {
		if (wg == nullptr) return 0;
		return wg->MagicType;
	}
	case DynamicVarEnum::var_is_person: {
		if (params_.size() < 1)
		{
			printf("var_is_person incorrect params\n");
			return 0;
		}
		int pid = params_[0];
		if (c == nullptr) return 0;
		if (c->RealID == pid) return 1;
		return 0;
	}
	case DynamicVarEnum::var_has_status: {
		if (params_.size() < 2)
		{
			printf("var_has_status incorrect params\n");
			return 0;
		}
		int statusID = params_[0];
		int val = params_[1];
		if (c == nullptr) return 0;
		auto mangerPtr = conf.getStatusManager(c->ID);
		if (mangerPtr) {
			if (mangerPtr->getBattleStatusVal(statusID) >= val) {
				return 1;
			}
		}
		return 0;
	}
	case DynamicVarEnum::var_wg_power: {
		if (c == nullptr || wg == nullptr) return 0;
		// �����䣬������const ��û��
		Role* cc = const_cast<Role*>(c);
		Magic* mm = const_cast<Magic*>(wg);
		// ���߿�id�� Save:: Ҳ����
		int level_index = Save::getInstance()->getRoleLearnedMagicLevelIndex(cc, mm);
		level_index = mm->calMaxLevelIndexByMP(cc->MP, level_index);
		if (mm->HurtType == 1) return mm->HurtMP[level_index];
		return mm->Attack[level_index];
	}
	default: {
		printf("%d variable id not found\n", dynamicCode_);
		break;
	}
	}
	return 0;
}

void BattleMod::DynamicVariable::addParam(int p)
{
	params_.push_back(p);
}

void BattleMod::DynamicVariable::print(std::ostream & os) const
{
    if (target_ == VarTarget::Other) {
        os << "����";
    }
#define OSOUT(str) { os << str; return;}
    switch (dynamicCode_) {
    case DynamicVarEnum::var_char_sex: OSOUT("�Ԅe");
    case DynamicVarEnum::var_char_level: OSOUT("�ȼ�");
    case DynamicVarEnum::var_char_exp: OSOUT("���");
    case DynamicVarEnum::var_char_hp: OSOUT("����");
    case DynamicVarEnum::var_char_maxhp: OSOUT("�������ֵ");
    case DynamicVarEnum::var_char_equip0: OSOUT("����");
    case DynamicVarEnum::var_char_equip1: OSOUT("����");
    case DynamicVarEnum::var_char_mptype: OSOUT("��������");
    case DynamicVarEnum::var_char_mp: OSOUT("����");
    case DynamicVarEnum::var_char_maxmp: OSOUT("�������ֵ");
    case DynamicVarEnum::var_char_attack: OSOUT("����");
    case DynamicVarEnum::var_char_speed: OSOUT("�p��");
    case DynamicVarEnum::var_char_defence: OSOUT("���R");
    case DynamicVarEnum::var_char_medicine: OSOUT("�t��");
    case DynamicVarEnum::var_char_usepoison: OSOUT("�ö�");
    case DynamicVarEnum::var_char_detoxification: OSOUT("�ⶾ");
    case DynamicVarEnum::var_char_antipoison: OSOUT("����");
    case DynamicVarEnum::var_char_fist: OSOUT("ȭ��");
    case DynamicVarEnum::var_char_sword: OSOUT("����");
    case DynamicVarEnum::var_char_blade: OSOUT("ˣ��");
    case DynamicVarEnum::var_char_unusual: OSOUT("����");
    case DynamicVarEnum::var_char_hiddenweapon: OSOUT("����");
    case DynamicVarEnum::var_char_knowledge: OSOUT("֪�R");
    case DynamicVarEnum::var_char_morality: OSOUT("Ʒ��");
    case DynamicVarEnum::var_char_attackwithpoison: OSOUT("����");
    case DynamicVarEnum::var_char_attacktwice: OSOUT("���һ���");
    case DynamicVarEnum::var_char_fame: OSOUT("��");
    case DynamicVarEnum::var_char_iq: OSOUT("�Y�|");
    case DynamicVarEnum::var_using_char: OSOUT("ʹ�ý�ɫ");
    case DynamicVarEnum::var_books: OSOUT("�씵����");
    case DynamicVarEnum::var_cur_wg_level: OSOUT("�ȼ�");
    case DynamicVarEnum::var_wg_level: {
        if (params_.size() < 1)
        {
            printf("var_wg_level incorrect params\n");
            OSOUT("*�书�ȼ�*�e�`*");
        }
        os << Save::getInstance()->getMagic(params_[0])->Name << "�ȼ�";
        break;
    }
    case DynamicVarEnum::var_count_item: {
        if (params_.size() < 1)
        {
            printf("var_count_item incorrect params\n");
            OSOUT("*��Ʒ����*�e�`*");
        }
        // ��ȡ�������
        int itemID = params_[0];
        os << Save::getInstance()->getItem(itemID)->Name << "����";
        break;
    }
    case DynamicVarEnum::var_has_wg: {
        os << "�����书<";
        int idx = 0;
        for (int id : params_) {
            os << Save::getInstance()->getMagic(id)->Name;
            if (idx != params_.size() - 1) os << ",";
            idx++;
        }
        os << ">�r=1��t=0";
        break;
    }
    case DynamicVarEnum::var_wg_type: {
        os << "�书���";
        break;
    }
    case DynamicVarEnum::var_is_person: {
        if (params_.size() < 1)
        {
            printf("var_is_person incorrect params\n");
            OSOUT("*����id*�e�`*");
        }
        int pid = params_[0];
        os << "���" << Save::getInstance()->getRole(pid)->Name << "�r=1��t=0";
        break;
    }
    case DynamicVarEnum::var_has_status: {
        if (params_.size() < 2)
        {
            printf("var_has_status incorrect params\n");
            OSOUT("*�����B*�e�`*");
        }
        int statusID = params_[0];
        int val = params_[1];
        os << BattleConfManager::battleStatus[statusID].display << "��춵��" << val << "�r=1��t=0";
        break;
    }
    case DynamicVarEnum::var_wg_power: {
        os << "ʹ���书����";
        break;
    }
    default: OSOUT("*�e�`*");
    }
}

BattleMod::StatusVariable::StatusVariable(const BattleStatus & status, VarTarget target) : status_(status), target_(target)
{
}

int BattleMod::StatusVariable::getVal(BattleConfManager& conf, Role * attacker, Role * defender, const Magic * wg) const
{
	Role * c = attacker;
	if (target_ == VarTarget::Other) c = defender;
	auto managerPtr = conf.getStatusManager(c->ID);
	return managerPtr->getBattleStatusVal(status_.id);
}

void BattleMod::StatusVariable::print(std::ostream & os) const
{
    os << status_.display;
}

BattleMod::Adder::Adder(const std::string & description) : description_(description)
{
}

void BattleMod::Adder::print(std::ostream & os) const
{
    if (description_.size() == 0) return;
    os << description_ << " ";
}

BattleMod::RandomAdder::RandomAdder(const std::string & description, int min, int max) : 
    Adder(description), min_(min), max_(max)
{
    if (max_ < min_)
        max_ = min_;
}

BattleMod::RandomAdder::RandomAdder(const std::string & description, std::vector<int>&& items) : 
    Adder(description), items_(std::move(items))
{
}

int BattleMod::RandomAdder::getVal(BattleConfManager& conf, Role * attacker, Role * defender, const Magic * wg) const
{
    if (items_.empty()) {
        // ����è��ʦ������ܲ����ð�
        // 4, 10: 10-4 = 6 -> 7 -> 0~6
        return BattleScene::rng_.rand_int(max_ - min_ + 1) + min_;
    }
    return items_[BattleScene::rng_.rand_int(items_.size())];
}

void BattleMod::RandomAdder::print(std::ostream & os) const
{
    Adder::print(os);
    if (items_.empty()) {
        os << "�S�C" << min_ << "~" << max_;
    }
    else {
        os << "�S�C [";
        for (auto item : items_) {
            os << item << ",";
        }
        os << "]";
    }
}

BattleMod::LinearAdder::LinearAdder(const std::string & description, double k, std::unique_ptr<Variable> v) : 
    Adder(description), k_(k), v_(std::move(v))
{
}

int BattleMod::LinearAdder::getVal(BattleConfManager& conf, Role * attacker, Role * defender, const Magic * wg) const
{
    return int(k_ * v_->getVal(conf, attacker, defender, wg));
}

void BattleMod::LinearAdder::print(std::ostream & os) const
{
    Adder::print(os);
    os << k_ << "X" << "(" << *(v_) << ")";
}

BattleMod::VariableParam::VariableParam(int base, int min, int max) : 
    base_(base), min_(min), max_(max)
{
}

void BattleMod::VariableParam::setMin(int min)
{
    min_ = min;
}

void BattleMod::VariableParam::setMax(int max)
{
    max_ = max;
}

int BattleMod::VariableParam::getBase() const
{
    return base_;
}

int BattleMod::VariableParam::getVal(BattleConfManager& conf, Role * attacker, Role * defender, const Magic * wg) const
{
    int sum = base_;
    // Adder ֮�� �ţ����Ҽ��������Ժ���������� max/min��
    for (const auto& adder : adders_) {
        sum += adder->getVal(conf, attacker, defender, wg);
    }
    if (sum < min_) sum = min_;
    if (sum > max_) sum = max_;
    // �ǲ��ǾͿ�attacker�͹����أ���������Ч��ʱ���Ƿ�����߱����attacker��
    // ���������ʽһ��Ҫ��
    return sum;
}

void BattleMod::VariableParam::addAdder(std::unique_ptr<Adder> adder)
{
    adders_.push_back(std::move(adder));
}

void BattleMod::VariableParam::print(std::ostream & os) const
{
    if (base_ != 0) {
        os << base_;
        if (adders_.size() != 0) {
            os << " + ";
        }
    }
    // TODO use STL
    int i = 0;
    for (const auto& adder : adders_) {
        os << *(adder);
        if (i != adders_.size() - 1) {
            os << " + ";
        }
        i += 1;
    }
}

BattleMod::Condition::Condition(std::unique_ptr<Variable> left, std::unique_ptr<Variable> right, ConditionOp op) :
	left_(std::move(left)), right_(std::move(right)), op_(op)
{
}

bool BattleMod::Condition::check(BattleConfManager& conf, Role * attacker, Role * defender, const Magic * wg) const
{
    int leftVal = left_->getVal(conf, attacker, defender, wg);
    int rightVal = right_->getVal(conf, attacker, defender, wg);
    switch (op_) {
    case ConditionOp::equal: return std::equal_to<int>()(leftVal, rightVal);
    case ConditionOp::greater_than: return std::greater<int>()(leftVal, rightVal);
    case ConditionOp::greater_than_equal: return std::greater_equal<int>()(leftVal, rightVal);
    }
    return false;
}

void BattleMod::Condition::print(std::ostream & os) const
{
    os << *(left_);
    switch (op_) {
    case ConditionOp::equal: os << "��" << *(right_); break;
    case ConditionOp::greater_than: os << "���" << *(right_); break;
    case ConditionOp::greater_than_equal: os << "��춵��" << *(right_); break;
    }
}

BattleMod::EffectParamPair::EffectParamPair(const SpecialEffect & effect, const std::string & desc, 
    EffectDisplayPosition displayOnPerson, int animationEffect) : eip_(effect, desc, displayOnPerson, animationEffect)
{
}

EffectIntsPair BattleMod::EffectParamPair::materialize(BattleConfManager& conf, Role * attacker, Role * defender, const Magic * wg) const
{
    // ��Ҫһ��copy
    EffectIntsPair eip = eip_;
    for (const auto& param : params_) {
        eip.addParam(param.getVal(conf, attacker, defender, wg));
    }
    // ǿ����Ч ֱ����Ч
    if (eip.effect.id == 9)
    {
        conf.applyStatusFromParams(eip.getParams(), attacker);
    }
    else if (eip.effect.id == 8)
    {
        conf.applyStatusFromParams(eip.getParams(), defender);
    }
    //if (!eip.description.empty())
    //    printf("�ɹ�����%d %s\n", eip.effect.id, eip.description.c_str());
    return eip;
}

void BattleMod::EffectParamPair::addParam(VariableParam && vp)
{
    params_.push_back(std::move(vp));
}

void BattleMod::EffectParamPair::print(std::ostream & os) const
{
    // TODO effect ��Ҫһ�����õĴ�ӡ��ʽ
    if (eip_.description.size() == 0) {
        os << eip_.effect;
    }
    else {
        os << eip_.description << " " << eip_.effect;
    }
    if (eip_.effect.id >= 6 && eip_.effect.id <= 9) {
        int id = params_[0].getBase();
        os << "<" << BattleConfManager::battleStatus[id].display << ">[" << params_[1] << "]�c";
    }
    else {
        for (const auto& param : params_) {
            os << "[" << param << "]";
        }
    }
}

void BattleMod::ProccableEffect::addConditions(Conditions&& c)
{
    conditionz_.push_back(std::move(c));
}

bool BattleMod::ProccableEffect::checkConditions(BattleConfManager& conf, Role * attacker, Role * defender, const Magic * wg)
{
    if (conditionz_.empty()) return true;
    // ��"����"�ڣ�ÿһ��֮��Ĺ�ϵ��"��"����OR��
    // ��"����"�ڣ�ÿһ��֮��Ĺ�ϵ��"��"����AND��
    for (auto const& conds : conditionz_) {             // ����
        for (auto const& cond : conds) {                // ����
            if (!cond.check(conf, attacker, defender, wg)) {
                // goto�����һƬ����
                goto nextConds;
            }
        }
        // �������ͨ�� ok
        return true;
    nextConds:;
    }
    return false;
}

void BattleMod::ProccableEffect::print(std::ostream & os) const
{
    if (conditionz_.size() == 0) {
        return;
    }
    os << "����";
    // ��"����"�ڣ�ÿһ��֮��Ĺ�ϵ��"��"����OR��
    // ��"����"�ڣ�ÿһ��֮��Ĺ�ϵ��"��"����AND��
    // Ϲ���
    for (auto const& conds : conditionz_) {             // ����
        os << "{";
        for (auto const& cond : conds) {                // ����
            os << cond;
        }
        os << "}";
    }
    os << '\n';
}

BattleMod::EffectSingle::EffectSingle(VariableParam && p, std::vector<EffectParamPair> && epps) :
    percentProb_(std::move(p)), effectPairs_(std::move(epps))
{
}

// ����EffectIntsPair�Ǹ�copy������ֱ�ӷ���ptr�ˣ�������Ϲ��ֱ���������Ҫ���std::optional(C++17)���������heap allocated std::unique_ptr�Ҳ�ϲ��
std::vector<EffectIntsPair> BattleMod::EffectSingle::proc(BattleConfManager& conf, Role * attacker, Role * defender, const Magic * wg)
{
    if (!ProccableEffect::checkConditions(conf, attacker, defender, wg)) return {};
    // rand [0 1)
    // ����100��ȡ��������˵ʵ�ʷ�Χ��0-99��Ҳ����˵�����1
    int prob = percentProb_.getVal(conf, attacker, defender, wg);
    if (prob <= 0) return {};
    // if (prob != 100)
    //     printf("�������� %d\n", prob);
    std::vector<EffectIntsPair> procs;
    if (BattleScene::rng_.rand_int(100) + 1 <= prob) {
        for (auto& effectPair : effectPairs_) {
            procs.push_back(std::move(effectPair.materialize(conf, attacker, defender, wg)));
        }
    }
    return procs;
}

void BattleMod::EffectSingle::print(std::ostream & os) const
{
    ProccableEffect::print(os);
    os << "[" << percentProb_ << "]% �l��\n";
    for (const auto& epp : effectPairs_) {
        os << epp << "\n";
    }
}

std::vector<EffectIntsPair> BattleMod::EffectWeightedGroup::proc(BattleConfManager& conf, Role * attacker, Role * defender, const Magic * wg)
{
    if (!ProccableEffect::checkConditions(conf, attacker, defender, wg)) return {};
    // printf("���Դ���\n");
    // [0 total)
    int t = BattleScene::rng_.rand_int(total_.getVal(conf, attacker, defender, wg));
    int c = 0;
    for (auto& p : group_) {
        c += p.first.getVal(conf, attacker, defender, wg);
        if (t < c) {
            return { std::move(p.second.materialize(conf, attacker, defender, wg)) };
        }
    }
    return {};
}

BattleMod::EffectWeightedGroup::EffectWeightedGroup(VariableParam && total) : total_(std::move(total))
{
}

void BattleMod::EffectWeightedGroup::addProbEPP(VariableParam && weight, EffectParamPair && epp)
{
    group_.emplace_back(std::move(weight), std::move(epp));
}

void BattleMod::EffectWeightedGroup::print(std::ostream & os) const
{
    ProccableEffect::print(os);
    os << "������" << total_;
    for (const auto& item : group_) {
        os << "����" << item.first << " " << item.second << "\n";
    }
}

BattleMod::EffectPrioritizedGroup::EffectPrioritizedGroup()
{
}

// ���￼���ع�һ�£�����ؘ���
std::vector<EffectIntsPair> BattleMod::EffectPrioritizedGroup::proc(BattleConfManager& conf, Role * attacker, Role * defender, const Magic * wg)
{
    if (!ProccableEffect::checkConditions(conf, attacker, defender, wg)) return {};
    for (auto& p : group_) {
        if (BattleScene::rng_.rand_int(100) < p.first.getVal(conf, attacker, defender, wg)) {
            return { std::move(p.second.materialize(conf, attacker, defender, wg)) };
        }
    }
    return {};
}

void BattleMod::EffectPrioritizedGroup::addProbEPP(VariableParam && weight, EffectParamPair && epp)
{
    group_.emplace_back(std::move(weight), std::move(epp));
}

void BattleMod::EffectPrioritizedGroup::print(std::ostream & os) const
{
    ProccableEffect::print(os);
    os << "������Ȱl��" << "\n";
    for (const auto& item : group_) {
        os << "����" << item.first << " " << item.second << "\n";
    }
}

BattleMod::EffectCounter::EffectCounter(VariableParam && total, VariableParam && add, std::vector<EffectParamPair> && epps) :
    total_(std::move(total)), add_(std::move(add)), effectPairs_(std::move(epps))
{
}

std::vector<EffectIntsPair> BattleMod::EffectCounter::proc(BattleConfManager& conf, Role * attacker, Role * defender, const Magic * wg)
{
    if (attacker == nullptr) return {};
    if (!ProccableEffect::checkConditions(conf, attacker, defender, wg)) return {};
    int id = attacker->RealID;
    auto& count = counter_[id];
    count += add_.getVal(conf, attacker, defender, wg);
    if (count > total_.getVal(conf, attacker, defender, wg)) {
        count = 0;
        std::vector<EffectIntsPair> procs;
        for (auto& effectPair : effectPairs_) {
            procs.push_back(std::move(effectPair.materialize(conf, attacker, defender, wg)));
        } 
        return procs;
    }
    return {};
}

void BattleMod::EffectCounter::print(std::ostream & os) const
{
    ProccableEffect::print(os);
    os << "Ӌ���l�� " << total_ << "ÿ������" << add_ << "\n";
    for (const auto& epp : effectPairs_) {
        os << epp << "\n";
    }
}

bool BattleMod::EffectManager::hasEffect(int eid)
{
    return epps_.find(eid) != epps_.end();
}

int BattleMod::EffectManager::getEffectParam0(int eid)
{
    auto iter = epps_.find(eid);
    // ����0����Ӧ��û����ɡ���
    if (iter == epps_.end()) return 0;
    return iter->second.getParam0();
}

std::vector<int> BattleMod::EffectManager::getAllEffectParams(int eid)
{
    auto iter = epps_.find(eid);
    if (iter == epps_.end()) return {};
    return iter->second.getParams();
}

EffectIntsPair * BattleMod::EffectManager::getEPP(int eid)
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

void BattleMod::EffectManager::addEPP(const EffectIntsPair & ewp)
{
    auto iter = epps_.find(ewp.effect.id);
    if (iter == epps_.end())
        epps_.insert({ ewp.effect.id, ewp });
    else {
        iter->second += ewp;
    }
}

std::size_t BattleMod::EffectManager::size()
{
    return epps_.size();
}

void BattleMod::EffectManager::clear()
{
    epps_.clear();
}

BattleMod::BattleStatus::BattleStatus(int id, int max, const std::string & display, bool hide, BP_Color color) : 
    id(id), max(max), display(display), hide(hide), color(color)
{
}

void BattleMod::BattleStatus::print(std::ostream & os) const
{
    os << display;
}

int BattleMod::BattleStatusManager::myLimit(int & cur, int add, int min, int max)
{
    // ����èд�Ĳ�����
    int curTemp = cur;
    cur = GameUtil::limit(cur + add, min, max);
    return cur - curTemp;
}

int BattleMod::BattleStatusManager::getBattleStatusVal(int statusID) const
{
    if (r_ == nullptr)
    {
        return 0;
    }
    switch (statusID) {
        // �⼸��ƾʲô��һ����Ӧ��ȫ��ͳһ��
    case 0: return r_->Hurt;
    case 1: return r_->Poison;
    case 2: return r_->PhysicalPower;
    default: break;
    }
	auto iter = actualStatusVal_.find(statusID);
	if (iter == actualStatusVal_.end()) return 0;
    return iter->second;
}

void BattleMod::BattleStatusManager::incrementBattleStatusVal(int statusID, int val)
{
    if (val != 0) {
        // printf("pid %d add %s %d\n", r_->ID, (*status_)[statusID].display.c_str(), val);
    }
    tempStatusVal_[statusID] += val;
}

void BattleMod::BattleStatusManager::setBattleStatusVal(int statusID, int val)
{
    actualStatusVal_[statusID] = val;
    tempStatusVal_[statusID] = 0;
}

void BattleMod::BattleStatusManager::initStatus(Role * r, const std::vector<BattleStatus>* status)
{
    status_ = status;
    r_ = r;
}

std::vector<std::pair<const BattleStatus&, int>> BattleMod::BattleStatusManager::materialize()
{
    std::vector<std::pair<const BattleStatus&, int>> changes;
    for (auto& p : tempStatusVal_) {
        int add = 0;
        switch (p.first) {
            // getMaxValue ֵ����0��
        case 0: add = myLimit(r_->Hurt, p.second, 0, 100); break;
        case 1: add = myLimit(r_->Poison, p.second, 0, 100); break;
        case 2: add = myLimit(r_->PhysicalPower, p.second, 0, 100); break;
        default: add = myLimit(actualStatusVal_[p.first], p.second, (*status_)[p.first].min, (*status_)[p.first].max); break;
        }
        if (add != 0)
            changes.emplace_back((*status_)[p.first], add);
        // printf("%d ��ǰ %s %d\n", r_->ID, (*status_)[p.first].display.c_str(), actualStatusVal_[p.first]);
        p.second = 0;
    }
    return changes;
}

std::vector<SpecialEffect> BattleMod::BattleConfManager::effects;
std::vector<BattleStatus> BattleMod::BattleConfManager::battleStatus;

BattleMod::BattleConfManager::BattleConfManager()
{
    effects.clear();
    battleStatus.clear();
	init();
}

const BattleStatusManager * BattleMod::BattleConfManager::getStatusManager(int id) const
{
	auto iter = battleStatusManager.find(id);
	if (iter == battleStatusManager.end()) return nullptr;
	return &(iter->second);
}

void BattleMod::BattleConfManager::init()
{

	// ����
	/*
	Event::getInstance()->setRoleMagic(0, 1, 2, 999);
	Save::getInstance()->getRole(0)->MaxHP = 999;
	Save::getInstance()->getRole(0)->HP = 999;
	Save::getInstance()->getRole(0)->Defence = 80;
	*/

	// �����Ļ�����Ҫ��֤��� ����֮
	YAML::Node baseNode;
	// ������������try�������������Чȫ���
	try {
		baseNode = YAML::LoadFile(BattleMod::CONFIGPATH);
	}
	catch (std::exception e) {
		printf(e.what());
		printf("yaml config missing\n");
		return;
	}

	strPool_.reserve(baseNode[u8"�ַ��������С"].as<int>());
	strPool_.push_back("");

	for (const auto& spNode : baseNode[u8"��Ч"]) {
		// ���밴˳��������Ϊ������TODO ��һ�ģ����ǲ����أ��п��ٸģ�
		assert(effects.size() == spNode[u8"���"].as<int>());
		auto desc = PotConv::conv(spNode[u8"����"].as<std::string>(), "utf-8", "cp936");
		std::reference_wrapper<std::string> descRef(strPool_.front());
		if (!desc.empty()) {
			strPool_.push_back(desc);
			descRef = strPool_.back();
		}
		effects.emplace_back(spNode[u8"���"].as<int>(), descRef);
	}

	for (const auto& bNode : baseNode[u8"ս��״̬"]) {
		int id = bNode[u8"���"].as<int>();
		assert(battleStatus.size() == id);
		auto desc = PotConv::conv(bNode[u8"����"].as<std::string>(), "utf-8", "cp936");

		int max = 100;
		if (const auto& maxNode = bNode[u8"��ֵ"]) {
			max = maxNode.as<int>();
		}

		bool hide = false;
		if (const auto& hideNode = bNode[u8"����"]) {
			hide = hideNode.as<bool>();
		}

		// Ĭ�ϰ�ɫ
		BP_Color c = { 255, 255, 255, 255 };
		if (const auto& cNode = bNode[u8"��ɫ"]) {
			c = { (Uint8)cNode[0].as<int>(), (Uint8)cNode[1].as<int>(), (Uint8)cNode[2].as<int>(), 255 };
			if (cNode.size() >= 4) {
				c.a = (Uint8)cNode[3].as<int>();
			}
		}

		std::reference_wrapper<std::string> descRef(strPool_.front());
		if (!desc.empty()) {
			strPool_.push_back(desc);
			descRef = strPool_.back();
		}
		battleStatus.emplace_back(id, max, descRef, hide, c);
	}

	// ���¿���refactor��TODO �ģ�����
	if (baseNode[u8"�书"]) {
		for (const auto& magicNode : baseNode[u8"�书"]) {
			int wid = magicNode[u8"�书���"].as<int>();
			if (magicNode[u8"����"]) {
				readIntoMapping(magicNode[u8"����"], atkMagic[wid]);
			}
			if (magicNode[u8"����"]) {
				readIntoMapping(magicNode[u8"����"], defMagic[wid]);
			}
			if (magicNode[u8"����"]) {
				readIntoMapping(magicNode[u8"����"], speedMagic[wid]);
			}
			if (magicNode[u8"�غ�"]) {
				readIntoMapping(magicNode[u8"�غ�"], turnMagic[wid]);
			}
		}
	}

	if (auto const& allNode = baseNode[u8"ȫ����"]) {
		if (allNode[u8"����"]) {
			readIntoMapping(allNode[u8"����"], atkAll);
		}
		if (allNode[u8"����"]) {
			readIntoMapping(allNode[u8"����"], defAll);
		}
		if (allNode[u8"����"]) {
			readIntoMapping(allNode[u8"����"], speedAll);
		}
		if (allNode[u8"�غ�"]) {
			readIntoMapping(allNode[u8"�غ�"], turnAll);
		}
	}

	if (baseNode[u8"����"]) {
		for (const auto& personNode : baseNode[u8"����"]) {
			int pid = personNode[u8"������"].as<int>();
			if (personNode[u8"����"]) {
				readIntoMapping(personNode[u8"����"], atkRole[pid]);
			}
			if (personNode[u8"����"]) {
				readIntoMapping(personNode[u8"����"], defRole[pid]);
			}
			if (personNode[u8"����"]) {
				readIntoMapping(personNode[u8"����"], speedRole[pid]);
			}
			if (personNode[u8"�غ�"]) {
				readIntoMapping(personNode[u8"�غ�"], turnRole[pid]);
			}
		}
	}
	printf("load yaml config complete\n");

    std::cout << "����" << "\n";
    printEffects(atkAll);
    std::cout << "���R" << "\n";
    printEffects(defAll);
    std::cout << "�ٶ�" << "\n";
    printEffects(speedAll);
    std::cout << "�غ�" << "\n";
    printEffects(turnAll);

}

std::unique_ptr<Variable> BattleMod::BattleConfManager::readVariable(const YAML::Node & node)
{
	VarTarget target = VarTarget::Self;
	if (node.IsScalar()) {
		int v = node.as<int>();
		return std::make_unique<FlatValue>(v);
	}
	else if (node[u8"״̬"]) {
		int statusID = node[u8"״̬"].as<int>();
		// ��ʱ��֧�ֶԷ�״̬
		return std::make_unique<StatusVariable>(battleStatus[statusID], target);
	}
	else if (const auto& varNode = node[u8"����"]) {
		if (const auto& targetNode = varNode[u8"����"]) {
			target = static_cast<VarTarget>(targetNode.as<int>());
		}
		int varID = varNode[u8"���"].as<int>();
		DynamicVarEnum var = static_cast<DynamicVarEnum>(varID);
		auto dv = std::make_unique<DynamicVariable>(var, target);
		const auto& paramsNode = varNode[u8"����"];
		if (paramsNode) {
            if (paramsNode.IsScalar()) {
                dv->addParam(paramsNode.as<int>());
            }
            else {
                for (const auto& paramNode : paramsNode) {
                    dv->addParam(paramNode.as<int>());
                }
            }
		}
		return std::move(dv);
	}
	return std::make_unique<FlatValue>(0);
}

const std::string& BattleMod::BattleConfManager::adderDescription(const YAML::Node & adderNode, const YAML::Node & subNode, bool copy)
{
    // ��ȡ˵��
    if (const auto& descNode = subNode[u8"˵��"]) {
        // �ǿ���״̬���ڶ��ε��ã��򷵻�����
        if (!copy) {
            const auto& textNode = descNode[u8"����"];
            strPool_.push_back(PotConv::conv(textNode.as<std::string>(), "utf-8", "cp936"));
            return strPool_.back();
        }
        if (const auto& charNode = descNode[u8"����"]) {
            int id = charNode.as<int>();
            auto copyAdder = readAdder(adderNode, false);
            roleAdder[id].push_back(std::move(copyAdder));
            return strPool_[0];
        }
        else if (const auto& magicNode = descNode[u8"�书"]) {
            int id = magicNode.as<int>();
            auto copyAdder = readAdder(adderNode, false);
            magicAdder[id].push_back(std::move(copyAdder));
            return strPool_[0];
        }
        else {
            // û�У���ֱ�ӷ���˵��
            const auto& textNode = descNode[u8"����"];
            strPool_.push_back(PotConv::conv(textNode.as<std::string>(), "utf-8", "cp936"));
            return strPool_.back();
        }
    }
    return strPool_[0];
}

std::unique_ptr<Adder> BattleMod::BattleConfManager::readAdder(const YAML::Node & node, bool copy)
{
    // �����е㸴��
    // ��˵�������У�"�书"����"����"��ʱ���ٵ���һ�Σ��ѽ��������
    // 1. �Ƿ���˵����û���򲻹�
    // 2. �Ƿ�������/�书���� - ��������˵����û�� - ��ȡ˵��
	std::unique_ptr<Adder> adder;
	if (const auto& randNode = node[u8"���"]) {
		const auto& rangeNode = randNode[u8"��Χ"];
		if (rangeNode.IsSequence()) {
			std::vector<int> range;
			for (const auto& n : rangeNode) {
				range.push_back(n.as<int>());
			}
            const std::string& desc = adderDescription(node, randNode, copy);
			adder = std::make_unique<RandomAdder>(desc, std::move(range));
		}
		else {
			// ��ͻȻ��Ӧ�������Ҳ������variable TODO �ĳɶ�variable
			int min = rangeNode[u8"��С"].as<int>();
			int max = rangeNode[u8"���"].as<int>();
            const std::string& desc = adderDescription(node, randNode, copy);
			adder = std::make_unique<RandomAdder>(desc, min, max);
		}
	}
	else if (const auto& linearNode = node[u8"����"]) {
        const std::string& desc = adderDescription(node, linearNode, copy);
		adder = std::make_unique<LinearAdder>(desc, linearNode[u8"ϵ��"].as<double>(), readVariable(linearNode));
	}
	return adder;
}

VariableParam BattleMod::BattleConfManager::readVariableParam(const YAML::Node & node)
{
	if (node.IsScalar()) {
		return VariableParam(node.as<int>());
	}
	const auto& pNode = node[u8"�ɱ����"];
	VariableParam vp(pNode[u8"����"].as<int>());
	if (const auto& minNode = pNode[u8"��С"]) {
		vp.setMin(minNode.as<int>());
	}
	if (const auto& maxNode = pNode[u8"���"]) {
		vp.setMax(maxNode.as<int>());
	}
	if (const auto& adders = pNode[u8"�ӳ�"]) {
		for (const auto& adder : adders) {
			vp.addAdder(readAdder(adder));
		}
	}
	return vp;
}

Conditions BattleMod::BattleConfManager::readConditions(const YAML::Node & node)
{
	Conditions conditions;
	const auto& condNode = node[u8"����"];
	for (const auto& cond : condNode) {
		conditions.push_back(std::move(readCondition(cond)));
	}
	return conditions;
}

Condition BattleMod::BattleConfManager::readCondition(const YAML::Node & node)
{
	const auto& condNode = node[u8"����"];
	auto lhs = readVariable(node[u8"���"]);
	auto rhs = readVariable(node[u8"�ұ�"]);
	ConditionOp opID = static_cast<ConditionOp>(node[u8"�Ա�"].as<int>());
	return Condition(std::move(lhs), std::move(rhs), opID);
}

EffectParamPair BattleConfManager::readEffectParamPair(const YAML::Node& node) {
	int id = node[u8"���"].as<int>();
	auto display = PotConv::conv(node[u8"��ʾ"].as<std::string>(), "utf-8", "cp936");
    EffectDisplayPosition pos = EffectDisplayPosition::no;
    if (const auto& posNode = node[u8"λ��"]) {
        auto posInt = posNode.as<int>();
        pos = static_cast<EffectDisplayPosition>(posInt);
    }
    int eft = -1;
    if (const auto& animNode = node[u8"����"]) {
        eft = animNode.as<int>();
    }
	std::reference_wrapper<std::string> displayRef(strPool_.front());
	if (!display.empty()) {
		strPool_.push_back(display);
		displayRef = strPool_.back();
	}
	// ����Ч�������Ժ�Ҫ������
	EffectParamPair epp(effects[id], displayRef, pos, eft);
	if (node[u8"Ч������"].IsScalar() || node[u8"Ч������"].IsMap()) {
		epp.addParam(readVariableParam(node[u8"Ч������"]));
	}
	else {
		for (const auto& param : node[u8"Ч������"]) {
			epp.addParam(readVariableParam(param));
		}
	}
	return epp;
}

std::vector<EffectParamPair> BattleConfManager::readEffectParamPairs(const YAML::Node& node) {
	std::vector<EffectParamPair> pairs;
	if (node.IsMap()) {
		pairs.push_back(std::move(readEffectParamPair(node)));
	}
	else {
		for (const auto& enode : node) {
			pairs.push_back(std::move(readEffectParamPair(enode)));
		}
	}
	return pairs;
}

std::unique_ptr<ProccableEffect> BattleConfManager::readProccableEffect(const YAML::Node& node) {
	int probType = node[u8"������ʽ"].as<int>();
	ProcProbability prob = static_cast<ProcProbability>(probType);
	std::unique_ptr<ProccableEffect> pe;
	switch (prob) {
	case ProcProbability::random: {
		pe = std::make_unique<EffectSingle>(readVariableParam(node[u8"��������"]), readEffectParamPairs(node[u8"��Ч"]));
		break;
	}
	case ProcProbability::distributed: {
		auto group = std::make_unique<EffectWeightedGroup>(readVariableParam(node[u8"�ܱ���"]));
		for (const auto& eNode : node[u8"��Ч"]) {
			group->addProbEPP(readVariableParam(eNode[u8"��������"]), readEffectParamPair(eNode));
		}
		pe = std::move(group);
		break;
	}
	case ProcProbability::prioritized: {
		auto group = std::make_unique<EffectPrioritizedGroup>();
		for (const auto& eNode : node[u8"��Ч"]) {
			group->addProbEPP(readVariableParam(eNode[u8"��������"]), readEffectParamPair(eNode));
		}
		pe = std::move(group);
		break;
	}
	case ProcProbability::counter: {
		pe = std::make_unique<EffectCounter>(readVariableParam(node[u8"����"]),
			readVariableParam(node[u8"��������"]),
			readEffectParamPairs(node[u8"��Ч"]));
		break;
	}
	}
	if (pe) {
		if (const auto& reqNode = node[u8"����"]) {
			for (const auto& condNode : reqNode) {
				pe->addConditions(readConditions(condNode));
			}
		}
	}
	return pe;
}

void BattleConfManager::readIntoMapping(const YAML::Node& node, BattleMod::Effects& effects) {
	for (auto& spNode : node) {
		effects.push_back(std::move(readProccableEffect(spNode)));
	}
}

void BattleMod::BattleConfManager::printEffects(const Effects & t)
{
    for (const auto& iter : t) {
        std::cout << *(iter) << "\n";
    }
}


std::vector<EffectIntsPair> BattleMod::BattleConfManager::tryProcAndAddToManager(const Effects & list, EffectManager & manager, 
	Role * attacker, Role * defender, const Magic * wg)
{
	std::vector<EffectIntsPair> procd;
	for (const auto& effect : list) {
		auto epps = effect->proc(*this, attacker, defender, wg);
		for (const auto& epp : epps) {
			manager.addEPP(epp);
			procd.push_back(epp);
		}
	}
	return procd;
}

// �ٸ���EffectIntsPair�������Ҿ��ø��������������
std::vector<EffectIntsPair> BattleMod::BattleConfManager::tryProcAndAddToManager(int id, const EffectsTable & table, EffectManager & manager,
	Role * attacker, Role * defender, const Magic * wg)
{
	std::vector<EffectIntsPair> procd;
	auto iter = table.find(id);
	if (iter != table.end()) {
		// TODO �������Ǹ�
		for (const auto& effect : iter->second) {
			auto epps = effect->proc(*this, attacker, defender, wg);
			for (const auto& epp : epps) {
				manager.addEPP(epp);
				procd.push_back(epp);
			}
		}
	}
	return procd;
}

void BattleMod::BattleConfManager::applyStatusFromParams(const std::vector<int>& params, Role * target)
{
	if (params.empty()) return;
	// [״̬id, ״̬ǿ��, ״̬id, ״̬ǿ��...]
	for (std::size_t i = 0; i < params.size() - 1; i += 2) {
		battleStatusManager[target->ID].incrementBattleStatusVal(params[i], params[i + 1]);
	}
}


void BattleMod::BattleConfManager::setStatusFromParams(const std::vector<int>& params, Role * target)
{
	if (params.empty()) return;
	// [״̬id, ״̬ǿ��, ״̬id, ״̬ǿ��...]
	for (std::size_t i = 0; i < params.size() - 1; i += 2) {
		battleStatusManager[target->ID].setBattleStatusVal(params[i], params[i + 1]);
	}
}