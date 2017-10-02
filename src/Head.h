#pragma once
#include "Element.h"
#include "Types.h"
#include <memory>

//ע�⣬���ֽڵ�̳����ˣ���Ϊ��ʹ��roleָ��
class Head : public Element
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

