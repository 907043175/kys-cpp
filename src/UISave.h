#pragma once
#include "Menu.h"

class UISave : public MenuText
{
public:
    UISave();
    ~UISave();

    int mode_ = 0;  //0Ϊ������1Ϊ�浵

    void onEntrance() override;

};

