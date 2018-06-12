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

//��ȡcoflow�������ʱ��
float Coflow::getFinishtime()
{
	return finishtime;
}

Flow Coflow::getFlow()
{
	Flow flow=flowtable.back();
	flowtable.pop_back();
	return flow;
}

//�жϵ�ǰcoflow�����Ƿ�Ϊ��
bool Coflow::TableEmpty()
{
	return flowtable.empty();
}

//����coflow��С
void Coflow::setSize(int m_size)
{
	size=m_size;
}

//�����ѷ��ʹ�С
void Coflow::setSentsize(int m_sentsize)
{
	sentsize=m_sentsize;
}

//����coflow�������ʱ��
void Coflow::setFinishtime(float time)
{
	finishtime=time;
}

//�����½ڵ�
void Coflow::InsertFlow(Flow flow)
{
	flowtable.push_back(flow);
}

//ɾ��ָ���ڵ�
bool Coflow::PopFlow(Flow flow)
{
	vector<Flow>::iterator iter;
	for(iter=flowtable.begin();iter!=flowtable.end();iter++)
	{
		if(iter->getFlowtag()==flow.getFlowtag())
		{
			flowtable.erase(iter);
			return true;
		}
	}
	return false;
}