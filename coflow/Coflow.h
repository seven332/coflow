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
	int getCotag();
	int getSize();
	int getSentsize();
	float getFinishtime();
	Flow getFlow();
	bool TableEmpty();
	void setSize(int m_size);
	void setSentsize(int m_sentsize);
	void setFinishtime(float time);
	void InsertFlow(Flow flow);
	bool PopFlow(Flow flow);
};

