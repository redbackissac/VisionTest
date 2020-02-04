#pragma once
//ѭ��������ģ�嶨��
template <typename ElemType>
class CQueue
{/*
private:
	ElemType **base;   //ָ���ָ�루һάָ�����飩�����д洢�ռ��ַ
	int front;  //��ͷ����		
	int rear;   //��β����
	int QueueSize; //��������*/
public:
	CQueue(int m);  //�вι���
	~CQueue();      //�������������ٶ���
	ElemType **base;   //ָ���ָ�루һάָ�����飩�����д洢�ռ��ַ
	int front;  //��ͷ����		
	int rear;   //��β����
	int QueueSize; //��������
	void EnQueue(ElemType *e);   //���
	ElemType *DeQueue();         //����
	ElemType *GetHead();         //��ȡ��ͷԪ��
	ElemType *GetLast();         //��ȡ��βԪ��
	bool isEmpty();              //�ж��Ƿ�ӿ�
	bool isFull();               //�ж��Ƿ����
};
