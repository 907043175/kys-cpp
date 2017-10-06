#pragma once
#include "Element.h"
#include "Types.h"
#include <memory>

//���ƴ�����ͷ��ļ���״̬
//ע�⣬�������ͼ̳д��࣬��Ϊ��ʹ��roleָ��
class Head : public Element
{
protected:
    Role* role_ = nullptr;
public:
    Head(Role* r = nullptr);
    virtual ~Head();

    virtual void draw() override;
    void setRole(Role* r) { role_ = r; }
    Role* getRole() { return role_; }
};

