#pragma once
#include "UI.h"
#include <vector>
#include <string>
using namespace std;
class Dialogues :
	public UI
{
public:
	Dialogues();
	~Dialogues();
	static vector<string> m_Dialogues;    //�Ի�ȫ����ȡ��������
	bool InitDialogusDate();
	string GBKToUTF8(const string& strGBK);
	vector<int> m_idxLen;    

	void draw();
	string fontsName, talkString;
	SDL_Color color;
	void SetFontsName(const string& fontsName);
	void SetFontsColor(SDL_Color &color);
};

