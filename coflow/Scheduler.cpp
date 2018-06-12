#include "Scheduler.h"


Scheduler::Scheduler(void)
{
}


Scheduler::~Scheduler(void)
{
}

//对比两个coflow的大小,升序
bool Scheduler::comparebycosize(Coflow a,Coflow b)
{
	if(a.getSize()<b.getSize())
		return true;
	else
		return false;
}

//定义流之间的比较函数
//根据流的到达时间比较大小,升序
bool Scheduler::comparebytime(Flow a, Flow b)
{
	if(a.getTime()<b.getTime())
		return true;
	else
		return false;
}

//定义流之间的比较函数
//根据流的标识比较大小,升序
bool Scheduler::comparebyflowtag(Flow a, Flow b)
{
	if(a.getFlowtag()<b.getFlowtag())
		return true;
	else
		return false;
}

//计算所有流传输完成所需时间
float Scheduler::FinishTime(Flow *flow)
{
	float time=0.0;
	for(int i=0;i<NUMOFFLOW;i++)
	{
		if(time < flow[i].getFinishtime())
		{
			time=flow[i].getFinishtime();
		}
	}
	return time;
}

//Coflow平均完成时间
float Scheduler::CCT(Coflow *coflow)
{
	float time=0.0;
	for(int i=0;i<NUMOFCOFLOW;i++)
	{
		float cotime=coflow[i].getFinishtime();
		time+=cotime;
		cout<<"Coflow："<<i+1<<"完成时间为："<<cotime<<endl;
	}
	return time/NUMOFCOFLOW;
}

//按照Coflow标识将流添加至coflow中
void Scheduler::ClassifyByCotag(Flow *flow, Coflow *coflow)
{
	for(int i=0;i<NUMOFFLOW;i++)
	{
		int cotag=flow[i].getCotag()-1;
		coflow[cotag].setSize(coflow[cotag].getSize()+flow[i].getSize());
		coflow[cotag].InsertFlow(flow[i]);
	}
}

//FIFO调度算法
void Scheduler::FIFO(Flow *flow, Coflow *coflow)
{
	cout<<"--------使用先入先出算法调度--------"<<endl;
	sort(flow,flow+NUMOFFLOW,comparebytime);
	float finishtime=0.0;
	for(int i=0;i<NUMOFFLOW;i++)
	{
		finishtime+=(float)flow[i].getSize()/BANDWIDTH;
		flow[i].setFinishtime(finishtime);
		int cotag=flow[i].getCotag()-1;
		coflow[cotag].setFinishtime(finishtime);
	}
	cout<<"所有流调度完成时间："<<finishtime<<endl;
	cout<<"所有Coflow调度完成的平均时间为："<<CCT(coflow)<<endl;
	cout<<"------------------------------------"<<endl;
}

//最小coflow平均完成时间调度方案
//一种离线分析方法，需要知道全部coflow的信息
void Scheduler::MINCCT(Flow *flow, Coflow *coflow)
{
	cout<<"--------使用最小平均完成时间算法调度--------"<<endl;
	ClassifyByCotag(flow,coflow);						//首先将所有流添加至对应coflow
	sort(coflow,coflow+NUMOFCOFLOW,comparebycosize);	//按照coflow大小升序排序
	sort(flow,flow+NUMOFFLOW,comparebyflowtag);			//按照flow的编号升序排序
	float finishtime=0.0;
	for(int i=0;i<NUMOFCOFLOW;i++)
	{
		while(!coflow[i].TableEmpty())
		{
			Flow f=coflow[i].getFlow();
			finishtime+=(float)f.getSize()/BANDWIDTH;
			flow[f.getFlowtag()-1].setFinishtime(finishtime);
			coflow[i].setFinishtime(finishtime);
		}
	}
	cout<<"所有流调度完成时间："<<FinishTime(flow)<<endl;
	cout<<"所有Coflow调度完成的平均时间为："<<CCT(coflow)<<endl;
	cout<<"--------------------------------------------"<<endl;
}

//多级优先权调度队列
void MPQ(Flow *flow, Coflow *coflow)
{

}