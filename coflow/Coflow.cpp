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

//��ȡcoflow��־
int Coflow::getCotag()
{
	return cotag;
}

//��ȡcoflow�ѷ����ֽ���
int Coflow::getSize()
{
	return size;
}

//�����½ڵ�
void Coflow::InsertFlow(Flow flow)
{
	FlowNode node;
	node.flow=flow;
	node.dispatch=false;
	flowtable.push_back(node);
}
