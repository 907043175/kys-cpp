#pragma once
#include <vector>
#include "Engine.h"
#include "Texture.h"

#define CONNECT(a,b) a##b

struct auto_ptr
{

};

class Base		//��Ϸ���ƻ����࣬����Ҫ��ʾ����ģ����̳��Դ�
{
public:
	Base();
	virtual ~Base();

	void LOG(const char *format, ...);

	virtual void draw() {}
	virtual void dealEvent(BP_Event& e) {}

	static std::vector<Base*> m_vcBase;   //������Ҫ���Ƶ����ݶ��洢��m_vcBase��

	bool m_bvisible = true;

	template <class T> void safe_delete(T*& pointer)
	{
		if (pointer)
			delete pointer;
		pointer = nullptr;
	}

	virtual void init() {}

	void push(Base* b) { m_vcBase.push_back(b); b->init(); }
	void pop() { safe_delete(m_vcBase.back()); m_vcBase.pop_back(); }
	static Base* getCurentBase() { return m_vcBase.at(0); }

	int m_nx = 0, m_ny = 0;
	void setPosition(int x, int y) { this->m_nx = x; this->m_ny = y; }
	int m_nw = 0, m_nh = 0;
	void setSize(int w, int h) { this->m_nw = w; this->m_nh = h; }

	bool inSide(int x, int y);

	int m_nfull = 0;  //��Ϊ0ʱ��ʾ��ǰ����Ϊ��ʼ�㣬���ڱ�����Ĳ㽫������ʾ

};

