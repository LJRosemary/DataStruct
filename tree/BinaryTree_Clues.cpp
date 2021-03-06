//线索二叉树
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>

typedef char TElemtype;
typedef enum {error, ok} status;
typedef enum {Link, Thread} Pointertag;
typedef struct BiThrNode {
	TElemtype data;
	struct BiThrNode *lchild, *rchild;
	Pointertag LTag, RTag;
}*BiThrTree;
BiThrNode *pre;//全局变量

status CreateBiTree(BiThrTree &T) {
	char ch;
	scanf_s("%c", &ch);
	if (ch == '#')
		T = NULL;
	else {
		T = (BiThrNode *)malloc(sizeof(BiThrNode));
		if (!T)
			return error;
		T->data = ch;
		T->LTag = T->RTag = Link;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return ok;
}

status DestoryBiTree(BiThrTree &T) {
	while (T) {
		if(T->LTag == Link)
			DestoryBiTree(T->lchild);
		if(T->RTag == Link)
			DestoryBiTree(T->rchild);
		free(T);
		T = NULL;
	}
	return ok;
}

status PreThreading(BiThrTree &T) {
	if (T) {
		if (T->lchild == NULL) {
			T->LTag = Thread;
			T->lchild = pre;
		}
		if (pre->rchild == NULL) {
			pre->RTag = Thread;
			pre->rchild = T;
		}
		pre = T;
		if(T->LTag == Link)//防止线索化时进入死循环
			PreThreading(T->lchild);
		if(T->RTag == Link)
			PreThreading(T->rchild);
	}
	return ok;
}

status PreorderThreading(BiThrTree &Thrt, BiThrTree &T) {
	Thrt = (BiThrNode *)malloc(sizeof(BiThrNode));
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if (T == NULL)
		Thrt->lchild = Thrt;
	else {
		Thrt->lchild = T;
		pre = Thrt;
		PreThreading(T);
		pre->rchild = Thrt;
		pre->RTag = Thread;
		Thrt->rchild = pre;
	}
	return ok;
}

status PreorderTraverse(BiThrTree Thrt) {
	BiThrTree p;
	p = Thrt->lchild;
	while (p != Thrt) {
		printf("%2c", p->data);
		if (p->LTag == Link)
			p = p->lchild;
		else
			p = p->rchild;
	}
	return ok;
}

status InThreading(BiThrTree &T) {
	if (T) {
		InThreading(T->lchild);
		if (T->lchild == NULL) {
			T->LTag = Thread;
			T->lchild = pre;
		}
		if (pre->rchild == NULL) {
			pre->RTag = Thread;
			pre->rchild = T;
		}
		pre = T;
		InThreading(T->rchild);
	}
	return ok;
}

status InorderThreading(BiThrTree &Thrt, BiThrTree &T) {
	Thrt = (BiThrNode *)malloc(sizeof(BiThrNode));
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if (T == NULL)
		Thrt->lchild = Thrt;
	else {
		Thrt->lchild = T;
		pre = Thrt;
		InThreading(T);
		pre->rchild = Thrt;
		pre->RTag = Thread;
		Thrt->rchild = pre;
	}
	return ok;
}

status InorderTraverse(BiThrTree Thrt) {
	BiThrTree p;
	p = Thrt->lchild;
	while (p != Thrt) {
		while (p->LTag == Link)
			p = p->lchild;
		printf("%2c", p->data);
		while (p->RTag == Thread && p->rchild != Thrt) {
			p = p->rchild;
			printf("%2c", p->data);
		}
		p = p->rchild;
	}
	return ok;
}

status PostThreading(BiThrTree &T) {
	if (T) {
		PostThreading(T->lchild);
		PostThreading(T->rchild);
		if (T->lchild == NULL) {
			T->LTag = Thread;
			T->lchild = pre;
		}
		if (pre->rchild == NULL) {
			pre->RTag = Thread;
			pre->rchild = T;
		}
		pre = T;
	}
	return ok;
}

status PostorderThreading(BiThrTree &Thrt, BiThrTree &T) {
	Thrt = (BiThrNode *)malloc(sizeof(BiThrNode));
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if (T == NULL)
		Thrt->lchild = Thrt;
	else {
		Thrt->lchild = T;
		pre = Thrt;
		PostThreading(T);
		pre->rchild = Thrt;
		pre->RTag = Thread;
		Thrt->rchild = pre;
	}
	return ok;
}

////无法遍历到双亲节点，无法实现遍历
//status PostorderTraverse(BiThrTree Thrt) {
//	BiThrTree p;
//	p = Thrt->lchild;
//	while (p != Thrt) {
//		while (p->LTag == Link) {
//			p = p->lchild;
//		}
//		while (p->RTag == Thread) {
//			printf("%2c", p->data);
//			p = p->rchild;
//		}
//
//	}
//}

int main()
{
	BiThrTree T1 = NULL, Thrt1 = NULL;
	BiThrTree T2 = NULL, Thrt2 = NULL;
	BiThrTree T3 = NULL, Thrt3 = NULL;
	CreateBiTree(T1);
	PreorderThreading(Thrt1, T1);
	PreorderTraverse(Thrt1);
	printf("\n");
	DestoryBiTree(Thrt1);
	getchar();
	CreateBiTree(T2);
	InorderThreading(Thrt2, T2);
	InorderTraverse(Thrt2);
	printf("\n");
	DestoryBiTree(Thrt2);
	getchar();
	CreateBiTree(T3);
	PostorderThreading(Thrt3, T3);
	//PreorderTraverse(Thrt2);
	printf("\n");
	DestoryBiTree(Thrt3);
	system("pause");
    return 0;
}

