#pragma once
#include <string>
#include "others/SimpleIni.h"
#include <algorithm>
#include "others/libconvert.h"
#include <functional>

//�������ڶ�ȡ�����ļ�����ת�����е��ִ�����Ϊö��
//ע��ʵ��ֻ��ȡ˫������������ǵ�����ģʽ�������ʽת��
//��ȡ������ʱ���Ȼ�ȡ˫��������ǿ��ת��
struct Option
{
    Option() {}
    Option(const std::string& filename) : Option() { loadIniFile(filename); }
    ~Option() {}

private:

    static Option option_;

    CSimpleIniA ini_reader_;
    std::string default_section_ = "";

    std::string dealString(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        convert::replaceAllString(str, "_", "");
        return str;
    }

public:

    static Option* getInstance() { return &option_; }

    //����ini�ļ�
    void loadIniFile(const std::string& filename);
    void loadIniString(const std::string& content);

    //Ĭ��section
    void setDefautlSection(const std::string& section) { default_section_ = section; }
    const std::string& getDefautlSection() { return default_section_; }

    //��Ĭ��section��ȡ
    int getInt(const std::string& key, int default_value = 0)
    {
        return int(getRealFromSection(default_section_, key, default_value));
    }
    double getReal(const std::string& key, double default_value = 0.0)
    {
        return getRealFromSection(default_section_, key, default_value);
    }
    std::string getString(const std::string& key, std::string default_value = "")
    {
        return getStringFromSection(default_section_, key, default_value);
    }

    //��ָ��section��ȡ
    int getIntFromSection(const std::string& section, const std::string& key, int default_value = 0)
    {
        return int(ini_reader_.GetDoubleValue(dealString(section).c_str(), dealString(key).c_str(), default_value));
    }
    double getRealFromSection(const std::string& section, const std::string& key, double default_value = 0.0)
    {
        return ini_reader_.GetDoubleValue(dealString(section).c_str(), dealString(key).c_str(), default_value);
    }
    std::string getStringFromSection(const std::string& section, const std::string& key, std::string default_value = "");

    void print();

public:
    int MaxLevel = 30;
    int MaxHP = 999;
    int MaxMP = 999;
    int MaxPhysicalPower = 100;

    int MaxPosion = 100;

    int MaxAttack = 100;
    int MaxDefence = 100;
    int MaxSpeed = 100;

    int MaxMedcine = 100;
    int MaxUsePoison = 100;
    int MaxDetoxification = 100;
    int MaxAntiPoison = 100;

    int MaxFist = 100;
    int MaxSword = 100;
    int MaxKnife = 100;
    int MaxUnusual = 100;
    int MaxHiddenWeapon = 100;

    int MaxKnowledge = 100;
    int MaxMorality = 100;
    int MaxAttackWithPoison = 100;
    int MaxFame = 999;
    int MaxIQ = 100;

    int MaxExp = 99999;

    int MoneyItemID = 174;
    int CompassItemID = 182;

    void loadSaveValues();
};


