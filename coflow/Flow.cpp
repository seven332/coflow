#include "Flow.h"



Flow::Flow(void)
{
}


Flow::~Flow(void)
{
}

//有参构造函数
Flow::Flow(int m_flowtag, int m_size, int m_time, int m_cotag, int m_tag)
{
	flowtag=m_flowtag;
	size=m_size;
	time=m_time;
	cotag=m_cotag;
	tag=m_tag;
}

//获取流标签
int Flow::getFlowtag()
{
	return flowtag;
}

//获取流大小
int Flow::getSize()
{
	return size;
}

//获取流到达时间
int Flow::getTime()
{
	return time;
}

//获取所属coflow标志
int Flow::getCotag()
{
	return cotag;
}

//获取实际分类结果
int Flow::getTag()
{
	return tag;
}