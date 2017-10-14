#pragma once
#include "Menu.h"

class UISave : public MenuText
{
public:
    UISave();
    ~UISave();

    int mode_ = 0;  //0Ϊ������1Ϊ�浵

    void setMode(int m) { mode_ = m; }

    void onEntrance() override;

    virtual void onPressedOK() override;

    static void load(int r);
    static void save(int r);
};

