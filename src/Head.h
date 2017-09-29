#pragma once
#include "Base.h"
#include "Types.h"
#include <memory>

//ע�⣬���ֽڵ�̳����ˣ���Ϊ��ʹ��roleָ��
class Head : public Base
{
protected:
    Role* role_ = nullptr;
public:
    Head(Role* r = nullptr);
    virtual ~Head();

    virtual void draw();
    void setRole(Role* r) { role_ = r; }
    Role* getRole() { return role_; }
};

