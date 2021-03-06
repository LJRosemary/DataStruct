//图:邻接矩阵
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>

#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 100
//#define MAX_WEIGHT 100
typedef int VRType;
typedef char InfoType;
typedef char vertexType;
typedef enum {error, ok} status;
typedef enum {DG, DN, UDG, UDN} GraphKind;//有向图，有向网，无向图，无向网
typedef struct ArcCell {
	VRType adj;//权值
	//InfoType *info;//根据需要建立
}AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {
	vertexType vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum, arcnum;
	GraphKind kind;
}MGraph;
int visit[MAX_VERTEX_NUM];
typedef struct QGraph {
	vertexType v;
	QGraph *next;
};
typedef struct {
	QGraph *front;
	QGraph *rear;
}Queue;
typedef struct {
	vertexType v;
	VRType w;
}closedge[MAX_VERTEX_NUM];//Prim算法辅助数组
typedef struct {
	vertexType v1;
	vertexType v2;
	VRType w;
}Sortlist[MAX_VERTEX_NUM];//Kruskal算法辅助数组
status CreateGraph(MGraph &G);//创建图
status CreateGraphUDG(MGraph &G);//创建无向图
status CreateGraphDG(MGraph &G);//创建有向图
status CreateGraphUDN(MGraph &G);//创建无向网
status CreateGraphDN(MGraph &G);//创建有向网
int getindex(MGraph G, vertexType v);//根据节点获得节点的位置
vertexType getvalue(MGraph G, int index);//根据位置获得节点
//status DestoryGraph(MGraph &G);//数组类型的数据，无需销毁
status InsertVex(MGraph &G, vertexType v);//插入节点
status DeleteVex(MGraph &G, vertexType v);//删除节点
status InsertArc(MGraph &G, vertexType v, vertexType w);//插入边
status InsertArc_w(MGraph &G, vertexType v, vertexType w, VRType weight);//插入带权值的边
status DeleteArc(MGraph &G, vertexType v, vertexType w);//删除边
status Visit(vertexType w);//访问节点
status DFSTraverse(MGraph G, vertexType v, status Visit(vertexType w));//深度优先遍历
status BFSTraverse(MGraph G, vertexType v, status Visit(vertexType w));//广度优先遍历
status DisplayVex(MGraph G);//显示图中的所有节点
status DisplayArc(MGraph G);//显示图中的边的信息
status InitQ(Queue &Q);//初始化辅助队列
status EnQueue(Queue &Q, vertexType v);//入队列
status DeQueue(Queue &Q, vertexType &v);//出队列
status IsEmpty(Queue Q);//队列是否为空
status IsExist(Queue Q, vertexType v);//该节点是否在队列中已存在
int mininum(closedge c, int len);//求辅助数组权值最小的编号
status MiniSpanTree_Prim(MGraph G, vertexType v);//最小生成树Prim算法
int lenoflist(char list[]);//求辅助数组的辅助字符数组长度
status Existinlist(char list[], vertexType v);//字符是否存在于list数组
int LenOfT(Sortlist T);//辅助数组的长度
int NumOfNode(Sortlist T);//辅助数组的字符种类数
status ExistInT(Sortlist T, vertexType v1, vertexType v2);//判断该节点是否可合并
status MiniSpanTree_Kruskal(MGraph G);//最小生成树Kruskal算法

status DisplayVex(MGraph G) {
	printf("当前有%d个节点\n", G.vexnum);
	printf("分别为：\n");
	for (int i = 0; i < G.vexnum; i++) {
		printf("%2c", G.vexs[i]);
	}
	printf("\n");
	return ok;
}
status DisplayArc(MGraph G) {
	printf("当前有%d条边\n", G.arcnum);
	printf("边的情况为：\n");
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			if (G.arcs[i][j].adj != INFINITY)
				printf("%2d", G.arcs[i][j].adj);
			else
				printf(" #");
		}
		printf("\n");
	}
	return ok;
}
status CreateGraph(MGraph &G) {
	GraphKind kind;
	printf("请输入要建立的图的类型：(0-3)\n");
	printf("注：\n0：有向图\n1：有向网\n2：无向图\n3：无向网\n");
	scanf_s("%d", &kind);
	switch (kind)
	{
	case DG:
		G.kind = DG;
		CreateGraphDG(G);
		break;
	case UDG:
		G.kind = UDG;
		CreateGraphUDG(G);
		break;
	case DN:
		G.kind = DN;
		CreateGraphDN(G);
		break;
	case UDN:
		G.kind = UDN;
		CreateGraphUDN(G);
		break;
	default:
		printf("输入错误!\n");
		break;
	}
	return ok;
}
int getindex(MGraph G, vertexType v) {
	int index = INFINITY;
	for (index = 0; index < G.vexnum; index++) {
		if (v == G.vexs[index])
			break;
	}
	return index;
}
vertexType getvalue(MGraph G, int index) {
	return G.vexs[index];
}
status CreateGraphUDG(MGraph &G) {//无向图
	int i, j, k;
	printf("请输入该图的节点数和边数：\n");
	scanf_s("%d, %d", &G.vexnum, &G.arcnum);
	getchar();
	printf("请输入节点信息（单字符）：\n");
	for (i = 0; i < G.vexnum; i++) {
		scanf_s("%c", &G.vexs[i]);
	}
	getchar();
	for (i = 0; i < G.vexnum; i++) {
		for (j = 0; j < G.vexnum; j++) {
			G.arcs[i][j].adj = 0;
		}
	}
	vertexType v1, v2;
	printf("请输入边的信息：(每条边的两个节点)\n");
	for (k = 0; k < G.arcnum; k++) {
		v1 = getchar();
		v2 = getchar();
		getchar();
		i = getindex(G, v1);
		j = getindex(G, v2);
		printf("该边的节点为%c, %c\n", v1, v2);
		printf("该边的节点编号为%d, %d\n", i, j);
		if (i == INFINITY || j == INFINITY)
			return error;
		G.arcs[i][j].adj = 1;
		G.arcs[j][i].adj = 1;
	}
	DisplayVex(G);
	DisplayArc(G);
	return ok;
}
status CreateGraphDG(MGraph &G) {//有向图
	int i, j, k;
	printf("请输入该图的节点数和边数：\n");
	scanf_s("%d, %d", &G.vexnum, &G.arcnum);
	getchar();
	printf("请输入节点信息（单字符）：\n");
	for (i = 0; i < G.vexnum; i++) {
		scanf_s("%c", &G.vexs[i]);
	}
	getchar();
	for (i = 0; i < G.vexnum; i++) {
		for (j = 0; j < G.vexnum; j++) {
			G.arcs[i][j].adj = 0;
		}
	}
	vertexType v1, v2;
	printf("请输入边的信息：(每条边的两个节点，按方向顺序)\n");
	for (k = 0; k < G.arcnum; k++) {
		//scanf_s("%c, %c", &v1, &v2);
		v1 = getchar();
		v2 = getchar();
		getchar();
		i = getindex(G, v1);
		j = getindex(G, v2);
		if (i == INFINITY || j == INFINITY)
			return error;
		G.arcs[i][j].adj = 1;
		//G.arcs[j][i].adj = 1;
	}
	DisplayVex(G);
	DisplayArc(G);
	return ok;
}
status CreateGraphUDN(MGraph &G) {//无向网
	int i, j, k, w;
	printf("请输入该图的节点数和边数：\n");
	scanf_s("%d, %d", &G.vexnum, &G.arcnum);
	getchar();
	printf("请输入节点信息（单字符）：\n");
	for (i = 0; i < G.vexnum; i++) {
		scanf_s("%c", &G.vexs[i]);
	}
	getchar();
	for (i = 0; i < G.vexnum; i++) {
		for (j = 0; j < G.vexnum; j++) {
			G.arcs[i][j].adj = INFINITY;
		}
	}
	vertexType v1, v2;
	printf("请输入边的信息：(每条边的两个节点以及该边的权值)\n");
	for (k = 0; k < G.arcnum; k++) {
		//scanf_s("%c, %c, %d", &v1, &v2, &w);
		v1 = getchar();
		v2 = getchar();
		scanf_s("%d", &w);
		getchar();
		i = getindex(G, v1);
		j = getindex(G, v2);
		if (i == INFINITY || j == INFINITY)
			return error;
		G.arcs[i][j].adj = w;
		G.arcs[j][i].adj = w;
	}
	DisplayVex(G);
	DisplayArc(G);
	return ok;
}
status CreateGraphDN(MGraph &G) {//有向网
	int i, j, k, w;
	printf("请输入该图的节点数和边数：\n");
	scanf_s("%d, %d", &G.vexnum, &G.arcnum);
	getchar();
	printf("请输入节点信息（单字符）：\n");
	for (i = 0; i < G.vexnum; i++) {
		scanf_s("%c", &G.vexs[i]);
	}
	getchar();
	for (i = 0; i < G.vexnum; i++) {
		for (j = 0; j < G.vexnum; j++) {
			G.arcs[i][j].adj = INFINITY;
		}
	}
	vertexType v1, v2;
	printf("请输入边的信息：(每条边的两个节点以及该边的权值，节点按方向顺序输入)\n");
	for (k = 0; k < G.arcnum; k++) {
		//scanf_s("%c, %c, %d", &v1, &v2, &w);
		v1 = getchar();
		v2 = getchar();
		//w = getchar();
		scanf_s("%d", &w);
		getchar();
		i = getindex(G, v1);
		j = getindex(G, v2);
		if (i == INFINITY || j == INFINITY)
			return error;
		G.arcs[i][j].adj = w;
		//G.arcs[j][i].adj = w;
	}
	DisplayVex(G);
	DisplayArc(G);
	return ok;
}
//status DestoryGraph(MGraph &G) {
//	G = NULL;
//	return ok;
//}
status InsertVex(MGraph &G, vertexType v) {
	if (G.vexnum >= MAX_VERTEX_NUM)
		return error;
	G.vexs[G.vexnum] = v;
	G.vexnum++;
	if (G.kind == UDG || G.kind == DG) {
		for (int i = 0; i < G.vexnum; i++) {
			G.arcs[G.vexnum - 1][i].adj = 0;
			G.arcs[i][G.vexnum - 1].adj = 0;
		}
	}
	if (G.kind == UDN || G.kind == DN) {
		for (int i = 0; i < G.vexnum; i++) {
			G.arcs[G.vexnum - 1][i].adj = INFINITY;
			G.arcs[i][G.vexnum - 1].adj = INFINITY;
		}
	}
	return ok;
}
status DeleteVex(MGraph &G, vertexType v) {
	int i;
	for (i = 0; i < G.vexnum; i++) {
		if (v == G.vexs[i])
			break;
	}
	if (i >= G.vexnum)
		return error;
	for (int j= i; j < G.vexnum; j++) {
		G.vexs[j] = G.vexs[j + 1];
	}
	G.vexnum--;
	return ok;
}
status InsertArc(MGraph &G, vertexType v, vertexType w) {
	int flag1 = 0, flag2 = 0;
	for (int i = 0; i < G.vexnum; i++) {
		if (G.vexs[i] == v)
			flag1 = 1;
		if (G.vexs[i] == w)
			flag2 = 1;
	}
	//printf("%d___%d\n", flag1, flag2);
	if (flag1 == 0 || flag2 == 0)
		return error;
	G.arcnum++;
	int x;
	int index1, index2;
	index1 = getindex(G, v);
	index2 = getindex(G, w);
	if (G.kind == DG) {
		G.arcs[index1][index2].adj = 1;
	}
	else if (G.kind == UDG) {
		G.arcs[index1][index2].adj = 1;
		G.arcs[index2][index1].adj = 1;
	}
	else if (G.kind == DN) {
		printf("请输入所要添加边的权值：>>");
		scanf_s("%d", &x);
		G.arcs[index1][index2].adj = x;
	}
	else if (G.kind == UDN) {
		printf("请输入所要添加边的权值：>>");
		scanf_s("%d", &x);
		G.arcs[index1][index2].adj = x;
		G.arcs[index2][index1].adj = x;
	}
	else
		return error;
	return ok;
}
status InsertArc_w(MGraph &G, vertexType v, vertexType w, VRType weight) {
	int flag1 = 0, flag2 = 0;
	for (int i = 0; i < G.vexnum; i++) {
		if (G.vexs[i] == v)
			flag1 = 1;
		if (G.vexs[i] == w)
			flag2 = 1;
	}
	if (flag1 == 0 || flag2 == 0)
		return error;
	G.arcnum++;
	int x;
	int index1, index2;
	index1 = getindex(G, v);
	index2 = getindex(G, w);
	if (G.kind == DG) {
		G.arcs[index1][index2].adj = 1;
	}
	else if (G.kind == UDG) {
		G.arcs[index1][index2].adj = 1;
		G.arcs[index2][index1].adj = 1;
	}
	else if (G.kind == DN) {
		G.arcs[index1][index2].adj = weight;
	}
	else if (G.kind == UDN) {
		G.arcs[index1][index2].adj = weight;
		G.arcs[index2][index1].adj = weight;
	}
	else
		return error;
	return ok;
}
status DeleteArc(MGraph &G, vertexType v, vertexType w) {
	int flag1 = 0, flag2 = 0;
	for (int i = 0; i < G.vexnum; i++) {
		if (G.vexs[i] == v)
			flag1 = 1;
		if (G.vexs[i] == w)
			flag2 = 1;
	}
	if (flag1 == 0 || flag2 == 0)
		return error;
	int index1, index2;
	index1 = getindex(G, v);
	index2 = getindex(G, w);
	if (G.kind == DG) {
		G.arcs[index1][index2].adj = 0;
	}
	else if (G.kind == UDG) {
		G.arcs[index1][index2].adj = 0;
		G.arcs[index2][index1].adj = 0;
	}
	else if (G.kind == DN) {
		G.arcs[index1][index2].adj = INFINITY;
	}
	else if (G.kind == UDN) {
		G.arcs[index1][index2].adj = INFINITY;
		G.arcs[index2][index1].adj = INFINITY;
	}
	else
		return error;
	G.arcnum--;
	return ok;
}
status Visit(vertexType w) {
	printf("%2c", w);
	return ok;
}
status DFSTraverse(MGraph G, vertexType v, status Visit(vertexType w)) {
	int index = getindex(G, v);
	visit[index] = 1;
	Visit(v);
	for (int i = 0; i < G.vexnum; i++) {
		if (visit[i] != 1 && G.arcs[index][i].adj == 1)
			DFSTraverse(G, getvalue(G, i), Visit);
	}
	for (int i = 0; i < G.vexnum; i++) {//非连通图遍历
		if(visit[i] == 0)
			DFSTraverse(G, getvalue(G, i), Visit);
	}
	return ok;
}
status InitQ(Queue &Q) {
	Q.front = Q.rear = (QGraph *)malloc(sizeof(QGraph));
	if (!Q.front)
		return error;
	Q.front->next = NULL;
	return ok;
}
status EnQueue(Queue &Q, vertexType v) {
	QGraph *q;
	q = (QGraph *)malloc(sizeof(QGraph));
	if (!q)
		return error;
	q->v = v;
	Q.rear->next = q;
	Q.rear = q;
	q->next = NULL;
	if (Q.front->next == NULL)
		Q.front->next = Q.rear;
	return ok;
}
status DeQueue(Queue &Q, vertexType &v) {
	QGraph *q;
	if (Q.front->next == NULL)
		return error;
	q = Q.front->next;
	v = q->v;
	Q.front->next = q->next;
	free(q);
	if (Q.front->next == NULL)
		Q.rear = Q.front;
	return ok;
}
status IsEmpty(Queue Q) {
	if (Q.front == Q.rear)
		return ok;
	else
		return error;
}
status IsExist(Queue Q, vertexType v) {
	QGraph *temp;
	temp = Q.front->next;
	while (temp) {
		if (v == temp->v)
			return ok;
		temp = temp->next;
	}
	return error;
}
status BFSTraverse(MGraph G, vertexType v, status Visit(vertexType w)) {
	Queue Q;
	InitQ(Q);
	EnQueue(Q, v);
	for (int j = 0; j <= G.vexnum; j++) {//非连通图遍历
		int flag = 0;
		while (!IsEmpty(Q)) {
			DeQueue(Q, v);
			visit[getindex(G, v)] = 1;
			Visit(v);
			for (int i = 0; i < G.vexnum; i++) {
				if (visit[i] != 1 && G.arcs[getindex(G, v)][i].adj == 1) {
					flag = IsExist(Q, getvalue(G, i));//避免连通分量使某几个元素重复遍历
					if (!flag)
						EnQueue(Q, getvalue(G, i));
				}
			}
		}
		if (visit[j] == 0)
			EnQueue(Q, getvalue(G, j));
	}
	
	return ok;
}
int mininum(closedge c, int len) {
	int k = 0;
	int weight = 0;
	for (int i = 0; i < len; i++) {
		if (c[i].w != 0)
		{
			weight = c[i].w;
			k = i;
			break;
		}
	}
	for (int i = 0; i < len; i++) {
		if (c[i].w != 0 && c[i].w < weight) {
			weight = c[i].w;
			k = i;
		}
	}
	return k;
}
status MiniSpanTree_Prim(MGraph G, vertexType v) {
	closedge c;
	int k = getindex(G, v);
	for (int i = 0; i < G.vexnum; i++) {
		if (i != k) {
			c[i].v = v;
			c[i].w = G.arcs[k][i].adj;
		}
	}
	c[k].w = 0;
	for (int i = 0; i < G.vexnum; i++) {
		k = mininum(c, G.vexnum);
		printf("%c--%c\n", c[k].v, G.vexs[k]);
		c[k].w = 0;
		for (int j = 0; j < G.vexnum; j++) {
			if (G.arcs[k][j].adj < c[j].w) {
				c[j].w = G.arcs[k][j].adj;
				c[j].v = G.vexs[k];
			}
		}
		int flag = 0;
		for (int j = 0; j < G.vexnum; j++) {
			if (c[j].w != 0)
				flag = 1;
		}
		if (flag == 0)
			break;
	}
	return ok;
}
int LenOfT(Sortlist T) {
	int len;
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		if (T[i].v1 == '#' && T[i].v2 == '#' && T[i].w == INFINITY) {
			len = i;
			break;
		}
	}
	return len;
}
int lenoflist(char list[]) {
	int len;
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		if (list[i] == '#') {
			len = i;
			break;
		}
	}
	return len;
}
status Existinlist(char list[], vertexType v) {
	for (int i = 0; i < lenoflist(list); i++) {
		if (v == list[i])
			return ok;
	}
	return error;
}
int NumOfNode(Sortlist T) {
	char list[MAX_VERTEX_NUM];
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		list[i] = '#';
	}
	list[0] = T[0].v1;
	list[1] = T[0].v2;
	for (int i = 0; i < LenOfT(T); i++) {
		if (!Existinlist(list, T[i].v1))
			list[lenoflist(list)] = T[i].v1;
		if(!Existinlist(list, T[i].v2))
			list[lenoflist(list)] = T[i].v2;
	}
	return lenoflist(list);
}
status ExistInT(Sortlist T, vertexType v1, vertexType v2) {
	if (v1 == v2)
		return error;
	int count = LenOfT(T);
	T[count].v1 = v1;
	T[count].v2 = v2;
	T[count].w = 1;
	//printf("%d, %d\n", NumOfNode(T), LenOfT(T));
	if (NumOfNode(T) == LenOfT(T)) {//利用有连通的图的节点数等于边数来判断是否是连通图
		T[count].v1 = '#';
		T[count].v2 = '#';
		T[count].w = INFINITY;
		return error;
	}
	return ok;
}
status MiniSpanTree_Kruskal(MGraph G) {
	Sortlist T;
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		T[i].v1 = '#';
		T[i].v2 = '#';
		T[i].w = INFINITY;
	}
	int min_index1, min_index2;
	VRType min_w = INFINITY;
	for (int k = 0; k < G.vexnum * (G.vexnum-1) / 2; k++) {
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = i + 1; j < G.vexnum; j++) {
				if (G.arcs[i][j].adj < min_w) {
					min_w = G.arcs[i][j].adj;
					min_index1 = i;
					min_index2 = j;
				}
			}
		}
		G.arcs[min_index1][min_index2].adj = INFINITY;
		//DisplayArc(G);
		if (min_w != INFINITY && ExistInT(T, getvalue(G, min_index1), getvalue(G, min_index2)) != error) {
			T[k].v1 = getvalue(G, min_index1);
			T[k].v2 = getvalue(G, min_index2);
			T[k].w = min_w;
		}
		min_w = INFINITY;
	}
	for (int i = 0; i < LenOfT(T); i++) {
		printf("%c--%c\n", T[i].v1, T[i].v2);
	}
	return ok;
}

typedef struct VNode{
	vertexType v;
	VNode *next;
}*VStack;
VRType ve[MAX_VERTEX_NUM], vl[MAX_VERTEX_NUM];//到达每个节点所对应的最早时间和最晚时间//DN中有效
status InitVStack(VStack &S) {
	S = (VNode *)malloc(sizeof(VNode));
	if (!S)
		return error;
	S->next = NULL;
	return ok;
}
status Push(VStack &S, vertexType v) {
	VNode *temp;
	temp = (VNode *)malloc(sizeof(VNode));
	if (!temp)
		return error;
	temp->v = v;
	temp->next = S->next;
	S->next = temp;
	return ok;
}
status Pop(VStack &S, vertexType &v) {
	VNode *temp;
	if (S->next == NULL)
		return error;
	temp = S->next;
	S->next = temp->next;
	v = temp->v;
	free(temp);
	return ok;
}
status EmptyStack(VStack S) {
	if (S->next == NULL)
		return ok;
	else
		return error;
}
//int LenofS(VStack S) {//无用。。。
//	int len = 0;
//	vertexType temp;
//	while (S->next != NULL) {
//		Pop(S, temp);
//		len++;
//	}
//	//printf("%d\n", len);
//	return len;
//}
int IndegreeNum(MGraph G, vertexType v) {
	int num = 0;
	int index = getindex(G, v);
	if (G.vexnum == index)
		return error;
	if (G.kind == UDG || G.kind == DG) {
		for (int i = 0; i < G.vexnum; i++) {
			if (G.arcs[i][index].adj != 0)
				num++;
		}
	}
	else if (G.kind == UDN || G.kind == DN) {
		for (int i = 0; i < G.vexnum; i++) {
			if (G.arcs[i][index].adj != INFINITY)
				num++;
		}
	}
	return num;
}
int OutdegreeNum(MGraph G, vertexType v) {
	int num = 0;
	int index = getindex(G, v);
	if (G.vexnum == index)
		return error;
	if (G.kind == UDG || G.kind == DG) {
		for (int i = 0; i < G.vexnum; i++) {
			if (G.arcs[index][i].adj != 0)
				num++;
		}
	}
	else if (G.kind == UDN || G.kind == DN) {
		for (int i = 0; i < G.vexnum; i++) {
			if (G.arcs[index][i].adj != INFINITY)
				num++;
		}
	}
	return num;
}
status Traverse_S(VStack T) {
	vertexType temp;
	while (T->next != NULL) {
		Pop(T, temp);
		Visit(temp);
	}
	return ok;
}
status TopoLogicalSort(MGraph G, VStack &T) {
	if (G.kind == UDG || G.kind == UDN)
		return error;
	int indegree[MAX_VERTEX_NUM];
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		indegree[i] = INFINITY;
		ve[i] = 0;
	}
	for (int i = 0; i < G.vexnum; i++) {
		indegree[i] = IndegreeNum(G, getvalue(G, i));
	}
	VStack S;
	InitVStack(S);
	InitVStack(T);
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		if (indegree[i] == 0)
			Push(S, getvalue(G, i));
		if (indegree[i] == INFINITY)
			break;
	}
	if (EmptyStack(S))
		return error;
	vertexType temp;
	while (!EmptyStack(S)) {
		Pop(S, temp);
		Push(T, temp);
		int index1 = getindex(G, temp);
		for (int i = 0; i < G.vexnum; i++) {
			if (G.kind == DN && G.arcs[index1][i].adj != INFINITY) {
				if (--indegree[i] == 0) {
					Push(S, getvalue(G, i));
				}

			}
			if (G.kind == DG && G.arcs[index1][i].adj != 0) {
				if (--indegree[i] == 0) {
					Push(S, getvalue(G, i));
				}
			}
		}
	}
	int flag = 0;
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		if (indegree[i] == INFINITY)
			break;
		if (indegree[i] != 0) {
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		return ok;
	else
		return error;
}
status Reverse_Stack(VStack T, VStack &T0) {//倒置后原栈中数据丢失
	//int len = LenofS(T);
	//printf("%d\n", len);
	vertexType temp;
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		if (T->next == NULL)
			break;
		Pop(T, temp);
		Push(T0, temp);
		//printf("%c\n", temp);
	}
	return ok;
}

int main()
{
	MGraph G_UDN;
	G_UDN.kind = UDN;
	G_UDN.arcnum = 0;
	G_UDN.vexnum = 0;
	//CreateGraph(G_UDG);
	/*MGraph G_DG;
	CreateGraph(G_DG);
	MGraph G_UDN;
	CreateGraph(G_UDN);
	MGraph G_DN;
	CreateGraph(G_DN);*/
	InsertVex(G_UDN, 'A');
	InsertVex(G_UDN, 'B');
	InsertVex(G_UDN, 'C');
	InsertVex(G_UDN, 'D');
	InsertVex(G_UDN, 'E');
	InsertArc_w(G_UDN, 'A', 'B', 1);
	InsertArc_w(G_UDN, 'A', 'C', 2);
	InsertArc_w(G_UDN, 'A', 'D', 3);
	InsertArc_w(G_UDN, 'C', 'E', 4);
	InsertArc_w(G_UDN, 'D', 'E', 1);
	InsertVex(G_UDN, 'F');
	InsertArc_w(G_UDN, 'B', 'F', 1);
	InsertArc_w(G_UDN, 'E', 'F', 2);
	//InsertArc(G_UDG, 'A', 'F');
	DisplayVex(G_UDN);
	DisplayArc(G_UDN);
	printf("Prim算法:\n");
	MiniSpanTree_Prim(G_UDN, 'A');
	printf("Kruskal算法:\n");
	MiniSpanTree_Kruskal(G_UDN);
	/*DeleteArc(G_UDG, 'A', 'F');
	DisplayArc(G_UDG);
	DeleteVex(G_UDG, 'F');
	DisplayVex(G_UDG);
	DisplayArc(G_UDG);*/
	/*for (int i = 0; i < G_UDN.vexnum; i++) {
		visit[i] = 0;
	}*/
	/*printf("DFS深度优先遍历：\n");
	DFSTraverse(G_UDN, 'A', Visit);
	printf("\n");
	for (int i = 0; i < G_UDN.vexnum; i++) {
		visit[i] = 0;
	}
	printf("BFS广度优先遍历：\n");
	BFSTraverse(G_UDN, 'A', Visit);
	printf("\n");*/
	MGraph G_DN;
	G_DN.kind = DN;
	G_DN.arcnum = 0;
	G_DN.vexnum = 0;
	InsertVex(G_DN, 'A');
	InsertVex(G_DN, 'B');
	InsertVex(G_DN, 'C');
	InsertVex(G_DN, 'D');
	InsertVex(G_DN, 'E');
	InsertVex(G_DN, 'F');
	InsertVex(G_DN, 'G');
	InsertArc_w(G_DN, 'A', 'B', 1);
	InsertArc_w(G_DN, 'A', 'C', 1);
	InsertArc_w(G_DN, 'A', 'D', 1);
	InsertArc_w(G_DN, 'B', 'G', 1);
	InsertArc_w(G_DN, 'C', 'B', 1);
	InsertArc_w(G_DN, 'C', 'F', 1);
	InsertArc_w(G_DN, 'C', 'E', 1);
	InsertArc_w(G_DN, 'D', 'E', 1);
	InsertArc_w(G_DN, 'E', 'G', 1);
	InsertArc_w(G_DN, 'F', 'E', 1);
	//InsertArc_w(G_DN, 'G', 'C', 1);
	DisplayVex(G_DN);
	DisplayArc(G_DN);
	VStack T;
	if (TopoLogicalSort(G_DN, T))
		printf("该图无环！\n");
	else
		printf("该图有环！\n");
	VStack T0;
	InitVStack(T0);
	Reverse_Stack(T, T0);
	TopoLogicalSort(G_DN, T);
	Traverse_S(T);
	printf("\n");
	Traverse_S(T0);
	printf("\n");
	system("pause");
    return 0;
}

