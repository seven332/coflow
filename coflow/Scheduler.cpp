﻿#include "Scheduler.h"


Scheduler::Scheduler(void)
{
}


Scheduler::~Scheduler(void)
{
}

//更新接收队列
//将达到时间小于指定时间的未被调度的流加入到接收队列
//同时修改相应流的状态为已调度
void Scheduler::UpdateRecvq(Flow *flow, float time)
{
	for(int i=0;i<NUMOFFLOW;i++)
	{
		if((flow[i].getTime()<=time)&&!flow[i].getState())
		{
			recvq.push_back(flow[i]);
			flow[i].setState(true);
		}
	}
}

//从接收队列取制定coflow的流
//将属于制定coflow中的所有流从接收队列存入coflow
void Scheduler::GetFlowbyCotag(Coflow *coflow, int cotag)
{

}

//发送指定流
//根据线速计算发送所需时间
//返回更新后的当前时间
float Scheduler::SendFlow(Flow f, float time)
{
	float finishtime=time+(float)f.getSize()/BANDWIDTH;
	return finishtime;
}

//更新制定流所属coflow完成时间
void Scheduler::UpdateCoflowFinishtime(Coflow *coflow, Flow f)
{
	int cotag=f.getCotag()-1;
	coflow[cotag].setFinishtime(f.getFinishtime());
}

//更新Coflow流表
//将接收队列中的流添加至coflow流表
void UpdateCoflowFlowtable(Coflow *coflow)
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
	sort(flow,flow+NUMOFFLOW,comparebytime);	//按照流的到达时间排序
	float time=0.0;				//实时更新时间
	float lastflashtime=0.0;	//记录上一次更新流表时间
	UpdateRecvq(flow,time);		//开始更新接收队列
	//接收队列未空前持续流调度过程
	while(!recvq.empty())
	{
		//处理队头元素
		Flow f=recvq.front();
		vector<Flow>::iterator it=recvq.begin();
		recvq.erase(it);
		time=SendFlow(f,time);	
		f.setFinishtime(time);

		//更新处理后流所属coflow完成时间
		UpdateCoflowFinishtime(coflow,f);

		//每个时间单位更新接收队列
		if(time-lastflashtime>=1.0)
		{
			UpdateRecvq(flow,time);
			lastflashtime=time;
		}
	}
	//流调度结束
	cout<<"所有流调度完成时间："<<time<<endl;
	cout<<"所有Coflow调度完成的平均时间为："<<CCT(coflow)<<endl;
	cout<<"------------------------------------"<<endl;
}

//debug MINCCT
//在此情况下，已经预先知道了所有coflow的大小，在较小的coflow拥有最高的调度优先级
void Scheduler::NEWMIN(Flow *flow, Coflow *coflow)
{
	cout<<"--------NEWMIN--------"<<endl;
	float time=0.0;				//实时更新时间
	float lastflashtime=0.0;	//记录上一次更新流表时间
	UpdateRecvq(flow,time);		//开始更新接收队列
	///////////right here//////////////
	while(!recvq.empty())
	{
		for(int i=0;i<NUMOFCOFLOW;i++)
		{
			//处理队列中属于响应coflow的流

			//每个时间单位更新接收队列
			if(time-lastflashtime>=1.0)
			{
				UpdateRecvq(flow,time);
				lastflashtime=time;
				break;
			}
		}
	}
	cout<<"----------------------"<<endl;
}

//最小coflow平均完成时间调度方案
//一种离线分析方法，需要知道全部coflow的信息
void Scheduler::MINCCT(Flow *flow, Coflow *coflow)
{
	cout<<"--------使用最小平均完成时间算法调度--------"<<endl;
	ClassifyByCotag(flow,coflow);						//首先将所有流添加至对应coflow
	sort(coflow,coflow+NUMOFCOFLOW,comparebycosize);	//按照coflow大小升序排序
	sort(flow,flow+NUMOFFLOW,comparebyflowtag);			//按照flow的编号升序排序
	float finishtime=0.0;								//实时更新完成时间
	
	//对所有coflow，按照其大小依次调度
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
	cout<<"--------使用基于coflow的多级优先级队列算法调度--------"<<endl;
	float time=0.0;				//实时更新时间
	float lastflashtime=0.0;	//记录上一次更新流表时间

	cout<<"------------------------------------------------------"<<endl;
}