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
    return 1;
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

/*单链表的操作（默认是带头结点的链表）
 * 1. 建表（尾插法）
 * 2. 建表（头插法）
 * 3. 合并两个单链表（升序）
 * 4. 合并两个单链表（降序）
 * 5. 查找及删除结点
 */

// 1
void createllistR(LNode *&C, int a[], int n) // 要改变的变量用引用型
{
    LNode *s, *r; // s用来指向新申请的结点，r始终指向C的终端结点
    int i;
    C = (LNode *)malloc(sizeof(LNode)); // 申请C的头结点空间
    C->next = NULL;
    r = C;                  // r指向头结点，因为此时头结点就是终端结点
    for (i = 0; i < n; ++i) // 循环申请n个结点来接收数组a中的元素
    {
        s = (LNode *)malloc(sizeof(LNode)); // s指向新申请的结点
        s->data = a[i];                     // 用新申请的结点来接收a中的一个元素
        r->next = s;                        // 用r来接纳新结点
        r = r->next;                        // r指向终端结点，以便于接纳下一个到来的结点
    }
    r->next = NULL; // 数组a中所有的元素都已经装入链表C中， C的终端结点的指针域置为NULL，C建立完成
}

// 2
void createlistF(LNode *&C, int a[], int n)
{
    LNode *s;
    int i;
    C = (LNode *)malloc(sizeof(LNode));
    C->next = NULL;
    for (i = 0; i < n; ++i)
    {
        s = (LNode *)malloc(sizeof(LNode));
        s->data = a[i];
        // 下边两句是头插法的关键步骤
        s->next = C->next; // s所指新结点的指针域next指向C中的开始结点
        C->next = s;       // 头结点的指针域next指向s结点，使得s成为新的开始结点
    }
}

// 3
void mergeA(LNode *A, LNode *B, LNode *&C)
{
    LNode *p = A->next; // p来跟踪A的最小值结点
    LNode *q = B->next; // q来跟踪B的最小值结点
    LNode *r;           // r始终指向C的终端结点
    C = A;              // 用A的头结点来做C的头结点
    C->next = NULL;
    free(B);                       // B的头结点已无用，则释放掉
    r = C;                         // r指向C，因为此时头结点也是终端结点
    while (p != NULL && q != NULL) // 当p与q都不空时没选取p与q所指结点中的较小者插入C的尾部
    {
        // 尾插法思想
        if (p->data <= q->data)
        {
            r->next = p;
            p = p->next;
            r = r->next;
        }
        else
        {
            r->next = q;
            q = q->next;
            r = r->next;
        }
    }
    r->next = NULL;
    if (p != NULL)
    {
        r->next = p;
    }

    if (q != NULL)
    {
        r->next = q;
    }
}

// 4
void merge(LNode *A, LNode *B, LNode *&C)
{
    LNode *p = A;
    LNode *q = B;
    LNode *s;
    C = A;
    C->next = NULL;
    free(B);
    while (p != NULL && q != NULL)
    {
        // 头插法思想
        if (p->data <= q->data)
        {
            s = p;
            p->next = C->next;
            C->next = s;
        }
        else
        {
            s = q;
            q = q->next;
            s->next = C->next;
            C->next = s;
        }
    }

    /*下边这两个循环是和求递增归并序列不同的地方，必须将剩余元素逐个插入C的头部才能得到最终的递减序列*/
    while (p != NULL)
    {
        s = p;
        p = p->next;
        s->next = C->next;
        C->next = s;
    }

    while (q != NULL)
    {
        s = q;
        q = q->next;
        s->next = C->next;
        C->next = s;
    }
}

// 5

int findAndDeleteL(LNode *C, int x)
{
    LNode *p, *q;
    p = C;
    /*查找部分开始*/
    while (p->next != NULL)
    {
        if (p->next->data == x)
        {
            break;
        }
        p = p->next;
    }
    /*查找部分结束*/
    if (p->next == NULL)
    {
        return 0;
    }
    else
    {
        /*删除部分开始*/
        q = p->next;
        p->next = p->next->next;
        free(q);
        /*删除部分结束*/
        return 1;
    }
}

/*双链表的操作*/

/*循环链表的操作*/

/*逆置问题*/
