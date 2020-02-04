#pragma once
//循环队列类模板定义
template <typename ElemType>
class CQueue
{/*
private:
	ElemType **base;   //指针的指针（一维指针数组），队列存储空间基址
	int front;  //队头索引		
	int rear;   //队尾索引
	int QueueSize; //队列容量*/
public:
	CQueue(int m);  //有参构造
	~CQueue();      //析构函数：销毁队列
	ElemType **base;   //指针的指针（一维指针数组），队列存储空间基址
	int front;  //队头索引		
	int rear;   //队尾索引
	int QueueSize; //队列容量
	void EnQueue(ElemType *e);   //入队
	ElemType *DeQueue();         //出队
	ElemType *GetHead();         //获取队头元素
	ElemType *GetLast();         //获取队尾元素
	bool isEmpty();              //判断是否队空
	bool isFull();               //判断是否队满
};
