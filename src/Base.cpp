#include "Base.h"
#include <stdio.h>
#include <stdarg.h>
#include "UI.h"

std::vector<Base*> Base::root_;

Base::~Base()
{
    for (auto c : childs_)
    {
        delete c;
    }
}

void Base::LOG(const char* format, ...)
{
    char s[1000];
    va_list arg_ptr;
    va_start(arg_ptr, format);
    vsprintf(s, format, arg_ptr);
    va_end(arg_ptr);
    fprintf(stderr, s);
}

void Base::drawAll()
{
    //�����һ����ռ��Ļ�ĳ�����ʼ��
    int begin_base = 0;
    for (int i = 0; i < Base::root_.size(); i++)    //��¼���һ��ȫ���Ĳ�
    {
        root_[i]->backRun();
        if (Base::root_[i]->full_window_)
        {
            begin_base = i;
        }
    }
    for (int i = begin_base; i < Base::root_.size(); i++)  //�����һ��ȫ���㿪ʼ��
    {
        auto b = Base::root_[i];
        if (b->visible_)
        { b->drawSelfAndChilds(); }
    }
}

void Base::setPosition(int x, int y)
{
    for (auto c : childs_)
    {
        c->setPosition(c->x_ + x - x_, c->y_ + y - y_);
    }
    x_ = x; y_ = y;
}

//����
//����Ϊ�Ƿ���root�����У�Ϊ���������ƣ�Ϊ���򲻻ᱻ����
int Base::run(bool in_root /*= true*/)
{
    BP_Event e;
    auto engine = Engine::getInstance();
    if (in_root) { push(this); }
    entrance();
    loop_ = true;
    result_ = -1;
    while (loop_ && engine->pollEvent(e) >= 0)
    {
        int t0 = engine->getTicks();
        if (Base::root_.size() == 0) { break; }
        Base::drawAll();
        checkStateAndEvent(e);
        switch (e.type)
        {
        case BP_QUIT:
            //if (engine->showMessage("Quit"))
            //loop_ = false;
            break;
        default:
            break;
        }
        engine->renderPresent();
        int t1 = engine->getTicks();
        int t = 25 - (t1 - t0);
        if (t > 0)
        { engine->delay(t); }
    }
    //while (engine->pollEvent(e) > 0);
    //engine->flushEvent();
    exit();
    if (in_root) { pop(); }
    return result_;
}

Base* Base::pop()
{
    Base* b = nullptr;
    if (root_.size() > 0)
    {
        b = root_.back();
        root_.pop_back();
    }

    //�����������Ӧ����������ģ����������
    //ĳЩ����Ľڵ㲻������
    //����Ӧ��ʹ������ָ�룬������
    //if (b != UI::getInstance())
    //{
    //    delete b;
    //}
    return b;
}

void Base::drawSelfAndChilds()
{
    if (visible_)
    {
        draw();
        for (auto c : childs_)
        {
            if (c->visible_) { c->draw(); }
        }
    }
}

void Base::addChild(Base* b, int x, int y)
{
    childs_.push_back(b);
    b->setPosition(x_ + x, y_ + y);
}

void Base::clearChilds()
{
    for (auto c : childs_)
    {
        delete c;
    }
    childs_.clear();
}

//ֻ����ǰ�Ľڵ�͵�ǰ�ڵ���ӽڵ㣬�������Ƿ��ڷ�Χ��
void Base::checkStateAndEvent(BP_Event& e)
{
    //ע�������Ƿ���
    for (int i = childs_.size() - 1; i >= 0; i--)
    {
        childs_[i]->checkStateAndEvent(e);
    }
    //setState(Normal);
    if (e.type == BP_MOUSEMOTION)
    {
        if (inSide(e.motion.x, e.motion.y))
        {
            state_ = Pass;
        }
        else
        {
            state_ = Normal;
        }
    }
    if (e.type == BP_MOUSEBUTTONDOWN)
    {
        if (inSide(e.motion.x, e.motion.y))
        {
            state_ = Press;
        }
    }
    dealEvent(e);
}

//����������Լ���ѭ����ʹ�ã����⿨��
void Base::pollEvent()
{
    BP_Event e;
    Engine::getInstance()->pollEvent(e);
    switch (e.type)
    {
    case BP_QUIT:
        /*if (Engine::getInstance()->showMessage("Quit"))
        {
            Engine::getInstance()->destroy();
        }*/
        break;
    default:
        break;
    }
}
