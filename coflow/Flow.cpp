#include "Flow.h"



Flow::Flow(void)
{
}


Flow::~Flow(void)
{
}

//有参构造函数
Flow::Flow(int m_flowtag, int m_size, float m_time, int m_cotag)
{
	flowtag=m_flowtag;
	size=m_size;
	time=m_time;
	cotag=m_cotag;
	tag=0;
	state=false;
	finishtime=0;
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
float Flow::getTime()
{
	return time;
}

//获取所属coflow标志
int Flow::getCotag()
{
	return cotag;
}

//获取调度状态
bool Flow::getState()
{
	return state;
}

//获取实际分类结果
int Flow::getTag()
{
	return tag;
}

//获取流调度完成时间
float Flow::getFinishtime()
{
	return finishtime;
}

//设置调度状态
void Flow::setState(bool m_state)
{
	state=m_state;
}

//设置流调度完成时间
void Flow::setFinishtime(float time)
{
	finishtime=time;
}

//输出流信息
void Flow::print()
{
	cout<<"------流："<<flowtag<<"--------"<<endl;
	cout<<"大小："<<size<<endl;
	cout<<"到达时间："<<time<<endl;
	cout<<"所属coflow标识："<<cotag<<endl;
	cout<<"-------------------"<<endl<<endl;
}