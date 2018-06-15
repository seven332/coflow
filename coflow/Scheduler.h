//定义调度器
//调度算法包括：
//FIFO调度算法
//基于coflow识别的多级优先权队列调度算法

#pragma once

#include "Generator.h"
#include <queue>

#define LOWTHRESHOLD 300
#define HIGHTHRESHOLD 500

class Scheduler
{
private:
	vector<Flow> recvq;				//流接收队列
	priority_queue<Coflow> ql;		//小流优先级队列
	priority_queue<Coflow> qm;		//中等流优先级队列
	priority_queue<Coflow> qh;		//大流优先级队列
public:
	Scheduler(void);
	~Scheduler(void);
	bool UpdateRecvq(Flow *flow, float time);			//更新接收队列
	void UpdateFlowtable(Coflow *coflow, int cotag);	//更新指定coflow流表
	float SendFlow(Flow f, float time);					//发送指定流
	void UpdateInfo(Flow *flow, Coflow *coflow, Flow f);//更新信息
	void UpdateCoflowFlowtable(Coflow *coflow);			//更新Coflow流表
	void classifier(Coflow cf);							//将coflow分配到符合条件的优先级队列中
	void MINCCT(Flow *flow, Coflow *coflow);			//最小coflow平均完成时间调度方案
	void FIFO(Flow *flow, Coflow *coflow);				//FIFO调度算法
	void MPQ(Flow *flow, Coflow *coflow);				//多级优先权调度队列
	void ClassifyByCotag(Flow *flow, Coflow *coflow);	//按照Coflow标识将流添加至coflow中
	float FinishTime(Flow *flow);						//计算所有流传输完成所需时间
	float CCT(Coflow *coflow);							//Coflow平均完成时间
	static bool comparebycosize(Coflow a,Coflow b);		//对比两个coflow的大小,升序
	static bool comparebytime(Flow a, Flow b);			//根据流的到达时间比较大小,升序
	static bool comparebyflowtag(Flow a, Flow b);		//根据流的标识比较大小,升序			
};

