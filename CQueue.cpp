#include "CQueue.h"
#pragma execution_character_set("utf-8")


template <typename ElemType>
CQueue<ElemType>::CQueue(int m)
{
	/*
	      有参构造
	*/
	//1.初始化队列指针数组
	this->base = (ElemType **)malloc((m + 1) * sizeof(ElemType *)); //由于队尾有一个元素留空，用来区分队空队满，故多设一个空间
	//2.初始状态：队头队尾指向 下标索引0
	this->front = 0;
	this->rear = 0;
	//3.队列容量
	this->QueueSize = m + 1;
}

template <typename ElemType>
CQueue<ElemType>::~CQueue()
{
	/*
	    析构函数：销毁队列
		注：仅销毁一维指针数组，不销毁元素对象
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
	       入队
	*/
	//1.入队前判断队满
	if (isFull())
	{
		return;
	}
	//2.队尾赋值
	*(this->base + this->rear) = e;
	//3.队尾后移+1
	this->rear = (this->rear + 1) % this->QueueSize;//对队长取余%，可以实现下标索引循环
}

template <typename ElemType>
ElemType *CQueue<ElemType>::DeQueue()
{
	/*
	       出队
	*/
	//1.出队前队空判断
	if (isEmpty())
	{
		return NULL;
	}
	//2.取队头元素出队
	ElemType *e = *(this->base + front);
	//3.队头后移+1
	this->front = (this->front + 1) % this->QueueSize; //对队长取余%，可以实现下标索引循环
	return e;
}

template <typename ElemType>
ElemType *CQueue<ElemType>::GetHead()
{
	/*
	      取队头元素
	*/
	//1.取队头元素前，判断队空
	if (isEmpty())
	{
		return NULL;
	}
	//2.取队头元素
	return *(this->base + this->front);
}

template <typename ElemType>
ElemType *CQueue<ElemType>::GetLast()
{
	/*
	       取队尾元素
	*/
	//1.取队尾元素前，判断队空
	if (isEmpty)
	{
		return NULL;
	}
	//2.取队尾元素，rear前移减1
	return *(this->base + (this->rear - 1 + this->QueueSize) % this->QueueSize);
}

template <typename ElemType>
bool CQueue<ElemType>::isFull()
{
	/*
	       判断是否队满
	*/
	return (this->rear + 1) % this->QueueSize == this->front ? true : false;
}

template <typename ElemType>
bool CQueue<ElemType>::isEmpty()
{
	/*
	       判断是否队空
	*/
	return this->rear == this->front ? true : false;
}