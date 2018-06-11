//������

#pragma once
#include <iostream>
using namespace std;

class Flow
{
private:
	int flowtag;		//����ʶ
	int size;			//����С
	int time;			//������ʱ��
	int cotag;			//����coflow��ʶ-��ʵֵ
	int tag;			//������coflow��ʶ-������ֵ-���ܻ��д���
	float finishtime;	//�������ʱ��
public:
	Flow(int m_flowtag, int m_size, int m_time, int m_cotag);
	Flow(void);
	~Flow(void);

	int getFlowtag();
	int getSize();
	int getTime();
	int getCotag();
	int getTag();
	float getFinishtime();
	void setFinishtime(float time);
	void print();
};

