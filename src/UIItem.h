#pragma once
#include "Element.h"
#include "Button.h"
#include "Menu.h"
#include "Types.h"

class UIItem : public Element
{
public:
    UIItem();
    ~UIItem();

    //����ע�⣬������ʾ��ƷͼƬ�İ�ť��������ʵ�ʾ�����Ʒ���
    std::vector<Button*> item_buttons_;
    std::vector<int> items_;  //��ǰ�������Ʒ�б�
    int leftup_index_ = 0;  //���Ͻǵ�һ����Ʒ�ڵ�ǰ�����б��е�����

    const int item_each_line_ = 7;
    const int line_count_ = 3;

    MenuText* title_ = nullptr;

    int getItemDetailType(Item* item);

    int geItemBagIndexByType(int item_type);

    void draw() override;
    void dealEvent(BP_Event& e) override;

    void showItemProperty(Item* item);
    void showOneProperty(int v, std::string format_str, int size, BP_Color c, int& x, int& y);

    Item* current_item_ = nullptr;

};

