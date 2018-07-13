#pragma once
#include "Element.h"

class TextBox : public Element
{
public:
    TextBox() {}
    virtual ~TextBox() {}
protected:
    std::string text_ = "";
    int font_size_ = 20;
    int text_x_ = 0, text_y_ = 0;
    BP_Color color_normal_ = { 32, 32, 32, 255 };
    BP_Color color_pass_ = { 255, 255, 255, 255 };
    BP_Color color_press_ = { 255, 255, 255, 255 };
    bool have_box_ = true;

    std::string texture_path_ = "";
    int texture_normal_id_ = -1, texture_pass_id_ = -1, texture_press_id_ = -1; //����״̬�İ�ťͼƬ

    bool resize_with_text_ = false;

public:
    void setTexture(const std::string& path, int normal_id, int pass_id = -1, int press_id = -1);
    int getNormalTextureID() { return texture_normal_id_; }

    void setFontSize(int size);
    void setText(std::string text);
    std::string  getText() { return text_; };
    void setTextPosition(int x, int y) { text_x_ = x; text_y_ = y; }  //ע�⣺����ᵼ�½���������⣬ͨ����Ϊ��ʵ��һЩ����Ч������������ʹ��
    void setTextColor(BP_Color c1, BP_Color c2, BP_Color c3);
    void setTextColor(BP_Color c1) { color_normal_ = c1; }

    virtual void draw() override;
    void setHaveBox(bool h) { have_box_ = h; }

    virtual void onPressedOK() override { exitWithResult(0); }
    virtual void onPressedCancel() override { exitWithResult(-1); }
};

