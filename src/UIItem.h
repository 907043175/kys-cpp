#pragma once
#include "Base.h"
#include "Button.h"

class UIItem : public Base
{
public:
    UIItem();
    ~UIItem();

    //����ע�⣬������ʾ��ƷͼƬ�İ�ť��������ʵ�ʾ�����Ʒ���
    std::vector<Button*> item_buttons_;
    std::vector<int> items_;  //��ǰ�������Ʒ�б�
    int leftup_index_=0;  //���Ͻǵ�һ����Ʒ�ڵ�ǰ�����б��е�����

};

