#pragma once
class Flow
{
private:
	int flowtag;	//����ʶ
	int size;		//����С
	int time;		//������ʱ��
	int cotag;		//����coflow��ʶ-��ʵֵ
	int tag;		//������coflow��ʶ-������ֵ-���ܻ��д���
public:
	Flow(int m_flowtag, int m_size, int m_time, int m_cotag, int m_tag);
	int getFlowtag();
	int getSize();
	int getTime();
	int getCotag();
	int getTag();
	Flow(void);
	~Flow(void);
};

