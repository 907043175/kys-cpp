#include "UIItem.h"
#include "Save.h"
#include "others\libconvert.h"
#include "Font.h"
#include "MainScene.h"

UIItem::UIItem()
{
    item_buttons_.resize(21);
    items_.resize(ITEM_IN_BAG_COUNT);
    for (int i = 0; i < item_buttons_.size(); i++)
    {
        auto b = new Button();
        item_buttons_[i] = b;
        b->setPosition(i % item_each_line_ * 85 + 40, i / item_each_line_ * 85 + 100);
        //b->setTexture("item", Save::getInstance()->getItemByBagIndex(i)->ID);
        addChild(b);
    }
    title_ = new MenuText();
    title_->setStrings({ "����", "����", "��ˎ", "����", "ȭ��", "���V", "���", "���T", "�ķ�" });
    title_->setFontSize(25);
    title_->arrange(0, 50, 65, 0);

    addChild(title_);
    int i = 0;
}

UIItem::~UIItem()
{
}

//ԭ���ࣺ0���飬1װ����2���ţ�3ҩƷ��4����
//��ϸ���ࣺ"0����", "1����", "2��ˎ", "3����", "4ȭ��", "5���V", "6���", "7���T", "8�ķ�"
int UIItem::getItemDetailType(Item* item)
{
    if (item == nullptr) { return -1; }
    if (item->ItemType == 0)
    {
        return 0;
    }
    else if (item->ItemType == 1)
    {
        return 1;
    }
    else if (item->ItemType == 3)
    {
        return 2;
    }
    else if (item->ItemType == 4)
    {
        return 3;
    }
    else if (item->ItemType == 2)
    {
        auto m = Save::getInstance()->getMagic(item->MagicID);
        if (m)
        {
            //��ȡ�������Ϊ8
            if (m->HurtType == 0)
            {
                return m->MagicType + 3;
            }
        }
        return 8;
    }
    //δ֪�����൱�ɾ���
    return 0;
}

//ע����䵽�б�����ڱ����е�λ�ö�������Ʒid
void UIItem::geItemBagIndex(int item_type)
{
    std::fill(items_.begin(), items_.end(), -1);
    int k = 0;
    for (int i = 0; i < ITEM_IN_BAG_COUNT; i++)
    {
        if (getItemDetailType(Save::getInstance()->getItemByBagIndex(i)) == item_type)
        {
            items_[k] = i;
            k++;
        }
    }
}

void UIItem::draw()
{
    geItemBagIndex(title_->getResult());

    Item* current_item = nullptr;
    int current_count = 0;
    result_ = -1;
    for (int i = 0; i < item_buttons_.size(); i++)
    {
        auto item = Save::getInstance()->getItemByBagIndex(items_[i]);
        if (item)
        {
            item_buttons_[i]->setTexture("item", item->ID);
            if (item_buttons_[i]->getState() == Pass)
            {
                current_item = item;
                current_count = Save::getInstance()->getItemCountByBagIndex(items_[i]);
            }
        }
        else
        {
            item_buttons_[i]->setTexture("item", -1);
        }
    }
    if (current_item)
    {
        auto str = convert::formatString("%s", current_item->Name);
        Font::getInstance()->draw(str, 25, x_ + 10, y_ + 370, { 255, 255, 255, 255 });
        str = convert::formatString("%5d", current_count);
        Font::getInstance()->draw(str, 25, x_ + 10 + 25 * 7, y_ + 370, { 255, 255, 255, 255 });
        result_ = current_item->ID;
        showItemProperty(current_item);
    }
}

void UIItem::dealEvent(BP_Event& e)
{


}

void UIItem::showItemProperty(Item* item)
{
    Font::getInstance()->draw(item->Introduction, 20, x_ + 10, y_ + 400, { 255, 255, 255, 255 });

    int x = 10, y = 430;
    int size = 20;

    //������ʾ��Ʒ������
    BP_Color c = { 255, 228, 196, 255 };

    //�ر��ж�����
    if (item->isCompass())
    {
        int x, y;
        MainScene::getIntance()->getManPosition(x, y);
        auto str = convert::formatString("��ǰ���ˣ�%d, %d��", x, y);
        showOneProperty(1, str, size, c, x, y);
    }

    //������Ʒ��������ʾ��
    if (item->ItemType == 0)
    {
        return;
    }

    //Font::getInstance()->draw("Ч����", size, x_ + x, y_ + y, c);
    //y += size + 10;

    showOneProperty(item->AddHP, "����%+d", size, c, x, y);
    showOneProperty(item->AddMaxHP, "��������%+d", size, c, x, y);
    showOneProperty(item->AddMP, "����%+d", size, c, x, y);
    showOneProperty(item->AddMaxMP, "��������%+d", size, c, x, y);
    showOneProperty(item->AddPhysicalPower, "�w��%+d", size, c, x, y);
    showOneProperty(item->AddPoison, "�ж�%+d", size, c, x, y);

    showOneProperty(item->AddAttack, "����%+d", size, c, x, y);
    showOneProperty(item->AddSpeed, "�p��%+d", size, c, x, y);
    showOneProperty(item->AddDefence, "���R%+d", size, c, x, y);

    showOneProperty(item->AddMedcine, "�t��%+d", size, c, x, y);
    showOneProperty(item->AddUsePoison, "�ö�%+d", size, c, x, y);
    showOneProperty(item->AddDetoxification, "�ⶾ%+d", size, c, x, y);
    showOneProperty(item->AddAntiPoison, "����%+d", size, c, x, y);

    showOneProperty(item->AddFist, "ȭ��%+d", size, c, x, y);
    showOneProperty(item->AddSword, "����%+d", size, c, x, y);
    showOneProperty(item->AddKnife, "ˣ��%+d", size, c, x, y);
    showOneProperty(item->AddUnusual, "�������%+d", size, c, x, y);
    showOneProperty(item->AddHiddenWeapon, "����%+d", size, c, x, y);

    showOneProperty(item->AddKnowledge, "����%+d", size, c, x, y);
    showOneProperty(item->AddMorality, "����%+d", size, c, x, y);
    showOneProperty(item->AddAttackWithPoison, "���􎧶�%+d", size, c, x, y);

    showOneProperty(item->ChangeMPType == 2, "�����{��", size, c, x, y);
    showOneProperty(item->AddAttackTwice == 1, "�p��", size, c, x, y);

    auto magic = Save::getInstance()->getMagic(item->MagicID);
    if (magic)
    {
        auto str = convert::formatString("������W%s", magic->Name);
        showOneProperty(1, str, size, c, x, y);
    }

    //������ʾ��Ʒ����

    //ҩƷ�Ͱ����಻������ʾ��
    if (item->ItemType == 3 || item->ItemType == 4)
    {
        return;
    }

    x = 10;
    y += size + 10;  //����
    c = { 230, 230, 250, 255 };
    //Font::getInstance()->draw("����", size, x_ + x, y_ + y, c);
    //y += size + 10;
    auto role = Save::getInstance()->getRole(item->OnlySuitableRole);
    if (role)
    {
        auto str = convert::formatString("�H�m��%s", role->Name);
        showOneProperty(1, str, size, c, x, y);
        return;
    }

    showOneProperty(item->NeedMP, "����%d", size, c, x, y);
    showOneProperty(item->NeedAttack, "����%d", size, c, x, y);
    showOneProperty(item->NeedSpeed, "�p��%d", size, c, x, y);

    showOneProperty(item->NeedMedcine, "�t��%d", size, c, x, y);
    showOneProperty(item->NeedUsePoison, "�ö�%d", size, c, x, y);
    showOneProperty(item->NeedDetoxification, "�ⶾ%d", size, c, x, y);

    showOneProperty(item->NeedFist, "ȭ��%d", size, c, x, y);
    showOneProperty(item->NeedSword, "����%d", size, c, x, y);
    showOneProperty(item->NeedKnife, "ˣ��%d", size, c, x, y);
    showOneProperty(item->NeedUnusual, "�������%d", size, c, x, y);
    showOneProperty(item->NeedHiddenWeapon, "����%d", size, c, x, y);

    showOneProperty(item->NeedIQ, "�Y�|%d", size, c, x, y);

    showOneProperty(item->NeedExp, "���A���%d", size, c, x, y);
}

void UIItem::showOneProperty(int v, std::string format_str, int size, BP_Color c, int& x, int& y)
{
    if (v != 0)
    {
        auto str = convert::formatString(format_str.c_str(), v);
        //�����ǲ��ǳ�����
        int draw_length = size * str.size() / 2 + size;
        int x1 = x + draw_length;
        if (x1 > 700)
        {
            x = 10;
            y += size + 5;
        }
        Font::getInstance()->draw(str, size, x_ + x, y_ + y, c);
        x += draw_length;
    }
}
