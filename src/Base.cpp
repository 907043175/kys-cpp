#include "Base.h"
#include "UI.h"

std::vector<Base*> Base::root_;

Base::~Base()
{
    for (auto c : childs_)
    {
        delete c;
    }
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
        {
            b->drawSelfAndChilds();
        }
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
    exit_ = false;
    result_ = -1;
    if (in_root) { addOnRootTop(this); }
    onEntrance();
    while (!exit_)
    {
        if (Base::root_.size() == 0) { break; }
        oneFrame(true);
    }
    onExit();
    if (in_root) { removeFromRoot(this); }
    return result_;
}

Base* Base::removeFromRoot(Base* b)
{
    if (b == nullptr)
    {
        if (root_.size() > 0)
        {
            b = root_.back();
            root_.pop_back();
        }
    }
    else
    {
        for (int i = 0; i < root_.size(); i++)
        {
            if (root_[i] == b)
            {
                root_.erase(root_.begin() + i);
                break;
            }
        }
    }
    //collector_.insert(b);
    return b;
}

void Base::addChild(Base* b)
{
    childs_.push_back(b);
}

void Base::addChild(Base* b, int x, int y)
{
    addChild(b);
    b->setPosition(x_ + x, y_ + y);
}

void Base::removeChild(Base* b)
{
    for (int i = 0; i < childs_.size(); i++)
    {
        if (childs_[i] == b)
        {
            childs_.erase(childs_.begin() + i);
            break;
        }
    }
    //collector_.insert(b);
}

void Base::clearChilds()
{
    for (auto c : childs_)
    {
        delete c;
    }
    childs_.clear();
}

void Base::drawSelfAndChilds()
{
    if (visible_)
    {
        draw();
        for (auto c : childs_)
        {
            if (c->visible_) { c->drawSelfAndChilds(); }
        }
    }
}

//ֻ����ǰ�Ľڵ�͵�ǰ�ڵ���ӽڵ㣬�������Ƿ��ڷ�Χ��
void Base::checkStateAndEvent(BP_Event& e)
{
    if (visible_)
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
        //ע���¸�ʱ��Żử�����Կ�����dealEvent�иı�ԭ��״̬
        dealEvent(e);
    }
}

//һ��ѭ���е�����ע��Ҳ���Ե������ã����ڳ�������
void Base::oneFrame(bool check_event)
{
    BP_Event e;
    auto engine = Engine::getInstance();
    
    Base::drawAll();
    engine->pollEvent(e);
    if (check_event)
    {
        checkStateAndEvent(e);
    }
    switch (e.type)
    {
    case BP_QUIT:
        //if (engine->showMessage("Quit"))
        //loop_ = false;
        break;
    default:
        break;
    }
    int t1 = engine->getTicks();
    int t = 25 - (t1 - prev_present_ticks_);
    if (t <= 0) { t = 1; }
    engine->delay(t);
    engine->renderPresent();
    prev_present_ticks_ = t1;
}

void Base::setAllChildState(State s)
{
    for (auto c : childs_)
    {
        c->state_ = s;;
    }
}

void Base::setChildState(int i, State s)
{
    if (i >= 0 && i < childs_.size())
    {
        childs_[i]->state_ = s;
    }
}
