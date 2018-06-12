//定义coflow

#pragma once
#include "flow.h"
#include <vector>


////定义流表节点
////用于记录coflow中包含的所有流以及其调度情况
//typedef struct FLOWNODE
//{
//	Flow flow;	//流
//	bool tag;	//调度标志
//}FlowNode;

class Coflow
{
private:
	int cotag;		//coflow标识
	int size;		//coflow大小
	int sentsize;	//已发送大小
	float finishtime;	//coflow调度完成时间
	vector<Flow> flowtable;	//coflow的流表
public:
	Coflow(void);
	Coflow(int m_cotag);	//带参构造函数
	~Coflow(void);
	int getCotag();			//获取coflow标志
	int getSize();			//获取coflow大小
	int getSentsize();		//获取coflow已发送大小
	float getFinishtime();	//获取coflow调度完成时间
	Flow getFlow();			//获取流表中末置位元素
	bool TableEmpty();		//判断当前coflow流表是否为空
	void setSize(int m_size);	//设置coflow大小
	void setSentsize(int m_sentsize);	//设置coflow已发送大小
	void setFinishtime(float time);		//设置coflow调度完成时间
	void InsertFlow(Flow flow);			//将新来的子流插入流表
	bool PopFlow(Flow flow);			//从流表去掉制定流
};

