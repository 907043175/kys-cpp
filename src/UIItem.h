#pragma once
#include "Element.h"
#include "Button.h"
#include "Menu.h"

class UIItem : public Element
{
public:
    UIItem();
    ~UIItem();

    //����ע�⣬������ʾ��ƷͼƬ�İ�ť��������ʵ�ʾ�����Ʒ���
    std::vector<Button*> item_buttons_;
    std::vector<int> items_;  //��ǰ�������Ʒ�б�
    int leftup_index_=0;  //���Ͻǵ�һ����Ʒ�ڵ�ǰ�����б��е�����

    MenuText* title_ = nullptr;

};

