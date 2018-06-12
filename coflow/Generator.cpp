#include "Generator.h"


Generator::Generator(void)
{
}


Generator::~Generator(void)
{
}

//定义随机数生成函数
//生成制定范围内的随机整数
int Generator::random(int l ,int h)
{
	return rand()%(h-l)+l;
}



//生成模拟数据
void Generator::produce(Flow *flow)
{
	int tag=1;	
	srand((unsigned)time(NULL));
	for(int i = 0;i< NUMOFCOFLOW;i++)
	{
		int range=BANDWIDTH/NUMOFCOFLOW;
		int mean=range*(i+1);
		for(int j = 0;j < NUMPERCOFLOW;j++)
		{
			int size=random(mean-range+1,mean+range);
			Flow f(tag,size,j,i+1);
			tag++;
			flow[i*NUMPERCOFLOW+j]=f;
		}
	}
}