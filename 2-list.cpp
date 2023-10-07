#include <iostream>
#include <vector>
#include <string>

/*线性表*/
#define N 50
#define maxSize 100

/*结构体的定义*/

/*顺序表的结构体定义*/
typedef struct
{
    int data[maxSize]; // 存放该顺序表元素的数组
    int length;        // 存放顺序表的长度
} Sqlist;

/*单链表结点定义*/
typedef struct LNode
{
    int data;           // data中存放结点数据域
    struct LNode *next; // 指向后继节点的指针
} LNode;

/*双链表结点定义*/
typedef struct DLNode {
    int data;            // data中存放结点数据域
    struct DLNode *prior;// 指向前驱结点的指针
    struct DLNode *next; // 指向后继节点的指针
}DLNode;

int main(int argc, char const *argv[])
{
    /* code */

    LNode *L = (LNode *)malloc(sizeof(LNode));
    DLNode *DL = (DLNode *)malloc(sizeof(DLNode));
    
    return 0;
}
