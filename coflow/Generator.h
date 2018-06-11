//��������������,��������ģ������

#pragma once

#include "Flow.h"
#include "Coflow.h"
#include <ctime>
#include <algorithm>

#define NUMOFFLOW 100		//���������� 
#define NUMOFCOFLOW 10		//����coflow����
#define NUMPERCOFLOW 10		//����ÿ��coflow������Ŀ
#define BANDWIDTH 100		//�������

class Generator
{
public:
	Generator(void);
	~Generator(void);
	int random(int l, int h);
	static bool compare(Flow a, Flow b);
	void produce(Flow *flow);
};

