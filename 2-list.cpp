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
typedef struct DLNode
{
    int data;             // data中存放结点数据域
    struct DLNode *prior; // 指向前驱结点的指针
    struct DLNode *next;  // 指向后继节点的指针
} DLNode;

int main(int argc, char const *argv[])
{
    /* code */

    LNode *L = (LNode *)malloc(sizeof(LNode));
    DLNode *DL = (DLNode *)malloc(sizeof(DLNode));

    return 0;
}

/*顺序表的操作
 * 1. 按元素值的查找算法
 * 2. 插入数据元素的算法
 * 3. 顺序表的初始化
 * 4. 求指定位置元素的算法
 * 5. 删除指定位置的元素的算法
 */

// 1
int findElem(Sqlist L, int e)
{
    int i;
    for (i = 0; i < L.length; ++i)
    {
        if (e == L.data[i])
        {
            return i; // 若找到，则返回下标
        }
    }
    return -1; // 没找到，返回-1， 作为失败标记
}

// 2
int insertElem(Sqlist &L, int p, int e)
{
    int i;
    if (p < 0 || p > L.length || L.length == maxSize) // 位置错误或者表长已经达到
    {
        return 0; // 顺序表的最大允许值，此时插入不成功，返回0
    }
    for (i = L.length - 1; i >= p; --i)
    {
        L.data[i + 1] = L.data[i]; // 从后往前，逐个将元素往后移动一个位置
    }
    L.data[p] = e; // 将e放在插入位置p上
    ++(L.length);  // 表内元素多了一个，因此表长自增1
    return 1;      // 插入成功，返回1
}

// 3

void initList(Sqlist &L) // L本身要发生变化，所以用引用型
{
    L.length = 0;
}

// 4

int getElem(Sqlist L, int p, int &e) // 要改变，所以用引用型
{
    if (p < 0 || p > L.length - 1) // p值越界错误，返回0
    {
        return 0;
    }
    e = L.data[p];
    return 1
}

// 5
int deleteElem(Sqlist &L, int p, int &e) // 需要改变的变量用引用型
{
    int i;
    if (p < 0 || p > L.length - 1)
    {
        return 0; // 位置不对返回0， 代表删除不成功
    }
    e = L.data[p];                     // 将被删除元素赋值给e
    for (i = p; i < L.length - 1; ++i) // 从p位置开始，将其后边的元素逐个前移一个位置
    {
        L.data[i] = L.data[i + 1];
    }
    --(L.length); // 表长减1
    return 1;     // 删除成功，返回1
}

/*单链表的操作*/

/*双链表的操作*/

/*循环链表的操作*/

/*逆置问题*/
