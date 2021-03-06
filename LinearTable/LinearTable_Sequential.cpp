//线性表的顺序存储
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LIST_INIT_SIZE 80
#define LISTINCREMENT 10

typedef enum {error, ok} status;
typedef int num;

typedef struct {
	//char name[10];//定义成char name[10]则不能直接赋值，可通过strcpy赋值
	char *name;
	int age;
	char sex;
	float score;
}Elemtype;

typedef struct {
	Elemtype *elem;
	int length;
	int listsize;
}Sqlist;
//&表示对本来的L进行操作，直接改变原来的值，如果使用*L，则不会因为函数中的操作改变L中的数据
status init(Sqlist &L);
status destory(Sqlist &L);
status ClearList(Sqlist &L);
status is_empty(Sqlist &L);
num list_length(Sqlist &L);
num priorElem(Sqlist &L, int index, Elemtype &pre);
num nextElem(Sqlist &L, int index, Elemtype &next);
num GetElem(Sqlist &L, int i, Elemtype *e);
status compare(Elemtype p, Elemtype q);
num LocateElem(Sqlist &L, Elemtype *e, status(*compare)(Elemtype, Elemtype));
num ListInsert(Sqlist &L, int i, Elemtype *e);
num ListDelete(Sqlist &L, int i, Elemtype *e);
status visit(Elemtype p);
status ListTraverse(Sqlist &L, status visit(Elemtype));


//初始化
status init(Sqlist &L) {
	L.elem = (Elemtype*)malloc(LIST_INIT_SIZE * sizeof(Elemtype));//申请空间
	if (!L.elem) {
		return error;
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return ok;
}
//销毁线性表
status destory(Sqlist &L) {
	free(L.elem);
	return ok;
}
//清空线性表
status ClearList(Sqlist &L) {
	L.length = 0;
	return ok;
}
//是否为空
status is_empty(Sqlist &L) {
	if (L.length == 0)
		return ok;
	else
		return error;
}
//线性表长度
num list_length(Sqlist &L) {
	return L.length;
}
//查找前驱
num priorElem(Sqlist &L, int index, Elemtype &pre) {
	if (index < 1 || L.length == 0 || index > L.length-1)
		return error;
	else
		pre = L.elem[index - 1];
	return ok;
}
//查找后继
num nextElem(Sqlist &L, int index, Elemtype &next) {
	if (index < 0 || L.length == 0 || index >= L.length-1)
		return error;
	else
		next = L.elem[index + 1];
	return ok;
}
//获取某个索引对应的元素值
num GetElem(Sqlist &L, int i, Elemtype *e) {
	if (i < 0 || i >= L.length)
		return error;
	else {
		e->name = L.elem[i].name;
		e->age = L.elem[i].age;
		e->sex = L.elem[i].sex;
		e->score = L.elem[i].score;
	}
		//e = L.elem[i];
	return ok;
}

status compare(Elemtype p, Elemtype q) {
	if (p.age == q.age && p.sex == q.sex && p.score == q.score && !(strcmp(p.name, q.name)))//strcmp，相等返回0
		return ok;
	else
		return error;
}
//查找某个数据是否存在
num LocateElem(Sqlist &L, Elemtype *e, status(*compare)(Elemtype, Elemtype)) {
	int i = 0;
	Elemtype *p = L.elem;
	while (i < L.length && !(*compare)(*p, *e)) {
		//printf("test:\n");
		//visit(*p);
		i++;
		p++;
	}
	//visit(*p);
	//visit(*e);
	//printf("test over\n");
	if (i < L.length) 
		return i;
	else return -1;
}
//插入数据
num ListInsert(Sqlist &L, int i, Elemtype *e) {
	Elemtype *newbase;
	if (i < 0 || i > L.length) return error;
	if (L.length >= L.listsize) {
		newbase = (Elemtype *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(Elemtype));
		if (!newbase) exit(0);
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	//指针表示法
	//Elemtype *q = &(L.elem[i - 1]);
	//Elemtype *p;
	//for (p = &(L.elem[L.length - 1]); p >= q; --p)
	//	*(p + 1) = *p;
	//*q = e;
	//插入在i位置，i之后的所有元素向后移一位
	if (L.length > 0) {
		for (int j = L.length - 1; j >= i; --j) {
			L.elem[j + 1] = L.elem[j];
		}
	}
	L.elem[i] = *e;
	++L.length;
	return ok;
}
//删除元素
num ListDelete(Sqlist &L, int i, Elemtype *e) {
	if (i < 0 || i >= L.length)
		return error;
	//数组表示法
//	e = L.elem[i-1];
//	for (int j = i-1; j < L.length-1; j++)
//		L.elem[j] = L.elem[j + 1];
//	--L.length;
//	return ok;
	Elemtype *p = &(L.elem[i]);
	//e = p;
	//e->name = p->name;
	//strcpy_s(e->name, p->name);
	e->name = p->name;
	e->age = p->age;
	e->sex = p->sex;
	e->score = p->score;
	Elemtype *q = L.elem + L.length - 1;
	//第一个++p只执行一次
	for (++p; p <= q; ++p) {
		*(p - 1) = *p;
	}
	--L.length;
	return ok;
}

status visit(Elemtype p) {
	printf("姓名：%s， 年龄：%d， ", p.name, p.age);
	if (p.sex == '1')
		printf("性别：男, ");
	else if (p.sex == '0')
		printf("性别：女, ");
	else
		printf("性别：未知, ");
	printf("成绩：%f\n", p.score);
	return ok;
}
//遍历
status ListTraverse(Sqlist &L, status visit(Elemtype)) {
	//Elemtype *p;
	for (int i = 0; i < L.length; i++)
		visit(L.elem[i]);
	return ok;
}

void show_menu() {
	printf("请用序号选择所使用的功能：\n");
	printf("1、遍历当前线性表\n");
	printf("2、插入新的数据\n");
	printf("3、删除指定数据\n");
	printf("4、查询索引对应数据\n");
	printf("5、清空当前线性表\n");
	printf("6、退出程序\n");
	printf("\n");
	printf(">>>");
}
void menu1(Sqlist &L) {
	if (L.length == 0)
		printf("线性表为空！\n");
	else {
		printf("当前线性表长度：%d， 该线性表初始空间剩余长度：%d\n", L.length, L.listsize - L.length);
		ListTraverse(L, visit);
	}
}
void menu2(Sqlist &L) {
	int i;
	Elemtype *p;
	char *name;
	int age;
	char sex;
	float score;
	//sex = (char)malloc(sizeof(char));
	name = (char *)malloc(10 * sizeof(char));//scanf读入char*型数据必须实现申请空间！
	p = (Elemtype *)malloc(sizeof(Elemtype));
	//printf("请输入要插入的数据：（位置(0-%d)， 年龄， 分数， 性别（0、1），姓名）\n>>>", L.length);
	//getchar();
	//scanf_s("%d, %s, %d, %c, %f", &i, &name, &age, &sex, &score);
	//scanf_s("%d, %d, %f, %c", &i, &age, &score, &sex);
	printf("请输入必要的数据：\n");
	printf("插入位置(0-%d)：\n>>>", L.length);
	scanf_s("%d", &i);
	printf("姓名(英文字符，十个以内)：\n>>>");
	scanf_s("%s", name, 10);//scanf_s后面必须要加读取字符串的最大长度
	printf("年龄：\n>>>");
	scanf_s("%d", &age);
	getchar();//整型后面要加一个getchar（）去换行符
	printf("性别（0或1：女 or 男）：\n>>>");
	scanf_s("%c", &sex);
	printf("分数：\n>>>");
	scanf_s("%f", &score);
	//scanf_s("%d, %d, %f, %c, %s", &i, &age, &score, &sex);
	//i = 0;
	//name = "dufu";
	//age = 12;
	//sex = '1';
	//score = 22;
	p->name = name;
	p->age = age;
	p->sex = sex;
	p->score = score;
	printf("%d, %s, %d, %c, %f\n", i, p->name, p->age, p->sex, p->score);
	ListInsert(L, i, p);
	return;
}
void menu3(Sqlist &L) {
	int i;
	Elemtype *p;
	p = (Elemtype *)malloc(sizeof(Elemtype));
	printf("请输入所要删除数据的序号：\n>>>");
	scanf_s("%d", &i);
	if (!ListDelete(L, i, p)) {
		printf("序号输入有误，删除失败！\n");
		return;
	}
	printf("删除的数据：\n");
	visit(*p);
	return;
}
void menu4(Sqlist &L) {
	int i;
	Elemtype *p;
	p = (Elemtype *)malloc(sizeof(Elemtype));
	printf("请输入要查数据的索引：\n>>>");
	scanf_s("%d", &i);
	if (!GetElem(L, i, p))
		printf("索引值有误， 查询失败！\n");
	else
		visit(*p);
	return;
}
void menu5(Sqlist &L) {
	ClearList(L);
	if (is_empty(L))
		printf("清空成功！\n");
	else
		printf("清空失败！\n");
	return;
}

void main() {
	Sqlist L;
	if (!init(L)) {
		printf("初始化错误！\n");
		system("pause");
		exit(0);
	}
	Elemtype *p;
	p = (Elemtype *)malloc(sizeof(Elemtype));
	p->name = "libai";
	p->age = 233;
	p->sex = '1';
	p->score = 99.5;
	ListInsert(L, 0, p);
	int menu;
	while (true) {
		show_menu();
		scanf_s("%d", &menu);
		//printf("%d", menu);
		getchar();
		switch (menu) {
		case 1:
			
			menu1(L);
			break;
		case 2:
			menu2(L);
			break;
		case 3:
			menu3(L);
			break;
		case 4:
			menu4(L);
			break;
		case 5:
			menu5(L);
			break;
		case 6:
			exit(0);
		default:
			break;
		}
	}

	system("pause");
}

//void main() {
//	Sqlist L;
//	Elemtype *test, *test1, *test2, *test3;
//	Elemtype *e;
//	test = (Elemtype *)malloc(sizeof(Elemtype));
//	//*test->name = 'laaa';
//	//test->name = 'libai';
//	//strcpy_s(test->name, "libai");
//	test->name = "libai";
//	test->age = 20;
//	test->sex = '0';
//	test->score = 11.2;
//
//	if (!init(L)){
//		printf("初始化错误！\n");
//		system("pause");
//		exit(0);
//	}
//	else {
//		printf("Running normal!\n");
//	}
//	printf("%d, %d\n", L.length, L.listsize);
//	if (ListInsert(L, 0, test)) {
//		printf("Running mormal!\n");
//		visit(L.elem[0]);
//	}
//	else
//		printf("error");
//	printf("length of list: %d\n", list_length(L));
//	test1 = (Elemtype *)malloc(sizeof(Elemtype));
//	//strcpy_s(test1->name, "dufu");
//	test1->name = "dufu";
//	test1->age = 44;
//	test1->sex = '1';
//	test1->score = 99.0001;
//	ListInsert(L, 0, test1);
//	
//	e = (Elemtype *)malloc(sizeof(Elemtype));
//
//	test2 = (Elemtype *)malloc(sizeof(Elemtype));
//	//strcpy_s(test2->name, "li qing");
//	test2->name = "li qing";
//	test2->age = 33;
//	test2->sex = '0';
//	test2->score = 100;
//	ListInsert(L, 2, test2);
//	visit(L.elem[0]);
//
//	test3 = (Elemtype *)malloc(sizeof(Elemtype));;
//	//strcpy_s(test3->name, "li qing");
//	test3->name = "li qing";
//	test3->age = 33;
//	test3->sex = '0';
//	test3->score = 100;
//	printf("index : %d\n", LocateElem(L, test3, compare));
//
//	
//	ListDelete(L, 1, e);
//	visit(*e);
//	visit(L.elem[1]);
//
//	printf("length of list: %d\n", list_length(L));
//
//	printf("遍历：\n");
//	ListTraverse(L, visit);
//
//	ClearList(L);
//	if (is_empty)
//		printf("clear success!\n");
//	else
//		printf("clear fault!\n");
//	printf("length of list: %d\n", list_length(L));
//	system("pause");
//}

