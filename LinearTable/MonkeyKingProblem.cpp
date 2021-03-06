//猴王问题
//某森林中有n只猴子要选举猴王，所有的猴子都相当猴王，因此商量了一个办法：
//所有的猴子围成一圈，先从第一个猴子开始报数，报数到13的猴子就出列，紧接着下一个猴子有从1开始进行新一轮的报数
//报数到12的猴子再出列，依次重复下去，每一轮的报数都比上一轮少1，知道报数减到一之后，又从13开始报数
//直到原列中只剩下一个为止，这个猴子就是猴王
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum { error, ok }status;
typedef int Elemtype;
typedef struct LNode{
	Elemtype data;
	LNode *next;
}*Linklist;

status Create_list(Linklist &L, Elemtype n);
status Monkey(Linklist &L);
//创建猴子链，从0开始编号
status Create_list(Linklist &L, Elemtype n) {
	LNode *p, *q;
	if (!(L = (LNode *)malloc(sizeof(LNode))))
		return error;
	L->data = 0;
	L->next = L;
	q = L;
	for (int i = 1; i < n; i++) {
		p = (LNode *)malloc(sizeof(LNode));
		p->data = i;
		p->next = q->next;
		q->next = p;
		q = q->next;
	}
	return ok;
}
//计数计算
status Monkey(Linklist &L) {
	LNode *q;//准备删除的节点
	LNode *p;//计数到的节点
	p = L;
	for (int i = 13; i > 0; --i) {
		for (int j = 1; j < i-1; j++) {
			//printf("%d ", p->data);
			p = p->next;	
		}
		//printf("\n");
		if (p->next == p)
			break;
		if (i == 1)
			i = 13;
		q = p->next;
		p->next = q->next;
		p = p->next;
		//printf("第%d轮删除的元素是：%d\n", 13-i+1,  q->data);
		free(q);
		//printf("i = %d\n", i);
	}
	printf("最后一个猴子的编号为：%d\n", p->data);
	return ok;
}

int main()
{
	Linklist L;
	Elemtype n;
	printf("请输入猴子个数n：\n>>>");
	scanf_s("%d", &n);
	Create_list(L, n);
	Monkey(L);
	system("pause");
    return 0;
}

