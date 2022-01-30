#include<stdlib.h>
#include<iostream>
#include<assert.h>
using namespace std;

typedef enum ColorType { RED, BLACK } ColorType;

typedef struct interval {
    int low;
    int high;
}Interval;

typedef struct rbt {
    Interval interval;
    int max;
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
rbt_root* rbt_insert(rbt_root*& T, int low, int high);
void rbt_left_rotate(rbt_root* T, rbt* x);
void rbt_right_rotate(rbt_root* T, rbt* x);
bool rbt_judge(rbt_root* T, int low, int high);
void print_tree(rbt_root* T);
int get_max(int high, int left, int right);

int get_max(int high, int left, int right) {
    int temp = (left > right) ? left : right;
    return (temp > high) ? temp : high;
}

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
    else if (y->interval.low < y->p->interval.low)
        y->p->left = y;
    else
        y->p->right = y;

    y->left = x;
    x->p = y;

    x->max = get_max(x->interval.high, x->left->max, x->right->max);
    y->max = get_max(y->interval.high, y->left->max, y->right->max);
}
void rbt_right_rotate(rbt_root* T, rbt* x) {
    rbt* y = x->left;
    x->left = y->right;

    if (T->nil != x->left)
        x->left->p = x;

    y->p = x->p;
    if (y->p == T->nil)
        T->root = y;
    else if (y->interval.low < y->p->interval.low)
        y->p->left = y;
    else
        y->p->right = y;

    y->right = x;
    x->p = y;

    x->max = get_max(x->interval.high, x->left->max, x->right->max);
    y->max = get_max(y->interval.high, y->left->max, y->right->max);
}
void rbt_handleReorient(rbt_root* T, rbt* x, int k) {
    //�ڵ�һ������£�������ɫ��ת�� �ڵڶ�������£��൱�ڶ��²����x���ʼ��
    x->color = RED;
    x->left->color = x->right->color = BLACK;

    //���x.pΪ��ɫ����ôx.pһ�����Ǹ���x.p.pһ������T.nil������Ϊ��ɫ
    if (RED == x->p->color) {
        x->p->p->color = RED;//��ʱx, p, x.p.p��Ϊ��

        if (x->p->interval.low < x->p->p->interval.low) {
            if (k > x->p->interval.low) {
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
            if (k < x->p->interval.low) {
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

rbt_root* rbt_insert(rbt_root*& T, int low, int high) {
    rbt* x, * p;
    x = T->root;
    p = x;

    if (!rbt_judge(T, low, high)) {
        cout << -1 << endl;
        return T;
    }
    cout << 0 << endl;

    //��x�³���Ҷ���ϣ����ұ�֤һ·�ϲ�����ͬʱΪ��ɫ���ֵ�
    while (x != T->nil) {
        //
        //��֤û��һ���ֵ�ͬʱΪ��ɫ�� ΪʲôҪ��ô����
        if (x != T->nil)
            if (x->left->color == RED && x->right->color == RED)
                rbt_handleReorient(T, x, low);

        p = x;
        if (low < x->interval.low) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }

    //Ϊx����ռ䣬��������г�ʼ��
    x = (rbt*)malloc(sizeof(rbt));
    assert(NULL != x);
    x->interval.low = low;
    x->interval.high = high;
    x->color = RED;
    x->left = x->right = T->nil;
    x->p = p;

    //��x�ĸ���ָ��x
    if (T->root == T->nil)
        T->root = x;
    else if (low < p->interval.low)
        p->left = x;
    else
        p->right = x;

    //��Ϊһ·���������x�ĸ����Ǻ�ɫ����ôx������϶����Ǻ�ɫ�ˣ����ʱ��ֻ��Ҫ��һ�·�ת���ɡ�
    rbt_handleReorient(T, x, low);
    return T;
}

bool rbt_judge(rbt_root* T, int low, int high) {

    rbt* x = T->root;
    rbt* p = x;
    while (x != T->nil) {
        if (low <= x->interval.high && high >= x->interval.low) { return false; }
        if (low > x->interval.low) { p = x; x = x->right; }
        else if (low < x->interval.low) { p = x; x = x->left; }
    }
    return true;
}

void print_tree(rbt_root* T, rbt* x) {
    if (x != T->nil) {
        print_tree(T, x->left);
        cout << x->interval.low << x->color << endl;
        print_tree(T, x->right);
    }
}

int main() {
    int num;
    int i;
    int low, high;
    rbt_root* T = rbt_init();
    cin >> num;
    for (i = 0; i < num; i++) {
        cin >> low >> high;
        rbt_insert(T, low, high);
    }
    return 0;
}