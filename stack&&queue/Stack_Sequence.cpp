//栈的基本操作：顺序实现
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef enum {error, ok}status;
typedef struct {
	int data;
}SElemtype;

typedef struct {
	SElemtype *top;
	SElemtype *base;
	int stacksize;
}SqStack;

status InitStack(SqStack &S);
status DestoryStack(SqStack &S);
status ClearStack(SqStack &S);
status StackEmpty(SqStack S);
int StackLength(SqStack S);
status GetTop(SqStack S, int &e);
status Push(SqStack &S, int e);
status Pop(SqStack &S, int &e);
status visit(SElemtype p);
status StackTraverse(SqStack S, status visit(SElemtype));

//初始化
status InitStack(SqStack &S) {
	S.base = (SElemtype *)malloc(STACK_INIT_SIZE * sizeof(SElemtype));
	if (!S.base)
		return error;
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return ok;
}
//销毁栈
status DestoryStack(SqStack &S) {
	free(S.base);
	return ok;
}
//清空栈
status ClearStack(SqStack &S) {
	S.top = S.base;
	return ok;
}
//栈是否为空
status StackEmpty(SqStack S) {
	if (S.top == S.base)
		return ok;
	else
		return error;
}
//长度
int StackLength(SqStack S) {
	return (S.top-S.base);
}
//获得栈顶元素
status GetTop(SqStack S, int &e) {
	if (S.top == S.base)
		return error;
	e = (S.top-1)->data	;
	return ok;
}
//入栈
status Push(SqStack &S, int e) {
	//SElemtype *p;
	//p = (SElemtype *)malloc(sizeof(SElemtype));
	if (S.top - S.base >= S.stacksize) {
		S.base = (SElemtype *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemtype));
		if (!S.base)
			return error;
		S.top = S.base + S.stacksize;
		S.stacksize = S.stacksize + STACKINCREMENT;
	}
	
	S.top->data = e;
	S.top++;
	return ok;
}
//出栈
status Pop(SqStack &S, int &e) {
	if (S.base == S.top)
		return error;
	e = (S.top - 1)->data;
	S.top--;
	return ok;
}
//访问一个元素数据
status visit(SElemtype p) {
	printf("该元素的值为：%d\n", p.data);
	return ok;
}
//遍历
status StackTraverse(SqStack S, status visit(SElemtype)) {
	while (S.base != S.top) {
		visit(*(S.top - 1));
		S.top--;
	}
	return ok;
}
//测试
//int main()
//{
//	SqStack S;
//	if (!InitStack(S)) {
//		printf("初始化失败！\n");
//		system("pause");
//		exit(0);
//	}
//	int k = 99;
//	Push(S, k);
//	int j;
//	GetTop(S, j);
//	printf("j = %d\n", j);
//	ClearStack(S);
//	int c = StackLength(S);
//	printf("c = %d\n", c);
//	for (int i = 0; i < 10; i++) {
//		Push(S, i);
//	}
//	StackTraverse(S, visit);
//	int a;
//	Pop(S, a);
//	printf("弹出第一个元素为：%d\n", a);
//	StackTraverse(S, visit);
//	int b;
//	GetTop(S, b);
//	printf("栈顶元素是：%d\n", b);
//	printf("length = %d\n", StackLength(S));
//
//	system("pause");
//    return 0;
//}

