#pragma once
#include "Base.h"
#include <vector>
#include <string>
using namespace std;
class Dialogues :
	public Base
{
public:
	Dialogues();
	~Dialogues();
	static vector<string> m_Dialogues;    //�Ի�ȫ����ȡ��������
	bool InitDialogusDate();
	string GBKToUTF8(const string& strGBK);
	vector<int> m_idxLen;                
};

