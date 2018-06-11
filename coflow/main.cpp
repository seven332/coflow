#include "main.h"


int main()
{
	Flow flow[NUMOFFLOW];
	Generator gen;
	Scheduler sch;
	gen.produce(flow);
	sch.FIFO(flow);
	cout<<flow[99].getFinishtime()<<endl;
	//for(int i = 0; i < 10; i++)
	//{
	//	flow[i].print();
	//}
}