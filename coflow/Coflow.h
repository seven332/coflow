#pragma once
#include "flow.h"
#include <vector>
using namespace std;

//��������ڵ�
//���ڼ�¼coflow�а������������Լ���������
typedef struct FLOWNODE
{
	Flow flow;
	bool dispatch;
}FlowNode;

class Coflow
{
private:
	int cotag;		//coflow��ʶ
	int size;		//�ѷ��ʹ�С
	vector<FlowNode> flowtable;	//coflow������
public:
	Coflow(void);
	Coflow(int m_cotag);	//���ι��캯��
	~Coflow(void);
	int getCotag();
	int getSize();
	void InsertFlow(Flow flow);
};

