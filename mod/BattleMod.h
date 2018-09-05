#pragma once

#include "Random.h"
#include "BattleScene.h"
#include "BattleConfig.h"
#include "BattleNetwork.h"
#include "BattleConfig.h"

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
	BattleConfManager conf;
	// simulation��calMagicHurt�ܲ��Ѻ�
    bool simulation_ = false;
    // ���ع�������� ���� ���һ�����
    int multiAtk_ = 0;
    // �����ߣ��纯������Ҫ�Ĺ�����Ч����...�����ַ�����
    std::vector<std::string> atkNames_;

public:

    // �Ҿ����ⲻ��һ��singleton�������ؿ���Ϸ�Ϳ��Բ���
    BattleModifier();

	// �˷�virtual����������Ҫ
	void setID(int id);

    void dealEvent(BP_Event & e) override;

    // ���ҿ����޸���Щ����
    virtual void setRoleInitState(Role* r) override;

    virtual void actRest(Role* r);
    virtual void actUseMagicSub(Role* r, Magic* magic) override;
    virtual void calExpGot() override;
    virtual int calMagicHurt(Role* r1, Role* r2, Magic* magic);
    virtual int calMagiclHurtAllEnemies(Role* r, Magic* m, bool simulation = false);    //����ȫ��������˺�
    // virtual void showNumberAnimation();
    // ������¼ӵ�
    virtual Role* semiRealPickOrTick();
    void setupRolePosition(Role* r, int team, int x, int y);

    void showMagicNames(const std::vector<std::string>& names);

    virtual void renderExtraRoleInfo(Role* r, int x, int y);    // �������ϣ���ʾѪ����

private:
    void addAtkAnim(Role * r, BP_Color color, const std::vector<EffectIntsPair> & eips);
	void addDefAnim(Role * r, BP_Color color, const std::vector<EffectIntsPair> & eips);
};

}