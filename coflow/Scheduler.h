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
	void FIFO(Flow *flow);
	float FinishTime(Flow *flow);
};

