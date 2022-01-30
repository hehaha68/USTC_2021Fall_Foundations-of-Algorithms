/*
��Ŀ��
�ڷܵ�С��Ϊ��Ԥϰ��ѧ�ڵ����ݿ�γ̣���������ʵ��һ���򵥵����ݿ�ϵͳ�������ݿ�ϵͳ��Ҫ�����û���
���ݿ����Ͳ�ѯ��䣬�������Ӧ�������������˵���û������빲�����������������Ͳ�ѯ��䡣����ÿ
������������һ���Ǹ�������ʾ��Ҫ��������ݡ�ÿ����ѯ������һ��������ʾ����ѯ�ļ�ֵ�����ü�ֵ��
����ֱ������ü�ֵ������������ݿ��бȸü�ֵС������ֵ��

���룺�����������в�����䣬ÿ�еĸ�ʽΪ���µ�һ�֣�
INSERT key
FIND key
��󵥶���һ��EXIT��ʾ���������
�������Ͳ�ѯ���һ��������2,000,000����0��key��10^9��

�������ÿ����ѯ������һ�У�ÿ�����1�����֣���ʾ��ѯ�Ľ�����ü�ֵ������ֱ������ü�ֵ���������
���ݿ��бȸü�ֵС������ֵ��

���ӣ�
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
	int color, key, size, prop; //1�� 0��              
	struct RBT_Node* left, * right, * parent;
}RBT_Node;

typedef struct RBT {
	RBT_Node* root;
	RBT_Node* nil;
}RBT;

//���������
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

//����
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

//����
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

//������� 
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