﻿#include "main.h"

//初始化coflow数组
void InitCoflow(Coflow  *coflow, int num)
{
	for(int i=0;i<num;i++)
		coflow[i]=Coflow(i);
}

//重置所有流的调度状态，改为非调度状态
//重置所有流调度完成时间
//重置所有coflow调度完成时间
void ResetFlowState(Flow *flow)
{
	for(int i=0;i<NUMOFFLOW;i++)
	{
		flow[i].setState(false);
		flow[i].setFinishtime(0);
	}
	for(int i=0;i<NUMPERCOFLOW;i++)
	{

	}
}

//打印所有流信息
void PrintFlowInfo(Flow *flow)
{
	for(int i=0;i<NUMOFFLOW;i++)
	{
		flow[i].print();
	}
}

//主函数
int main()
{
	Flow flow[NUMOFFLOW];

	Coflow coflow[NUMOFCOFLOW];
	Generator gen;
	Scheduler sch;
	InitCoflow(coflow,NUMOFCOFLOW);
	gen.produce(flow);	
	sch.FIFO(flow,coflow);
	InitCoflow(coflow,NUMOFCOFLOW);
	ResetFlowState(flow);
	sch.MINCCT(flow,coflow);
	InitCoflow(coflow,NUMOFCOFLOW);
	ResetFlowState(flow);
	sch.MPQ(flow,coflow);
	InitCoflow(coflow,NUMOFCOFLOW);
	ResetFlowState(flow);
	flow[99].setCotag(0);
	flow[99].setTag(9);
	flow[18].setCotag(8);
	flow[18].setTag(1);
	flow[9].setCotag(9);	
	flow[9].setTag(0);
	sch.EMPQ(flow,coflow);
	InitCoflow(coflow,NUMOFCOFLOW);
	ResetFlowState(flow);
	sch.ETMPQ(flow,coflow);
}