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

/*双链表的操作
 * 1. 建表(尾插法)
 * 2. 查找结点的算法
 * 3. 插入结点的算法(在p后边插入x)
 * 4. 删除结点的算法(删除p的后继结点)
 */

// 1
void createDlistR(DLNode *&L, int a[], int n)
{
    DLNode *s, *r;
    int i;
    L = (DLNode *)malloc(sizeof(DLNode));
    L->prior = NULL;
    L->next = NULL;
    r = L;
    for (i = 0; i < n; ++i)
    {
        s = (DLNode *)malloc(sizeof(DLNode));
        s->data = a[i];
        // 下边3句将s插入到L尾部，并且r指向s，s->prior = r；这一句是和建立单链表不同的地方
        r->next = s;
        s->prior = r;
        r = s;
    }
    r->next = NULL;
}

// 2
DLNode *findDLNode(DLNode *C, int x)
{
    DLNode *p = C->next;
    while (p != NULL)
    {
        if (p->data == x)
        {
            break;
        }
        p = p->next;
    }
    return p; // 如果找到，则p中内容是结点地址（循环因break结束）。如果没找到则p中内容是NULL（循环因p等于NULL而结束）。因此这一句可以将两种返回值的情况统一起来
}

// 3
void insertDLNode(DLNode *C, int x, int p)
{
    DLNode *s, *r;
    r = findDLNode(C, p);
    s = (DLNode *)malloc(sizeof(DLNode));
    s->data = x;

    s->next = r->next; // 先链入要插入的结点前驱和后继指向
    s->prior = r;
    r->next = s; // 更新插入结点的前驱和后继结点的指向
    if (s->next != NULL)
    {
        s->next->prior = s;
    }
}

// 4
void deleteDLNode(DLNode *C, int p)
{
    DLNode *s, *r;
    r = findDLNode(C, p);

    s = r->next;
    r->next = s->next;
    s->next->prior = r;
    free(s);
}

/*循环链表的操作 （表尾结点 p->next == head）, 操作与非循环链表类似*/

/*逆置问题
 * 1. 将一长度为n的数组的前端k(k<n)个元素逆序后移动到数组后端，要求原数组中数据不丢失，其余元素的位置无关紧要
 * 2. 将一长度为n的数组的前端k(k<n)个元素保持原序移动到数组后端，要求原数组中数据不丢失，其余元素的位置无关紧要
 * 3. 将数组中的元素(X0, X1,···,X(n-1)),经过移动后变为(Xp, x(p+1),···,X(n-1), X0, X1,···，X(p-1)),即循环左移p(0<p<n)个位置
 */

// 1 只需逆置整个数组即可满足要求
void reverse(int a[], int left, int right, int k)
{
    int temp;
    for (int i = left, j = right; i < left + k && i < j; ++i, --j)
    {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}

// 2 只需将前端k个元素逆置，然后将整个数组逆置，即可满足要求
void moveToEnd(int a[], int n, int k)
{
    reverse(a, 0, k - 1, k);
    reverse(a, 0, n - 1, k);
}

// 3 只需将0~p-1个位置的元素逆置，再将p~n-1位置的元素逆置，然后将整个数组逆置即可
void moveP(int a[], int n, int p)
{
    reverse(a, 0, p - 1, p);
    reverse(a, p, n - 1, n - p);
    reverse(a, 0, n - 1, n);
}

/*仿真题
 * 1. 设顺序表用数组A[]表示，表中元素存储在数组下标0~m+n+1的范围内，前m个元素递增有序，后n个元素也递增有序，设计一个算法，使得整个顺序表有序。
 * (1) 给出算法的基本设计思想。
 * (2) 根据设计思想，采用C或C++语言描述算法，并在关键处给出注释。
 * (3) 说明你所设计的算法的时间复杂度和空间复杂度
 * 2. 已知递增有序的单链表A、B(A、B中元素个数分别为m、n, 且A、B都带有头结点)分别存储了一个集合，请设计算法，以求出两个集合A和B的差集A-B（仅由在A中出现而不在B中出现的元素所构成的集合）。将差集保存在单链表A中，并保持元素的递增有序性。
 * (1) 给出算法的基本设计思想
 * (2) 根据设计思想，采用C或C++语言描述算法，并在关键处给出注释。
 * (3) 说明你所设计的算法的时间复杂度和空间复杂度
 */

// 1
/* (1)
 * 将数组A[]中的m+n个元素看成是两个顺序表：表L和表R。将数组当前状态看做起始状态，即此时表L由A[]中前m个元素构成，表R由A[]中后n个元素构成。要使A[]中m+n个元素整体有序，只需将表R中的元素逐个插入表L中的合适位置即可。
 * 插入过程：取表R中的第一个元素A[m]存入辅助变量temp中，让temp逐个与A[m-1],···,A[0]进行比较，当temg<A[j](0<=j<=m-1)时，将A[j]后移一位，否则将temp存入A[j+1]中。重复上述过程，继续插入A[m+1],A[m+1],···,A[m+n-1]，最终A[]中元素整体有序。
 */

// (2)
void insertElem(int A[], int m, int n)
{
    int i, j;
    int temp;                   // 辅助变量，用来暂存待插入元素
    for (i = m; i < m + n; ++i) // 将A[m,···,m+n-1]插入到A[0,···,m-1]中
    {
        temp = A[i];
        for (j = i - 1; j >= 0 && temp < A[j]; --j)
        {
            A[j + 1] = A[j]; // 元素后移，以便腾出一个位置插入temp
        }
        A[j + 1] = temp; // 插入temp，由于for循环后j多前移了一位，因此在j+1处插入
    }
}

// (3) 时间复杂度 O(mn): 取A[j + 1] = A[j]为基础操作。 空间复杂度 O(1)。

// 2 (1）略 (2)
void difference(LNode *A, LNode *B)
{
    LNode *p = A->next; // p和q是两个辅助指针
    LNode *q = B->next; // pre为A中p所指结点的前驱结点的指针
    LNode *pre = A;
    LNode *r;
    while (p != NULL && q != NULL)
    {
        if (p->data < q->data)
        {
            pre = p;
            p = p->next; // A链表中当前节点指针后移
        }
        else if (p->data > q->data)
        {
            q = q->next; // B链表中当前节点指针后移
        }
        else
        {
            r = p; // 处理A、B中元素值相同的结点，应删除
            pre->next = p->next;
            p = p->next;
            free(r); // 释放结点空间
        }
    }
}

// (3) O(m+n)

/* 一.
 * 1. A
 * 2. B
 * 3. C
 * 4. A
 * 5. D
 * 6. C
 * 7. B
 * 8. A
 * 9. D -> B
 * 10. B
 * 11. B
 * 12. B
 * 13. D
 * 14. A
 * 15. D
 * 16. D
 * 17. A
 * 18. D
 * 19. C
 * 20. A
 * 21. C -> B
 * 22. B
 * 23. D
 * 24. D
 * 25. C
 * 26. C
 * 27. C
 * 28. D
 * 29. D
 * 30. B
 * 31. ① B -> C ② B ③ A
 */