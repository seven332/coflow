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

//插入新节点
void Coflow::InsertFlow(Flow flow)
{
	FlowNode node;
	node.flow=flow;
	node.dispatch=false;
	flowtable.push_back(node);
}
