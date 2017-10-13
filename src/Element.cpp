#include "Element.h"
#include "UISystem.h"

std::vector<Element*> Element::root_;
int Element::prev_present_ticks_ = 0;

Element::~Element()
{
    for (auto c : childs_)
    {
        delete c;
    }
}

void Element::drawAll()
{
    //�����һ����ռ��Ļ�ĳ�����ʼ��
    int begin_base = 0;
    for (int i = 0; i < root_.size(); i++)    //��¼���һ��ȫ���Ĳ�
    {
        root_[i]->backRun();
        if (root_[i]->full_window_)
        {
            begin_base = i;
        }
    }
    for (int i = begin_base; i < root_.size(); i++)  //�����һ��ȫ���㿪ʼ��
    {
        auto b = root_[i];
        if (b->visible_ && !b->exit_)
        {
            b->drawSelfAndChilds();
        }
    }
}

//����λ�ã���ı��ӽڵ��λ��
void Element::setPosition(int x, int y)
{
    for (auto c : childs_)
    {
        c->setPosition(c->x_ + x - x_, c->y_ + y - y_);
    }
    x_ = x; y_ = y;
}

//�ӻ��Ƶĸ��ڵ��Ƴ�
Element* Element::removeFromRoot(Element* element)
{
    if (element == nullptr)
    {
        if (!root_.empty())
        {
            element = root_.back();
            root_.pop_back();
        }
    }
    else
    {
        for (int i = 0; i < root_.size(); i++)
        {
            if (root_[i] == element)
            {
                root_.erase(root_.begin() + i);
                break;
            }
        }
    }
    return element;
}

//����ӽڵ�
void Element::addChild(Element* element)
{
    childs_.push_back(element);
}

//��ӽڵ㲢ͬʱ�����ӽڵ��λ��
void Element::addChild(Element* element, int x, int y)
{
    addChild(element);
    element->setPosition(x_ + x, y_ + y);
}

//�Ƴ�ĳ���ڵ�
void Element::removeChild(Element* element)
{
    for (int i = 0; i < childs_.size(); i++)
    {
        if (childs_[i] == element)
        {
            childs_.erase(childs_.begin() + i);
            break;
        }
    }
}

//����ӽڵ�
void Element::clearChilds()
{
    for (auto c : childs_)
    {
        delete c;
    }
    childs_.clear();
}

//����������ӽڵ�
void Element::drawSelfAndChilds()
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

void Element::checkResult()
{
    //��ȡ��ǰ���ڱ�����İ�ť����Ҫ������
    for (int i = 0; i < getChildCount(); i++)
    {
        if (getChild(i)->getState() == Press)
        {
            result_ = i;
        }
    }
}

void Element::setAllChildState(int s)
{
    for (auto c : childs_)
    {
        c->state_ = s;
    }
}

void Element::setAllChildVisible(bool v)
{
    for (auto c : childs_)
    {
        c->visible_ = v;
    }
}

int Element::findNextVisibleChild(int i0, int direct)
{
    if (direct == 0 || childs_.size() == 0) { return i0; }
    direct = direct > 0 ? 1 : -1;

    int i1 = i0;
    for (int i = 1; i < childs_.size(); i++)
    {
        i1 += direct;
        i1 = (i1 + childs_.size()) % childs_.size();
        if (childs_[i1]->visible_)
        {
            return i1;
        }
    }
    return i0;
}

int Element::findFristVisibleChild()
{
    for (int i = 0; i < childs_.size(); i++)
    {
        if (childs_[i]->visible_)
        {
            return i;
        }
    }
    return -1;
}

//���б��ڵ㣬����Ϊ�Ƿ���root�����У�Ϊ���������ƣ�Ϊ���򲻻ᱻ����
int Element::run(bool in_root /*= true*/)
{
    exit_ = false;
    visible_ = true;
    if (in_root) { addOnRootTop(this); }
    onEntrance();
    while (!exit_)
    {
        if (root_.empty()) { break; }
        checkEventAndPresent(true);
        drawAll();
    }
    onExit();
    if (in_root) { removeFromRoot(this); }
    return result_;
}

//����������¼���Ӧ
//ֻ����ǰ�Ľڵ�͵�ǰ�ڵ���ӽڵ㣬�������Ƿ��ڷ�Χ��
//ע��ȫ����Ľڵ�Ҫһֱ�����¼�
void Element::checkStateAndEvent(BP_Event& e)
{
    if (visible_ || full_window_ != 0)
    {
        //ע�������Ƿ���
        for (int i = childs_.size() - 1; i >= 0; i--)
        {
            childs_[i]->checkStateAndEvent(e);
        }

        //�����꾭�������µ�״̬
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
        if (e.type == BP_MOUSEBUTTONDOWN || e.type == BP_MOUSEBUTTONUP)
        {
            if (inSide(e.motion.x, e.motion.y))
            {
                state_ = Press;
            }
            else
            {
                state_ = Normal;
            }
        }
        if ((e.type == BP_KEYDOWN && (e.key.keysym.sym == BPK_RETURN || e.key.keysym.sym == BPK_SPACE)))
        {
            if (state_ == Pass)
            {
                state_ = Press;
            }
        }

        //ע���¸�ʱ��Żử�����Կ�����dealEvent�иı�ԭ��״̬
        dealEvent(e);
        //Ϊ�򻯴��룬�����»س���ESC�Ĳ���д�ڴ˴�
        if ((e.type == BP_KEYUP && (e.key.keysym.sym == BPK_RETURN || e.key.keysym.sym == BPK_SPACE))
            || (e.type == BP_MOUSEBUTTONUP && e.button.button == BP_BUTTON_LEFT))
        {
            checkResult();
            onPressedOK();
        }
        if ((e.type == BP_KEYUP && e.key.keysym.sym == BPK_ESCAPE)
            || (e.type == BP_MOUSEBUTTONUP && e.button.button == BP_BUTTON_RIGHT))
        {
            onPressedCancel();
        }
    }
    else
    {
        state_ = Normal;
    }
}

//����¼��������Ƶ�ͼ��ʾ����
void Element::checkEventAndPresent(bool check_event)
{
    BP_Event e;
    auto engine = Engine::getInstance();
    while (engine->pollEvent(e) > 0);  //ʵ����ֻҪ���һ���¼�
    //engine->pollEvent(e);
    if (check_event)
    {
        checkStateAndEvent(e);
    }
    switch (e.type)
    {
    case BP_QUIT:
        UISystem::askExit();
        break;
    default:
        break;
    }
    int t1 = engine->getTicks();
    int t = max_delay_ - (t1 - prev_present_ticks_);
    if (t > max_delay_) { t = max_delay_; }
    if (t <= 0) { t = 1; }
    engine->delay(t);
    engine->renderPresent();
    prev_present_ticks_ = t1;
}

void Element::exitAll(int begin)
{
    for (int i = begin; i < root_.size(); i++)
    {
        root_[i]->exit_ = true;
        for (auto c : root_[i]->childs_)
        {
            c->exit_ = true;
        }
    }
}

//ר������ĳЩ����¶�������ʾ����ʱ
//�м���Բ���һ����������Щʲô���벻�����õķ�����
int Element::drawAndPresent(int times, std::function<void(void*)> func, void* data)
{
    if (times < 1) { times = 1; }
    if (times > 100) { times = 100; }
    for (int i = 0; i < times; i++)
    {
        drawAll();
        if (func)
        {
            func(data);
        }
        checkEventAndPresent(false);
    }
    return times;
}

//void Element::setChildState(int i, int s)
//{
//    if (i >= 0 && i < childs_.size())
//    {
//        childs_[i]->state_ = s;
//    }
//}
//
//int Element::getChildState(int i)
//{
//    if (i >= 0 && i < childs_.size())
//    {
//        return childs_[i]->state_;
//    }
//    return Normal;
//}
