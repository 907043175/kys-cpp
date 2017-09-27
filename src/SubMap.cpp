#include "SubMap.h"
#include "MainMap.h"
#include "BattleMap.h"
#include "Event.h"
#include "UI.h"

SubMapRecord* SubMap::current_submap_record_;
int SubMap::current_submap_id_;
//int SubMap::current_item_id_;
int SubMap::event_x_, SubMap::event_y_;

SubMap::SubMap() :
    man_x_(Save::getInstance()->SubMapX),
    man_y_(Save::getInstance()->SubMapY)
{
    full_window_ = 1;
}

SubMap::SubMap(int num) : SubMap()
{
    setSceneNum(num);
    record_ = Save::getInstance()->getSubMapRecord(num);
    record_->ID = num;
    setPosition(record_->EntranceX, record_->EntranceY);
}

SubMap::~SubMap()
{

}

void SubMap::draw()
{
    int k = 0;
    struct DrawInfo { int i; Point p; };
    //std::map<int, DrawInfo> map;
    Engine::getInstance()->fillColor({ 0, 0, 0, 255 }, 0, 0, -1, -1);

    //���»�����������
    //�޸߶ȵ���һ�λ���
    for (int sum = -view_sum_region_; sum <= view_sum_region_ + 15; sum++)
    {
        for (int i = -view_width_region_; i <= view_width_region_; i++)
        {
            int i1 = view_x_ + i + (sum / 2);
            int i2 = view_y_ - i + (sum - sum / 2);
            auto p = getPositionOnScreen(i1, i2, view_x_, view_y_);
            if (i1 >= 0 && i1 < MAX_COORD && i2 >= 0 && i2 < MAX_COORD)
            {
                int h = record_->BuildingHeight(i1, i2);
                int num = record_->Earth(i1, i2) / 2;
                //�޸߶ȵ���
                if (num > 0 && h == 0)
                {
                    TextureManager::getInstance()->renderTexture("smap", num, p.x, p.y);
                }
            }
        }
    }
    for (int sum = -view_sum_region_; sum <= view_sum_region_ + 15; sum++)
    {
        for (int i = -view_width_region_; i <= view_width_region_; i++)
        {
            int i1 = view_x_ + i + (sum / 2);
            int i2 = view_y_ - i + (sum - sum / 2);
            auto p = getPositionOnScreen(i1, i2, view_x_, view_y_);
            if (i1 >= 0 && i1 < MAX_COORD && i2 >= 0 && i2 < MAX_COORD)
            {
                //�и߶ȵ���
                int h = record_->BuildingHeight(i1, i2);
                int num = record_->Earth(i1, i2) / 2;
                if (num > 0 && h > 0)
                {
                    TextureManager::getInstance()->renderTexture("smap", num, p.x, p.y);
                }
                //����������
                num = record_->Building(i1, i2) / 2;
                if (num > 0)
                {
                    TextureManager::getInstance()->renderTexture("smap", num, p.x, p.y - h);
                }
                if (i1 == man_x_ && i2 == man_y_)
                {
                    if (man_pic_ != -1)
                    {
                        man_pic_ = MAN_PIC_0 + Scene::towards_ * MAN_PIC_COUNT + step_;
                        TextureManager::getInstance()->renderTexture("smap", man_pic_, p.x, p.y - h);
                    }
                }
                //�¼�
                auto event = record_->Event(i1, i2);
                if (event)
                {
                    num = record_->Event(i1, i2)->CurrentPic / 2;
                    //map[calBlockTurn(i1, i2, 2)] = s;
                    if (num > 0)
                    {
                        TextureManager::getInstance()->renderTexture("smap", num, p.x, p.y - record_->EventHeight(i1, i2) - h);
                    }
                }
                //װ��
                num = record_->Decoration(i1, i2) / 2;
                if (num > 0)
                {
                    TextureManager::getInstance()->renderTexture("smap", num, p.x, p.y - h);
                }
            }
            //k++;
        }
    }
}

void SubMap::dealEvent(BP_Event& e)
{
    //���¹��¼�ʹ��
    current_submap_record_ = record_;
    //current_submap_id_ = record_->ID;
    //current_item_id_ = -1;
    event_x_ = man_x_, event_y_ = man_y_;

    int x = man_x_, y = man_y_;
    //drawCount++;
    if (e.type == BP_MOUSEBUTTONUP)
    {
        getMousePosition(e.button.x, e.button.y);
        stopFindWay();
        if (canWalk(mouse_x_, mouse_y_) && !isOutScreen(mouse_x_, mouse_y_))
        {
            FindWay(view_x_, view_y_, mouse_x_, mouse_y_);
        }
    }
    if (!way_que_.empty())
    {
        PointEx newMyPoint = way_que_.back();
        x = newMyPoint.x;
        y = newMyPoint.y;
        isExit(x, y);
        Towards myTowards = (Towards)(newMyPoint.towards);
        //log("myTowards=%d", myTowards);
        tryWalk(x, y, myTowards);
        way_que_.pop_back();
        //log("not empty2 %d,%d", wayQue.top()->x, wayQue.top()->y);
    }
    if (e.type == BP_KEYDOWN)
    {
        //�ⲿ������̫�࣬������
        switch (e.key.keysym.sym)
        {
        case BPK_LEFT:
        {
            x--;
            if (isExit(x, y))
            {
                break;
            }
            tryWalk(x, y, LeftDown);
            stopFindWay();
            break;
        }
        case BPK_RIGHT:
        {
            x++;
            if (isExit(x, y))
            {
                break;
            }
            tryWalk(x, y, RightUp);
            stopFindWay();
            break;
        }
        case BPK_UP:
        {
            y--;
            if (isExit(x, y))
            {
                break;
            }
            tryWalk(x, y, LeftUp);
            stopFindWay();
            break;
        }
        case BPK_DOWN:
        {
            y++;
            if (isExit(x, y))
            {
                break;
            }
            tryWalk(x, y, RightDown);
            stopFindWay();
            break;
        }
        case BPK_ESCAPE:
        {
            stopFindWay();
            break;
        }
        case BPK_RETURN:
        case BPK_SPACE:
        {
            /* stopFindWay();
             ReSetEventPosition(x, y);
             if (current_submap_->Building();
             Save::getInstance()->m_SceneMapData[scene_id_].Data[3][x][y] >= 0)
                 if (Save::getInstance()->m_SceneEventData[scene_id_].Data[Save::getInstance()->m_SceneMapData[scene_id_].Data[3][x][y]].Event1 >= 0)
                     EventManager::getInstance()->callEvent(Save::getInstance()->m_SceneEventData[scene_id_].Data[Save::getInstance()->m_SceneMapData[scene_id_].Data[3][x][y]].Event1);
            */
            break;
        }
        case SDLK_b:
        {
            auto s = new BattleMap();
            addOnRootTop(s);
            break;
        }
        default:
        {
        }
        }
    }
    if (e.type == BP_KEYUP)
    {
        if (e.key.keysym.sym == BPK_ESCAPE)
        {
            UI::getInstance()->run();
            clearEvent(e);
        }
        if (e.key.keysym.sym == BPK_RETURN || e.key.keysym.sym == BPK_SPACE)
        {
            if (checkEvent1(x, y, towards_))
            { clearEvent(e); }
        }
    }
}

void SubMap::backRun()
{
    for (int i = 0; i < MAX_SUBMAP_EVENT; i++)
    {
        auto e = record_->Event(i);
        //if (e->PicDelay > 0)
        {
            e->CurrentPic++;
            //e->CurrentPic += e->PicDelay;
        }
        if (e->CurrentPic > e->EndPic)
        {
            e->CurrentPic = e->BeginPic;
        }
    }
}

//������������
void SubMap::tryWalk(int x, int y, Towards t)
{
    if (canWalk(x, y))
    {
        setPosition(x, y);
    }
    if (Scene::towards_ != t)
    {
        Scene::towards_ = t;
        step_ = 0;
    }
    else
    {
        step_++;
    }
    step_ = step_ % MAN_PIC_COUNT;
}

//��һ���¼�������������
bool SubMap::checkEvent1(int x, int y, Towards t)
{
    getTowardsPosition(man_x_, man_y_, &x, &y);
    int event_index_submap = record_->EventIndex(x, y);
    if (event_index_submap >= 0)
    {
        Event::getInstance()->callEvent(record_->Event(x, y)->Event1);
        return true;
    }
    return false;
}

//�ڶ����¼�������Ʒ�����¼�
bool SubMap::checkEvent2(int x, int y, Towards t, Item* item)
{
    return false;
}

bool SubMap::checkEvent3(int x, int y)
{
    return false;
}

bool SubMap::canWalk(int x, int y)
{
    bool ret = true;
    if (isOutLine(x, y) || isBuilding(x, y) || isWater(x, y)
        || isCannotPassEvent(x, y) || isFall(x, y))
    {
        ret = false;
    }
    if (isCanPassEvent(x, y))
    {
        ret = true;
    }
    return ret;
}

bool SubMap::isBuilding(int x, int y)
{
    return record_->Building(x, y) > 0;
    //if (current_submap_->Building(x, y) >= -2 && current_submap_->Building(x, y) <= 0)
    //{
    //    return false;
    //}
    //else
    //{
    //    return true;
    //}
}

bool SubMap::isOutLine(int x, int y)
{
    return (x < 0 || x >= MAX_COORD || y < 0 || y >= MAX_COORD);
}

bool SubMap::isWater(int x, int y)
{
    int num = record_->Earth(x, y) / 2;
    if (num >= 179 && num <= 181
        || num == 261 || num == 511
        || num >= 662 && num <= 665
        || num == 674)
    {
        return true;
    }
    return false;
}

bool SubMap::isCanPassEvent(int x, int y)
{
    auto e = record_->Event(x, y);
    if (e && !e->CannotWalk)
    {
        return true;
    }
    return false;
}

bool SubMap::isCannotPassEvent(int x, int y)
{
    auto e = record_->Event(x, y);
    if (e && e->CannotWalk)
    {
        return true;
    }
    return false;
}

//what is this?
bool SubMap::isFall(int x, int y)
{
    //if (abs(Save::getInstance()->m_SceneMapData[scene_id_].Data[4][x][y] -
    //Save::getInstance()->m_SceneMapData[scene_id_].Data[4][Cx][Cy] > 10))
    //{
    //    true;
    //}
    return false;
}

bool SubMap::isExit(int x, int y)
{
    if (record_->ExitX[0] == x && record_->ExitY[0] == y
        || record_->ExitX[1] == x && record_->ExitY[1] == y
        || record_->ExitX[2] == x && record_->ExitY[2] == y)
    {
        loop_ = false;
        Save::getInstance()->InSubmap = 1;
        return true;
    }
    return false;
}

bool SubMap::isOutScreen(int x, int y)
{
    return (abs(view_x_ - x) >= 2 * view_width_region_ || abs(view_y_ - y) >= view_sum_region_);
}

void SubMap::getMousePosition(int _x, int _y)
{
    //int x = _x;
    //int y = _y;
    ////int yp = 0;
    //int yp = -(Save::getInstance()->m_SceneMapData[scene_id_].Data[4][x][y]);
    //Msx = (-(x - Center_X) / singleMapScene_X + (y + yp - Center_Y) / singleMapScene_Y) / 2 + Cx;
    //Msy = ((y + yp - Center_Y) / singleMapScene_Y + (x - Center_X) / singleMapScene_X) / 2 + Cy;
}


