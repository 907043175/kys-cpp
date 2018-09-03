#pragma once

#include "Types.h"
#include "Save.h"

#define YAML_CPP_DLL
#include "yaml-cpp/yaml.h"

#include <vector>
#include <unordered_map>
#include <utility>
#include <memory>
#include <functional>

// ���´�������
// �Ȱ����ж������� EffectsTable��ս���оͲ�ѯ��
// EffectsTable�б��� ProccableEffect
// ProccableEffect �и�proc�����������������书��Ϣ��û�о�nullptr
// proc���ж���Ч�����Ƿ�ﵽ��һ��vector��Conditions
// ֻҪ��һ��Conditions��꼴��
// ����Conditions��һ��vector��Condition������Condition����ȫ�����
// Condition����Variable-��һ������ָ��ʵ�ֻ�ȡ��Ӧ��ֵ
// ��check�ж�Condition�Ƿ�ͨ��
// Ȼ����ݷ�����ʽ��ProccableEffect������SingleEffect����Pooled
// ���ж�EffectParamPair�Ƿ񴥷�����������һ�� pair<Param, EffectParamPair> �ȸ����Ǹ�Param...
// EffectParamPair ������ EffectIntsPair��Params���
// �����󷵻�EffectIntsPair�����ұ�֤���е�Paramsȫ��ת������Ints
// ���ڽ���Param��ɶ
// �����ǵ�������
// �����Ǹ�VariableParam - һ��vector��<Adder> 
// LinearAdder ȡ������� for k,var in varParam: sum += k*var.getVal()
// RandomAdder ���
// Ȼ��VariableParam�ǿ����б�ŵģ���������ú���ָ��ķ�ʽ͸©BattleMod˽����Ϣ������е���������书���Զ�VariableParam�ӳɣ�
// ���EffectIntsPair�ᱻ��ӵ����Ӧ��EffectManager
// �ٶ����һ��Variable ��ȡ������ʱ��ͻ���ݱ�ŵ��ҵ����ʵĺ���ָ�룬�͵ȵ�ʱ�򴫵�����id���书id(������һ����)���ٵ���

namespace BattleMod {

    // nb
    // https://stackoverflow.com/questions/476272/how-to-properly-overload-the-operator-for-an-ostream
    template<class T>
    auto operator<<(std::ostream& os, const T& t) -> decltype(t.print(os), os)
    {
        t.print(os);
        return os;
    }

    const std::string CONFIGPATH = "../game/config/battle.yaml";

    // ������Ч��������Ч����
    class SpecialEffect {
    public:
        SpecialEffect(int id, const std::string& desc);
        void print(std::ostream& os) const;
        const std::string& description;
        const int id;
    };

	class BattleStatus {
	public:
		// ��һ��Ҫ��ʾ����������Ĵ���
		BattleStatus(int id, int max, const std::string& display, bool hide, BP_Color color);
        void print(std::ostream& os) const;
		const int id;
		const int max;
		const std::string& display;
		const int min = 0;
		const bool hide;
		BP_Color color;
	};

	class BattleStatusManager {
	public:
		int getBattleStatusVal(int statusID) const;
		void incrementBattleStatusVal(int statusID, int val);
		void setBattleStatusVal(int statusID, int val);

		// ��ʼ�������õ�
		void initStatus(Role* r, const std::vector<BattleStatus>* status);

		// �˺������ʱ��Ż��ս���е�״̬ʵЧ�����ҷ�������ֵ��Ч��
		std::vector<std::pair<const BattleStatus&, int>> materialize();
        // void print(std::ostream& os) const;

	private:
		Role * r_;
		const std::vector<BattleStatus>* status_;
		std::map<int, int> tempStatusVal_;
		std::map<int, int> actualStatusVal_;
		int myLimit(int& cur, int add, int min, int max);
	};

    enum class EffectDisplayPosition {
        no,
        on_person,
        on_top,
    };

    // ��Ч�� ��������
    class EffectIntsPair {
    public:
        EffectIntsPair(const SpecialEffect& effect, const std::string& desc, 
            EffectDisplayPosition displayOnPerson = EffectDisplayPosition::no, int animationEffect = -1);

        int getParam0();
        const std::vector<int>& getParams();
        int getAnimation() const;
        void addParam(int p);
        // ���ӷ�ʽ�ɲ�ͬ�����ھͶ�һ����
        virtual EffectIntsPair & operator+=(const EffectIntsPair & rhs);
        void print(std::ostream& os) const;

        const EffectDisplayPosition position;
        const SpecialEffect& effect;
        // ��Ч��˵(��ʾ����?)
        const std::string& description;

    protected:
        // �����ж������
        // ����ÿ�������Ǹ�int�����Լ�������
        // ��������书/����ȼ����ӵ�
        // ��ʱ��������typedef
        std::vector<int> params_;
        int animationEffect_;
    };


	class BattleConfManager;

	class Variable {
	public:
		virtual ~Variable() = default;
		virtual int getVal(BattleConfManager& conf, Role * attacker, Role * defender, const Magic* wg) const = 0;
        virtual void print(std::ostream& os) const = 0;
	};

	class FlatValue : public Variable {
	public:
		FlatValue(int val);
		int getVal(BattleConfManager& conf, Role * attacker, Role * defender, const Magic* wg) const override;
        void print(std::ostream& os) const;
	private:
		int val_;
	};

	enum class VarTarget {
		Self = 0,
		Other = 1,
	};

	enum class DynamicVarEnum {
		var_char_sex = 0,
		var_char_level = 1,
		var_char_exp = 2,
		var_char_hp = 3,
		var_char_maxhp = 4,
		var_char_equip0 = 5,
		var_char_equip1 = 6,
		var_char_mptype = 7,
		var_char_mp = 8,
		var_char_maxmp = 9,
		var_char_attack = 10,
		var_char_speed = 11,
		var_char_defence = 12,
		var_char_medicine = 13,
		var_char_usepoison = 14,
		var_char_detoxification = 15,
		var_char_antipoison = 16,
		var_char_fist = 17,
		var_char_sword = 18,
		var_char_blade = 19,
		var_char_unusual = 20,
		var_char_hiddenweapon = 21,
		var_char_knowledge = 22,
		var_char_morality = 23,
		var_char_attackwithpoison = 24,
		var_char_attacktwice = 25,
		var_char_fame = 26,
		var_char_iq = 27,
		var_using_char = 28,
		var_books = 29,
		var_cur_wg_level = 30,
		var_wg_level = 31,
		var_count_item = 32,
		var_has_wg = 33,
		var_wg_type = 34,
		var_is_person = 35,
		var_has_status = 36,
		var_wg_power = 37,
	};

	class DynamicVariable : public Variable {
	public:
		DynamicVariable(DynamicVarEnum dynamicCode, VarTarget target);
		int getVal(BattleConfManager& conf, Role * attacker, Role * defender, const Magic* wg) const override;
		void addParam(int p);
        void print(std::ostream& os) const;
	private:
		DynamicVarEnum dynamicCode_;
		VarTarget target_;
		std::vector<int> params_;
	};

	class StatusVariable : public Variable {
	public:
		StatusVariable(const BattleStatus& status, VarTarget target);
		int getVal(BattleConfManager& conf, Role * attacker, Role * defender, const Magic* wg) const override;
        void print(std::ostream& os) const;
	private:
		const BattleStatus& status_;
		VarTarget target_;
	};

    // ������������move constructor������д copy constructorȫɾ��
    class Adder {
    public:
        virtual int getVal(BattleConfManager& conf, Role * attacker, Role * defender, const Magic* wg) const = 0;
        Adder(const std::string& description);
        virtual ~Adder() = default;
        virtual void print(std::ostream& os) const;
    protected:
        const std::string& description_;
    };

    class RandomAdder : public Adder {
    public:
        RandomAdder(const std::string & description, int min, int max);
        RandomAdder(const std::string & description, std::vector<int>&& items);
        int getVal(BattleConfManager& conf, Role * attacker, Role * defender, const Magic* wg) const override;
        void print(std::ostream& os) const;
    private:
        int min_;
        int max_;
        std::vector<int> items_;
    };

    class LinearAdder : public Adder {
    public:
        // �������һ�£�&&�������ȫ���ᱻmove��
        LinearAdder(const std::string & description, double k, std::unique_ptr<Variable> v);
        int getVal(BattleConfManager& conf, Role * attacker, Role * defender, const Magic* wg) const override;
        void print(std::ostream& os) const;
    private:
        double k_;
        std::unique_ptr<Variable> v_;
    };

    class VariableParam {
    public:
        // ��int���ֵ��ʵ�������ã������С�жϺ��鷳
        static const int DEFAULTMIN = -999999;
        static const int DEFAULTMAX = 999999;
        VariableParam(int base, int min = VariableParam::DEFAULTMIN, int max = VariableParam::DEFAULTMAX);
        void setMin(int min);
        void setMax(int max);
        int getBase() const;
        int getVal(BattleConfManager& conf, Role * attacker, Role * defender, const Magic* wg) const;
        void addAdder(std::unique_ptr<Adder> adder);
        VariableParam(const VariableParam&) = delete;
        VariableParam(VariableParam&& o) noexcept : base_(o.base_), min_(o.min_), max_(o.max_), adders_(std::move(o.adders_)) { }
        void print(std::ostream& os) const;
    private:
        int base_;
        int min_;
        int max_;
        std::vector<std::unique_ptr<Adder>> adders_;
    };

    enum class ConditionOp {
        greater_than = 0,
        greater_than_equal = 1,
        equal = 2
    };
    class Condition {
    public:
        Condition(std::unique_ptr<Variable> left, std::unique_ptr<Variable> right, ConditionOp op);
		Condition(const Condition&) = delete;
        Condition(Condition&& o) noexcept : left_(std::move(o.left_)), right_(std::move(o.right_)), op_(std::move(o.op_)) {}
        bool check(BattleConfManager& conf, Role * attacker, Role * defender, const Magic* wg) const;
        void print(std::ostream& os) const;
    private:
		std::unique_ptr<Variable> left_;
		std::unique_ptr<Variable> right_;
        ConditionOp op_;
    };

    class EffectParamPair {
    public:
        EffectParamPair(const SpecialEffect& effect, const std::string& desc, EffectDisplayPosition displayOnPerson, int animationEffect);
        EffectIntsPair materialize(BattleConfManager& conf, Role * attacker, Role * defender, const Magic* wg) const;
        void addParam(VariableParam&& vp);
        EffectParamPair(EffectParamPair&& o) noexcept : params_(std::move(o.params_)), eip_(o.eip_) { }
        EffectParamPair(const EffectParamPair&) = delete;
        void print(std::ostream& os) const;
    private:
        std::vector<VariableParam> params_;
        EffectIntsPair eip_;
    };

    using Conditions = std::vector<Condition>;
    class ProccableEffect {
    public:
        virtual ~ProccableEffect() = default;
        // ���������������������
        // �����书��� �Ƿ����������书
        // �Ƿ�ӵ����Ʒ�������������������Եȵȵȵ�
        // proc���ش�����Ч����nullptrΪ����ʧ��
        virtual std::vector<EffectIntsPair> proc(BattleConfManager& conf, Role * attacker, Role * defender, const Magic* wg) = 0;
        // Condition���ݽ�ȥ֮�����������
        void addConditions(Conditions&& c);
        ProccableEffect() {}
        ProccableEffect(ProccableEffect&& o)  noexcept : conditionz_(std::move(o.conditionz_)) {}
        ProccableEffect(const ProccableEffect&) = delete;
        // �H��ӡ����
        virtual void print(std::ostream& os) const;

    protected:
        bool checkConditions(BattleConfManager& conf, Role * attacker, Role * defender, const Magic * wg);
        std::vector<Conditions> conditionz_;
    };

    enum class ProcProbability {
        random = 0,
        distributed = 1,
        prioritized = 2,
        counter = 3,
    };

    // ��������
    // �����ˣ��Ӵ˵���ָ�����жϣ����Զ����Чͬʱ����!
    // �Ժ�Ͳ���std::optional��
    class EffectSingle : public ProccableEffect {
    public:
        EffectSingle(VariableParam&& p, std::vector<EffectParamPair>&& epps);
        std::vector<EffectIntsPair> proc(BattleConfManager& conf, Role * attacker, Role * defender, const Magic* wg) override;
        EffectSingle(EffectSingle&& o) noexcept : ProccableEffect(std::move(o)), percentProb_(std::move(o.percentProb_)), effectPairs_(std::move(o.effectPairs_)) { }
        EffectSingle(const EffectSingle&) = delete;
        void print(std::ostream& os) const;
    private:
        VariableParam percentProb_;
        std::vector<EffectParamPair> effectPairs_;
    };

    // һ����Ч�������ټ̳У�����group��
    class EffectWeightedGroup : public ProccableEffect {
    public:
        std::vector<EffectIntsPair> proc(BattleConfManager& conf, Role * attacker, Role * defender, const Magic* wg) override;
        EffectWeightedGroup(VariableParam&& total);
        EffectWeightedGroup(EffectWeightedGroup&& o) noexcept : ProccableEffect(std::move(o)), group_(std::move(o.group_)), total_(std::move(o.total_)) { }
        void addProbEPP(VariableParam&& weight, EffectParamPair&& epp);
        EffectWeightedGroup(const EffectWeightedGroup&) = delete;
        void print(std::ostream& os) const;
    private:
        // ��������������Ч
        std::vector<std::pair<VariableParam, EffectParamPair>> group_;
        VariableParam total_;
    };

    class EffectPrioritizedGroup : public ProccableEffect {
    public:
        EffectPrioritizedGroup();
        EffectPrioritizedGroup(EffectPrioritizedGroup&& o) noexcept :ProccableEffect(std::move(o)), group_(std::move(o.group_)) { }
        std::vector<EffectIntsPair> proc(BattleConfManager& conf, Role * attacker, Role * defender, const Magic* wg) override;
        void addProbEPP(VariableParam&& prob, EffectParamPair&& epp);
        EffectPrioritizedGroup(const EffectPrioritizedGroup&) = delete;
        void print(std::ostream& os) const;
    private:
        std::vector<std::pair<VariableParam, EffectParamPair>> group_;
    };

    // ʵ�ַ�ʽ�ǣ��ٸ�һ��std::unordered_map
    class EffectCounter : public ProccableEffect {
    public:
        EffectCounter(VariableParam&& total, VariableParam&& add, std::vector<EffectParamPair>&& epps);
        std::vector<EffectIntsPair> proc(BattleConfManager& conf, Role * attacker, Role * defender, const Magic* wg) override;
        EffectCounter(EffectCounter&& o) noexcept : ProccableEffect(std::move(o)), total_(std::move(o.total_)),
                                                    add_(std::move(o.add_)), 
                                                    effectPairs_(std::move(o.effectPairs_)), counter_(std::move(counter_)){ }
        EffectCounter(const EffectCounter&) = delete;
        void print(std::ostream& os) const;
    private:
        VariableParam total_;
        VariableParam add_;
        std::vector<EffectParamPair> effectPairs_;
        std::unordered_map<int, int> counter_;
    };

    class EffectManager {
    public:
        bool hasEffect(int eid);
        int getEffectParam0(int eid);
        std::vector<int> getAllEffectParams(int eid);
        EffectIntsPair* getEPP(int eid);    // TODO ��std::optional
                                            // �ϲ��������Ч
        void unionEffects(const EffectManager& other);
        // ����ȫ����ȡһ��ֱ�Ӽӵ�Ч��
        void addEPP(const EffectIntsPair& ewp);
        std::size_t size();
        void clear();
    private:
        std::unordered_map<int, EffectIntsPair> epps_;
    };

    using Effects = std::vector<std::unique_ptr<ProccableEffect>>;
    using EffectsTable = std::unordered_map<int, BattleMod::Effects>;

	// ��֪��ȡɶ������
	class BattleConfManager {
	public:
		BattleConfManager();
		const BattleStatusManager * getStatusManager(int id) const;
        std::vector<EffectIntsPair> tryProcAndAddToManager(const Effects& list, EffectManager& manager,
            Role * attacker, Role * defender, const Magic* wg);
        std::vector<EffectIntsPair> tryProcAndAddToManager(int id, const EffectsTable& table, EffectManager& manager,
            Role * attacker, Role * defender, const Magic* wg);

        void applyStatusFromParams(const std::vector<int>& params, Role* target);
        void setStatusFromParams(const std::vector<int>& params, Role* target);

		// ����Ҫһ�����ú���
		static std::vector<SpecialEffect> effects;
		static std::vector<BattleStatus> battleStatus;

		// �书Ч����������Magic����࣬�޸ĵĶ���̫��
		// �����书Ч��������ʹ������书����
		EffectsTable atkMagic;
		// ���������ʱ���Ч��
		EffectsTable defMagic;
		// ������Ч
		EffectsTable speedMagic;
		// �غ�/�ж���Ч�������ж��󷢶�������һ�����ж�ǰ���������
		EffectsTable turnMagic;

		// ���� ������Ч
		EffectsTable atkRole;
		// ���� ������Ч
		EffectsTable defRole;
		// ���� ������Ч
		EffectsTable speedRole;
		EffectsTable turnRole;

		// �������ﹲ��
		Effects atkAll;
		Effects defAll;
		Effects speedAll;
		Effects turnAll;

        // ��Ч˵��
        std::unordered_map<int, std::vector<std::unique_ptr<Adder>>> magicAdder;
        std::unordered_map<int, std::vector<std::unique_ptr<Adder>>> roleAdder;

		// ������Ч
		// ������Ч������ֻ��һ�����ڹ������������
		EffectManager atkEffectManager;
		// ������Ч������ֻ��һ�����ڰ�����������
		EffectManager defEffectManager;
		// ������Ч ����Ҳֻ��Ҫһ���ˣ�
		EffectManager speedEffectManager;
		// �غ� Ҳһ����
		EffectManager turnEffectManager;
		std::unordered_map<int, BattleStatusManager> battleStatusManager;

	private:
		// �Ͻ�����string
		std::vector<std::string> strPool_;

		void init();
		std::unique_ptr<Variable> readVariable(const YAML::Node& node);
		std::unique_ptr<Adder> readAdder(const YAML::Node& node, bool copy = true);
        const std::string& adderDescription(const YAML::Node & adderNode, const YAML::Node & subNode, bool copy);
		VariableParam readVariableParam(const YAML::Node& node);
		Conditions readConditions(const YAML::Node& node);
		Condition readCondition(const YAML::Node& node);
		std::unique_ptr<ProccableEffect> readProccableEffect(const YAML::Node& node);
		EffectParamPair readEffectParamPair(const YAML::Node& node);
		std::vector<EffectParamPair> readEffectParamPairs(const YAML::Node& node);
		void readIntoMapping(const YAML::Node& node, BattleMod::Effects& effects);

        void printEffects(const Effects& t);
	};
}