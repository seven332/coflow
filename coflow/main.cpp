#include "main.h"

//初始化coflow数组
void InitCoflow(Coflow  *coflow, int num)
{
	for(int i=0;i<num;i++)
		coflow[i]=Coflow(i+1);
}

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

}