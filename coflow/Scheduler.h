//���������
//�����㷨������
//FIFO�����㷨
//����coflowʶ��Ķ༶����Ȩ���е����㷨

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

