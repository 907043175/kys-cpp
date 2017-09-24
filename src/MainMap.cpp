#include "MainMap.h"
#include <iomanip>
#include <fstream>
#include <istream>
#include <ostream>
#include "File.h"
#include "TextureManager.h"
#include "SubMap.h"

MainMap::MapArray MainMap::Earth, MainMap::Surface, MainMap::Building, MainMap::BuildX, MainMap::BuildY, MainMap::Entrance;

void MainMap::divide2(MapArray& ma)
{
    for (int i = 0; i < maxX; i++)
    {
        for (int j = 0; j < maxY; j++)
        {
            ma[i][j] /= 2;
        }
    }
}

bool MainMap::_readed = false;

MainMap::MainMap()
{
    full_window_ = 1;
    //_Mx = &Save::getInstance()->m_BasicData[0].m_sMx;
    //_My = &Save::getInstance()->m_BasicData[0].m_sMy;
}

MainMap::~MainMap()
{
    for (int i = 0; i < 100; i++)
    { delete cloudVector[i]; }
}

void MainMap::draw()
{
    int k = 0;
    auto t0 = Engine::getInstance()->getTicks();
    struct DrawInfo { int i; Point p; };
    std::map<int, DrawInfo> map;
    //TextureManager::getInstance()->renderTexture("mmap", 0, 0, 0);
    for (int sum = -sumregion; sum <= sumregion + 15; sum++)
    {
        for (int i = -widthregion; i <= widthregion; i++)
        {
            int i1 = Mx + i + (sum / 2);
            int i2 = My - i + (sum - sum / 2);
            auto p = getPositionOnScreen(i1, i2, Mx, My);
            //auto p = getMapPoint(i1, i2, *_Mx, *_My);
            if (i1 >= 0 && i1 <= MaxMainMapCoord && i2 >= 0 && i2 <= MaxMainMapCoord)
            {
                //����3�㣬���棬���棬���������ǰ����ڽ�����
                if (Earth[i1][i2] > 0)
                { TextureManager::getInstance()->renderTexture("mmap", Earth[i1][i2], p.x, p.y); }
                if (Surface[i1][i2] > 0)
                { TextureManager::getInstance()->renderTexture("mmap", Surface[i1][i2], p.x, p.y); }
                if (Building[i1][i2] > 0)
                {
                    auto t = Building[i1][i2];
                    //����ͼƬ�Ŀ�ȼ���ͼ���е�, Ϊ�������С��, ʵ�����е������2��
                    //��Ҫ����������y����
                    //ֱ������z��
                    auto tex = TextureManager::getInstance()->loadTexture("mmap", t);
                    auto w = tex->w;
                    auto h = tex->h;
                    auto dy = tex->dy;
                    int c = ((i1 + i2) - (w + 35) / 36 - (dy - h + 1) / 9) * 1024 + i1;
                    map[2 * c + 1] = { t, p };
                }
                if (i1 == Mx && i2 == My)
                {
                    manPicture = offset_manPic + Scene::towards * num_manPic + step;
                    if (restTime >= begin_restTime)
                    { manPicture = offset_restPic + Scene::towards * num_restPic + (restTime - begin_restTime) / each_pictrueTime % num_restPic; }
                    int c = 1024 * (i1 + i2) + i1;
                    map[2 * c] = { manPicture, p };
                }
            }
            k++;
        }
    }
    for (auto i = map.begin(); i != map.end(); i++)
    { TextureManager::getInstance()->renderTexture("mmap", i->second.i, i->second.p.x, i->second.p.y); }
    auto t1 = Engine::getInstance()->getTicks();
    //�Ƶ���ͼ
    //for (auto& c : cloudVector)
    //{ Texture::getInstance()->renderTexture("cloud", c->num, c->m_nx, c->m_ny); }
    //log("%d\n", t1 - t0);
}

void MainMap::init()
{
    srand(int(time(nullptr)));

    if (!_readed)
    {
        //log("Reading main map.",0);
        int length = sizeof(MapArray);
        File::readFile("../game/resource/earth.002", &Earth, length);
        File::readFile("../game/resource/surface.002", &Surface, length);
        File::readFile("../game/resource/building.002", &Building, length);
        File::readFile("../game/resource/buildx.002", &BuildX, length);
        File::readFile("../game/resource/buildy.002", &BuildY, length);
        divide2(Earth);
        divide2(Surface);
        divide2(Building);
    }
    _readed = true;

    //�ʼ������.
    //*_Mx = m_BasicData[0].*_Mx;
    //*_My = m_BasicData[0].*_My;
    //CommonScene::towards = (Towards)m_BasicData[0].MFace;
    LOG("toward=%d\n", towards);
    //log("Mface=%d\n", SaveGame::getInstance()->RBasic_Data.Mface);

    //�������Ʋ�
//  auto mainLayer = Node::create();
//  auto cloudLayer = Node::create();
//  this->addChild(mainLayer, 1);
//  this->addChild(cloudLayer, 2);
//  auto scene = HelloWorld::createScene();
//  Director::getInstance()->replaceScene(scene);
    //���㹲����ٸ�
//  for (int i = 0; i < calNumberOfSprites(); i++)
//  {
//      addNewSpriteIntoVector(EarthS);
//      addNewSpriteIntoVector(SurfaceS);
//      addNewSpriteIntoVector(BuildingS);
//  }
    //100����
    for (int i = 0; i < 100; i++)
    {
        auto c = new Cloud();
        cloudVector.push_back(c);
        c->initRand();
    }

    getEntrance();

    //auto s = new SubScene(35);//��ʱ��ʼ���뿪��

}


//��ʱ��������ͼ�Լ�һЩ��������
void MainMap::dealEvent(BP_Event& e)
{
    int x = Mx, y = My;
    //drawCount++;
    if (e.type == BP_MOUSEBUTTONDOWN)
    {
        getMousePosition(e.button.x, e.button.y);
        stopFindWay();
        if (canWalk(Msx, Msy) && !checkIsOutScreen(Msx, Msy))
        {
            FindWay(Mx, My, Msx, Msy);
        }
    }
    if (!wayQue.empty())
    {
        Point newMyPoint = wayQue.top();
        x = newMyPoint.x;
        y = newMyPoint.y;
        checkIsEntrance(x, y);
        Towards myTowards = (Towards)(newMyPoint.towards);
        //log("myTowards=%d", myTowards);
        walk(x, y, myTowards);
        wayQue.pop();
        //log("not empty2 %d,%d", wayQue.top()->x, wayQue.top()->y);
    }
    if (e.type == BP_KEYDOWN)
        switch (e.key.keysym.sym)
        {
        case BPK_LEFT:
        {
            y--;
            checkIsEntrance(x, y);
            walk(x, y, LeftDown);
            stopFindWay();
            break;
        }
        case BPK_RIGHT:
        {
            y++;
            checkIsEntrance(x, y);
            walk(x, y, RightUp);
            stopFindWay();
            break;
        }
        case BPK_UP:
        {
            x--;
            checkIsEntrance(x, y);
            walk(x, y, LeftUp);
            stopFindWay();
            break;
        }
        case BPK_DOWN:
        {
            x++;
            checkIsEntrance(x, y);
            walk(x, y, RightDown);
            stopFindWay();
            break;
        }
        case BPK_ESCAPE:
        {
            stopFindWay();
            break;
        }
        case BPK_SPACE:
        {
            stopFindWay();
            //                Save::getInstance()->m_BasicData[0].*_Mx = *_Mx;
            //                Save::getInstance()->m_BasicData[0].*_My = *_My;
            //                Save::getInstance()->m_BasicData[0].MFace = towards;
            //                auto s = new BattleScene(Entrance[x][y]);
            //                push(s);
        }
        default:
        {
            restTime++;
        }
        }
    cloudMove();
}



void MainMap::walk(int x, int y, Towards t)
{
    if (canWalk(x, y))
    {
        Mx = x;
        My = y;
    }
    if (towards != t)
    {
        towards = t;
        //step = 0;
    }
    else
    { step++; }
    step = step % num_manPic;
    restTime = 0;
}

bool MainMap::checkIsBuilding(int x, int y)
{

    if (Building[BuildY[x][y]][BuildX[x][y]] > 0)
    { return  true; }
    else
    { return false; }
    /*    if (BuildX[x][y] == 0)
        { return false; }
        else
        { return true; }*/
}

bool MainMap::checkIsWater(int x, int y)
{
    if (Earth[x][y] == 838 || Earth[x][y] >= 612 && Earth[x][y] <= 670)
    { return true; }
    else if (Earth[x][y] >= 358 && Earth[x][y] <= 362
        || Earth[x][y] >= 506 && Earth[x][y] <= 670
        || Earth[x][y] >= 1016 && Earth[x][y] <= 1022)
    {
        return true;
    }
    else
    { return false; }
}


bool MainMap::checkIsOutLine(int x, int y)
{
    if (x < 0 || x > maxX || y < 0 || y > maxY)
    { return true; }
    else
    { return false; }
}

bool MainMap::canWalk(int x, int y)
{
    if (checkIsBuilding(x, y) || checkIsOutLine(x, y) || checkIsWater(x, y))
    { return false; }
    else
    { return true; }
}

void MainMap::cloudMove()
{
    for (auto& c : cloudVector)
    {
        c->changePosition();
        c->setPositionOnScreen(Mx, My, Center_X, Center_Y);
    }
}

bool MainMap::checkIsEntrance(int x, int y)
{
    //if (Entrance[x][y] > 0 && Entrance[x][y] <= config::MAXScene)
    //{
    //    Save::getInstance()->m_BasicData[0].m_sMx = Mx;
    //    Save::getInstance()->m_BasicData[0].m_sMx = My;
    //    Save::getInstance()->m_BasicData[0].m_sMFace = towards;
    //    Save::getInstance()->m_BasicData[0].m_sWhere = 1;
    //    auto s = new SubScene(Entrance[x][y]);
    //    push(s);
    //    return true;
    //}
    return false;
}

void MainMap::getEntrance()
{
    //for (int x = 0; x < maxX; x++)
    //    for (int y = 0; y < maxY; y++)
    //    { Entrance[x][y] = -1; }
    //for (int i = 0; i < Save::getInstance()->m_SceneData.size(); i++)
    //{

    //    int x = Save::getInstance()->m_SceneData[i].MainEntranceX1;
    //    int y = Save::getInstance()->m_SceneData[i].MainEntranceY1;
    //    if (x > 0 && y > 0 && x < maxX && y < maxY)
    //    {
    //        Entrance[x][y] = i;
    //    }
    //    x = Save::getInstance()->m_SceneData[i].MainEntranceX2;
    //    y = Save::getInstance()->m_SceneData[i].MainEntranceY2;
    //    if (x > 0 && y > 0 && x < maxX && y < maxY)
    //    {
    //        Entrance[x][y] = i;
    //    }
    //}
}

//A*Ѱ·
void MainMap::FindWay(int Mx, int My, int Fx, int Fy)
{
    bool visited[479][479] = { false };                                 //�ѷ��ʱ��(�ر��б�)
    int dirs[4][2] = { { -1, 0 }, { 0, 1 }, { 0, -1 }, { 1, 0 } };      //�ĸ�����
    Point* myPoint = new Point;
    myPoint->x = Mx;
    myPoint->y = My;
    myPoint->towards = (Point::Towards)CallFace(Mx, My, Fx, Fy);
    myPoint->parent = myPoint;
    myPoint->Heuristic(Fx, Fy);
    //log("Fx=%d,Fy=%d", Fx, Fy);
    //log("Mx=%d,My=%d", Mx, My);
    while (!wayQue.empty())
    {
        wayQue.pop();
    }
    std::priority_queue<Point*, std::vector<Point*>, Compare> que;            //��С���ȼ�����(�����б�)
    que.push(myPoint);
    int sNum = 0;
    while (!que.empty() && sNum <= 300)
    {
        Point* t = new Point();
        t = que.top();
        que.pop();
        visited[t->x][t->y] = true;
        sNum++;
        //log("t.x=%d,t.y=%d",t->x,t->y);
        if (t->x == Fx && t->y == Fy)
        {
            minStep = t->step;
            wayQue.push(*t);
            int k = 0;
            while (t != myPoint && k <= minStep)
            {
                //log("t.x=%d,t.y=%d,s.x=%d,s.y=%d,t.f=%d", t->x, t->y, t->parent->x, t->parent->y,t->f);

                t->towards = t->parent->towards;
                wayQue.push(*t);
                t = t->parent;
                k++;
                //log("go in!");
            }
            //log("minStep=%d", minStep);
            //log("wayQue=%d", wayQue.size());
            break;
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                Point* s = new Point();
                s->x = t->x + dirs[i][0];
                s->y = t->y + dirs[i][1];
                if (canWalk(s->x, s->y) && !checkIsOutScreen(s->x, s->y) && !visited[s->x][s->y])
                {
                    s->g = t->g + 10;
                    s->towards = (Point::Towards)i;
                    if (s->towards == t->towards)
                    {
                        s->Heuristic(Fx, Fy);
                    }
                    else
                    {
                        s->h = s->Heuristic(Fx, Fy) + 1;
                    }
                    s->step = t->step + 1;
                    s->f = s->g + s->h;
                    //t->towards = (MyPoint::Towards)i;
                    //s->Gx = dirs[i][0];
                    //s->Gy = dirs[i][1];
                    //t->child[i] = s;
                    //if (s->parent)
                    s->parent = t;
                    //log("s.x=%d,s.y=%d,t.x=%d,t.y=%d", s->x, s->y, t->x, t->y);
                    //log("s.g=%d,s.h=%d,s.f=%d", s.g, s.h, s.f);
                    que.push(s);
                }
            }
        }
    }
    myPoint->delTree(myPoint);
}


bool MainMap::checkIsOutScreen(int x, int y)
{
    if (abs(Mx - x) >= 2 * widthregion || abs(My - y) >= sumregion)
    { return true; }
    else
    { return false; }
}


void MainMap::stopFindWay()
{
    while (!wayQue.empty())
    { wayQue.pop(); }
}

void MainMap::getMousePosition(int _x, int _y)
{
    int x = _x;
    int y = _y;
    int yp = 0;
    Msx = (-(x - Center_X) / singleMapScene_X + (y + yp - Center_Y) / singleMapScene_Y) / 2 + Mx;
    Msy = ((y + yp - Center_Y) / singleMapScene_Y + (x - Center_X) / singleMapScene_X) / 2 + My;
}

void Cloud::initRand()
{
    position.x = rand() % maxX;
    position.y = rand() % maxY;
    speed = 1 + rand() % 3;
    num = rand() % numTexture;
    //this->setOpacity(128 + rand() % 128);
    //this->setColor(Color3B(rand() % 256, rand() % 256, rand() % 256));
}

void Cloud::setPositionOnScreen(int x, int y, int Center_X, int Center_Y)
{
    //this->m_nx = position.x - (-x * 18 + y * 18 + maxX / 2 - Center_X);
    //this->m_ny =position.y - (x * 9 + y * 9 + 9 - Center_Y);
}

void Cloud::changePosition()
{
    position.x += speed;
    if (position.x > maxX)
    {
        position.x = 0;
    }
}
