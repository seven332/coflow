//定义调度器
//调度算法包括：
//FIFO调度算法
//基于coflow识别的多级优先权队列调度算法

#pragma once

#include "Generator.h"

class Scheduler
{
public:
	Scheduler(void);
	~Scheduler(void);
	void MINCCT(Flow *flow, Coflow *coflow);
	void FIFO(Flow *flow, Coflow *coflow);
	void MPQ(Flow *flow, Coflow *coflow);
	void ClassifyByCotag(Flow *flow, Coflow *coflow);
	float FinishTime(Flow *flow);
	float CCT(Coflow *coflow);
	static bool comparebycosize(Coflow a,Coflow b);
};

