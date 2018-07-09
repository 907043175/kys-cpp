#pragma once
#include "Engine.h"
#include <map>
#include <string>

class Font
{
private:
    Font() {}
    ~Font();
    std::map<int, BP_Texture*> buffer_; //���������Ѿ�����������

    std::string fontnamec_ = "../game/font/chinese.ttf";
    std::string fontnamee_ = "../game/font/english.ttf";

    BP_Texture* indexTex(int size, uint16_t c);

public:
    static Font* getInstance()
    {
        static Font f;
        return &f;
    }
    void draw(const std::string& text, int size, int x, int y, BP_Color color = { 255, 255, 255, 255 }, uint8_t alpha = 255);
    void drawWithBox(const std::string& text, int size, int x, int y, BP_Color color = { 255, 255, 255, 255 }, uint8_t alpha = 255, uint8_t alpha_box = 255);
};
