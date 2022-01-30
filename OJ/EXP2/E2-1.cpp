/*
题目：
勤奋的小明为了预习下学期的数据库课程，决定亲自实现一个简单的数据库系统。该数据库系统需要处理用户的
数据库插入和查询语句，并输出相应的输出。具体来说，用户的输入共包含若干条插入语句和查询语句。其中每
条插入语句包含一个非负整数表示需要插入的数据。每条查询语句包含一个整数表示待查询的键值，若该键值存
在则直接输出该键值，否则输出数据库中比该键值小的最大键值。

输入：首先是若干行插入语句，每行的格式为如下的一种：
INSERT key
FIND key
最后单独的一行EXIT表示输入结束。
插入语句和查询语句一共不超过2,000,000条。0≤key≤10^9。

输出：对每条查询语句输出一行，每行输出1个数字，表示查询的结果。该键值存在则直接输出该键值，否则输出
数据库中比该键值小的最大键值。

例子：
Input:
INSERT 7
INSERT 11
INSERT 2
FIND 2
INSERT 5
INSERT 3
FIND 4
FIND 7
EXIT

Output:
2
3
7
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct RBT_Node {
	int color, key, size, prop; //1黑 0红              
	struct RBT_Node* left, * right, * parent;
}RBT_Node;

typedef struct RBT {
	RBT_Node* root;
	RBT_Node* nil;
}RBT;

//建立红黑树
RBT* CREATE_RBT(void) {
	RBT* T;
	T = (RBT*)malloc(sizeof(RBT));
	T->nil = (RBT_Node*)malloc(sizeof(RBT_Node));
	T->nil->color = 1;
	T->nil->left = T->nil->right = T->nil->parent = NULL;
	T->nil->size = 0;
	T->root = T->nil;
	return(T);
}

//左旋
void LEFT_ROTATE(RBT* T, RBT_Node* x) {
	RBT_Node* y;
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
	y->size = x->size;
	x->size = x->left->size + x->right->size + 1;
}

//右旋
void RIGHT_ROTATE(RBT* T, RBT_Node* x) {
	RBT_Node* y;
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
	y->size = x->size;
	x->size = x->left->size + x->right->size + 1;
}

//插入调整 
void  RB_INSERT_FIXUP(RBT* T, RBT_Node* z) { 
	RBT_Node* y;
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

void RB_INSERT(RBT* T, RBT_Node* z) {
	RBT_Node* x, * y;
	x = T->root; 
	y = T->nil;
	while (x != T->nil){
		x->size++;
		y = x;
		if (z->key < x->key) 
			x = x->left;
		else x = x->right;
	}
	z->parent = y;
	if (y == T->nil) 
		T->root = z;
	else if (z->key < y->key) 
		y->left = z;
	else y->right = z;
	z->left = z->right = T->nil;
	z->color = 0;
	z->size = 1;
	RB_INSERT_FIXUP(T, z);
}


struct RBT_Node* SEARCH_BRT(RBT* T, int k){
	RBT_Node* x;
	x = T->root;
	while (x != T->nil && x->key != k) {
		if (k < x->key)
			x = x->left;
		else x = x->right;
	}
	if (x == T->nil) return(NULL); 
	else return(x);
}


int main(){
	int n, i, num, r;
	char s[10];
	RBT* T = CREATE_RBT();
	RBT_Node* z, * y, * x;
	scanf("%s", s);
	while (s[0] != 'E'){
		scanf("%d", &num);

		if (s[0] == 'I'){
			y = SEARCH_BRT(T, num);
			if (y == NULL){
				z = (RBT_Node*)malloc(sizeof(RBT_Node));
				z->key = num;
				RB_INSERT(T, z);
			}
		}
		else if (s[0] == 'F'){
			y = SEARCH_BRT(T, num);
			if (y == NULL) printf("-1");
			else printf("%d\n", num);
		}
		scanf("%s", s);
	}
}