#include<stdlib.h>
#include<iostream>
#include<assert.h>
using namespace std;

typedef enum ColorType { RED, BLACK } ColorType;
typedef struct rbt {
    int key;
    rbt* left;
    rbt* right;
    rbt* p;
    ColorType color;
}rbt;

typedef struct rbt_root {
    rbt* root;
    rbt* nil;
}rbt_root;

rbt_root* rbt_init(void);
void rbt_handleReorient(rbt_root* T, rbt* x, int k);
rbt_root* rbt_insert(rbt_root*& T, int k);
void rbt_left_rotate(rbt_root* T, rbt* x);
void rbt_right_rotate(rbt_root* T, rbt* x);
void rbt_search(rbt_root* T, int k);
void find_preccessor(rbt_root* T, rbt* x, int k);
void print_tree(rbt_root* T);

rbt_root* rbt_init(void) {
    rbt_root* T;

    T = (rbt_root*)malloc(sizeof(rbt_root));
    assert(NULL != T);

    T->nil = (rbt*)malloc(sizeof(rbt));
    assert(NULL != T->nil);
    T->nil->color = BLACK;
    T->nil->left = T->nil->right = NULL;
    T->nil->p = NULL;

    T->root = T->nil;
    return T;
}
void rbt_left_rotate(rbt_root* T, rbt* x) {
    rbt* y = x->right;

    x->right = y->left;
    if (x->right != T->nil)//����ĳ���ĸ���ʱ��Ҫȷ���˽�㲻��T.nil
        x->right->p = x;

    y->p = x->p;
    if (x->p == T->nil) {//���x��ǰ����������ô��������������
        T->root = y;
    }
    else if (y->key < y->p->key)
        y->p->left = y;
    else
        y->p->right = y;

    y->left = x;
    x->p = y;
}
void rbt_right_rotate(rbt_root* T, rbt* x) {
    rbt* y = x->left;
    x->left = y->right;

    if (T->nil != x->left)
        x->left->p = x;

    y->p = x->p;
    if (y->p == T->nil)
        T->root = y;
    else if (y->key < y->p->key)
        y->p->left = y;
    else
        y->p->right = y;

    y->right = x;
    x->p = y;
}
void rbt_handleReorient(rbt_root* T, rbt* x, int k) {
    //�ڵ�һ������£�������ɫ��ת�� �ڵڶ�������£��൱�ڶ��²����x���ʼ��
    x->color = RED;
    x->left->color = x->right->color = BLACK;

    //���x.pΪ��ɫ����ôx.pһ�����Ǹ���x.p.pһ������T.nil������Ϊ��ɫ
    if (RED == x->p->color) {
        x->p->p->color = RED;//��ʱx, p, x.p.p��Ϊ��

        if (x->p->key < x->p->p->key) {
            if (k > x->p->key) {
                x->color = BLACK;
                rbt_left_rotate(T, x->p);
                rbt_right_rotate(T, x->p);
            }
            else {
                x->p->color = BLACK;
                rbt_right_rotate(T, x->p->p);
            }

        }
        else {
            if (k < x->p->key) {
                x->color = BLACK;
                rbt_right_rotate(T, x->p);
                rbt_left_rotate(T, x->p);
            }
            else {
                x->p->color = BLACK;
                rbt_left_rotate(T, x->p->p);
            }
        }
    }
    T->root->color = BLACK;//���������Ϊ��ɫ
}
rbt_root* rbt_insert(rbt_root*& T, int k) {

    rbt* x, * p;
    x = T->root;
    p = x;

    //��x�³���Ҷ���ϣ����ұ�֤һ·�ϲ�����ͬʱΪ��ɫ���ֵ�
    while (x != T->nil) {
        //
        //��֤û��һ���ֵ�ͬʱΪ��ɫ�� ΪʲôҪ��ô����
        if (x != T->nil)
            if (x->left->color == RED && x->right->color == RED)
                rbt_handleReorient(T, x, k);

        p = x;
        if (k < x->key)
            x = x->left;
        else {
            x = x->right;
        }
    }

    //Ϊx����ռ䣬��������г�ʼ��
    x = (rbt*)malloc(sizeof(rbt));
    assert(NULL != x);
    x->key = k;
    x->color = RED;
    x->left = x->right = T->nil;
    x->p = p;

    //��x�ĸ���ָ��x
    if (T->root == T->nil)
        T->root = x;
    else if (k < p->key)
        p->left = x;
    else
        p->right = x;

    //��Ϊһ·���������x�ĸ����Ǻ�ɫ����ôx������϶����Ǻ�ɫ�ˣ����ʱ��ֻ��Ҫ��һ�·�ת���ɡ�
    rbt_handleReorient(T, x, k);
    return T;
}
void rbt_search(rbt_root* T, int k) {
    bool find = false;
    rbt* x = T->root;
    rbt* p = x;
    while (x != T->nil) {
        if (k > x->key) { p = x; x = x->right; }
        else if (k < x->key) { p = x; x = x->left; }
        else { cout << k << endl; find = true; break; }
    }
    if (!find) {
        find_preccessor(T, p, k);
    }
}

void find_preccessor(rbt_root* T, rbt* x, int k) {
    if (k > x->key) {
        cout << x->key << endl;
        return;
    }
    else {
        while (x != x->p->right) {
            x = x->p;
        }
        cout << x->p->key << endl;
        return;
    }
}

void print_tree(rbt_root* T, rbt* x) {
    if (x != T->nil) {
        print_tree(T, x->left);
        cout << x->key << x->color << endl;
        print_tree(T, x->right);
    }
}

int main() {
    rbt_root* T = rbt_init();
    char* str = (char*)malloc(7 * sizeof(char));
    int num;

    while (true) {
        cin >> str;
        if (str[0] == 'E') { break; }
        cin >> num;
        if (str[0] == 'I') {
            T = rbt_insert(T, num);
        }
        else {
            rbt_search(T, num);
        }
    }
    return 0;
}