//线性表的链式存储：循环链表
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum { error, ok } status;
typedef int Elemtype;
typedef struct LNode {
	Elemtype data;
	LNode *next;
}*Linklist;

status init(Linklist &L);
status destory(Linklist &L);
status ClearList(Linklist &L);
status is_empty(Linklist L);
Elemtype list_length(Linklist L);
status priorElem(Linklist L, int index, LNode &pre);
status nextElem(Linklist L, int index, LNode &next);
status GetElem(Linklist L, int i, Elemtype &e);
status compare(LNode p, LNode q);
Elemtype LocateElem(Linklist L, LNode *e, status(*compare)(LNode, LNode));
status ListInsert(Linklist &L, int i, Elemtype e);
status ListDelete(Linklist &L, int i, Elemtype &e);
status visit(LNode p);
status ListTraverse(Linklist L, status visit(LNode));
//初始化
status init(Linklist &L) {
	if (!(L = (LNode *)malloc(sizeof(LNode))))
		return error;
	L->next = L;
	return ok;
}
//清空线性表
status ClearList(Linklist &L) {
	LNode *p;
	while (L->next != L) {
		p = L->next;
		L->next = p->next;
		free(p);
	}
	return ok;
}
//销毁线性表
status destory(Linklist &L) {
	ClearList(L);
	free(L);
	L = NULL;
	return ok;
}
//是否为空线性表
status is_empty(Linklist L) {
	if (L->next == L)
		return ok;
	else
		return error;
}
//线性表长度
Elemtype list_length(Linklist L) {
	int i = 0;
	LNode *p;
	p = L;
	//visit(*L);
	while (L->next != p)
	{
		//visit(*L->next);
		//system("pause");
		i++;
		L = L->next;
	}
	return i;
}
//求节点前驱
status priorElem(Linklist L, int index, LNode &pre) {
	if (index < 1 || list_length == 0 || index > list_length(L) - 1)
		return error;
	for (int i = 0; i < index; i++) {
		L = L->next;
	}
	pre = *L;
	return ok;
}
//求节点后继
status nextElem(Linklist L, int index, LNode &next) {
	if (index < 0 || list_length(L) == 0 || index >= list_length(L) - 1)
		return error;
	for (int i = 0; i <= index; i++) {
		L = L->next;
	}
	next = *L->next;
	return ok;
}
//获取该位置的值
status GetElem(Linklist L, int i, Elemtype &e) {
	if (i < 0 || i > list_length(L) || list_length(L) == 0)
		return error;
	for (int j = 0; j <= i; j++)
		L = L->next;
	e = L->data;
	return ok;
}
//比较节点是否相同
status compare(LNode p, LNode q) {
	if (p.data == q.data)
		return ok;
	else
		return error;
}
//根据节点求索引值
Elemtype LocateElem(Linklist L, LNode *e, status(*compare)(LNode, LNode)) {
	LNode *p;
	int i = 0;
	p = L->next;
	while (p || !(compare(*p, *e))) {
		p = p->next;
		i++;
	}
	if (i < list_length(L))
		return i;
	else
		return error;
}
//输出节点值
status visit(LNode p) {
	printf("该节点的值是：%d\n", p.data);
	return ok;
}
//遍历
status ListTraverse(Linklist L, status visit(LNode)) {
	LNode *p;
	p = L;
	while (L->next != p) {
		visit(*L->next);
		L = L->next;
	}
	return ok;
}
//插入
status ListInsert(Linklist &L, int i, Elemtype e) {
	LNode *p;
	LNode *temp;
	temp = (LNode *)malloc(sizeof(LNode));
	temp->data = e;
	p = L;
	if (i < 0 || i > list_length(L))
		return error;
	for (int j = 0; j < i; j++) {
		p = p->next;
	}
	if (i != list_length(L)) {
		temp->next = p->next;
		p->next = temp;
	}
	else {
		p->next = temp;
		temp->next = L;
	}

	return ok;
}
//删除
status ListDelete(Linklist &L, int i, Elemtype &e) {
	LNode *p;
	LNode *temp;
	p = L;
	if (i < 0 || i >= list_length(L))
		return error;
	for (int j = 0; j < i; j++) {
		p = p->next;
		//printf("1\n");
	}
	temp = p->next;
	p->next = temp->next;
	e = temp->data;
	free(temp);
	return ok;
}

//测试
//int main()
//{
//	Linklist L;
//	Elemtype e;
//	if (!init(L)) {
//		printf("初始化失败！\n");
//		system("pause");
//		exit(0);
//	}
//	printf("%d\n", list_length(L));
//	Elemtype a = 1;
//	if (ListInsert(L, 0, a)) {
//		printf("插入成功！\n");
//		visit(*L->next);
//	}
//	else
//		printf("插入失败！\n");
//	if (L->next->next == L)
//		printf("ok!\n");
//	printf("2\n");
//	if (!ListDelete(L, 0, e)) {
//		printf("删除失败！\n");
//	}
//	printf("e = %d\n", e);
//	ClearList(L);
//	if (is_empty(L))
//		printf("清理成功！\n");
//	for (int j = 0; j < 10; j++) {
//		ListInsert(L, 0, j);
//		printf("插入的数据是：%d\n", j);
//		printf("线性表长度为：%d\n", list_length(L));
//	}
//	system("pause");
//	ListTraverse(L, visit);
//	
//	Elemtype c;
//	GetElem(L, 5, c);
//	printf("序号为5的对应数据为：%d\n", c);
//	Elemtype b;
//	printf("线性表长度是：%d\n", list_length(L));
//	for (int j = 0; j < 10; j++) {
//		ListDelete(L, 0, b);
//		printf("删除的数据为：%d\n", b);
//		printf("线性表长度为：%d\n", list_length(L));
//	}
//
//	destory(L);
//	system("pause");
//    return 0;
//}
