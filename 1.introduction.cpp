#include <iostream>
#include <vector>
#include <string>

/*数据类型的定义*/

#define N 50
#define maxSize 50

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode;

typedef struct Sqlite
{
    int data[maxSize];
    int length;
} Sqlite;

int main(int argc, char const *argv[])
{

    /*结构型
     * 数组
     * 结构体
     */
    int a[maxSize]; // 顺序数组

    int *p; // 动态数组
    p = (int *)malloc(sizeof(int));

    typedef struct // 结构体
    {
        int a;
        char b;
        float c;
    } TypeA;

    /*指针型*/

    int *a;
    char *b;
    float *c;
    TypeA *d;

    /*结点的构造
     * 链表
     * 二叉树
     */

    typedef struct Node // 链表结点
    {
        int data;          // 这里默认的是int型，如需其他类型可修改
        struct Node *next; // 指向Node型变量的指针
    } Node;

    typedef struct BTNode // 二叉树结点
    {
        int data;
        struct BTNode *lchild;
        struct BTNode *rchild;
    } BTNode;

    BTNode *BT;                            // 声明结点
    BT = (BTNode *)malloc(sizeof(BTNode)); // 此句要熟练掌握

    return 0;
}

/*函数*/

/*被传入函数的参数是否会改变
 * 要注意的是，数组作为参数，当前场景都是引用型，不做引用和非引用区分
 */

void f(int x[], int n) // 一维数组作为参数，n为操作数一般与数组长度一致
{
}

void f2(int x[][maxSize], int n) // 二维数组作为参数
{
}

/*关于参数引用型的其他例子*/

void insert(Sqlite &L, int x)
{ // 因为L本身要发生改变，所以用引用型
    int p, i;
    p = LocateElem(L, x);
    for (i = L.length - 1; i >= p; --i)
        L.data[i + 1] = L.data[i];
    L.data[p] = x;
    ++(L.length);
}

int SearchAndDelete(LNode *C, int x)
{
    LNode *p, *q;
    p = C;
    while (p->next != NULL)
    {
        if (p->next->data == x)
        {
            break;
        }
        p = p->next;
    }
    if (p->next == NULL)
    {
        return 0;
    }
    else
    {
        q = p->next;
        p->next = q->next->next;
        free(q);
        return 1;
    }
}

void merge(LNode *A, LNode *B, LNode *&C)
{ // LNode *&C这种声明方式允许函数修改传递给它的指针 C 指向的对象，而不只是对象本身。
    LNode *p = A->next;
    LNode *q = B->next;
    LNode *r;
    C = A;
    C->next = NULL;
    free(B);
    r = C;
    //...省略
}

/*有返回值的函数*/
int f(int a)
{
    return a;
}
