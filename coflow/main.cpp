#include "main.h"

//初始化coflow数组
void InitCoflow(Coflow  *coflow, int num)
{
	for(int i=0;i<num;i++)
		coflow[i]=Coflow(i+1);
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
	sch.MINCCT(flow,coflow);
}