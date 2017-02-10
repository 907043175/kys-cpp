#include "BattleScene.h"
#include "MainMap.h"
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include "config.h"
#include "Save.h"

BattleScene::BattleScene()
{
    full = 1;
}


BattleScene::~BattleScene()
{
}

void BattleScene::draw()
{
    int k = 0;
    struct DrawInfo { int i; Point p; };
    std::map<int, DrawInfo> map;
    for (int sum = -sumregion; sum <= sumregion + 15; sum++)
    {
        for (int i = -widthregion; i <= widthregion; i++)
        {
            int i1 = Bx + i + (sum / 2);
            int i2 = By - i + (sum - sum / 2);
            auto p = getPositionOnScreen(i1, i2, Bx, By);
            if (i1 >= 0 && i1 <= MaxSceneCoord && i2 >= 0 && i2 <= MaxSceneCoord)
            {
                //EarthS[k]->setVisible(false);
                //BuildS[k]->setVisible(false);
                //����ע��״��
                Point p1 = Point(0, -battleSceneData[battleSceneNum].Data[4][i1][i2]);
                Point p2 = Point(0, -battleSceneData[battleSceneNum].Data[5][i1][i2]);
                int num = battleSceneData[battleSceneNum].Data[0][i1][i2] / 2;
                if (num >= 0)
                {
                    Texture::getInstance()->copyTexture("smap", num, p.x, p.y);
                    /*if (p1.y < -0.1)
                    {
                    map[calBlockTurn(i1, i2, 0)] = s;
                    }
                    else
                    {
                    s->visit();
                    }*/
                }
                //����������ͬһ��
                num = battleSceneData[battleSceneNum].Data[1][i1][i2] / 2;
                if (num > 0)
                {
                    Texture::getInstance()->copyTexture("smap", num, p.x, p.y);
                    map[calBlockTurn(i1, i2, 1)] = { num, p };
                }
                else if (i1 == Bx && i2 == By)
                {
                    manPicture = 0 + Scene::towards * 4;
                    map[calBlockTurn(i1, i2, 1)] = { manPicture, p };
                    //s->visit();
                }
            }
            k++;
        }
    }
    for (auto i = map.begin(); i != map.end(); i++)
    {
        Texture::getInstance()->copyTexture("smap", i->second.i, i->second.p.x, i->second.p.y);
    }
}

void BattleScene::dealEvent(BP_Event& e)
{

}

void BattleScene::checkTimer2()
{
    if (!isMenuOn)
    {
        moveRole(curRoleNum);
    }
    //Draw();
}

void BattleScene::walk(int x, int y, Towards t)
{
    if (canWalk(x, y))
    {
        Bx = x;
        By = y;
    }
    if (Scene::towards != t)
    {
        Scene::towards = t;
        step = 0;
    }
    else
    {
        step++;
    }
    step = step % offset_BRolePic;
}

bool BattleScene::canWalk(int x, int y)
{
    if (checkIsOutLine(x, y) || checkIsBuilding(x, y) || checkIsHinder(x, y)
        || checkIsEvent(x, y) || checkIsFall(x, y))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool BattleScene::checkIsBuilding(int x, int y)
{
    if (battleSceneData[battleSceneNum].Data[1][x][y] >= -2
        && battleSceneData[battleSceneNum].Data[1][x][y] <= 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool BattleScene::checkIsOutLine(int x, int y)
{
    if (x < 0 || x > MaxSceneCoord || y < 0 || y > MaxSceneCoord)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool BattleScene::checkIsHinder(int x, int y)
{
    return false;
}

bool BattleScene::checkIsEvent(int x, int y)
{
    return false;
}

bool BattleScene::checkIsFall(int x, int y)
{
    return false;
}

bool BattleScene::checkIsExit(int x, int y)
{
    return false;
}

void BattleScene::callEvent(int x, int y)
{
}

bool BattleScene::checkIsOutScreen(int x, int y)
{
    if (abs(Bx - x) >= 16 || abs(By - y) >= 20)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//��������
void BattleScene::getMousePosition(Point* point)
{
    int x = point->x;
    int y = Center_Y * 2 - point->y;
    //int yp = 0;
    int yp = -(battleSceneData[battleSceneNum].Data[1][x][y]);
    Msx = (-x + Center_X + 2 * (y + yp) - 2 * Center_Y + 18) / 36 + Bx;
    Msy = (x - Center_X + 2 * (y + yp) - 2 * Center_Y + 18) / 36 + By;
}

void BattleScene::FindWay(int Mx, int My, int Fx, int Fy)
{
}

int BattleScene::CallFace(int x1, int y1, int x2, int y2)
{
    int d1, d2, dm;
    d1 = x2 - x1;
    d2 = y2 - y1;
    dm = abs(d1) - abs(d2);
    if ((d1 != 0) || (d2 != 0))
    {
        if (dm >= 0)
        {
            if (d1 < 0)
            {
                return 0;
            }
            else
            {
                return 3;
            }
        }
        else
        {
            if (d2 < 0)
            {
                return 2;
            }
            else
            {
                return 1;
            }
        }
    }
}

void BattleScene::initData(int scenenum)
{
    //  for (int i = 0; i < maxBRoleSelect; i++)
    //  {
    //      int numBRole = ResultofBattle[i];
    //      char *fightPath = new char[30];
    //      sprintf(fightPath, "fight/fight%03d", numBRole);
    //      char *fightPathIn = new char[30];
    //      sprintf(fightPathIn, "fight/fight%03d/index.ka", numBRole);
    //      auto file = FileUtils::getInstance();
    //      //std::fstream file;
    //      if (file->isFileExist(fightPathIn)){
    //          loadTexture(fightPath, MyTexture2D::Battle, 250, numBRole);
    //      }
    //      //delete(fightPath);
    //      delete(fightPathIn);
    //  }
}



void BattleScene::autoSetMagic(int rnum)
{


}

bool BattleScene::autoInBattle()
{
    int x, y;
    int autoCount = 0;
    for (int i = 0; i < MaxBRoleNum; i++)
    {
        battleRole[i].Team = 1;
        battleRole[i].rnum = -1;
        //�ҷ��Զ���ս����
        if (mods >= -1)
        {
            for (int i = 0; i < sizeof(battleInfo[battleNum].mate) / sizeof(battleInfo[battleNum].mate[0]); i++)
            {
                x = battleInfo[battleNum].mate_x[i];
                y = battleInfo[battleNum].mate_y[i];
            }
            if (mods == -1)
            {
                battleRole[BRoleAmount].rnum = battleInfo[battleNum].autoMate[i];
            }
            else
            {
                battleRole[BRoleAmount].rnum = -1;
            }
            battleRole[BRoleAmount].Team = 0;
            battleRole[BRoleAmount].Y = y;
            battleRole[BRoleAmount].X = x;
            battleRole[BRoleAmount].Face = 2;
            if (battleRole[BRoleAmount].rnum == -1)
            {
                battleRole[BRoleAmount].Dead = 1;
                battleRole[BRoleAmount].Show = 1;
            }
            else
            {
                battleRole[BRoleAmount].Dead = 0;
                battleRole[BRoleAmount].Show = 0;
                //if (!((m_Character[battleRole[BRoleAmount].rnum].TeamState == 1)
                //    || (m_Character[battleRole[BRoleAmount].rnum].TeamState == 2))
                //    && !(m_Character[battleRole[BRoleAmount].rnum].Faction == m_Character[0].Faction))
                //{
                //    autoSetMagic(battleRole[BRoleAmount].rnum);
                //    autoCount++;
                //}
            }
            battleRole[BRoleAmount].Step = 0;
            battleRole[BRoleAmount].Acted = 0;
            battleRole[BRoleAmount].ExpGot = 0;
            if (battleRole[BRoleAmount].rnum == 0)
            {
                battleRole[BRoleAmount].Auto = -1;
            }
            else
            {
                battleRole[BRoleAmount].Auto = 3;
            }
            battleRole[BRoleAmount].Progress = 0;
            battleRole[BRoleAmount].round = 0;
            battleRole[BRoleAmount].Wait = 0;
            battleRole[BRoleAmount].frozen = 0;
            battleRole[BRoleAmount].killed = 0;
            battleRole[BRoleAmount].Knowledge = 0;
            battleRole[BRoleAmount].Zhuanzhu = 0;
            battleRole[BRoleAmount].szhaoshi = 0;
            battleRole[BRoleAmount].pozhao = 0;
            battleRole[BRoleAmount].wanfang = 0;

        }
        //�Զ���ս����
    }
    return true;
}

int BattleScene::selectTeamMembers()
{
    //menuOn();
    //int i, i2;
    //max0 = 1;
    //menuString[0] = "ȫ�T����";
    //for (i = 0; i < config::MaxTeamMember; i++)
    //{
    //    if (m_BasicData[0].TeamList[i] >= 0)
    //    {
    //        menuString[i + 1] = m_Character[m_BasicData[0].TeamList[i]].Name;
    //        max0++;
    //    }
    //}
    //menuString[max0] = "�_ʼ���Y";
    //ShowMultiMenu(max0, 0);
    //Draw();
    return 1;
}

void BattleScene::ShowMultiMenu(int max0, int menuNum)
{
    ////unschedule(schedule_selector(CommonScene::checkTimer));
    //string str;
    //for (int k = 0; k < 8; k++)
    //{
    //    SlectOfresult[k] = false;
    //    item[k] = nullptr;
    //}

    //for (int i = 0; i < 6; i++)
    //{
    //    ResultofBattle[i] = -1;
    //    BattleList[i] = -1;//  ��ս��Ա�б��ʼ�� ����սΪ-1
    //}
    //for (int i = 0; i <= max0; i++)
    //{
    //    MenuItemFont::setFontName("fonts/chinese.ttf");
    //    MenuItemFont::setFontSize(24);
    //    str = CommonScene::a2u(menuString[i].c_str());
    //    item[i] = MenuItemFont::create(str, CC_CALLBACK_1(BattleScene::menuCloseCallback, this));
    //    if (menuString[i] == "�_ʼ���Y")
    //    {
    //        item[i]->setTag(8);
    //    }
    //    else
    //    {
    //        item[i]->setTag(i + 1);
    //    }


    //}

    //item[max0]->setEnabled(false);
    //CommonScene::cleanAllWords();
    //initMultiMenu();
    //showSlectMenu(s_list, 0);
    //Vec2 vec[7];
    //for (int i = 0; i < 7; i++)
    //{
    //    vec[i].x = xx;
    //    vec[i].y = yy - 170 - i * 20;
    //}
    //CommonScene::drawWords(s_list, 20, BattleScene::kindOfRole, vec);
}

/*
void BattleScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
    return;
#endif
    auto p = dynamic_cast<MenuItemFont*> (pSender);
    if (p == nullptr)
        return;
    switch (p->getTag())
    {
    case 1:
    {
        SlectOfresult[0] = !SlectOfresult[0];
        if (SlectOfresult[0] == true)
        {
            counter = max0 - 1;
            for (int i = 1; i < 7; i++)
            {
                if (m_BasicData[0].TeamList[i - 1] >= 0)
                {
                    item[i]->setColor(Color3B::RED);
                }
            }
            for (int i = 0; i < 6; i++)
            {
                if (m_BasicData[0].TeamList[i] >= 0)
                {
                    SlectOfresult[i + 1] = true;
                    ResultofBattle[i] = 1;
                }
            }
        }
        else if (SlectOfresult[0] == false)
        {
            counter = 0;
            for (int i = 1; i < 7; i++)
            {
                item[i]->setColor(Color3B::WHITE);
            }
        }
        if (counter > 0)
        {
            item[max0]->setEnabled(true);
        }
        else
        {
            item[max0]->setEnabled(false);
        }
        break;
    }
    case 2:
    {

        SlectOfresult[1] = !SlectOfresult[1];
        if (SlectOfresult[1] == true)
        {
            item[1]->setColor(Color3B::RED);
            ResultofBattle[0] = 1;
            counter++;
        }
        else if (SlectOfresult[1] == false)
        {
            item[1]->setColor(Color3B::WHITE);
            ResultofBattle[0] = 0;
            counter--;
        }
        if (counter > 0)
        {
            item[max0]->setEnabled(true);
        }
        else
        {
            item[max0]->setEnabled(false);
        }




        break;
    }
    case 3:
    {
        SlectOfresult[2] = !SlectOfresult[2];
        if (SlectOfresult[2] == true)
        {
            item[2]->setColor(Color3B::RED);
            ResultofBattle[1] = 1;
            counter++;
        }
        else if (SlectOfresult[2] == false)
        {
            item[2]->setColor(Color3B::WHITE);
            ResultofBattle[1] = 0;
            counter--;
        }
        if (counter > 0)
        {
            item[max0]->setEnabled(true);
        }
        else
        {
            item[max0]->setEnabled(false);
        }
        break;
    }

    case 4:
    {
        SlectOfresult[3] = !SlectOfresult[3];
        if (SlectOfresult[3] == true)
        {

            item[3]->setColor(Color3B::RED);
            ResultofBattle[2] = 1;
            counter++;
        }
        else if (SlectOfresult[3] == false)
        {
            item[3]->setColor(Color3B::WHITE);
            ResultofBattle[2] = 0;
            counter--;
        }
        if (counter > 0)
        {
            item[max0]->setEnabled(true);
        }
        else
        {
            item[max0]->setEnabled(false);
        }
        break;
    }
    case 5:
    {
        SlectOfresult[4] = !SlectOfresult[4];
        if (SlectOfresult[4] == true)
        {

            item[4]->setColor(Color3B::RED);
            ResultofBattle[3] = 1;
            counter++;
        }
        else if (SlectOfresult[4] == false)
        {
            item[4]->setColor(Color3B::WHITE);
            ResultofBattle[3] = 0;
            counter--;
        }
        if (counter > 0)
        {
            item[max0]->setEnabled(true);
        }
        else
        {
            item[max0]->setEnabled(false);
        }
        break;
    }
    case 6:
    {

        SlectOfresult[5] = !SlectOfresult[5];
        if (SlectOfresult[5] == true)
        {
            item[5]->setColor(Color3B::RED);
            ResultofBattle[4] = 1;
            counter++;
        }
        else if (SlectOfresult[5] == false)
        {
            item[5]->setColor(Color3B::WHITE);
            ResultofBattle[4] = 0;
            counter--;
        }
        if (counter > 0)
        {
            item[max0]->setEnabled(true);
        }
        else
        {
            item[max0]->setEnabled(false);
        }
        break;
    }
    case 7:
    {
        SlectOfresult[6] = !SlectOfresult[6];
        if (SlectOfresult[6] == true)
        {
            item[6]->setColor(Color3B::RED);
            ResultofBattle[5] = 1;
            counter++;
        }
        else if (SlectOfresult[1] == false)
        {
            item[6]->setColor(Color3B::WHITE);
            ResultofBattle[5] = 0;
            counter--;
        }
        if (counter > 0)
        {
            item[max0]->setEnabled(true);
        }
        else
        {
            item[max0]->setEnabled(false);
        }
        break;
    }
    case 8:
    {
        //  ��ʼս�����
        for (int i = 0; i < config::MaxTeamMember; i++)
        {
            if (ResultofBattle[i])
            {
                BattleList[i] = m_BasicData[0].TeamList[i];
            }

        }
        initBattleRoleState();
        battleMainControl();
        CommonScene::cleanAllWords();
        CommonScene::cleanRoleVerticaldRawing();
        CommonScene::cleanFiveDimensional();
        SpriteLayer->removeAllChildren();
        Draw();
        menuClose();
        showBattleMenu(50, 500);
        //schedule(schedule_selector(CommonScene::checkTimer), 0.025, kRepeatForever, 0.025);

        break;
    }
    }
}

void BattleScene::menuCloseCallback1(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
    return;
#endif
    auto p = dynamic_cast<MenuItemImage*> (pSender);
    Vec2 vec[7];
    for (int i = 0; i < 7; i++)
    {
        vec[i].x = xx;
        vec[i].y = yy - 170 - i * 20;
    }
    if (p == nullptr)
        return;
    switch (p->getTag())
    {
    case 9:
    {
        num_list--;
        if ((num_list >= 0) && (m_BasicData[0].TeamList[num_list] >= 0))
        {
            CommonScene::cleanRoleVerticaldRawing();
            CommonScene::cleanAllWords();
            showSlectMenu(s_list, num_list);
            CommonScene::drawWords(s_list, 20, BattleScene::kindOfRole, vec);

        }
        else
        {
            num_list = 0;
        }
        break;
    }
    case 10:
    {
        num_list++;
        if ((num_list <= 5) && (m_BasicData[0].TeamList[num_list] >= 0))
        {
            CommonScene::cleanRoleVerticaldRawing();
            CommonScene::cleanAllWords();
            showSlectMenu(s_list, num_list);
            CommonScene::drawWords(s_list, 20, BattleScene::kindOfRole, vec);

        }
        else
        {
            num_list = 5;
        }
        break;
    }
    case 11:
    {
        //  �ƶ�;
        if (battleRole[curRoleNum].Step > 0) {
            SpriteLayer->removeAllChildren();
            menuClose();
            Msx = Bx;
            Msy = By;
            Ax = Bx;
            Ay = By;
            moveRole(curRoleNum);

        }
        break;
    }

    case 12:
    {
        //  ��ѧ;
        break;
    }
    case 13:
    {
        //  �ö�;
        break;
    }
    case 14:
    {
        //  �ⶾ;
        break;
    }
    case 15:
    {
        //  ҽ��;
        break;
    }
    case 16:
    {
        //  ��Ѩ;
        break;
    }
    case 17:
    {
        //  רע;
        break;
    }
    case 18:
    {
        //  ��Ʒ;
        break;
    }
    case 19:
    {
        //  �ȴ�;
        break;
    }
    case 20:
    {
        //  ״̬;
        break;
    }
    case 21:
    {
        //  ��Ϣ;
        break;
    }
    case 22:
    {
        //  �Զ�;
        break;
    }
    }

}
*/
void BattleScene::showBattleMenu(int x, int y)
{
    //menuOn();
    //MenuItemImage* item1[12];
    //for (int i = 0; i < 12; i++)
    //{
    //    string str, str1;
    //    str = "menu/" + to_string(21 + i) + ".png";
    //    str1 = "menu/" + to_string(33 + i) + ".png";
    //    item1[i] = MenuItemImage::create(str, str1, CC_CALLBACK_1(BattleScene::menuCloseCallback1, this));
    //    item1[i]->setTag(11 + i);
    //    item1[i]->setPositionY(-30 * i);
    //}
    //auto menu = Menu::create(item1[0], item1[1], item1[2], item1[3], item1[4], item1[5], item1[6], item1[7], item1[8], item1[9], item1[10], item1[11], NULL);
    //menu->setPosition(Vec2(x, y));
    //SpriteLayer->addChild(menu);
}


void BattleScene::showSlectMenu(string* str, int x)
{
    //string name = "��ս����������";
    //string attack = "��������";
    //string defense = "��������";
    //string dodge = "�Ṧ    ��";
    //string sword = "����    ��";
    //string quanfa = "ȭ��    ��";
    //string daofa = "����    ��";
    //int num = m_BasicData[0].TeamList[x];
    //name += m_Character[num].Name;
    //attack += to_string(m_Character[num].Attack);
    //defense += to_string(m_Character[num].Defence);
    //dodge += to_string(m_Character[num].Speed);
    //str[0] = name;
    //str[1] = attack;
    //str[2] = defense;
    //str[3] = dodge;
    //str[4] = sword;
    //int num1 = ((m_Character[num].Fencing) / 200.0) * 10;
    //CommonScene::showRoleAbility(xx + 90, yy - 170 - 4 * 20 + 10, num1);
    //str[5] = quanfa;
    //num1 = ((m_Character[num].Boxing) / 200.0) * 10;
    //CommonScene::showRoleAbility(xx + 90, yy - 170 - 5 * 20 + 10, num1);
    //str[6] = daofa;
    //num1 = ((m_Character[num].Knife) / 200.0) * 10;
    //CommonScene::showRoleAbility(xx + 90, yy - 170 - 6 * 20 + 10, num1);
    //CommonScene::showRoleVerticaldRawing(xx + 20, 63, num, 40, 0.8, 0.9);
    //string str1 = "ui/beizhan/Node.csb";
    //CommonScene::myRunAction(str1, 0, 25);
    //CommonScene::cleanFiveDimensional();
    //CommonScene::showFiveDimensional(xx + 80, yy, num);
}

void BattleScene::initMultiMenu()
{
    //auto s = Director::getInstance()->getWinSize();
    //auto menu = Menu::create(item[0], item[1], item[2], item[3], item[4], item[5], item[6], item[7], nullptr);
    //menu->alignItemsVertically();
    //menu->setPosition(Vec2(s.width / 2.0 + 150, s.height / 2.0 + 50));

    //auto m_backgrand = Sprite::create("ui/beizhan/1.png");
    //m_backgrand->setPosition(Vec2(s.width / 2.0, s.height / 2.0));

    //auto m_backgrand1 = Sprite::create("ui/beizhan/21.png");
    //m_backgrand1->setScaleX(0.4);
    //m_backgrand1->setScaleY(1.0);
    //m_backgrand1->setPosition(Vec2(s.width / 2.0 + 150, s.height / 2.0 + 50));

    //auto m_backgrand4 = Sprite::create("ui/beizhan/21.png");
    //m_backgrand4->setScaleX(1);
    //m_backgrand4->setScaleY(1.3);
    //m_backgrand4->setOpacity(50);
    //m_backgrand4->setPosition(Vec2(s.width / 2.0, s.height / 2.0));

    //auto m_backgrand2 = Sprite::create("ui/beizhan/4.png");
    //m_backgrand2->setPosition(Vec2(s.width / 2.0 - 170, s.height / 2.0));
    //m_backgrand2->setScale(1.3);
    //m_backgrand2->setOpacity(40);

    //auto m_backgrand3 = Sprite::create("ui/beizhan/5.png");
    //m_backgrand3->setPosition(Vec2(s.width / 2.0 + 50, s.height / 2.0));
    //m_backgrand3->setScale(1.3);
    //m_backgrand3->setOpacity(40);

    //auto item1 = MenuItemImage::create("ui/beizhan/1-1.png", "ui/beizhan/1-1.png", CC_CALLBACK_1(BattleScene::menuCloseCallback1, this));
    //item1->setTag(9);
    //auto item2 = MenuItemImage::create("ui/beizhan/1-2.png", "ui/beizhan/1-2.png", CC_CALLBACK_1(BattleScene::menuCloseCallback1, this));
    //item2->setTag(10);
    //item2->setPositionY(-75);
    //auto menu1 = Menu::create(item1, item2, NULL);
    //menu1->setPosition(Vec2(297, 392 - 170));

    //SpriteLayer->addChild(m_backgrand);
    //SpriteLayer->addChild(m_backgrand4);
    ////addChild(m_backgrand3);
    //SpriteLayer->addChild(menu1);
    //SpriteLayer->addChild(menu);

}


bool BattleScene::battle(int battlenum, int getexp, int mods, int id, int maternum, int enemyrnum)
{
    return true;
}

bool BattleScene::initBattleData()
{
    //battle::FactionBackup FBackup[10];
    //battle::FactionBackup FBackup2[10];
    //battle::FactionBackup TFBackup;

    //TFBackup.len = 0;
    //TFBackup.captain = -1;
    //for (int i = 0; i < 10; i++)
    //{
    //    FBackup[i].len = 0;
    //    FBackup[i].captain = -1;
    //    FBackup2[i].len = 0;
    //    FBackup2[i].captain = -1;
    //}

    for (int i1 = 0; i1 <= 63; i1++)
    {
        for (int i2 = 0; i2 <= 63; i2++)
        {
            battleSceneData[battleSceneNum].Data[2][i1][i2] = -1;
            battleSceneData[battleSceneNum].Data[4][i1][i2] = -1;
            battleSceneData[battleSceneNum].Data[5][i1][i2] = -1;
        }
    }
    BRoleAmount = 0;
    //initBattleRoleState();
    return true;
}

bool BattleScene::initBattleRoleState()
{
    BattleData::getInstance()->m_BattleRole.resize(MaxBRoleNum);
    for (int i = 0; i < MaxBRoleNum; i++)
    {
        battleRole[i].X = -1;
        battleRole[i].Y = -1;
        battleRole[i].Show = 1;
    }
    BStatus = 0;
    isBattle = true;
    if (mods == -1)
    {
        selectTeamMembers();
    }
    else
    {
    }
    BRoleAmount = 0;
    int n0 = 0;
    int teamNum = 0;
    if (battleInfo[battleNum].mate[0] == 0)
    {
        teamNum = 1;
    }
    for (int i = 0; teamNum < maxBRoleSelect && i < sizeof(battleInfo[battleNum].mate) / sizeof(battleInfo[battleNum].mate[0]); i++)
    {
        if (battleInfo[battleNum].mate[BRoleAmount] >= 0)
        {
            battleRole[BRoleAmount].Y = battleInfo[battleNum].mate_x[i];
            battleRole[BRoleAmount].X = battleInfo[battleNum].mate_y[i];
            battleRole[BRoleAmount].Team = 0;
            battleRole[BRoleAmount].Face = 2;
            battleRole[BRoleAmount].rnum = battleInfo[battleNum].mate[BRoleAmount];
            battleRole[BRoleAmount].Auto = -1;
            setInitState(n0);
        }
        else if (BattleList[teamNum] >= 0)
        {
            battleRole[BRoleAmount].Y = battleInfo[battleNum].mate_x[i];
            battleRole[BRoleAmount].X = battleInfo[battleNum].mate_y[i];
            battleRole[BRoleAmount].Team = 0;
            battleRole[BRoleAmount].Face = 2;
            battleRole[BRoleAmount].rnum = BattleList[teamNum];
            battleRole[BRoleAmount].Auto = -1;
            setInitState(n0);
            teamNum++;
        }
        BRoleAmount++;
    }
    calMoveAbility();
    return true;
}

void BattleScene::setInitState(int& n0)
{
    battleRole[BRoleAmount].Step = 0;
    battleRole[BRoleAmount].Acted = 0;
    battleRole[BRoleAmount].ExpGot = 0;
    battleRole[BRoleAmount].Show = 0;
    battleRole[BRoleAmount].Progress = 0;
    battleRole[BRoleAmount].round = 0;
    battleRole[BRoleAmount].Wait = 0;
    battleRole[BRoleAmount].frozen = 0;
    battleRole[BRoleAmount].killed = 0;
    battleRole[BRoleAmount].Knowledge = 0;
    battleRole[BRoleAmount].Zhuanzhu = 0;
    battleRole[BRoleAmount].szhaoshi = 0;
    battleRole[BRoleAmount].pozhao = 0;
    battleRole[BRoleAmount].wanfang = 0;
    for (int j = 0; j <= 4; j++)
    {
        n0 = 0;
        if (battleRole[BRoleAmount].rnum > -1)
        {
            for (int j1 = 0; j1 <= 9; j1++)
            {
                //if (m_Character[battleRole[BRoleAmount].rnum].GongTi >= 0)
                //{
                //    if ((m_Magic[m_Character[battleRole[BRoleAmount].rnum].LMagic[m_Character[battleRole[BRoleAmount].rnum].GongTi]].MoveDistance[j1] == 60 + j))
                //    {
                //        n0 = m_Magic[m_Character[battleRole[BRoleAmount].rnum].LMagic[m_Character[battleRole[BRoleAmount].rnum].GongTi]].AttDistance[j1];
                //    }
                //}
            }
        }
        battleRole[BRoleAmount].zhuangtai[j] = 100;
        battleRole[BRoleAmount].lzhuangtai[j] = n0;
    }
    for (int j = 5; j <= 9; j++)
    {
        n0 = 0;
        if (battleRole[BRoleAmount].rnum > -1)
        {
            for (int j1 = 0; j1 <= 9; j1++)
            {
                //if (m_Character[battleRole[BRoleAmount].rnum].GongTi >= 0)
                //{
                //    if ((m_Magic[m_Character[battleRole[BRoleAmount].rnum].LMagic[m_Character[battleRole[BRoleAmount].rnum].GongTi]].MoveDistance[j1] == 60 + j))
                //    {
                //        n0 = m_Magic[m_Character[battleRole[BRoleAmount].rnum].LMagic[m_Character[battleRole[BRoleAmount].rnum].GongTi]].AttDistance[j1];
                //    }
                //}
            }
        }
        battleRole[BRoleAmount].zhuangtai[j] = n0;
        battleRole[BRoleAmount].lzhuangtai[j] = n0;
    }
    for (int j = 10; j <= 13; j++)
    {
        battleRole[BRoleAmount].zhuangtai[j] = 0;
    }

}
//������ƶ�����(����װ��)

void BattleScene::calMoveAbility()
{
    //int i, rnum, addspeed;
    //maxspeed = 0;
    //for (int i = 0; i < BRole.size(); i++)
    //{
    //    rnum = battleRole[i].rnum;
    //    if (rnum > -1)
    //    {
    //        addspeed = 0;
    //        //          if (CheckEquipSet(RRole[rnum].Equip[0], RRole[rnum].Equip[1], RRole[rnum].Equip[2], RRole[rnum].Equip[3]) == 5){
    //        //              addspeed += 30;
    //        //          }
    //        battleRole[i].speed = (getRoleSpeed(battleRole[i].rnum, true) + addspeed);
    //        if (battleRole[i].Wait == 0)
    //        {
    //            battleRole[i].Step = round(power(battleRole[i].speed / 15, 0.8) * (100 + battleRole[i].zhuangtai[8]) / 100);
    //            if (maxspeed > battleRole[i].speed)
    //            {
    //                maxspeed = maxspeed;
    //            }
    //            else { maxspeed = battleRole[i].speed; }
    //        }
    //        if (m_Character[rnum].Moveable > 0)
    //        {
    //            battleRole[i].Step = 0;
    //        }
    //    }
    //}
}

//���Ṧ��������(δ����װ��)
void BattleScene::reArrangeBRole()
{
    //int i, n, n1, i1, i2, x, t, s1, s2;
    //battle::TBattleRole temp;
    //i1 = 0;
    //i2 = 1;
    //for (i1 = 0; i1 < BRole.size() - 1; i1++)
    //{
    //    for (i2 = i1 + 1; i2 < BRole.size(); i2++)
    //    {
    //        s1 = 0;
    //        s2 = 0;
    //        if ((battleRole[i1].rnum > -1) && (battleRole[i1].Dead == 0))
    //        {
    //            s1 = getRoleSpeed(battleRole[i1].rnum, true);
    //            //          if checkEquipSet(Rrole[battleRole[i1].rnum].Equip[0], Rrole[battleRole[i1].rnum].Equip[1],
    //            //              Rrole[battleRole[i1].rnum].Equip[2], Rrole[battleRole[i1].rnum].Equip[3]) = 5 then
    //            //          s1  = s1 + 30;
    //        }
    //        if ((battleRole[i2].rnum > -1) && (battleRole[i2].Dead == 0))
    //        {
    //            s2 = getRoleSpeed(battleRole[i2].rnum, true);
    //        }
    //        if ((battleRole[i1].rnum != 0) && (battleRole[i1].Team != 0) && (s1 < s2) && (battleRole[i2].rnum != 0) && (battleRole[i2].Team != 0))
    //        {
    //            temp = battleRole[i1];
    //            battleRole[i1] = battleRole[i2];
    //            battleRole[i2] = temp;
    //        }
    //    }
    //}

    //for (i1 = 0; i1 < 64; i1++)
    //{
    //    for (i2 = 0; i2 < 64; i2++)
    //    {
    //        battleSceneData[battleSceneNum].Data[2][i1][i2] = -1;
    //        battleSceneData[battleSceneNum].Data[5][i1][i2] = -1;
    //    }
    //}
    //n = 0;
    //for (i = 0; i < BRole.size(); i++)
    //{
    //    if ((battleRole[i].Dead == 0) && (battleRole[i].rnum >= 0))
    //    {
    //        n++;
    //    }
    //}
    //n1 = 0;
    //for (i = 0; i < BRole.size(); i++)
    //{
    //    if (battleRole[i].rnum >= 0)
    //    {
    //        if (battleRole[i].Dead == 0)
    //        {
    //            battleSceneData[battleSceneNum].Data[2][battleRole[i].X][battleRole[i].Y] = i;
    //            battleSceneData[battleSceneNum].Data[5][battleRole[i].X][battleRole[i].Y] = -1;
    //            //              if battlemode > 0 then
    //            //                  battleRole[i].Progress : = (n - n1) * 5;
    //            n1++;
    //        }
    //        else
    //        {
    //            battleSceneData[battleSceneNum].Data[2][battleRole[i].X][battleRole[i].Y] = -1;
    //            battleSceneData[battleSceneNum].Data[5][battleRole[i].X][battleRole[i].Y] = i;
    //        }
    //    }
    //}
    //i2 = 0;
    //if (battlemode > 0) then
    //    for i1 : = 0 to length(Brole) - 1 do
    //        if ((GetPetSkill(5, 1) and (battleRole[i1].rnum = 0)) or (GetPetSkill(5, 3) and (battleRole[i1].Team = 0))) then
    //            battleRole[i1].Progress : = 299 - i2 * 5;
    //i2 = i2 + 1;
}

//��ȡ�����ٶ�
int BattleScene::getRoleSpeed(int rnum, bool Equip)
{
    int l;
    //int bResult;
    //bResult = m_Character[rnum].Speed;
    //if (m_Character[rnum].GongTi > -1)
    //{
    //    l = getGongtiLevel(rnum);
    //    bResult = m_Magic[m_Character[rnum].LMagic[m_Character[rnum].GongTi]].AddSpd[l];
    //}
    //if (Equip)
    //{
    //    for (int l = 0; l < config::MaxEquipNum; l++)
    //    {
    //        if (m_Character[rnum].Equip[l] >= 0)
    //        {
    //            bResult += m_Item[m_Character[rnum].Equip[l]].AddSpeed;
    //        }
    //        bResult = bResult * 100 / (100 + m_Character[rnum].Wounded + m_Character[rnum].Poison);
    //    }
    //}
    //return bResult;
    return 0;
}

//��ȡ���徭��
int BattleScene::getGongtiLevel(int rnum)
{
    int i;
    //int n = m_Character[rnum].GongTi;
    //if ((rnum >= 0) && (n >= -1))
    //{
    //    if (m_Magic[m_Character[rnum].LMagic[n]].MaxLevel > m_Character[rnum].MagLevel[n] / 100)
    //    {
    //        return m_Character[rnum].MagLevel[n] / 100;
    //    }
    //    else { return m_Magic[m_Character[rnum].LMagic[n]].MaxLevel; }
    //}
    //else { return 0; }
    return 0;
}


float BattleScene::power(float base, float Exponent)
{
    if (Exponent == 0.0)
    {
        return 1.0;
    }
    else if ((base == 0.0) && (Exponent > 0.0))
    {
        return 0.0;
    }
    else if (base < 0)
    {
        /*Error(reInvalidOp);*/
        return 0.0; // avoid warning W1035 Return value of function '%s' might be undefined
    }
    else { return exp(Exponent * log(base)); }
}

//��ʼ����Χ
//mode=0�ƶ���1�����ö�ҽ�Ƶȣ�2�鿴״̬
void BattleScene::calCanSelect(int bnum, int mode, int Step)
{
    int i;
    if (mode == 0)
    {
        for (int i1 = 0; i1 <= 63; i1++)
        {
            for (int i2 = 0; i2 <= 63; i2++)
            {
                battleSceneData[battleSceneNum].Data[3][i1][i2] = -1;
            }
        }
        battleSceneData[battleSceneNum].Data[3][battleRole[bnum].X][battleRole[bnum].Y] = 0;
        seekPath2(battleRole[bnum].X, battleRole[bnum].Y, Step, battleRole[bnum].Team, mode);
    }
    if (mode == 1)
    {
        for (int i1 = 0; i1 <= 63; i1++)
        {
            for (int i2 = 0; i2 <= 63; i2++)
            {
                battleSceneData[battleSceneNum].Data[3][i1][i2] = -1;
                if (abs(i1 - battleRole[bnum].X) + abs(i2 - battleRole[bnum].Y) <= step)
                {
                    battleSceneData[battleSceneNum].Data[3][i1][i2] = 0;
                }
            }
        }
    }

    if (mode == 2)
    {
        for (int i1 = 0; i1 <= 63; i1++)
        {
            for (int i2 = 0; i2 <= 63; i2++)
            {
                battleSceneData[battleSceneNum].Data[3][i1][i2] = -1;
                if (battleSceneData[battleSceneNum].Data[2][i1][i2] >= 0)
                {
                    battleSceneData[battleSceneNum].Data[3][i1][i2] = 0;
                }
            }
        }
    }
}

//������Ա�ѡ�е�λ��
//���ö���
//�ƶ������У��Ա��е��ˣ����ܼ����ƶ�
void BattleScene::seekPath2(int x, int y, int step, int myteam, int mode)
{
    int Xlist[4096];
    int Ylist[4096];
    int steplist[4096];
    int curgrid, totalgrid;
    int Bgrid[5]; //0��λ��1������2�Ѿ���3�о���4���磬5���߹� ��6ˮ��
    int Xinc[5], Yinc[5];
    int curX, curY, curstep, nextX, nextY, i;

    Xinc[1] = 1;
    Xinc[2] = -1;
    Xinc[3] = 0;
    Xinc[4] = 0;
    Yinc[1] = 0;
    Yinc[2] = 0;
    Yinc[3] = 1;
    Yinc[4] = -1;
    curgrid = 0;
    totalgrid = 0;
    Xlist[totalgrid] = x;
    Ylist[totalgrid] = y;
    steplist[totalgrid] = 0;
    totalgrid = totalgrid + 1;
    while (curgrid < totalgrid)
    {
        curX = Xlist[curgrid];
        curY = Ylist[curgrid];
        curstep = steplist[curgrid];
        if (curstep < step)
        {
            for (int i = 1; i < 5; i++)
            {
                nextX = curX + Xinc[i];
                nextY = curY + Yinc[i];
                if ((nextX < 0) || (nextX > 63) || (nextY < 0) || (nextY > 63))
                {
                    Bgrid[i] = 4;
                }
                else if (battleSceneData[battleSceneNum].Data[3][nextX][nextY] >= 0)
                {
                    Bgrid[i] = 5;
                }
                else if (battleSceneData[battleSceneNum].Data[1][nextX][nextY] > 0)
                {
                    Bgrid[i] = 1;
                }
                else if ((battleSceneData[battleSceneNum].Data[2][nextX][nextY] >= 0)
                         && (battleRole[battleSceneData[battleSceneNum].Data[2][nextX][nextY]].Dead == 0))
                {
                    if (battleRole[battleSceneData[battleSceneNum].Data[2][nextX][nextY]].Team == myteam)
                    {
                        Bgrid[i] = 2;
                    }
                    else { Bgrid[i] = 3; }
                }
                else if (((battleSceneData[battleSceneNum].Data[0][nextX][nextY] / 2 >= 179)
                          && (battleSceneData[battleSceneNum].Data[0][nextX][nextY] / 2 <= 190))
                         || (battleSceneData[battleSceneNum].Data[0][nextX][nextY] / 2 == 261)
                         || (battleSceneData[battleSceneNum].Data[0][nextX][nextY] / 2 == 511)
                         || ((battleSceneData[battleSceneNum].Data[0][nextX][nextY] / 2 >= 224)
                             && (battleSceneData[battleSceneNum].Data[0][nextX][nextY] / 2 <= 232))
                         || ((battleSceneData[battleSceneNum].Data[0][nextX][nextY] / 2 >= 662)
                             && (battleSceneData[battleSceneNum].Data[0][nextX][nextY] / 2 <= 674)))
                {
                    Bgrid[i] = 6;
                }
                else
                {
                    Bgrid[i] = 0;
                }
            }

            //�ƶ������
            //��Ϊ��ʼλ�ã��������Ա��ǵо������
            //���ƶ������У��Ա�û�ео�������²ż����ƶ�

            if (mode == 0)
            {
                if ((curstep == 0) || ((Bgrid[1] != 3) && (Bgrid[2] != 3) && (Bgrid[3] != 3) && (Bgrid[4] != 3)))
                {
                    for (int i = 1; i < 5; i++)
                    {
                        if (Bgrid[i] == 0)
                        {
                            Xlist[totalgrid] = curX + Xinc[i];
                            Ylist[totalgrid] = curY + Yinc[i];
                            steplist[totalgrid] = curstep + 1;
                            battleSceneData[battleSceneNum].Data[3][Xlist[totalgrid]][Ylist[totalgrid]] = steplist[totalgrid];
                            totalgrid = totalgrid + 1;
                        }
                    }
                }
            }
            else                    //���ƶ��������������ҽ�Ƶ�
            {
                for (int i = 1; i < 5; i++)
                {
                    if ((Bgrid[i] == 0) || (Bgrid[i] == 2) || ((Bgrid[i] == 3)))
                    {
                        Xlist[totalgrid] = curX + Xinc[i];
                        Ylist[totalgrid] = curY + Yinc[i];
                        steplist[totalgrid] = curstep + 1;
                        battleSceneData[battleSceneNum].Data[3][Xlist[totalgrid]][Ylist[totalgrid]] = steplist[totalgrid];
                        totalgrid = totalgrid + 1;
                    }
                }
            }
        }
        curgrid++;
    }
}

//�ƶ�

void BattleScene::moveRole(int bnum)
{
    int s, i;
    calCanSelect(bnum, 0, battleRole[bnum].Step);
    if (selectAim(bnum, battleRole[bnum].Step, 0))
    {
        moveAmination(bnum);
    }
}

//ѡ���
bool BattleScene::selectAim(int bnum, int step, int mods)
{
    //switch (keypressing)
    //{
    //case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    //{
    //    Ay--;
    //    if ((abs(Ax - Bx) + abs(Ay - By) > step) || (battleSceneData[battleSceneNum].Data[3][Ax][Ay] < 0))
    //    {
    //        Ay++;
    //    }
    //    return false;
    //    break;
    //}
    //case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    //{
    //    Ay++;
    //    if ((abs(Ax - Bx) + abs(Ay - By) > step) || (battleSceneData[battleSceneNum].Data[3][Ax][Ay] < 0))
    //    {
    //        Ay--;
    //    }
    //    return false;
    //    break;
    //}
    //case EventKeyboard::KeyCode::KEY_UP_ARROW:
    //{
    //    Ax--;
    //    if ((abs(Ax - Bx) + abs(Ay - By) > step) || (battleSceneData[battleSceneNum].Data[3][Ax][Ay] < 0))
    //    {
    //        Ax++;
    //    }
    //    return false;
    //    break;
    //}
    //case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
    //{
    //    Ax++;
    //    if ((abs(Ax - Bx) + abs(Ay - By) > step) || (battleSceneData[battleSceneNum].Data[3][Ax][Ay] < 0))
    //    {
    //        Ax--;
    //    }
    //    return false;
    //    break;
    //}
    //case EventKeyboard::KeyCode::KEY_ESCAPE:
    //{
    //    Ax = Bx;
    //    Ay = By;
    //    return false;
    //    break;
    //}
    //case EventKeyboard::KeyCode::KEY_SPACE:
    //case EventKeyboard::KeyCode::KEY_KP_ENTER:
    //{
    //    return true;
    //    break;
    //}
    //default:
    //{
    //    if (Msx >= 0 && Msy >= 0 && Msx != Ax && Msy != Ay)
    //    {
    //        if ((abs(Msx - Bx) + abs(Msy - By) > step) || (battleSceneData[battleSceneNum].Data[3][Msx][Msy] < 0))
    //        {
    //            Ax = Bx;
    //            Ay = By;
    //        }
    //        else
    //        {
    //            Ax = Msx;
    //            Ay = Msy;
    //        }
    //        return true;
    //    }
    //    return false;
    //}
    //}
    return true;
}

//�ƶ�����
void BattleScene::moveAmination(int bnum)
{
    int s, i, a, tempx, tempy;
    int Xinc[5], Yinc[5];
    //  Ax = Bx - 4;            //������
    //  Ay = By - 4;
    if (battleSceneData[battleSceneNum].Data[3][Ax][Ay] > 0)     //0��λ��1������2�Ѿ���3�о���4���磬5���߹� ��6ˮ��
    {
        Xinc[1] = 1;
        Xinc[2] = -1;
        Xinc[3] = 0;
        Xinc[4] = 0;
        Yinc[1] = 0;
        Yinc[2] = 0;
        Yinc[3] = 1;
        Yinc[4] = -1;
        //      MyPoint *pInt = new MyPoint();
        //      pInt->x = Bx;
        //      pInt->y = By;
        //      wayQue.push(*pInt);
        //      MyPoint *pAInt = new MyPoint();
        //      pAInt->x = Ax;
        //      pAInt->y = Ay;
        linex[0] = Bx;
        liney[0] = By;
        linex[battleSceneData[battleSceneNum].Data[3][Ax][Ay]] = Ax;
        liney[battleSceneData[battleSceneNum].Data[3][Ax][Ay]] = Ay;
        a = battleSceneData[battleSceneNum].Data[3][Ax][Ay] - 1;
        while (a >= 0)
        {
            for (int i = 1; i < 5; i++)
            {
                tempx = linex[a + 1] + Xinc[i];
                tempy = liney[a + 1] + Yinc[i];
                if (battleSceneData[battleSceneNum].Data[3][tempx][tempy] == battleSceneData[battleSceneNum].Data[3][linex[a + 1]][liney[a + 1]] - 1)
                {
                    linex[a] = tempx;
                    liney[a] = tempy;
                    break;
                }
            }
            a--;
        }

        curA = 1;
        //schedule(schedule_selector(BattleScene::moveAminationStep), battleSpeed, kRepeatForever, battleSpeed)
    }
}

void BattleScene::moveAminationStep(float dt)
{

    int a = curA;
    int bnum = curRoleNum;
    if (!((battleRole[bnum].Step == 0) || ((Bx == Ax) && (By == Ay))))
    {
        if ((linex[a] - Bx) > 0)
        {
            battleRole[bnum].Face = 3;
        }
        else if ((linex[a] - Bx) < 0)
        {
            battleRole[bnum].Face = 0;
        }
        else if ((liney[a] - By) < 0)
        {
            battleRole[bnum].Face = 2;
        }
        else { battleRole[bnum].Face = 1; }
        if (battleSceneData[battleSceneNum].Data[2][Bx][By] == bnum)
        {
            battleSceneData[battleSceneNum].Data[2][Bx][By] = -1;

        }
        Bx = linex[a];
        By = liney[a];
        battleRole[bnum].X = Bx;
        battleRole[bnum].Y = By;
        if (battleSceneData[battleSceneNum].Data[2][Bx][By] == -1)
        {
            battleSceneData[battleSceneNum].Data[2][Bx][By] = bnum;
        }
        a++;
        curA = a;
        battleRole[bnum].Step--;
        draw();
    }
    else
    {
        //      battleRole[bnum].X = Bx;
        //      battleRole[bnum].Y = By;
        //unschedule(schedule_selector(BattleScene::moveAminationStep));
        showBattleMenu(50, 500);
    }
}

void BattleScene::battleMainControl()
{

    battleMainControl(-1, -1);

}

void BattleScene::battleMainControl(int mods, int id)
{


    calMoveAbility(); //�����ƶ�����
    reArrangeBRole();
    Bx = battleRole[curRoleNum].X;
    By = battleRole[curRoleNum].Y;
    draw();
}

void BattleScene::attack(int bnum)
{
    int mnum, level;
    int i = 1;
    int rnum = battleRole[bnum].rnum;
    //mnum = m_Character[rnum].LMagic[i];
    //level = m_Character[rnum].MagLevel[i] / 100 + 1;
    curMagic = mnum;
}