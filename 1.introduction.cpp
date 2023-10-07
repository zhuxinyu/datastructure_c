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
