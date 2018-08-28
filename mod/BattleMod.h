#pragma once

#include "Random.h"
#include "BattleScene.h"
#include "BattleConfig.h"
#include "BattleNetwork.h"

#define YAML_CPP_DLL
#include "yaml-cpp/yaml.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <memory>
#include <functional>

// ��͵����һ��
namespace BattleMod {

class BattleModifier : public BattleScene {
    
private:

    // �Ͻ�����string
    std::vector<std::string> strPool_;

    std::vector<BattleMod::SpecialEffect> effects_;
    std::vector<BattleStatus> battleStatus_;

    // �书Ч����������Magic����࣬�޸ĵĶ���̫��
    // �����书Ч��������ʹ������书����
    EffectsTable atkMagic_;
    // ���������ʱ���Ч��
    EffectsTable defMagic_;
    // ������Ч
    EffectsTable speedMagic_;
    // �غ�/�ж���Ч�������ж��󷢶�������һ�����ж�ǰ���������
    EffectsTable turnMagic_;

    // ���� ������Ч
    EffectsTable atkRole_;
    // ���� ������Ч
    EffectsTable defRole_;
    // ���� ������Ч
    EffectsTable speedRole_;
    EffectsTable turnRole_;

    // �������ﹲ��
    Effects atkAll_;
    Effects defAll_;
    Effects speedAll_;
    Effects turnAll_;


    // ������Ч
    // ������Ч������ֻ��һ�����ڹ������������
    EffectManager atkEffectManager_;
    // ������Ч������ֻ��һ�����ڰ�����������
    EffectManager defEffectManager_;
    // ������Ч ����Ҳֻ��Ҫһ���ˣ�
    EffectManager speedEffectManager_;
    // �غ� Ҳһ����
    EffectManager turnEffectManager_;

    std::unordered_map<int, BattleStatusManager> battleStatusManager_;

    // simulation��calMagicHurt�ܲ��Ѻ�
    bool simulation_ = false;
    // ���ع�������� ���� ���һ�����
    int multiAtk_ = 0;
    // �����ߣ��纯������Ҫ�Ĺ�����Ч����...�����ַ�����
    std::vector<std::string> atkNames_;

    void init();
    Variable readVariable(const YAML::Node& node);
    std::unique_ptr<Adder> readAdder(const YAML::Node& node);
    VariableParam readVariableParam(const YAML::Node& node);
    Conditions readConditions(const YAML::Node& node);
    Condition readCondition(const YAML::Node& node);
    std::unique_ptr<ProccableEffect> readProccableEffect(const YAML::Node& node);
    EffectParamPair readEffectParamPair(const YAML::Node& node);
    std::vector<EffectParamPair> readEffectParamPairs(const YAML::Node& node);
    void readIntoMapping(const YAML::Node& node, BattleMod::Effects& effects);

    std::vector<EffectIntsPair> tryProcAndAddToManager(const Effects& list, EffectManager& manager,
                                                       const Role* attacker, const Role* defender, const Magic* wg);
    std::vector<EffectIntsPair> tryProcAndAddToManager(int id, const EffectsTable& table, EffectManager& manager,
                                                       const Role* attacker, const Role* defender, const Magic* wg);

    void applyStatusFromParams(const std::vector<int>& params, Role* target);
    void setStatusFromParams(const std::vector<int>& params, Role* target);

public:

    // �Ҿ����ⲻ��һ��singleton�������ؿ���Ϸ�Ϳ��Բ���
    BattleModifier();
    BattleModifier(int id);

    void dealEvent(BP_Event & e) override;

    // ���ҿ����޸���Щ����
    virtual void setRoleInitState(Role* r) override;

    virtual void actUseMagicSub(Role* r, Magic* magic) override;

    virtual int calMagicHurt(Role* r1, Role* r2, Magic* magic);
    virtual int calMagiclHurtAllEnemies(Role* r, Magic* m, bool simulation = false);    //����ȫ��������˺�
    // virtual void showNumberAnimation();
    // ������¼ӵ�
    virtual Role* semiRealPickOrTick();
    void setupRolePosition(Role* r, int team, int x, int y);

    void showMagicNames(const std::vector<std::string>& names);

    virtual void renderExtraRoleInfo(Role* r, int x, int y);    // �������ϣ���ʾѪ����
};

}