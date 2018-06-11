#pragma once
#include "flow.h"
#include <vector>
using namespace std;

//定义流表节点
//用于记录coflow中包含的所有流以及其调度情况
typedef struct FLOWNODE
{
	Flow flow;
	bool dispatch;
}FlowNode;

class Coflow
{
private:
	int cotag;		//coflow标识
	int size;		//已发送大小
	vector<FlowNode> flowtable;	//coflow的流表
public:
	Coflow(void);
	Coflow(int m_cotag);	//带参构造函数
	~Coflow(void);
	int getCotag();
	int getSize();
	void InsertFlow(Flow flow);
};

