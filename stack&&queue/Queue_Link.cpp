//链队列
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>

typedef enum {error, ok} status;
typedef int Elemtype;
typedef struct QNode {
	Elemtype data;
	QNode *next;
}*Queueptr;
typedef struct {
	Queueptr front;
	Queueptr rear;
}LinkQueue;

status InitQueue(LinkQueue &Q);
status DestoryQueue(LinkQueue &Q);
status ClearQueue(LinkQueue &Q);
status QueueEmpty(LinkQueue Q);
int QueueLength(LinkQueue Q);
status GetHead(LinkQueue Q, Elemtype &e);
status EnQueue(LinkQueue &Q, Elemtype e);
status DeQueue(LinkQueue &Q, Elemtype &e);
status visit(QNode p);
status QueueTraverse(LinkQueue Q, status visit(QNode));

//初始化
status InitQueue(LinkQueue &Q) {
	Q.front = Q.rear = (QNode *)malloc(sizeof(QNode));
	if (!Q.front)
		return error;
	Q.front->next = NULL;
	return ok;
}
//清空
status ClearQueue(LinkQueue &Q) {
	QNode *p;
	while (Q.front->next != NULL) {
		p = Q.front->next;
		Q.front->next = p->next;
		free(p);
	}
	Q.rear = Q.front;
	return ok;
}
//销毁
status DestoryQueue(LinkQueue &Q) {
	ClearQueue(Q);
	free(Q.front);
	Q.front = Q.rear = NULL;
	return ok;
}
//是否为空
status QueueEmpty(LinkQueue Q) {
	if (Q.front == Q.rear)
		return ok;
	else
		return error;
}
//长度
int QueueLength(LinkQueue Q) {
	int i = 0;
	while (Q.front != Q.rear) {
		i++;
		Q.front = Q.front->next;
	}
	return i;
}
//队头
status GetHead(LinkQueue Q, Elemtype &e) {
	if (Q.front == Q.rear)
		return error;
	e = Q.front->next->data;
	return ok;
}
//入队列
status EnQueue(LinkQueue &Q, Elemtype e) {
	QNode *p;
	p = (QNode *)malloc(sizeof(QNode));
	if (!p)
		return error;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	/*if (Q.front->next == NULL)
		printf("33\n");*/
	/*if (Q.front->next == Q.rear)
		printf("33\n");*/
	return ok;
}
//出队列
status DeQueue(LinkQueue &Q, Elemtype &e) {
	QNode *p;
	if (Q.front == Q.rear)
		return error;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	//if (p == Q.rear)
	//	printf("44\n");
	if (p == Q.rear)
		Q.rear = Q.front;
	free(p);
	return ok;
}
//输出一个节点
status visit(QNode p) {
	printf("该节点的值为：%d\n", p.data);
	return ok;
}
//遍历
status QueueTraverse(LinkQueue Q, status visit(QNode)) {
	while (Q.front->next != NULL) {
		visit(*Q.front->next);
		Q.front = Q.front->next;
	}
	return ok;
}
////测试
//int main()
//{
//	LinkQueue Q;
//	if (!InitQueue(Q)) {
//		printf("初始化失败！\n");
//		system("pause");
//		exit(0);
//	}
//	EnQueue(Q, 233);
//	int e;
//	GetHead(Q, e);
//	printf("e = %d\n", e);
//	//int a;
//	//DeQueue(Q, a);
//	ClearQueue(Q);
//	if (QueueEmpty(Q))
//		printf("Empty!\n");
//	else
//		printf("Not Empty!\n");
//	for (int i = 0; i < 10; i++) {
//		EnQueue(Q, i);
//	}
//	QueueTraverse(Q, visit);
//	printf("Length = %d\n", QueueLength(Q));
//	int b;
//	DeQueue(Q, b);
//	printf("b = %d\n", b);
//	printf("Length = %d\n", QueueLength(Q));
//	DestoryQueue(Q);
//	system("pause");
//    return 0;
//}

