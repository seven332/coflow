#include "Coflow.h"


Coflow::Coflow(void)
{
}


Coflow::~Coflow(void)
{
}

Coflow::Coflow(int m_cotag)
{
	cotag=m_cotag;
	size=0;
	finishtime=0.0;
	flowtable.clear();
	flowtable.shrink_to_fit();
}

//获取coflow标志
int Coflow::getCotag()
{
	return cotag;
}

//获取coflow已发送字节数
int Coflow::getSize()
{
	return size;
}

//获取coflow调度完成时间
float Coflow::getFinishtime()
{
	return finishtime;
}

Flow Coflow::getFlow()
{
	//vector<FlowNode>::iterator iter;
	//iter=flowtable.back();
	return flowtable.back().flow;
}

//判断当前coflow流表是否为空
bool Coflow::TableEmpty()
{
	return flowtable.empty();
}

//设置coflow大小
void Coflow::setSize(int m_size)
{
	size=m_size;
}

//设置已发送大小
void Coflow::setSentsize(int m_sentsize)
{
	sentsize=m_sentsize;
}

//设置coflow调度完成时间
void Coflow::setFinishtime(float time)
{
	finishtime=time;
}

//插入新节点
void Coflow::InsertFlow(Flow flow)
{
	FlowNode node;
	node.flow=flow;
	node.tag=false;
	flowtable.push_back(node);
}
