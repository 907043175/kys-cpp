#include "Option.h"

Option Option::option_;

void Option::loadIniFile(const std::string& filename)
{
    std::string content = convert::readStringFromFile(filename);
    loadIniString(content);
}

void Option::loadIniString(const std::string& content)
{
    std::string str = de(content);
    ini_reader_.load(str);
    //�����ļ�������һ��
    auto filenames = convert::splitString(getString("load_ini"), ",");
    for (auto filename : filenames)
    {
        if (filename != "")
        {
            ini_reader_.load(de(convert::readStringFromFile(filename)));
        }
    }
}

//��ȡ�ִ����ԣ���ȥ�������ţ�˫����
std::string Option::getStringFromSection(const std::string& section, const std::string& name, std::string v /*= ""*/)
{
    auto str = ini_reader_.Get(section, name, v);
    convert::replaceAllString(str, "\'", "");
    convert::replaceAllString(str, "\"", "");
    return str;
}

int Option::getIntFromSection2(const std::string& section, const std::string& name, int default_value)
{
    return int(getRealFromSection2(section, name, default_value));
}

//���Ȼ�ȡ�������֣����Թ�������ΪĬ��ֵ��ȡ���ⲿ��
double Option::getRealFromSection2(const std::string& section, const std::string& name, double default_value)
{
    double a = getReal(name, default_value);
    a = getRealFromSection(section, name, a);
    return a;
}

std::string Option::getStringFromSection2(const std::string& section, const std::string& name, std::string default_value)
{
    std::string a = getString(name, default_value);
    a = getStringFromSection(section, name, a);
    return a;
}

void Option::setOptions(std::string section, std::string name_values)
{
    setOptions(section, convert::splitString(name_values, ";"));
}

void Option::setOptions(std::string section, std::vector<std::string> name_values)
{
    for (auto name_value : name_values)
    {
        convert::replaceAllString(name_value, " ", "");
        auto p = name_value.find("=");
        if (p != std::string::npos)
        {
            auto name = name_value.substr(0, p);
            auto value = name_value.substr(p + 1);
            setOption(section, name, value);
        }
    }
}

void Option::loadSaveValues()
{
#define GET_VALUE_INT(v) v = this->getInt(#v, v)

    GET_VALUE_INT(MaxLevel);
    GET_VALUE_INT(MaxHP);
    GET_VALUE_INT(MaxMP);
    GET_VALUE_INT(MaxPhysicalPower);

    GET_VALUE_INT(MaxPosion);

    GET_VALUE_INT(MaxAttack);
    GET_VALUE_INT(MaxDefence);
    GET_VALUE_INT(MaxSpeed);

    GET_VALUE_INT(MaxMedcine);
    GET_VALUE_INT(MaxUsePoison);
    GET_VALUE_INT(MaxDetoxification);
    GET_VALUE_INT(MaxAntiPoison);

    GET_VALUE_INT(MaxFist);
    GET_VALUE_INT(MaxSword);
    GET_VALUE_INT(MaxKnife);
    GET_VALUE_INT(MaxUnusual);
    GET_VALUE_INT(MaxHiddenWeapon);

    GET_VALUE_INT(MaxKnowledge);
    GET_VALUE_INT(MaxMorality);
    GET_VALUE_INT(MaxAttackWithPoison);
    GET_VALUE_INT(MaxFame);
    GET_VALUE_INT(MaxIQ);

    GET_VALUE_INT(MaxExp);

    GET_VALUE_INT(MoneyItemID);
    GET_VALUE_INT(CompassItemID);
}

