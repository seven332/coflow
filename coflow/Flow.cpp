#include "Flow.h"



Flow::Flow(void)
{
}


Flow::~Flow(void)
{
}

//�вι��캯��
Flow::Flow(int m_flowtag, int m_size, int m_time, int m_cotag, int m_tag)
{
	flowtag=m_flowtag;
	size=m_size;
	time=m_time;
	cotag=m_cotag;
	tag=m_tag;
}

//��ȡ����ǩ
int Flow::getFlowtag()
{
	return flowtag;
}

//��ȡ����С
int Flow::getSize()
{
	return size;
}

//��ȡ������ʱ��
int Flow::getTime()
{
	return time;
}

//��ȡ����coflow��־
int Flow::getCotag()
{
	return cotag;
}

//��ȡʵ�ʷ�����
int Flow::getTag()
{
	return tag;
}