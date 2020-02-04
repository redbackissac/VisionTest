#include "CQueue.h"
#pragma execution_character_set("utf-8")


template <typename ElemType>
CQueue<ElemType>::CQueue(int m)
{
	/*
	      �вι���
	*/
	//1.��ʼ������ָ������
	this->base = (ElemType **)malloc((m + 1) * sizeof(ElemType *)); //���ڶ�β��һ��Ԫ�����գ��������ֶӿն������ʶ���һ���ռ�
	//2.��ʼ״̬����ͷ��βָ�� �±�����0
	this->front = 0;
	this->rear = 0;
	//3.��������
	this->QueueSize = m + 1;
}

template <typename ElemType>
CQueue<ElemType>::~CQueue()
{
	/*
	    �������������ٶ���
		ע��������һάָ�����飬������Ԫ�ض���
	*/
	if (this->base == NULL)
	{
		return;
	}
	delete[] this->base;
}

template <typename ElemType>
void CQueue<ElemType>::EnQueue(ElemType *e)
{
	/*
	       ���
	*/
	//1.���ǰ�ж϶���
	if (isFull())
	{
		return;
	}
	//2.��β��ֵ
	*(this->base + this->rear) = e;
	//3.��β����+1
	this->rear = (this->rear + 1) % this->QueueSize;//�Զӳ�ȡ��%������ʵ���±�����ѭ��
}

template <typename ElemType>
ElemType *CQueue<ElemType>::DeQueue()
{
	/*
	       ����
	*/
	//1.����ǰ�ӿ��ж�
	if (isEmpty())
	{
		return NULL;
	}
	//2.ȡ��ͷԪ�س���
	ElemType *e = *(this->base + front);
	//3.��ͷ����+1
	this->front = (this->front + 1) % this->QueueSize; //�Զӳ�ȡ��%������ʵ���±�����ѭ��
	return e;
}

template <typename ElemType>
ElemType *CQueue<ElemType>::GetHead()
{
	/*
	      ȡ��ͷԪ��
	*/
	//1.ȡ��ͷԪ��ǰ���ж϶ӿ�
	if (isEmpty())
	{
		return NULL;
	}
	//2.ȡ��ͷԪ��
	return *(this->base + this->front);
}

template <typename ElemType>
ElemType *CQueue<ElemType>::GetLast()
{
	/*
	       ȡ��βԪ��
	*/
	//1.ȡ��βԪ��ǰ���ж϶ӿ�
	if (isEmpty)
	{
		return NULL;
	}
	//2.ȡ��βԪ�أ�rearǰ�Ƽ�1
	return *(this->base + (this->rear - 1 + this->QueueSize) % this->QueueSize);
}

template <typename ElemType>
bool CQueue<ElemType>::isFull()
{
	/*
	       �ж��Ƿ����
	*/
	return (this->rear + 1) % this->QueueSize == this->front ? true : false;
}

template <typename ElemType>
bool CQueue<ElemType>::isEmpty()
{
	/*
	       �ж��Ƿ�ӿ�
	*/
	return this->rear == this->front ? true : false;
}