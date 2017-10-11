#pragma once
#include <string>
#include <map>
#include "Engine.h"

class Font
{
private:
    Font() {}
    ~Font();
    static Font font_;
    std::map<int, BP_Texture*> buffer_;  //���������Ѿ�����������

    std::string fontnamec_ = "../game/font/chinese.ttf";
    std::string fontnamee_ = "../game/font/english.ttf";

    int calIndex(int size, uint16_t c) { return size * 0x1000000 + c; }
public:
    static Font* getInstance() { return &font_; };
    void draw(const std::string& text, int size, int x, int y, BP_Color color = { 255, 255, 255, 255 }, uint8_t alpha = 255);
    void drawWithBox(const std::string& text, int size, int x, int y, BP_Color color = { 255, 255, 255, 255 }, uint8_t alpha = 255, uint8_t alpha_box = 255);
};

