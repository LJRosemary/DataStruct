//栈的基本操作：链式实现
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>

typedef enum {error, ok} status;
typedef struct SNode {
	int data;
	SNode *next;
}*LinkStack;

status InitStack(LinkStack &S);
status DestoryStack(LinkStack &S);
status ClearStack(LinkStack &S);
status StackEmpty(LinkStack S);
int StackLength(LinkStack S);
status GetTop(LinkStack S, int &e);
status Push(LinkStack &S, int e);
status Pop(LinkStack &S, int &e);
status visit(SNode p);
status StackTraverse(LinkStack S, status visit(SNode));

//初始化
status InitStack(LinkStack &S) {
	if (!(S = (SNode *)malloc(sizeof(SNode))))
		return error;
	S->next = NULL;
	return ok;
}
//清空
status ClearStack(LinkStack &S) {
	SNode *p;
	while (S->next) {
		p = S->next;
		S->next = p->next;
		free(p);
	}
	return ok;
}
//销毁
status DestoryStack(LinkStack &S) {
	ClearStack(S);
	free(S);
	S = NULL;
	return ok;
}
//是否为空
status StackEmpty(LinkStack S) {
	if (S->next)
		return error;
	else
		return ok;
}
//长度
int StackLength(LinkStack S) {
	int i = 0;
	while (S->next != NULL) {
		i++;
		S = S->next;
	}
	return i;
}
//获得栈顶元素
status GetTop(LinkStack S, int &e) {
	if (S->next == NULL)
		return error;
	e = S->next->data;
	return ok;
}
//入栈
status Push(LinkStack &S, int e) {
	SNode *p;
	p = (SNode *)malloc(sizeof(SNode));
	p->data = e;
	p->next = S->next;
	S->next = p;
	return ok;
}
//出栈
status Pop(LinkStack &S, int &e) {
	if (S->next == NULL)
		return error;
	SNode *p;
	p = S->next;
	e = p->data;
	S->next = p->next;
	free(p);
	return ok;
}
//输出元素数据
status visit(SNode p) {
	printf("该元素的值为：%d\n", p.data);
	return ok;
}
//遍历
status StackTraverse(LinkStack S, status visit(SNode)) {
	while (S->next != NULL) {
		visit(*S->next);
		S = S->next;
	}
	return ok;
}
//测试
//int main()
//{
//	LinkStack S;
//	if (!InitStack(S)) {
//		printf("初始化错误！\n");
//		system("pause");
//		exit(0);
//	}
//	Push(S, 100);
//	int e;
//	GetTop(S, e);
//	printf("e = %d\n", e);
//	ClearStack(S);
//	if (StackEmpty(S))
//		printf("Empty!\n");
//	else
//		printf("No Empty!\n");
//	for (int i = 0; i < 10; i++) {
//		Push(S, i);
//	}
//	StackTraverse(S, visit);
//	int a;
//	Pop(S, a);
//	printf("a = %d\n", a);
//	printf("Length = %d\n", StackLength(S));
//	system("pause");
//    return 0;
//}

