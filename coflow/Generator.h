//定义数据生成器,用于生成模拟数据

#pragma once

#include "Flow.h"
#include "Coflow.h"
#include <ctime>
#include <algorithm>

#define NUMOFFLOW 100		//定义流总数 
#define NUMOFCOFLOW 10		//定义coflow总数
#define NUMPERCOFLOW 10		//定义每个coflow中流数目
#define BANDWIDTH 100		//定义带宽

class Generator
{
public:
	Generator(void);
	~Generator(void);
	int random(int l, int h);	//生成制定范围内的随机整数
	void produce(Flow *flow);	//生成模拟数据
};

