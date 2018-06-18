//定义流

#pragma once
#include <iostream>
using namespace std;

class Flow
{
private:
	int flowtag;		//流标识
	int size;			//流大小
	float time;			//流到达时间
	int cotag;			//所属coflow标识-可能会有错误
	bool state;			//标识流是否已被调度
	int tag;			//分类后的coflow标识-真值
	float finishtime;	//调度完成时间
public:
	Flow(int m_flowtag, int m_size, float m_time, int m_cotag);	//有参构造函数
	Flow(void);
	~Flow(void);

	int getFlowtag();	//获取流标签
	int getSize();		//获取流大小
	float getTime();	//获取流到达时间
	int getCotag();		//获取所属coflow标志
	bool getState();	//获取调度状态
	int getTag();		//获取实际分类结果
	float getFinishtime();			//获取流调度完成时间
	void setCotag(int m_cotag);		//设置分类结果
	void setState(bool m_state);	//设置调度状态
	void setFinishtime(float time);	//设置流调度完成时间
	void setTag(int m_tag);			//设置真实标识
	void print();					//输出流信息
};

