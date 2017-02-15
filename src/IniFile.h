#ifndef _INI_READER_H_
#define _INI_READER_H_

#include<fstream>
#include<map>
#include<list>
#include<string>
using namespace std;

/*
.ini �ļ� ������
Section��Keyֻ��Ϊ��ĸ�����֡��»��ߡ��ո񡢼��š��㣨�����ַ�ֻ��Ϊ��ĸ���ֻ��»��ߣ��Զ�����ǰ���󵼿ո�
Value����Ϊ�Ʊ�������С��ֺŵȣ��Զ�����ǰ���󵼿ո�ֵ����Ϊ�գ�
���в��ܳ���4096�ֽ�
ĳ����ʶ�����ܳ���2048�ֽ�
*/
class IniReader
{
public:
	/**
	@Purpose: ���캯��
	@Parameter: file_name �ļ�����·����
	@Throw: ����ʧ����throw IniReaderError
	*/
	IniReader(string file_name);
	/**
	@Purpose: ��������
	*/
	~IniReader();
	/**
	@Purpose: �г�Section
	@Parameter: section_address �ַ�������ĵ�ַ�����ڴ�Ž���������ڲ������ڴ棬ΪNULL��ʾ����Ҫ�����
	@Return: Section�ĸ���
	*/
	int ListSection(string** section_address = NULL);
	/**
	@Purpose: �г�ĳSection��Key
	@Parameter: section Section�ַ���
	@Parameter: key_address �ַ�������ĵ�ַ�����ڴ�Ž���������ڲ������ڴ棬ΪNULL��ʾ����Ҫ�����
	@Return: Key�ĸ���
	*/
	int ListKey(string section, string** key_address = NULL);
	/**
	@Purpose: ��ȡĳSection��ĳKey��Ӧ��Value
	@Parameter: section Section�ַ���
	@Parameter: key Key�ַ���
	@Parameter: default_value Ĭ��ֵ����ʾû�д�Section�µ�Key-Value�ԣ��򷵻����Ĭ��ֵ��
	@Return: Value�ַ���
	*/
	string GetValue(string section, string key, string default_value = "");
private:
	map<string, map<string, string>*> smap; //Section-Key-Value Map
	list<string> slist; //Section List
	map<string, list<string>*> skmap; //Section-(Key List) Map
};

/**
IniReader����
�������ͣ�
-1���ļ���ʧ��
-2��Section������ĸ���»��߿�ͷ
-3��Sectionû�бպ�
-4����ֵ��ȱ��=
-5��ȱ��ֵ���ѷ�����
-6������û�������κ�Section��Key-Value��
*/
struct IniReaderError
{
	int type; //��������
	int line; //����
	IniReaderError(int t, int l);
};

#endif