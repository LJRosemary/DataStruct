//循环队列：顺序实现
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>

#define MAXQSIZE 5

typedef enum {error, ok} status;
typedef int Elemtype;
typedef struct {
	Elemtype *base;
	int front;
	int rear;
}SqQueue;

status InitQueue(SqQueue &Q);
status DestoryQueue(SqQueue &Q);
status ClearQueue(SqQueue &Q);
status QueueEmpty(SqQueue Q);
int QueueLength(SqQueue Q);
status GetHead(SqQueue Q, Elemtype &e);
status EnQueue(SqQueue &Q, Elemtype e);
status DeQueue(SqQueue &Q, Elemtype &e);
status visit(Elemtype p);
status QueueTraverse(SqQueue Q, status visit(Elemtype));

//初始化
status InitQueue(SqQueue &Q) {
	Q.base = (Elemtype *)malloc(MAXQSIZE * sizeof(Elemtype));
	if (!Q.base)
		return error;
	Q.front = Q.rear = 0;
	return ok;
}
//销毁
status DestoryQueue(SqQueue &Q) {
	free(Q.base);
	return ok;
}
//清空
status ClearQueue(SqQueue &Q) {
	Q.front = Q.rear = 0;
	return ok;
}
//是否为空
status QueueEmpty(SqQueue Q) {
	if (Q.front == Q.rear)
		return ok;
	else
		return error;
}
//长度
int QueueLength(SqQueue Q) {
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}
//队头
status GetHead(SqQueue Q, Elemtype &e) {
	e = Q.base[Q.front];
	return ok;
}
//入队列
status EnQueue(SqQueue &Q, Elemtype e) {
	if ((Q.rear + 1) % MAXQSIZE == Q.front)
		return error;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	return ok;
}
//出队列
status DeQueue(SqQueue &Q, Elemtype &e) {
	if (Q.front == Q.rear)
		return error;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	return ok;
}
//输出单个元素
status visit(Elemtype p) {
	printf("元素的值为：%d\n", p);
	return ok;
}
//遍历
status QueueTraverse(SqQueue Q, status visit(Elemtype)) {
	while (Q.front != Q.rear) {
		visit(Q.base[Q.front]);
		Q.front = (Q.front + 1) % MAXQSIZE;
	}
	return ok;
}
////测试
//int main()
//{
//	SqQueue Q;
//	if (!(InitQueue(Q))) {
//		printf("初始化错误！\n");
//		system("pause");
//		exit(0);
//	}
//	EnQueue(Q, 233);
//	int e;
//	GetHead(Q, e);
//	printf("e = %d\n", e);
//	ClearQueue(Q);
//	if (QueueEmpty(Q))
//		printf("Empty!\n");
//	else
//		printf("Not Empty!\n");
//	for (int i = 0; i < 10; i++)
//		EnQueue(Q, i);
//	QueueTraverse(Q, visit);
//	printf("Length = %d\n", QueueLength(Q));
//	int a;
//	DeQueue(Q, a);
//	printf("a = %d\n", a);
//	printf("Length = %d\n", QueueLength(Q));
//
//	DestoryQueue(Q);
//	system("pause");
//    return 0;
//}

