#include "Scheduler.h"


Scheduler::Scheduler(void)
{
}


Scheduler::~Scheduler(void)
{
}

//���������������������ʱ��
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

//FIFO�����㷨
void Scheduler::FIFO(Flow *flow)
{
	cout<<"-----ʹ�������ȳ��㷨����-----"<<endl;
	cout<<"�������������ʱ�䣺"<<FinishTime(flow)<<endl;
	
	cout<<"------------------------------"<<endl;
}
