#pragma once
class Flow
{
private:
	int flowtag;	//流标识
	int size;		//流大小
	int time;		//流到达时间
	int cotag;		//所属coflow标识-真实值
	int tag;		//分类后的coflow标识-分类结果值-可能会有错误
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

