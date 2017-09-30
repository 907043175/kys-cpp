#include "UIStatus.h"
#include "Font.h"
#include "others/libconvert.h"



UIStatus::UIStatus()
{
}


UIStatus::~UIStatus()
{
}

void UIStatus::draw()
{
    if (role_ == nullptr) { return; }

    TextureManager::getInstance()->renderTexture("head", role_->HeadNum, x_, y_);

    auto font = Font::getInstance();
    BP_Color color = { 255, 255, 255, 255 };
    const int font_size = 30;
    font->draw(convert::formatString("%s", role_->Name), font_size, x_ + 20, y_ + 150, color);
    font->draw(convert::formatString("�ȼ�%5d", role_->Level), font_size, x_ + 20, y_ + 190, color);
    font->draw(convert::formatString("����%5d/%5d", role_->HP, role_->MaxHP), font_size, x_ + 20, y_ + 230, color);
    font->draw(convert::formatString("����%5d/%5d", role_->MP, role_->MaxMP), font_size, x_ + 20, y_ + 270, color);
    font->draw(convert::formatString("�w��%5d/%5d", role_->PhysicalPower, 100), font_size, x_ + 20, y_ + 310, color);
    font->draw(convert::formatString("���%10d", role_->Exp), font_size, x_ + 20, y_ + 350, color);
    font->draw(convert::formatString("����%10d", role_->Exp), font_size, x_ + 20, y_ + 390, color);//�����˵

    font->draw(convert::formatString("����%10d", role_->Attack), font_size, x_ + 300, y_ + 150, color);
    font->draw(convert::formatString("���R%10d", role_->Defence), font_size, x_ + 300, y_ + 190, color);
    font->draw(convert::formatString("�p��%10d", role_->Speed), font_size, x_ + 300, y_ + 230, color);
    //font->draw(convert::formatString("�Ƅ�%10d", role_->Morality), font_size, x_ + 300, y_ + 270, color);//ԭ�治����
    font->draw(convert::formatString("�t������%10d", role_->Medcine), font_size, x_ + 300, y_ + 310, color);
    font->draw(convert::formatString("�ö�����%10d", role_->UsePoison), font_size, x_ + 300, y_ + 350, color);
    font->draw(convert::formatString("�ⶾ����%10d", role_->Detoxification), font_size, x_ + 300, y_ + 390, color);
    font->draw(convert::formatString("ȭ�ƹ���%10d", role_->Fist), font_size, x_ + 300, y_ + 430, color);
    font->draw(convert::formatString("��������%10d", role_->Sword), font_size, x_ + 300, y_ + 470, color);
    font->draw(convert::formatString("ˣ������%10d", role_->Knife), font_size, x_ + 300, y_ + 510, color);
    font->draw(convert::formatString("�������%10d", role_->Unusual), font_size, x_ + 300, y_ + 550, color);
    font->draw(convert::formatString("��������%10d", role_->HiddenWeapon), font_size, x_ + 300, y_ + 690, color);


}
