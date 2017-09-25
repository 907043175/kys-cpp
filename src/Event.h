#pragma once
#include "Base.h"

class Event : public Base
{
public:
    Event();
    virtual ~Event();
    static Event* getInstance()
    {
        return &event_;
    }

    std::vector<int> offset, length;

    std::vector<std::string> talk_;
    std::vector<std::vector<int16_t>> kdef_;

    int16_t* getEvent(int i);
    char* getTalk(int i);


    bool initEventData();       //�����¼�����
    bool callEvent(int num);    //����ָ�������д����
    int eventCount = 0;

    //�����¼�������Ӧ����һ��������Ϊָ��ָ���ƶ�����Ŀ
    void clear();  //0
    void talk_1();
    void getItem_2(short tnum, short amount, short rnum = 0);
    void getJueSe(short* rnum);
    void editEvent3(short snum, short ednum, short CanWalk, short Num, short Event1, short Event2, short Event3, short BeginPic1, short EndPic, short BeginPic2, short  PicDelay, short  XPos, short  YPos, short StartTime, short  Duration, short Interval, short  DoneTime, short  IsActive, short  OutTime, short  OutEvent);
    int judgeItem_4(short inum, short jump1, short jump2);
    int isFight_5(short jump1, short jump2);

    int isAdd_8(short jump1, short jump2);
    void StudyMagic(int rnum, int magicnum, int newmagicnum, int level, int dismode);
    void JumpScene(int snum, int x, int y);

private:
    static Event event_;
    static int NowEenWu;
    static bool isTry;
    static bool TryGo;
    static int TryEventTmpI;
    static int EventEndCount;

public:
    void clear() {}
    void oldTalk(int16_t i1, int16_t i2, int16_t i3);
    void getItem(int16_t i1, int16_t i2);
    void modifyEvent();
    void useItem();
    void askBattle();
    void tryBattle();
    void changeMMapMusic();
    void askJoin();
    void join();
    void askRest();
    void rest();
    void lightScence();
    void darkScence();
    void dead();
    void inTeam();
    void oldSetScenceMapPro();
    void haveItemBool();
    void oldSetScencePosition();
    void teamIsFull();
    void leaveTeam();
    void zeroAllMP();
    void setOneUsePoi();
    void blank();
    void scenceFromTo();
    void add3EventNum();
    void playAnimation();
    void judgeEthics();
    void judgeAttack();
    void walkFromTo();
    void judgeMoney();
    void addItem();
    void oldLearnMagic();
    void addAptitude();
    void setOneMagic();
    void judgeSexual();
    void addEthics();
    void changeScencePic();
    void openScence();
    void setRoleFace();
    void anotherGetItem();
    void judgeFemaleInTeam();
    void haveItemBool();
    void play2Amination();
    void addSpeed();
    void addMP();
    void addAttack();
    void addHP();
    void setMPPro();
    void judge5Item();
    void askSoftStar();
    void showEthics();
    void showRepute();
    void openAllScence();
    void judgeEventNum();
    void addRepute();
    void breakStoneGate();
    void fightForTop();
    void allLeave();
    void judgeScencePic();
    void judge14BooksPlaced();
    void backHome();
    void setSexual();
    void weiShop();
    void playMusic();
    void playWave();
};






