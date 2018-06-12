#include "Scheduler.h"


Scheduler::Scheduler(void)
{
}


Scheduler::~Scheduler(void)
{
}

//�Ա�����coflow�Ĵ�С,����
bool Scheduler::comparebycosize(Coflow a,Coflow b)
{
	if(a.getSize()<b.getSize())
		return true;
	else
		return false;
}

//������֮��ıȽϺ���
//�������ĵ���ʱ��Ƚϴ�С,����
bool Scheduler::comparebytime(Flow a, Flow b)
{
	if(a.getTime()<b.getTime())
		return true;
	else
		return false;
}

//������֮��ıȽϺ���
//�������ı�ʶ�Ƚϴ�С,����
bool Scheduler::comparebyflowtag(Flow a, Flow b)
{
	if(a.getFlowtag()<b.getFlowtag())
		return true;
	else
		return false;
}

//���������������������ʱ��
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

//Coflowƽ�����ʱ��
float Scheduler::CCT(Coflow *coflow)
{
	float time=0.0;
	for(int i=0;i<NUMOFCOFLOW;i++)
	{
		float cotime=coflow[i].getFinishtime();
		time+=cotime;
		cout<<"Coflow��"<<i+1<<"���ʱ��Ϊ��"<<cotime<<endl;
	}
	return time/NUMOFCOFLOW;
}

//����Coflow��ʶ���������coflow��
void Scheduler::ClassifyByCotag(Flow *flow, Coflow *coflow)
{
	for(int i=0;i<NUMOFFLOW;i++)
	{
		int cotag=flow[i].getCotag()-1;
		coflow[cotag].setSize(coflow[cotag].getSize()+flow[i].getSize());
		coflow[cotag].InsertFlow(flow[i]);
	}
}

//FIFO�����㷨
void Scheduler::FIFO(Flow *flow, Coflow *coflow)
{
	cout<<"--------ʹ�������ȳ��㷨����--------"<<endl;
	sort(flow,flow+NUMOFFLOW,comparebytime);
	float finishtime=0.0;
	for(int i=0;i<NUMOFFLOW;i++)
	{
		finishtime+=(float)flow[i].getSize()/BANDWIDTH;
		flow[i].setFinishtime(finishtime);
		int cotag=flow[i].getCotag()-1;
		coflow[cotag].setFinishtime(finishtime);
	}
	cout<<"�������������ʱ�䣺"<<finishtime<<endl;
	cout<<"����Coflow������ɵ�ƽ��ʱ��Ϊ��"<<CCT(coflow)<<endl;
	cout<<"------------------------------------"<<endl;
}

//��Сcoflowƽ�����ʱ����ȷ���
//һ�����߷�����������Ҫ֪��ȫ��coflow����Ϣ
void Scheduler::MINCCT(Flow *flow, Coflow *coflow)
{
	cout<<"--------ʹ����Сƽ�����ʱ���㷨����--------"<<endl;
	ClassifyByCotag(flow,coflow);						//���Ƚ��������������Ӧcoflow
	sort(coflow,coflow+NUMOFCOFLOW,comparebycosize);	//����coflow��С��������
	sort(flow,flow+NUMOFFLOW,comparebyflowtag);			//����flow�ı����������
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
	cout<<"�������������ʱ�䣺"<<FinishTime(flow)<<endl;
	cout<<"����Coflow������ɵ�ƽ��ʱ��Ϊ��"<<CCT(coflow)<<endl;
	cout<<"--------------------------------------------"<<endl;
}

//�༶����Ȩ���ȶ���
void MPQ(Flow *flow, Coflow *coflow)
{

}