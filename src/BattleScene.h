#pragma once

using namespace std;
 
class BattleScene : public Scene
{
public:
	BattleScene();
	~BattleScene();

    virtual void draw() override {}
    virtual void dealEvent(BP_Event& e) override {}

	static const int maxBRoleSelect = 6;		//ս��ѡ���������
	int MaxBRoleNum = 42;						//���ս����ս����	
//	int Sx, Sy;
	const int battleSpeed = 0.025;				//ս���ٶ�	
	int Bx, By;									//��ǰλ��
	int Ax, Ay;									//Ŀ��λ��
	int linex[480 * 480], liney[480 * 480];
	int manPicture;
	int step = 0;
	int curA;
	int counter = 0;                    // �������������ѡ���߼�����
	int xx = 317;                       // ������Ϣ�����x
	int yy = 382;                       // ������Ϣ�����y
	enum
	{
		kindOfRole = 7				  //������Ϣ�������������
	};
	string s_list[BattleScene::kindOfRole]; // ������Ϣ��������ԣ�Ĭ���������������������Ṧ��
	int num_list = 0;                   // ������Ϣ������б�λ��
	int offset_BRolePic = 1;				//����ս��ͼ����
	int BRoleAmount = 0;				//ս������
	int mods = 0;						//ս��ģʽ
	string menuString[maxBRoleSelect+2];				//ս������ѡ��
	int max0;						    //�������
	int maxspeed;						//�����

	int BStatus;
	bool isBattle;
	int WHERE;                          
	int curRoleNum;									//��ǰ�������
	int BattleList[maxBRoleSelect];                  //��ս��Ա�б�
	int ResultofBattle[maxBRoleSelect];              //ս��ѡ�˽��
	MenuItemFont *item[maxBRoleSelect+2];              //ѡ�˿ؼ�
	bool SlectOfresult[maxBRoleSelect+2];                  //ѡ��״̬
	int battleNum;										//��ǰս����
	int sceneNum;										//��ǰս��������
	int curMagic;										//��ǰ�书

	std::vector<Sprite*> EarthS, BuildS, AirS, EventS;
	stack<MyPoint> wayQue;												//ջ(·��ջ)


	battle &Battle = battle::bBattle;										//����battle
 	vector<battle::TBattleRole> BRole;							//����ս����Ա
	
	void Draw();

	virtual bool init(int scenenum);

	static BattleScene* create(int scenenum);

	static Scene* createScene(int scenenum);

	//void keyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	//void keyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	void Walk(int x, int y, Towards t);

	virtual void keyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	virtual void keyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	bool touchBegan(Touch *touch, Event *event);
	void touchEnded(Touch *touch, Event *event);
	void touchCancelled(Touch *touch, Event *event);
	void touchMoved(Touch *touch, Event *event);

	void checkTimer2();
	void callEvent(int x, int y);
	bool canWalk(int x, int y);
	virtual bool checkIsBuilding(int x, int y);
	virtual bool checkIsOutLine(int x, int y);
	bool checkIsHinder(int x, int y);
	bool checkIsEvent(int x, int y);
	bool checkIsFall(int x, int y);
	bool checkIsExit(int x, int y);
	bool checkIsOutScreen(int x, int y);

	void initData(int battlenum);
	bool initBattleData();
	bool initBattleRoleState();
	bool autoInBattle();

	void autoSetMagic(int rnum);
	int selectTeamMembers();
	void ShowMultiMenu(int max0, int menu);
	void showSlectMenu(string *str,int x);                               // ��ս������Ϣ
	void showBattleMenu(int x,int y);                                    // ս������
	
	void initMultiMenu();
	
	void loadBattleTiles();
	void getMousePosition(Point *point);
	virtual void FindWay(int Mx, int My, int Fx, int Fy);

	int CallFace(int x1, int y1, int x2, int y2);
	int CallFace(int num1, int num2);

	inline int calBlockTurn(int x, int y, int layer)
	{
		return 4 * (128 * (x + y) + x) + layer;
	}

	void menuCloseCallback(Ref* pSender);
	void menuCloseCallback1(Ref* pSender);
	bool battle(int battlenum, int getexp, int mods, int id, int maternum, int enemyrnum);
	void setInitState(int &n0);
	void calMoveAbility();
	void reArrangeBRole();
	int getRoleSpeed(int rnum, bool Equip);
	int getGongtiLevel(int rnum);
	float power(float Base, float Exponent);
	void moveRole(int bnum);
	void calCanSelect(int bnum, int mode, int step);
	void seekPath2(int x, int y, int step, int myteam, int mode);
	void moveAmination(int bnum);
	bool selectAim(int bnum, int step, int mods);
	void battleMainControl();
	void battleMainControl(int mods, int id);
	//void Draw(float dt);
	void moveAminationStep(float dt);
	void attack(int bum);
};