//二叉树的基本操作
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 100

typedef enum {error, ok} status;
typedef char TElemtype;
typedef struct BiTNode {
	TElemtype data;
	struct BiTNode *lchild, *rchild;
}*BiTree;
typedef struct QNode {
	BiTNode b;
	QNode *next;
};
typedef struct BiQueue {
	struct QNode *front;
	struct QNode *rear;
};
typedef struct SNode {
	BiTNode e;
	SNode *next;
} *BiStack;

status CreateBiTree(BiTree &T);//按定义构造二叉树
status InitBiTree(BiTree &T);// 构造空二叉树
status ClearBiTree(BiTree &T);//清空树T
BiTNode Root(BiTree T);//返回树T的根
status BiTreeEmpty(BiTree T);//判断树T是否为空
int BiTreeDepth(BiTree T);//求树T的深度
TElemtype Value(BiTree T, BiTNode e);//返回T中某节点e的值
TElemtype Parent(BiTree T, BiTNode e);//返回T中某节点e的父节点的值
TElemtype LeftChild(BiTree T, BiTNode e);//返回T中某节点e的左孩子的值
TElemtype RightChild(BiTree T, BiTNode e);//返回T中某节点e的右孩子的值
TElemtype LeftSibling(BiTree T, BiTNode e);//返回T中某节点e的左兄弟的值
TElemtype RightSibling(BiTree T, BiTNode e);//返回T中某节点e的左兄弟的值
status Assign(BiTree T, BiTNode &e, TElemtype value);//给节点e赋值为value
status InsertChild(BiTree T, BiTNode p, int LR, BiTree c);//插入子树--c右子树为空
status DeleteChild(BiTree &T, BiTNode p, int LR);//删除节点p的子树
status Visit(BiTNode e);//遍历节点e
status PreOrderTraverse(BiTree T, status Visit(BiTNode e));//树T的前序遍历
status inOrderTraverse(BiTree T, status Visit(BiTNode e));//树T的中序遍历
status PostOrderTraverse(BiTree T, status Visit(BiTNode e));//树T的后序遍历
status LevelOrderTraverse(BiTree T, status Visit(BiTNode e));//树T的层次遍历
status init_queue(BiQueue &q);//初始化树节点队列
status en_queue(BiQueue &q, BiTNode p);//树节点入队列
status de_queue(BiQueue &q, BiTNode &p);//树节点出队列
status queue_empty(BiQueue Q);//队列是否为空
status insert_BiTNode(BiTree &T, TElemtype e);//在指定位置插入树节点
int num_of_BiTNode(BiTree T);//树节点个数
int num_of_leaf(BiTree T);//叶子节点个数
status init_stack(BiStack &s);//初始化树节点栈
status stack_empty(BiStack s);//栈是否为空
status push(BiStack &s, BiTNode e);//树节点入栈
status pop(BiStack &s, BiTNode &p);//树节点出栈
status inOrderTraverse_Iter(BiTree T, status Visit(BiTNode e));//非递归中序遍历
status PreOrderTraverse_Iter(BiTree T, status Visit(BiTNode e));//非递归前序遍历
BiTree Create_tree_pre_in(char *pre, char *in, int n);//根据前序和中序建立树
BiTree Create_tree_post_in(char *post, char *in, int n);//根据中序和后序建立树
int NodeLevel(BiTree T, TElemtype x);//判断某个值在树的哪一层

status InitBiTree(BiTree &T) {
	T = NULL;
	return ok;
}
status CreateBiTree(BiTree &T) {
	char ch;
	scanf_s("%c", &ch);
	if (ch == '#')
		T = NULL;
	else {
		T = (BiTNode *)malloc(sizeof(BiTNode));
		if (!T)
			return error;
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return ok;
}
status ClearBiTree(BiTree &T) {
	while (T != NULL) {
		ClearBiTree(T->lchild);
		ClearBiTree(T->rchild);
		free(T);
		T = NULL;
	}
	return ok;
}
BiTNode Root(BiTree T) {
	return *T;
}
status BiTreeEmpty(BiTree T) {
	if (T == NULL)
		return ok;//空
	else
		return error;//非空
}
int BiTreeDepth(BiTree T) {//每个树的深度都等于它的左子树或右子树中深度最大的一个的深度加一
	int dl=0, dr=0;
	if (T == NULL)
		return 0;
	else {
		dl = BiTreeDepth(T->lchild);
		dr = BiTreeDepth(T->rchild);
		return dl > dr ? dl+1 : dr+1;
	}
}
TElemtype Value(BiTree T, BiTNode e) {
	return e.data;
}
TElemtype Parent(BiTree T, BiTNode e) {
	TElemtype temp1 = NULL, temp2 = NULL;
	if (T == NULL || (T->lchild == NULL && T->rchild == NULL))
		return NULL;
	else if (T->lchild != NULL && T->lchild->data == e.data) {//需先判断是否为空
		return T->data;
	}
	else if (T->rchild != NULL && T->rchild->data == e.data) {
		return T->data;
	}
	else {
		temp1 = Parent(T->lchild, e);
		temp2 = Parent(T->rchild, e);
		if (temp1 != NULL && temp2 == NULL)
			return temp1;
		else if (temp1 == NULL && temp2 != NULL)
			return temp2;
		else
			return NULL;
	}
}
TElemtype LeftChild(BiTree T, BiTNode e) {
	if (e.lchild != NULL)
		return e.lchild->data;
	else
		return NULL;
}
TElemtype RightChild(BiTree T, BiTNode e) {
	if (e.rchild != NULL)
		return e.rchild->data;
	else
		return NULL;
}
TElemtype LeftSibling(BiTree T, BiTNode e) {
	TElemtype temp1 = NULL, temp2 = NULL;
	if (T == NULL)
		return NULL;
	else if (T->lchild != NULL && T->rchild != NULL && T->rchild->data == e.data) {
		return T->lchild->data;
	}
	else {
		temp1 = LeftSibling(T->lchild, e);
		temp2 = LeftSibling(T->rchild, e);
		if (temp1 != NULL && temp2 == NULL)
			return temp1;
		else if (temp1 == NULL && temp2 != NULL)
			return temp2;
		else
			return NULL;
	}
}
TElemtype RightSibling(BiTree T, BiTNode e) {
	TElemtype temp1 = NULL, temp2 = NULL;
	if (T == NULL)
		return NULL;
	else if (T->lchild != NULL && T->rchild != NULL && T->lchild->data == e.data) {
		return T->rchild->data;
	}
	else {
		temp1 = RightSibling(T->lchild, e);
		temp2 = RightSibling(T->rchild, e);
		if (temp1 != NULL && temp2 == NULL)
			return temp1;
		else if (temp1 == NULL && temp2 != NULL)
			return temp2;
		else
			return NULL;
	}
}
status Assign(BiTree T, BiTNode &e, TElemtype value) {
	e.data = value;
	return ok;
}
status InsertChild(BiTree T, BiTNode p, int LR, BiTree c) {
	BiTNode *temp;
	if (LR == 0) {
		temp = p.lchild;
		p.lchild = c;
		c->rchild = temp;
	}
	else if (LR == 1) {
		temp = p.rchild;
		p.rchild = c;
		c->rchild = temp;
	}
	else
		return error;
	return ok;
}
status DeleteChild(BiTree &T, BiTNode p, int LR) {
	if (LR == 0)
		ClearBiTree(p.lchild);
	else if (LR == 1)
		ClearBiTree(p.rchild);
	else
		return error;
	return ok;
}
status Visit(BiTNode e) {
	printf("%2c", e.data);
	return ok;
}
status PreOrderTraverse(BiTree T, status Visit(BiTNode e)) {
	if (T == NULL)
		return ok;
	else {
		Visit(*T);
		PreOrderTraverse(T->lchild, Visit);
		PreOrderTraverse(T->rchild, Visit);
	}
	return ok;
}
status inOrderTraverse(BiTree T, status Visit(BiTNode e)) {
	if (T == NULL)
		return ok;
	else {
		inOrderTraverse(T->lchild, Visit);
		Visit(*T);
		inOrderTraverse(T->rchild, Visit);
	}
	return ok;
}
status PostOrderTraverse(BiTree T, status Visit(BiTNode e)) {
	if (T == NULL)
		return ok;
	else {
		PostOrderTraverse(T->lchild, Visit);
		PostOrderTraverse(T->rchild, Visit);
		Visit(*T);
	}
	return ok;
}
status init_queue(BiQueue &q) {
	q.front = q.rear = (QNode *)malloc(sizeof(QNode));
	if (!q.front)
		return error;
	q.front->next = NULL;
	return ok;
}
status en_queue(BiQueue &q, BiTNode p) {
	QNode *temp, *temp1;
	temp = (QNode *)malloc(sizeof(QNode));
	temp->b = p;
	q.rear->next = temp;
	q.rear = temp;
	q.rear->next = NULL;
	return ok;
}
status de_queue(BiQueue &q, BiTNode &p) {
	QNode *temp;
	if (q.front == q.rear)
		return error;
	temp = q.front->next;
	q.front->next = temp->next;
	p.data = temp->b.data;
	p.lchild = temp->b.lchild;
	p.rchild = temp->b.rchild;
	if (temp == q.rear)
		q.rear = q.front;
	free(temp);
	return ok;
}
status queue_empty(BiQueue Q) {
	if (Q.front == Q.rear)
		return ok;
	else
		return error;
}
status LevelOrderTraverse(BiTree T, status Visit(BiTNode e)) {
	BiQueue Q;
	BiTNode b;
	//int x = 0;
	init_queue(Q);
	if (T != NULL) {
		en_queue(Q, *T);
		while (!queue_empty(Q)) {
			de_queue(Q, b);
			//x++;
			Visit(b);
			if (b.lchild != NULL)
				en_queue(Q, *b.lchild);
			if (b.rchild != NULL)
				en_queue(Q, *b.rchild);
			//printf("第%d层\n", x/2);
		}
	}
	return ok;
}
status insert_BiTNode(BiTree &T, TElemtype e) {
	BiTNode *temp;
	temp = (BiTNode *)malloc(sizeof(BiTNode));
	if (!temp)
		return error;
	temp->data = e;
	temp->lchild = temp->rchild = NULL;
	T = temp;
	return ok;
}
int num_of_BiTNode(BiTree T) {
	if (T == NULL)
		return 0;
	else {
		return num_of_BiTNode(T->lchild) + num_of_BiTNode(T->rchild) + 1;
	}
}
int num_of_leaf(BiTree T) {
	if (T == NULL)
		return 0;
	else if (T->lchild == NULL && T->rchild == NULL) {
		return 1;
	}
	else {
		return num_of_leaf(T->lchild) + num_of_leaf(T->rchild);
	}
}
status init_stack(BiStack &s) {
	s = (SNode *)malloc(sizeof(SNode));
	if (!s)
		return error;
	s->next = NULL;
	return ok;
}
status stack_empty(BiStack s) {
	if (s->next == NULL)
		return ok;
	else
		return error;
}
status push(BiStack &s, BiTNode e) {
	SNode *temp = NULL;
	temp = (SNode *)malloc(sizeof(SNode));
	if (!temp)
		return error;
	//if (&e == NULL)
	//	return error;
	temp->e = e;
	SNode *temp1 = NULL;
	temp1 = s->next;
	s->next = temp;
	temp->next = temp1;
	return ok;
}
status pop(BiStack &s, BiTNode &p) {
	SNode *temp;
	if (s->next == NULL)
		return error;
	//printf("%c\n", s->next->e.data);
	temp = s->next;
	p = temp->e;
	s->next = temp->next;
	free(temp);
	return ok;
}
status inOrderTraverse_Iter(BiTree T, status Visit(BiTNode e)) {
	BiStack S;
	BiTNode *e;
	BiTNode temp;
	init_stack(S);
	e = T;
	while (e || !stack_empty(S)) {
		if (e) {
			push(S, *e);
			e = e->lchild;
			
		}
		else {
			pop(S, temp);
			e = &temp;
			Visit(*e);
			e = e->rchild;
		}
	}
	return ok;
}
status PreOrderTraverse_Iter(BiTree T, status Visit(BiTNode e)) {
	BiStack S;
	BiTNode *e;
	BiTNode temp;
	init_stack(S);
	e = T;
	while (e || !stack_empty(S)) {
		if (e) {
			Visit(*e);
			push(S, *e);
			e = e->lchild;

		}
		else {
			pop(S, temp);
			e = &temp;
			e = e->rchild;
		}
	}
	return ok;
}
////无法实现后序遍历
//status PostOrderTraverse_Iter(BiTree T, status Visit(BiTNode e)) {
//	BiStack S;
//	BiTNode *e;
//	BiTNode temp;
//	init_stack(S);
//	e = T;
//	while (e || !stack_empty(S)) {
//		//if (e != NULL)
//		//Visit(*e);
//		if (e) {
//			push(S, *e);
//			e = e->lchild;
//		}
//		else {
//			pop(S, temp);
//			e = &temp;
//			if (e->rchild != NULL) {
//				Visit(*e->rchild);
//			}	
//			//Visit(*e);
//			e = e->rchild;
//		}
//		//if (e != NULL)
//		//	Visit(*e);
//	}
//	return ok;
//}
//
BiTree Create_tree_pre_in(char *pre, char *in, int n) {
	BiTree T;
	if (n == 0)
		return NULL;
	//InitBiTree(T);
	T = (BiTNode *)malloc(sizeof(BiTNode));
	if (!T)
		return NULL;
	T->data = pre[0];
	char s1[N], s2[N];//中序拆分后序列
	char s3[N], s4[N];//前序
	int n1 = 0, n2 = 0;
	int m1 = 0, m2 = 0;
	for (int i = 0; i < n; i++) {
		if (i <= n1 && in[i] != pre[0])
			s1[n1++] = in[i];
		else if (in[i] != pre[0])
			s2[n2++] = in[i];
	}
	for (int i = 1; i < n; i++) {
		if (i <= n1)
			s3[m1++] = pre[i];
		else
			s4[m2++] = pre[i];
	}
	T->lchild = Create_tree_pre_in(s3, s1, n1);
	T->rchild = Create_tree_pre_in(s4, s2, n2);
	return T;
}
BiTree Create_tree_post_in(char *post, char *in, int n) {
	BiTree T2 = NULL;
	char s1[N], s2[N];//中序拆分后序列
	char s3[N], s4[N];//后序
	int n1 = 0, n2 = 0;
	int m1 = 0, m2 = 0;
	if (n == 0)
		return NULL;
	//InitBiTree(T);
	T2 = (BiTNode *)malloc(sizeof(BiTNode));
	if (!T2)
		return NULL;
	T2->data = post[n-1];
	T2->lchild = NULL;
	T2->rchild = NULL;
	for (int i = 0; i < n; i++) {
		if (i <= n1 && in[i] != post[n-1])
			s1[n1++] = in[i];
		else if (in[i] != post[n-1])
			s2[n2++] = in[i];
	}
	for (int i = 0; i < n-1; i++) {
		if (i < n1)
			s3[m1++] = post[i];
		else
			s4[m2++] = post[i];
	}
	T2->lchild = Create_tree_post_in(s3, s1, n1);
	T2->rchild = Create_tree_post_in(s4, s2, n2);
	return T2;
}
int NodeLevel(BiTree T, TElemtype x) {
	if (T == NULL)
		return error;
	if (T->data == x) {
		return 1;
	}
	else {
		/*int tl = 0, tr = 0;
		if (T->lchild != NULL)
			tl = NodeLevel(T->lchild, x);
		if (T->rchild != NULL)
			tr = NodeLevel(T->rchild, x);
		if (tl == 0 && tr == 0)
			return 0;
		else if (tl != 0)
			return tl+1;
		else if (tr != 0)
			return tr+1;
		else
			return error;*/
		//优化
		int tl = NodeLevel(T->lchild, x);
		if (tl >= 1)
			return tl + 1;
		int tr = NodeLevel(T->rchild, x);
		if (tr >= 1)
			return tr + 1;
		else
			return 0;
	}
}

int main()
{
	BiTree T;
	InitBiTree(T);
	//CreateBiTree(T);
	insert_BiTNode(T, 'A');
	insert_BiTNode(T->lchild, 'B');
	insert_BiTNode(T->rchild, 'C');
	insert_BiTNode(T->lchild->lchild, 'D');
	insert_BiTNode(T->rchild->rchild, 'E');
	insert_BiTNode(T->lchild->lchild->lchild, 'F');
	insert_BiTNode(T->rchild->rchild->rchild, 'G');
	printf("#########Level Test##########\n");
	printf("level = %d\n", NodeLevel(T, 'R'));//不在树节点内则返回0
	printf("#########Level Test##########\n");
	printf("当前树的节点数为：%d\n", num_of_BiTNode(T));
	printf("叶子节点的个数为：%d\n", num_of_leaf(T));
	printf("前序：\n");
	PreOrderTraverse(T, Visit);
	printf("\n");
	printf("中序：\n");
	inOrderTraverse(T, Visit);
	printf("\n");
	printf("后序：\n");
	PostOrderTraverse(T, Visit);
	printf("\n");
	printf("层次：\n");
	LevelOrderTraverse(T, Visit);
	printf("\n");
	printf("前序非递归：\n");
	PreOrderTraverse_Iter(T, Visit);
	printf("\n");
	printf("中序非递归：\n");
	inOrderTraverse_Iter(T, Visit);
	printf("\n");
	//printf("后序非递归：\n");
	//PostOrderTraverse_Iter(T, Visit);
	printf("\n");
	printf("修改某值\n");
	Assign(T, *T->lchild, 'x');
	//Visit(*T->lchild);
	printf("层次：\n");
	LevelOrderTraverse(T, Visit);
	printf("\n");
	printf("所查节点的值为：%c\n", Parent(T, *T->lchild->lchild->lchild));//D
	printf("所查节点的值为：%c\n", LeftSibling(T, *T->rchild));
	printf("所查节点的值为：%c\n", RightSibling(T, *T->lchild));
	printf("树的深度是：%d\n", BiTreeDepth(T));
	

	printf("清空。。。\n");
	ClearBiTree(T);
	if (BiTreeEmpty)
		printf("empty!");
	printf("\n");
	printf("通过前序中序序列获得后序序列：\n");
	BiTree T1;
	char pre[10] = { 'A', 'B', 'D', 'H', 'E', 'C', 'F', 'I', 'G', 'J' };
	char in[10] = { 'H', 'D', 'B', 'E', 'A', 'I', 'F', 'C', 'G', 'J' };
	T1 = Create_tree_pre_in(pre, in, 10);
	//printf("后序：\n");
	PostOrderTraverse(T1, Visit);
	printf("\n");
	ClearBiTree(T1);
	printf("通过中序后序序列获得前序序列：\n");
	BiTree T2;
	char in_[10] = { 'H', 'D', 'B', 'E', 'A', 'I', 'F', 'C', 'G', 'J' };
	char post[10] = { 'H', 'D', 'E', 'B', 'I', 'F', 'J', 'G', 'C', 'A' };
	T2 = Create_tree_post_in(post, in_, 10);
	//printf("前序：\n");
	PreOrderTraverse(T2, Visit);
	printf("\n");
	system("pause");
    return 0;
}

