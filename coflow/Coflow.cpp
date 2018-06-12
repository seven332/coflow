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

//获取coflow大小
int Coflow::getSize()
{
	return size;
}

//获取coflow已发送大小
int Coflow::getSentsize()
{
	return sentsize;
}

//获取coflow调度完成时间
float Coflow::getFinishtime()
{
	return finishtime;
}

//获取流表中末置位元素
Flow Coflow::getFlow()
{
	Flow flow=flowtable.back();
	flowtable.pop_back();
	return flow;
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

//将新来的子流插入流表
void Coflow::InsertFlow(Flow flow)
{
	flowtable.push_back(flow);
}

//从流表去掉制定流
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