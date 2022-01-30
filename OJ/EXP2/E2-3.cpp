/*
题目：
C语言中需要申请一块连续的内存时需要使用malloc等函数。如果分配成功则返回指向被分配内存的指针
(此存储区中的初始值不确定)，否则返回空指针NULL。
现在小明决定实现一个类似malloc的内存分配系统，具体来说，他需要连续处理若干申请内存的请求，这
个请求用一个闭区间[a_i..b_i]来表示。当这个区间和当前已被申请的内存产生重叠时，则返回内存分配
失败的信息。否则返回内存分配成功，并将该区间标记为已被占用。
假设初始状态下内存均未被占用，管理的内存地址范围为0~1GB（0~2^{30}。

输入：输入数据共n+1行。第一行一个整数n表示共需要处理n次内存分配。然后是n行数据，每行的格式为
a_i b_i表示申请区间为[a_i,b_i]。n≤1,000,000，0<a_i\leq b_i \leq 2^{30}。

输出：输出共n行。对于每行内存分配的申请，若申请成功则输出一行0，若申请失败则输出一行-1。

例子：
Input:
5
0 1
8 9
5 7
1 2
2 4
Output:
0
0
0
-1
0
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//区间树结点
typedef struct Interval_Node {
	int color, max, high, low; //1黑 0红              
	struct Interval_Node* left, * right, * parent;
}Interval_Node;

//区间树
typedef struct IntervalTree {
	Interval_Node* root;
	Interval_Node* nil;
}IntervalTree;

//建立区间树
IntervalTree* CREATE_IntervalTree(void) {
	IntervalTree* T;
	T = (IntervalTree*)malloc(sizeof(IntervalTree));
	T->nil = (Interval_Node*)malloc(sizeof(Interval_Node));
	T->nil->low = 0;
	T->nil->high = 0;
	T->nil->max = 0;
	T->nil->color = 1;
	T->nil->left = T->nil->right = T->nil->parent = NULL;
	T->root = T->nil;
	return(T);
}

int Max(int x, int y, int z) {
	if (x < y) return (y > z) ? y : z;
	else return (x > z) ? x : z;
}

//左旋
void LEFT_ROTATE(IntervalTree* T, Interval_Node* x) {
	Interval_Node* y;
	y = x->right;
	x->right = y->left;
	if (y->left != T->nil)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == T->nil)
		T->root = y;
	else if (x->parent->left == x)
		x->parent->left = y;
	else x->parent->right = y;
	y->left = x;
	x->parent = y;
	x->max = Max(x->high, x->left->max, x->right->max);
	y->max = Max(y->high, x->max, y->right->max);
}

//右旋
void RIGHT_ROTATE(IntervalTree* T, Interval_Node* x) {
	Interval_Node* y;
	y = x->left;
	x->left = y->right;
	if (y->right != T->nil)
		y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == T->nil)
		T->root = y;
	else if (x->parent->left == x)
		x->parent->left = y;
	else x->parent->right = y;
	y->right = x;
	x->parent = y;
	x->max = Max(x->high, x->left->max, x->right->max);
	y->max = Max(y->high, y->left->max, x->max);
}

//插入调整 
void  IntervalTree_INSERT_FIXUP(IntervalTree* T, Interval_Node* z) {
	Interval_Node* y;
	while (z->parent->color == 0)
		if (z->parent == z->parent->parent->left) {
			y = z->parent->parent->right;
			if (y->color == 0) {
				z->parent->color = 1;
				y->color = 1;
				z->parent->parent->color = 0;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					LEFT_ROTATE(T, z);
				}
				z->parent->color = 1;
				z->parent->parent->color = 0;
				RIGHT_ROTATE(T, z->parent->parent);
			}
		}
		else {
			y = z->parent->parent->left;
			if (y->color == 0) {
				z->parent->color = 1;
				y->color = 1;
				z->parent->parent->color = 0;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					RIGHT_ROTATE(T, z);
				}
				z->parent->color = 1;
				z->parent->parent->color = 0;
				LEFT_ROTATE(T, z->parent->parent);
			}
		}
	T->root->color = 1;
}

//区间树插入
void IntervalTree_INSERT(IntervalTree* T, Interval_Node* z) {
	Interval_Node* x, * y;
	x = T->root;
	y = T->nil;
	while (x != T->nil) {
		y = x;
		if (y->max < z->high)
			y->max = z->high;
		if (z->low < x->low)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if (y == T->nil)
		T->root = z;
	else if (z->low < y->low)
		y->left = z;
	else y->right = z;
	z->left = z->right = T->nil;
	z->color = 0;
	IntervalTree_INSERT_FIXUP(T, z);
}

//两区间重叠检查
int check(int a, int b, Interval_Node* x) {
	return (a <= x->high && x->low <= b);
}

//区间树重叠搜索
Interval_Node* SEARCH_IntervalTree(IntervalTree* T, int a,int b) {
	Interval_Node* x;
	x = T->root;
	while (x != T->nil && !check(a,b,x)) {
		if (x->left != T->nil && x->left->max >= a)
			x = x->left;
		else x = x->right;
	}
	if (x == T->nil) return(NULL);
	else return(x);
}


int main() {
	int n, i, a, b;
	IntervalTree* T = CREATE_IntervalTree();
	Interval_Node* x,*z;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d%d", &a,&b);
		if ((x = SEARCH_IntervalTree(T, a, b)) != NULL)
			printf("-1\n");
		else{
			z = (Interval_Node*)malloc(sizeof(Interval_Node));
			z->low = a;
			z->high = b;
			z->max = b;
			IntervalTree_INSERT(T, z);
			printf("0\n");
		}
	}
	return 0;
}