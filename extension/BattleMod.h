#pragma once

#include "Random.h"
#include "BattleScene.h"

#include "yaml-cpp/yaml.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <memory>

// ��͵����һ��
namespace BattleMod {
    typedef int Param;
    typedef std::vector<Param> Params;

    // ������Ч��������Ч����
    class SpecialEffect {
    public:
        SpecialEffect(int id, const std::string& desc);
        int getId() const;
        std::string getDescription() const;
    private:
        int id_;
        const std::string description_;
    };

    // ��Ч�󶨲���
    class EffectParamPair {
    public:
        EffectParamPair(const SpecialEffect& effect, Param p, const std::string& desc);
        // TODO �ټӶ�����ġ����� ˳������variadic template
        Param getParam0();
        const Params& getParams();
        // ���ӷ�ʽ�ɲ�ͬ�����ھͶ�һ����
        virtual EffectParamPair & operator+=(const EffectParamPair & rhs);


        const SpecialEffect& effect;
        // ��Ч��˵(��ʾ����?)
        const std::string description;

    protected:
        // �����ж������
        // ����ÿ�������Ǹ�int�����Լ�������
        // ��������书/����ȼ����ӵ�
        // ��ʱ��������typedef
        Params params_;
    };

    class ProccableEffect {
    public:
        virtual ~ProccableEffect() {};
        // ���������������������
        // �����书��� �Ƿ����������书
        // �Ƿ�ӵ����Ʒ�������������������Եȵȵȵ�
        // proc���ش�����Ч����nullptrΪ����ʧ��
        virtual EffectParamPair* proc(RandomDouble&) = 0;
    };

    enum class ProcProbability {
        random = 0,
        distributed = 1
    };

    // ��������
    class EffectSingle : public ProccableEffect {
    public:
        static const ProcProbability type = ProcProbability::random;
        EffectSingle(int p, EffectParamPair epp);
        EffectParamPair* proc(RandomDouble&) override;
    private:
        int percentProb_;
        EffectParamPair effectPair_;
    };

    // һ����Ч�������ټ̳У�����group��
    class EffectWeightedGroup : public ProccableEffect {
    public:
        static const ProcProbability type = ProcProbability::distributed;
        EffectParamPair* proc(RandomDouble&) override;
        EffectWeightedGroup(int total);
        void addProbEPP(int weight, EffectParamPair epp);
    private:
        // ��������������Ч
        std::vector<std::pair<int, EffectParamPair>> group_;
        int total_;
    };

    class EffectManager {
    public:
        bool hasEffect(int eid);
        Param getEffectParam0(int eid);
        Params getAllEffectParams(int eid);
        EffectParamPair* getEPP(int eid);
        // �ϲ��������Ч
        void unionEffects(const EffectManager& other);
        // ����ȫ����ȡһ��ֱ�Ӽӵ�Ч��
        void addEPP(const EffectParamPair& ewp);
        std::size_t size();
        void clear();
    private:
        std::unordered_map<int, EffectParamPair> epps_;
    };

    typedef std::vector<std::unique_ptr<ProccableEffect>> Effects;
    typedef std::unordered_map<int, BattleMod::Effects> EffectsTable;

class BattleModifier : public BattleScene {
    
private:
    const std::string PATH = "../game/config/battle.yaml";
    std::vector<BattleMod::SpecialEffect> effects_;

    // �书Ч����������Magic����࣬�޸ĵĶ���̫��
    // �����书Ч��������ʹ������书����
    EffectsTable activeAtkMagic_;
    // �����书Ч��������书���ڣ������Ϳ�����Ч
    EffectsTable passiveAtkMagic_;
    // ���������ʱ���Ч��
    EffectsTable passiveDefMagic_;
    // �书 ӵ�м��е�ȫ����Ч������ս���ж�һ�Σ�һ�����Ϊ100%?
    EffectsTable globalMagic_;

    // ����Ч����������Role����࣬�޸ĵĶ���̫��
    // ���� ����������Ч
    EffectsTable atkRole_;
    // ���� ����������Ч
    EffectsTable defRole_;
    // ���� ��ս������Ч������ս���ж�һ��
    EffectsTable globalRole_;


    // ������Ч
    // ������Ч������ֻ��һ�����ڹ������������
    EffectManager atkEffectManager_;
    // ������Ч������ֻ��һ�����ڰ�����������
    EffectManager defEffectManager_;
    // ����������������ӵ�Role���棬�����Ҳ������Ǹ��ļ�
    // ÿ����ս������һ��������Ч��������ÿʱ��params[1] -= 1����0ʱ���
    // ÿ����ս��Ҳ��һ��ȫ����Ч������
    // ������pid��ʶ
    std::unordered_map<int, EffectManager> timeEffectManagers_; // ��û��
    std::unordered_map<int, EffectManager> globalEffectManagers_;

    // simulation��calMagicHurt�ܲ��Ѻ�
    bool simulation_ = false;

    void init();
    std::unique_ptr<ProccableEffect> readProccableEffect(const YAML::Node& node);
    // TODO ȷ��EffectParamPair movable
    EffectParamPair readEffectParamPairs(const YAML::Node& node);
    void readIntoMapping(const YAML::Node& node, BattleMod::Effects& effects);
    std::vector<std::string> tryProcAndAddToManager(int id, const EffectsTable& table, EffectManager& manager);

public:
    // �Ҿ����ⲻ��һ��singleton�������ؿ���Ϸ�Ϳ��Բ���
    BattleModifier();
    BattleModifier(int id);

    // ���ҿ����޸���Щ����
    virtual void setRoleInitState(Role* r) override;
    virtual void useMagic(Role* r, Magic* m);
    virtual int calMagicHurt(Role* r1, Role* r2, Magic* magic);
    virtual int calMagiclHurtAllEnemies(Role* r, Magic* m, bool simulation = false);    //����ȫ��������˺�
    virtual void showNumberAnimation();
    // ������¼ӵ�
    virtual Role* semiRealPickOrTick();
};

}