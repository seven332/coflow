#include "Scheduler.h"


Scheduler::Scheduler(void)
{
}


Scheduler::~Scheduler(void)
{
}

//更新接收队列
//将达到时间小于指定时间的未被调度的流加入到接收队列
//同时修改相应流的状态为已调度
bool Scheduler::UpdateRecvq(Flow *flow, float time)
{
	bool state=false;	//用于判断是否存在未被处理的流
	for(int i=0;i<NUMOFFLOW;i++)
	{
		if((flow[i].getTime()<=time)&&!flow[i].getState())
		{
			recvq.push_back(flow[i]);
			flow[i].setState(true);
			state=true;
		}
	}
	return state;
}

//更新指定coflow流表
//从接收队列取制定coflow的流
//将属于制定coflow中的所有流从接收队列存入coflow
void Scheduler::UpdateFlowtable(Coflow *coflow, int cotag)	
{
	vector<Flow>::iterator it;
	for(it=recvq.begin();it!=recvq.end();)
	{
		//将指定coflow中的流从接收队列取出加入流表
		if(it->getCotag()==cotag)
		{
			//更新coflow大小
			coflow[cotag].setSize(coflow[cotag].getSize()+it->getSize());
			//更新coflow流表
			coflow[cotag].InsertFlow(*it);
			//接收队列中去除响应流
			it=recvq.erase(it);
		}
		else
		{
			it++;
		}
	}
}

//更新Coflow流表
//将接收队列中的流添加至coflow流表
void Scheduler::UpdateCoflowFlowtable(Coflow *coflow)
{
	vector<Flow>::iterator it;
	for(it=recvq.begin();it!=recvq.end();)
	{
		int cotag=it->getCotag();
		//更新coflow大小
		coflow[cotag].setSize(coflow[cotag].getSize()+it->getSize());
		//更新coflow流表
		coflow[cotag].InsertFlow(*it);
		//接收队列中去除响应流
		it=recvq.erase(it);
	}
}

//发送指定流
//根据线速计算发送所需时间
//返回更新后的当前时间
float Scheduler::SendFlow(Flow f, float time)
{
	float finishtime=time+(float)f.getSize()/BANDWIDTH;
	return finishtime;
}

//更新指定流及所属coflow的信息
//信息包括，flow的完成时间，coflow的完成时间，coflow的已发送大小
void Scheduler::UpdateInfo(Flow *flow, Coflow *coflow, Flow f)
{
	int flowtag=f.getFlowtag();
	int cotag=f.getCotag();
	int sentsize=coflow[cotag].getSentsize()+f.getSize();
	flow[flowtag].setFinishtime(f.getFinishtime());
	coflow[cotag].setFinishtime(f.getFinishtime());
	coflow[cotag].setSentsize(sentsize);
}

//计算coflow的待发送大小，依此将之分配到对应的优先级队列
void Scheduler::classifier(Coflow cf)
{
	int size;
	size=cf.getSentsize();

	if(size <= LOWTHRESHOLD)
	{
		ql.push(cf);
	}
	else if(size > LOWTHRESHOLD && size <= HIGHTHRESHOLD)
	{
		qm.push(cf);
	}
	else
	{
		qh.push(cf);
	}
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
		if(flow[i].getFinishtime()==0)
		{
			flow[i].print();
			continue;
		}
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
		//cout<<"Coflow："<<i+1<<"大小为："<<coflow[i].getSize()<<endl;
	}
	return time/NUMOFCOFLOW;
}

//按照Coflow标识将流添加至coflow中
void Scheduler::ClassifyByCotag(Flow *flow, Coflow *coflow)
{
	for(int i=0;i<NUMOFFLOW;i++)
	{
		int cotag=flow[i].getCotag();
		coflow[cotag].setSize(coflow[cotag].getSize()+flow[i].getSize());
		coflow[cotag].InsertFlow(flow[i]);
	}
}

//FIFO调度算法
void Scheduler::FIFO(Flow *flow, Coflow *coflow)
{
	cout<<"--------使用先入先出算法调度--------"<<endl;
	//sort(flow,flow+NUMOFFLOW,comparebytime);	//按照流的到达时间排序
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

		//更新处理后流以及所属coflow完成时间
		UpdateInfo(flow,coflow,f);

		//每个时间单位更新接收队列
		if(time-lastflashtime>=1.0)
		{
			UpdateRecvq(flow,time);
			lastflashtime=time;
		}
	}
	//流调度结束
	cout<<"所有流调度完成时间："<<FinishTime(flow)<<endl;
	cout<<"所有Coflow调度完成的平均时间为："<<CCT(coflow)<<endl;
	cout<<"------------------------------------"<<endl;
}

//最小coflow平均完成时间调度方案
//一种离线分析方法
//在此情况下，已经预先知道了所有coflow的大小，在较小的coflow拥有最高的调度优先级
//这里的方法是近似方法，不会打断当前传输的流，因此CCT会略高于理论值
void Scheduler::MINCCT(Flow *flow, Coflow *coflow)
{
	cout<<"--------NEWMIN--------"<<endl;
	float time=0.0;				//实时更新时间
	float lastflashtime=0.0;	//记录上一次更新流表时间
	UpdateRecvq(flow,time);		//开始更新接收队列

	///////////开始调度//////////////
	while(!recvq.empty())
	{
		for(int i=0;i<NUMOFCOFLOW;i++)
		{
			bool state=false;	//用于判断是否更新了接收队列
			//将接收队列中的流加入相应coflow的流表
			UpdateFlowtable(coflow,i);
			while(!coflow[i].TableEmpty())
			{
				//依次处理流表中的流
				Flow f;
				f=coflow[i].getFlow();
				time=SendFlow(f,time);
				f.setFinishtime(time);
				UpdateInfo(flow,coflow,f);
				//每个时间单位更新接收队列
				if(time-lastflashtime>=1.0)
				{
					if(!UpdateRecvq(flow,time))
					{
						continue;
					}
					lastflashtime=time;
					state=true;
					break;
				}
			}
			if(state) break;
		}
	}
	cout<<"所有流调度完成时间："<<FinishTime(flow)<<endl;
	cout<<"所有Coflow调度完成的平均时间为："<<CCT(coflow)<<endl;
	cout<<"----------------------"<<endl;
}

//多级优先权调度队列
void Scheduler::MPQ(Flow *flow, Coflow *coflow)
{
	cout<<"--------使用基于coflow的多级优先级队列算法调度--------"<<endl;
	float time=0.0;				//实时更新时间
	float lastflashtime=0.0;	//记录上一次更新流表时间
	bool dispatchtable[NUMOFCOFLOW];	//分配记录表
	UpdateRecvq(flow,time);		//开始更新接收队列
	//将接收队列中的流分配到对应coflow
	UpdateCoflowFlowtable(coflow);
	//将coflow分配到相应的优先级队列
	for(int i=0;i<NUMOFCOFLOW;i++)
	{
		classifier(coflow[i]);
		dispatchtable[i]=true;
	}

	////////////开始调度////////////
	while((!ql.empty())||(!qm.empty())||(!qh.empty()))
	{
		int cotag;
		Flow f;
		if(!ql.empty())
		{
			//优先处理q1中的coflow
			//首先取出顶部元素
			cotag=ql.top().getCotag();
			ql.pop();
		}
		else if(!qm.empty())
		{
			cotag=qm.top().getCotag();
			qm.pop();
		}
		else
		{
			cotag=qh.top().getCotag();
			qh.pop();
		}
		//发送其中一条流				
		f=coflow[cotag].getFlow();		
		time=SendFlow(f,time);
		//更新coflow信息和流表
		f.setFinishtime(time);
		UpdateInfo(flow,coflow,f);
		//判断coflow流表是否为空
		//若不为空，根据其信息加入相应优先级队列
		if(!coflow[cotag].TableEmpty())
		{
			classifier(coflow[cotag]);
		}
		//否则，更改分配表，以便后续从新分配
		else
		{
			dispatchtable[cotag]=false;
		}
		//一条流调度完毕后，判断时间，如果时间到，更新接收队列，从新更新coflow流表，更新优先队列内容
		if(time-lastflashtime>=1.0)
		{
			if(UpdateRecvq(flow,time))
			{
				lastflashtime=time;
				//将coflow分配到相应的优先级队列
				//将接收队列中的流分配到对应coflow
				UpdateCoflowFlowtable(coflow);	
				for(int i=0;i<NUMOFCOFLOW;i++)
				{
					if(!dispatchtable[i]&&!coflow[i].TableEmpty())
					{
						//将未被调度的待调度coflow加入优先级队列
						classifier(coflow[i]);		
						dispatchtable[i]=true;		
					}
				}
			}
		}
		//一次处理结束
	}

	cout<<"所有流调度完成时间："<<FinishTime(flow)<<endl;
	cout<<"所有Coflow调度完成的平均时间为："<<CCT(coflow)<<endl;
	cout<<"------------------------------------------------------"<<endl;
}

//重载<用于判断coflow优先级
bool operator < (Coflow a, Coflow b)
{
	if(a.getSentsize()>b.getSentsize())
	{
		return true;
	}
	else if(a.getSentsize()==b.getSentsize())
	{
		if(a.getSize()>b.getSize())
		{
			return true;
		}
		else 
			return false;
	}
	else
	{
		return false;
	}

}