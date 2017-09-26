#pragma once
#include <string>
#include <map>
#include "Engine.h"

class Font
{
private:
    static Font font_;
    std::map<int, BP_Texture*> buffer_;  //缓存所有已经画过的字体

    std::string fontnamec_ = "../game/font/chinese.ttf";
    std::string fontnamee_ = "../game/font/english.ttf";

    int calIndex(int size, uint16_t c) { return size * 65536 + c; }
    void splitText(std::string text);

public:
    Font() {}
    ~Font() {}
    static Font* getInstance() { return &font_; };
    void draw(std::string text, int size, int x, int y, BP_Color c, uint8_t alpha = 255);
};

