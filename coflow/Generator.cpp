#include "Generator.h"


Generator::Generator(void)
{
}


Generator::~Generator(void)
{
}

//������������ɺ���
//�����ƶ���Χ�ڵ��������
int Generator::random(int l ,int h)
{
	return rand()%(h-l)+l;
}

//������֮��ıȽϺ���
//�������ĵ���ʱ��Ƚϴ�С,����
bool Generator::compare(Flow a, Flow b)
{
	if(a.getTime()<b.getTime())
		return true;
	else
		return false;
}

//����ģ������
void Generator::produce(Flow *flow)
{
	int tag=0;	
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
	sort(flow,flow+NUMOFFLOW,compare);
}