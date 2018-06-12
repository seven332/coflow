//定义调度器
//调度算法包括：
//FIFO调度算法
//基于coflow识别的多级优先权队列调度算法

#pragma once

#include "Generator.h"
#include <queue>

class Scheduler
{
private:
	vector<Flow> recvq;	//流接收队列
public:
	Scheduler(void);
	~Scheduler(void);
	void UpdateRecvq(Flow *flow, float time);			//更新接收队列
	float SendFlow(Flow f, float time);					//发送指定流
	void UpdateCoflowFinishtime(Coflow *coflow, Flow f);//更新制定流所属coflow完成时间
	void UpdateCoflowFlowtable(Coflow *coflow);			//更新Coflow流表
	void MINCCT(Flow *flow, Coflow *coflow);			//最小coflow平均完成时间调度方案
	void NEWMIN(Flow *flow, Coflow *coflow);
	void FIFO(Flow *flow, Coflow *coflow);				//FIFO调度算法
	void MPQ(Flow *flow, Coflow *coflow);				//多级优先权调度队列
	void ClassifyByCotag(Flow *flow, Coflow *coflow);	//按照Coflow标识将流添加至coflow中
	float FinishTime(Flow *flow);						//计算所有流传输完成所需时间
	float CCT(Coflow *coflow);							//Coflow平均完成时间
	static bool comparebycosize(Coflow a,Coflow b);		//对比两个coflow的大小,升序
	static bool comparebytime(Flow a, Flow b);			//根据流的到达时间比较大小,升序
	static bool comparebyflowtag(Flow a, Flow b);		//根据流的标识比较大小,升序
};

