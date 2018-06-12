//����coflow

#pragma once
#include "flow.h"
#include <vector>


////��������ڵ�
////���ڼ�¼coflow�а������������Լ���������
//typedef struct FLOWNODE
//{
//	Flow flow;	//��
//	bool tag;	//���ȱ�־
//}FlowNode;

class Coflow
{
private:
	int cotag;		//coflow��ʶ
	int size;		//coflow��С
	int sentsize;	//�ѷ��ʹ�С
	float finishtime;	//coflow�������ʱ��
	vector<Flow> flowtable;	//coflow������
public:
	Coflow(void);
	Coflow(int m_cotag);	//���ι��캯��
	~Coflow(void);
	int getCotag();
	int getSize();
	int getSentsize();
	float getFinishtime();
	Flow getFlow();
	bool TableEmpty();
	void setSize(int m_size);
	void setSentsize(int m_sentsize);
	void setFinishtime(float time);
	void InsertFlow(Flow flow);
	bool PopFlow(Flow flow);
};

