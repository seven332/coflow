#include "Scheduler.h"


Scheduler::Scheduler(void)
{
}


Scheduler::~Scheduler(void)
{
}

//计算所有流传输完成所需时间
float Scheduler::FinishTime(Flow *flow)
{
	float time=0.0;
	for(int i=0;i<NUMOFFLOW;i++)
	{
		time+=(float)flow[i].getSize()/BANDWIDTH;
		flow[i].setFinishtime(time);
	}
	return time;
}

//FIFO调度算法
void Scheduler::FIFO(Flow *flow)
{
	cout<<"-----使用先入先出算法调度-----"<<endl;
	cout<<"所有流调度完成时间："<<FinishTime(flow)<<endl;
	
	cout<<"------------------------------"<<endl;
}
