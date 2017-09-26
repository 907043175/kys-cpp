#pragma once
#include "Base.h"
#include "Types.h"
#include <memory>

class Head : public Base
{
protected:
    Role* role_ = nullptr;
    static Texture square_;  //��Ѫ��ר�õ�������Ҫʱ��ɫ���������ʺϵĵط�
public:
    Head(Role* r = nullptr);
    virtual ~Head();

    virtual void draw();
    void setRole(Role* r) { role_ = r; }
    Role* getRole() { return role_; }
};

