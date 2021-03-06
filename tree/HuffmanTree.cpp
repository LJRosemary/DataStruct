//Huffman树//顺序表
#include "stdafx.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define N 10
#define M 2*N-1
typedef struct {
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode;
typedef struct {
	char data;
	int weight;
	char code[N];
}HTCode;

void Init(HTCode hc[], int &n) {
	int i;
	printf("\ninput n =");
	scanf_s("%d", &n);
	printf("\ninput %d character\n", n);
	for (i = 1; i <= n; i++) {
		scanf_s("%c", hc[i].data);
	}
	printf("\ninput %d weight\n", n);
	for (i = 1; i <= n; i++) {
		scanf_s("%d", hc[i].weight);
	}
}

void Select(HTNode ht[], int k, int &s1, int &s2) {
	int i;
	for (i = 1; i <= k && ht[i].parent != 0; i++) {
		s1 = i;
	}
	for (i = 1; i <= k; i++) {
		if (ht[i].parent == 0 && ht[i].weight < ht[s1].weight)
			s1 = i;
	}
	for (i = 1; i <= k; i++) {
		if (ht[i].parent == 0 && i != s1)
			break;
	}
	s2 = i;
	for (i = 1; i <= k; i++) {
		if (ht[i].parent == 0 && i != s1 && ht[i].weight < ht[s2].weight)
			s2 = i;
	}
}

void HuffmanCoding(HTNode ht[], HTCode hc[], int n) {
	char cd[N];
	int i, j, m, c, f, s1, s2, start;
	m = 2 * n - 1;
	for (i = 1; i <= m; i++) {
		if (i <= n)
			ht[i].weight = hc[i].weight;
		else
			ht[i].weight = 0;
		ht[i].parent = ht[i].lchild = ht[i].rchild = 0;
	}
	for (i = n + 1; i <= m; i++) {
		Select(ht, i - 1, s1, s2);
		ht[s1].parent = i;
		ht[s2].parent = i;
		ht[i].lchild = s1;
		ht[i].rchild = s2;
		ht[i].weight = ht[s1].weight + ht[s2].weight;
	}
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i++) {
		start = n - 1;
		for (c = i, f = ht[i].parent; f; c = f, f = ht[f].parent)
			if (ht[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		strcpy_s(hc[i].code, &cd[start]);
	}
}

int main()
{
	int i = 0, m = 0, n = 0, w[N + 1];
	HTNode ht[M + 1];
	HTCode hc[N + 1];
	Init(hc, n);
	HuffmanCoding(ht, hc, n);
	for (i = 1; i <= n; i++)
		printf("\n%c--%s", hc[i].data, hc[i].code);
	system("pause");
    return 0;
}

