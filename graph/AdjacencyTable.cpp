//图：邻接表
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTEX_NUM 100
#define INFINITY INT_MAX
typedef char VertexType;
typedef enum { error, ok } status;
typedef enum { DG, DN, UDG, UDN } GraphKind;//有向图，有向网，无向图，无向网
typedef struct ArcNode {
	int adjvex;
	int weight;
	struct ArcNode *nextarc;
	//InfoType *info;//需要时再添加
};
typedef struct VNode {
	VertexType data;
	ArcNode *firstarc;
}AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
	GraphKind kind;
}ALGraph;
int visit[MAX_VERTEX_NUM];
typedef struct QGraph {
	VNode v;
	QGraph *next;
};
typedef struct {
	QGraph *front;
	QGraph *rear;
}Queue;

status CreateGraph(ALGraph &G);//创建图
status CreateGraphUDG(ALGraph &G);//创建无向图
status CreateGraphDG(ALGraph &G);//创建有向图
status CreateGraphUDN(ALGraph &G);//创建无向网
status CreateGraphDN(ALGraph &G);//创建有向网
int getindex(ALGraph G, VertexType v);//根据节点获得节点的位置
VertexType getvalue(ALGraph G, int index);//根据位置获得节点
status DestoryGraph(ALGraph &G);//销毁图
status InsertVex(ALGraph &G, VertexType v);//插入节点
status DeleteVex(ALGraph &G, VertexType v);//删除节点
status InsertArc(ALGraph &G, VertexType v, VertexType w);//插入边
status DeleteArc(ALGraph &G, VertexType v, VertexType w);//删除边
status Visit(VertexType w);//访问节点
status DFSTraverse(ALGraph G, VertexType v, status Visit(VertexType w));//深度优先遍历
status BFSTraverse(ALGraph G, VertexType v, status Visit(VertexType w));//广度优先遍历
status DisplayVex(ALGraph G);//显示图中的所有节点
status DisplayArc(ALGraph G);//显示图中的边的信息
status InitQ(Queue &Q);//初始化辅助队列
status EnQueue(Queue &Q, VNode v);//入队列
status DeQueue(Queue &Q, VNode &v);//出队列
status IsEmpty(Queue Q);//队列是否为空
status IsExist(Queue Q, VNode v);//该节点是否在队列中已存在

int getindex(ALGraph G, VertexType v) {
	int index = INFINITY;
	for (index = 1; index <= G.vexnum; index++) {
		if (v == G.vertices[index].data)
			break;
	}
	return index;
}
VertexType getvalue(ALGraph G, int index) {
	return G.vertices[index].data;
}
status DisplayVex(ALGraph G) {
	printf("当前有%d个节点\n", G.vexnum);
	printf("分别为：\n");
	for (int i = 1; i <= G.vexnum; i++) {
		printf("%2c", G.vertices[i].data);
	}
	printf("\n");
	return ok;
}
status DisplayArc(ALGraph G) {
	printf("当前有%d条边\n", G.arcnum);
	printf("边的情况为：\n");
	for (int i = 1; i <= G.vexnum; i++) {
		printf("%c: ", getvalue(G, i));
		while (G.vertices[i].firstarc != NULL) {
			printf("%c%c: ", getvalue(G, i), getvalue(G, G.vertices[i].firstarc->adjvex));
			printf("%d ", G.vertices[i].firstarc->weight);
			G.vertices[i].firstarc = G.vertices[i].firstarc->nextarc;
		}
		printf("\n");
	}
	return ok;
}
status CreateGraph(ALGraph &G) {
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
status CreateGraphUDG(ALGraph &G) {
	int i, j, k;
	printf("请输入该图的节点数和边数：\n");
	scanf_s("%d, %d", &G.vexnum, &G.arcnum);
	getchar();
	printf("请输入节点信息（单字符）：\n");
	for (i = 1; i <= G.vexnum; i++) {
		//scanf_s("%c", G.vertices[i]->data);
		G.vertices[i].data = getchar();
		G.vertices[i].firstarc = NULL;
	}
	getchar();
	VertexType v1, v2;
	ArcNode *temp, *temp1;
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
		temp = (ArcNode *)malloc(sizeof(ArcNode));
		temp->adjvex = j;
		temp->weight = 0;
		temp->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = temp;
		temp1 = (ArcNode *)malloc(sizeof(ArcNode));
		temp1->adjvex = i;
		temp1->weight = 0;
		temp1->nextarc = G.vertices[j].firstarc;
		G.vertices[j].firstarc = temp1;
	}
	DisplayVex(G);
	DisplayArc(G);
	return ok;
}
status CreateGraphDG(ALGraph &G) {
	int i, j, k;
	printf("请输入该图的节点数和边数：\n");
	scanf_s("%d, %d", &G.vexnum, &G.arcnum);
	getchar();
	printf("请输入节点信息（单字符）：\n");
	for (i = 1; i <= G.vexnum; i++) {
		//scanf_s("%c", G.vertices[i]->data);
		G.vertices[i].data = getchar();
		G.vertices[i].firstarc = NULL;
	}
	getchar();
	VertexType v1, v2;
	ArcNode *temp;
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
		temp = (ArcNode *)malloc(sizeof(ArcNode));
		temp->adjvex = j;
		temp->weight = 0;
		temp->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = temp;
	}
	DisplayVex(G);
	DisplayArc(G);
	return ok;
}
status CreateGraphUDN(ALGraph &G) {
	int i, j, k, w;
	printf("请输入该图的节点数和边数：\n");
	scanf_s("%d, %d", &G.vexnum, &G.arcnum);
	getchar();
	printf("请输入节点信息（单字符）：\n");
	for (i = 1; i <= G.vexnum; i++) {
		//scanf_s("%c", G.vertices[i]->data);
		G.vertices[i].data = getchar();
		G.vertices[i].firstarc = NULL;
	}
	getchar();
	VertexType v1, v2;
	ArcNode *temp, *temp1;
	printf("请输入边的信息：(每条边的两个节点以及该边的权值)\n");
	for (k = 0; k < G.arcnum; k++) {
		v1 = getchar();
		v2 = getchar();
		scanf_s("%d", &w);
		getchar();
		i = getindex(G, v1);
		j = getindex(G, v2);
		printf("该边的节点为%c, %c\n", v1, v2);
		printf("该边的节点编号为%d, %d\n", i, j);
		if (i == INFINITY || j == INFINITY)
			return error;
		temp = (ArcNode *)malloc(sizeof(ArcNode));
		temp->adjvex = j;
		temp->weight = w;
		temp->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = temp;
		temp1 = (ArcNode *)malloc(sizeof(ArcNode));
		temp1->adjvex = i;
		temp1->weight = w;
		temp1->nextarc = G.vertices[j].firstarc;
		G.vertices[j].firstarc = temp1;
	}
	DisplayVex(G);
	DisplayArc(G);
	return ok;
}
status CreateGraphDN(ALGraph &G) {
	int i, j, k, w;
	printf("请输入该图的节点数和边数：\n");
	scanf_s("%d, %d", &G.vexnum, &G.arcnum);
	getchar();
	printf("请输入节点信息（单字符）：\n");
	for (i = 1; i <= G.vexnum; i++) {
		//scanf_s("%c", G.vertices[i]->data);
		G.vertices[i].data = getchar();
		G.vertices[i].firstarc = NULL;
	}
	getchar();
	VertexType v1, v2;
	ArcNode *temp;
	printf("请输入边的信息：(每条边的两个节点以及该边的权值)\n");
	for (k = 0; k < G.arcnum; k++) {
		v1 = getchar();
		v2 = getchar();
		scanf_s("%d", &w);
		getchar();
		i = getindex(G, v1);
		j = getindex(G, v2);
		printf("该边的节点为%c, %c\n", v1, v2);
		printf("该边的节点编号为%d, %d\n", i, j);
		if (i == INFINITY || j == INFINITY)
			return error;
		temp = (ArcNode *)malloc(sizeof(ArcNode));
		temp->adjvex = j;
		temp->weight = w;
		temp->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = temp;
	}
	DisplayVex(G);
	DisplayArc(G);
	return ok;
}
status DestoryGraph(ALGraph &G) {
	ArcNode *temp;
	for (int i = 1; i <= G.vexnum; i++) {
		while (G.vertices[i].firstarc) {
			temp = G.vertices[i].firstarc;
			G.vertices[i].firstarc = G.vertices[i].firstarc->nextarc;
			free(temp);
		}
	}
	G.arcnum = 0;
	G.vexnum = 0;
	return ok;
}
status InsertVex(ALGraph &G, VertexType v) {
	VNode *temp;
	temp = (VNode *)malloc(sizeof(VNode));
	temp->data = v;
	temp->firstarc = NULL;
	G.vertices[G.vexnum + 1] = *temp;
	G.vexnum++;
	return ok;
}
status DeleteVex(ALGraph &G, VertexType v) {
	ArcNode *temp;
	int index = getindex(G, v);
	/*while (G.vertices[index].firstarc) {
		temp = G.vertices[index].firstarc;
		G.vertices[index].firstarc = G.vertices[index].firstarc->nextarc;
		free(temp);
	}*/
	if (G.kind == UDG || G.kind == UDN) {
		for (int i = 1; i <= G.vexnum; i++) {
			DeleteArc(G, v, getvalue(G, i));
		}
	}
	else if (G.kind == DG || G.kind == DN) {
		for (int i = 1; i <= G.vexnum; i++) {
			DeleteArc(G, v, getvalue(G, i));
			DeleteArc(G, getvalue(G, i), v);
		}
	}
	for (int i = index; i <= G.vexnum; i++) {
		G.vertices[i] = G.vertices[i + 1];
	}
	G.vexnum--;
	return ok;
}
status InsertArc(ALGraph &G, VertexType v, VertexType w) {
	int flag = 0, flag1 = 0;
	for (int i = 1; i <= G.vexnum; i++) {
		if (v == G.vertices[i].data)
			flag = 1;
		if (w == G.vertices[i].data)
			flag1 = 1;
	}
	if (flag == 0 || flag1 == 0) {
		return error;
	}
	ArcNode *temp, *temp1;
	int index, index1;
	index = getindex(G, v);
	index1 = getindex(G, w);
	if (G.kind == UDG) {
		temp = (ArcNode *)malloc(sizeof(ArcNode));
		temp->adjvex = index1;
		temp->weight = 0;
		temp->nextarc = G.vertices[index].firstarc;
		G.vertices[index].firstarc = temp;
		temp1 = (ArcNode *)malloc(sizeof(ArcNode));
		temp1->adjvex = index;
		temp1->weight = 0;
		temp1->nextarc = G.vertices[index1].firstarc;
		G.vertices[index1].firstarc = temp1;
	}
	else if (G.kind == DG) {
		temp = (ArcNode *)malloc(sizeof(ArcNode));
		temp->adjvex = index1;
		temp->weight = 0;
		temp->nextarc = G.vertices[index].firstarc;
		G.vertices[index].firstarc = temp;
	}
	else if (G.kind == UDN) {
		int w;
		printf("请输入权值：\n");
		w = scanf_s("%d", &w);
		temp = (ArcNode *)malloc(sizeof(ArcNode));
		temp->adjvex = index1;
		temp->weight = w;
		temp->nextarc = G.vertices[index].firstarc;
		G.vertices[index].firstarc = temp;
		temp1 = (ArcNode *)malloc(sizeof(ArcNode));
		temp1->adjvex = index;
		temp1->weight = w;
		temp1->nextarc = G.vertices[index1].firstarc;
		G.vertices[index1].firstarc = temp1;
	}
	else if (G.kind == DN) {
		int w;
		printf("请输入权值：\n");
		w = scanf_s("%d", &w);
		temp = (ArcNode *)malloc(sizeof(ArcNode));
		temp->adjvex = index1;
		temp->weight = w;
		temp->nextarc = G.vertices[index].firstarc;
		G.vertices[index].firstarc = temp;
	}
	else
		return error;
	G.arcnum++;
	return ok;
}
status DeleteArc(ALGraph &G, VertexType v, VertexType w) {
	int flag = 0, flag1 = 0;
	for (int i = 1; i <= G.vexnum; i++) {
		if (v == G.vertices[i].data)
			flag = 1;
		if (w == G.vertices[i].data)
			flag1 = 1;
	}
	if (flag == 0 || flag1 == 0) {
		return error;
	}
	if (v == w)
		return error;
	ArcNode *temp, *temp1;
	int index, index1;
	index = getindex(G, v);
	index1 = getindex(G, w);
	if(G.kind == UDG || G.kind == UDN){
		if (G.vertices[index].firstarc == NULL || G.vertices[index1].firstarc == NULL)
			return error;
		temp = G.vertices[index].firstarc;
		temp1 = G.vertices[index].firstarc->nextarc;
		//temp1 = G.vertices[index];
		while (temp1) {
			if (temp1->adjvex == index1) {
				temp->nextarc = temp1->nextarc;
				free(temp1);
				break;
			}
			temp = temp->nextarc;
			temp1 = temp1->nextarc;
		}
		temp = G.vertices[index].firstarc;
		if (temp->adjvex == index1) {
			G.vertices[index].firstarc = temp->nextarc;
			free(temp);
		}
		//#########################################
		temp = G.vertices[index1].firstarc;
		temp1 = G.vertices[index1].firstarc->nextarc;
		//temp1 = G.vertices[index];
		while (temp1) {
			if (temp1->adjvex == index) {
				temp->nextarc = temp1->nextarc;
				free(temp1);
				break;
			}
			temp = temp->nextarc;
			temp1 = temp1->nextarc;
		}
		temp = G.vertices[index1].firstarc;
		if (temp->adjvex == index) {
			G.vertices[index1].firstarc = temp->nextarc;
			free(temp);
		}
	}
	else if (G.kind == DG || G.kind == DN) {
		if (G.vertices[index].firstarc == NULL)
			return error;
		temp = G.vertices[index].firstarc;
		temp1 = G.vertices[index].firstarc->nextarc;
		//temp1 = G.vertices[index];
		while (temp1) {
			if (temp1->adjvex == index1) {
				temp->nextarc = temp1->nextarc;
				free(temp1);
				break;
			}
			temp = temp->nextarc;
			temp1 = temp1->nextarc;
		}
		temp = G.vertices[index].firstarc;
		if (temp->adjvex == index1) {
			G.vertices[index].firstarc = temp->nextarc;
			free(temp);
		}
	}
	G.arcnum--;
	return ok;
}
status Visit(VertexType w) {
	printf("%2c", w);
	return ok;
}
status DFSTraverse(ALGraph G, VertexType v, status Visit(VertexType w)) {
	int index = getindex(G, v);
	visit[index] = 1;
	Visit(v);
	ArcNode *temp;
	temp = G.vertices[index].firstarc;
	while (temp) {
		if (visit[temp->adjvex] != 1) {
			DFSTraverse(G, getvalue(G, temp->adjvex), Visit);
		}
		temp = temp->nextarc;
	}
	for (int i = 1; i <= G.vexnum; i++) {
		if (visit[i] != 1) {
			DFSTraverse(G, getvalue(G, i), Visit);
		}
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
status EnQueue(Queue &Q, VNode v) {
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
status DeQueue(Queue &Q, VNode &v) {
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
status IsExist(Queue Q, VNode v) {
	QGraph *temp;
	temp = Q.front->next;
	while (temp) {
		if (v.data == temp->v.data)
			return ok;
		temp = temp->next;
	}
	return error;
}
status BFSTraverse(ALGraph G, VertexType v, status Visit(VertexType w)) {
	Queue Q;
	InitQ(Q);
	int index = getindex(G, v);
	VNode temp;
	ArcNode *tmp;
	EnQueue(Q, G.vertices[index]);
	for (int i = 1; i <= G.vexnum+1; i++) {
		int flag = 0;
		while (!IsEmpty(Q)) {
			DeQueue(Q, temp);
			visit[getindex(G, temp.data)] = 1;
			Visit(temp.data);
			tmp = temp.firstarc;
			while (tmp) {
				flag = IsExist(Q, G.vertices[tmp->adjvex]);
				if(flag == 0 && visit[tmp->adjvex] != 1)
					EnQueue(Q, G.vertices[tmp->adjvex]);
				tmp = tmp->nextarc;
			}
		}
		if (visit[i] != 1) {
			EnQueue(Q, G.vertices[i]);
		}
	}
	return ok;
}

int main()
{
	ALGraph G;
	//CreateGraph(G);
	G.kind = UDG;
	G.vexnum = 0;
	G.arcnum = 0;
	InsertVex(G, 'A');
	InsertVex(G, 'B');
	InsertVex(G, 'C');
	InsertVex(G, 'D');
	InsertVex(G, 'E');
	InsertArc(G, 'A', 'B');
	InsertArc(G, 'A', 'C');
	InsertArc(G, 'A', 'D');
	InsertArc(G, 'C', 'E');
	InsertArc(G, 'D', 'E');
	InsertVex(G, 'F');
	DeleteArc(G, 'A', 'B');
	DeleteVex(G, 'E');
	DisplayVex(G);
	DisplayArc(G);
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		visit[i] = 0;
	}
	printf("深度优先遍历：\n");
	DFSTraverse(G, 'A', Visit);
	printf("\n");
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		visit[i] = 0;
	}
	printf("广度优先遍历：\n");
	BFSTraverse(G, 'A', Visit);
	printf("\n");
	system("pause");
    return 0;
}