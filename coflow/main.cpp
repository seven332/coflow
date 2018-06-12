#include "main.h"

//��ʼ��coflow����
void InitCoflow(Coflow  *coflow, int num)
{
	for(int i=0;i<num;i++)
		coflow[i]=Coflow(i+1);
}

//��ӡ��������Ϣ
void PrintFlowInfo(Flow *flow)
{
	for(int i=0;i<NUMOFFLOW;i++)
	{
		flow[i].print();
	}
}

//������
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