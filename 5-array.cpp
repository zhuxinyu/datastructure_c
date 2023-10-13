#include <iostream>
#include <vector>
#include <string>

/*数组、矩阵与广义表*/
#define N 50
#define maxSize 100

/**
 * 数组常用的两种逻辑表示：
 * 1. 一维数组 (a0,a1,···,a(n-1))
 * 2. 二维数组 [(a(0,0),a(0,1),···,a(0,n-1)),
 *             (a(1,0),a(1,1),···,a(1,n-1)),
 *                      ···,
 *             (a(n-1,0),a(n-1,1),···,a(n-1,n-1))]
 */

/**
 * 二维数组的行优先和列优先存储
 * 常见题型：计算某元素下标
 */

/**
 * 矩阵的压缩存储
 * 1. 矩阵的定义及基础计算：转置、相加、相乘
 * 2. 特殊矩阵和稀疏矩阵
 *  ①特殊矩阵：对称矩阵、三角阵、对角矩阵
 *  ②稀疏矩阵的顺序存储：三元组表示法、伪地址表示法
 *  ③稀疏矩阵的链式存储：邻接表表示法、十字链表表示法
 */

/**
 * 矩阵：
 * 定义的简单方式：int A[m][n];
 */

// 转置
void trsmat(int A[][maxSize], int B[][maxSize], int m, int n)
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            B[j][i] = A[i][j];
        }
    }
}

// 相加
void addmat(int C[][maxSize], int A[][maxSize], int B[][maxSize], int m, int n)
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

/**
 * 相乘
 * 注意矩阵相乘要求A(前)(mxn)的列数必须等于B(后)(nxk)的行数。
 *
 */
void mutmat(int C[][maxSize], int A[][maxSize], int B[][maxSize], int m, int n, int k)
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < k; ++j)
        {
            C[i][j] = 0; // 因为下列操作是加法所以要初始化
            for (int h = 0; h < n; ++h)
            {
                C[i][j] += A[ih] * B[h][j];
            }
        }
    }
}

/**
 * 特殊矩阵
 * 1. 对称矩阵：矩阵中的二元素满足a(i,j) = a(j,i)的矩阵称为对称矩阵， 由于对角线上下方元素先等，所以一般三角阵加对角线元素保存即可。
 * 2. 三角阵：上/下三角阵为矩阵上/下三角阵部分（不包括对角线）元素全为c(c可为0)的矩阵。存储方式和对称矩阵类似，只需存储对角线及其上/下三角的一个元素c即可。
 * 3. 对角矩阵：其特点是除主对角线以及其上下两条带状区域内的元素外，其余元素皆为c(c可为0);
 */

/**
 * 稀疏矩阵
 * 稀疏矩阵中的相同元素c（假设c为0）在矩阵中的分布不像特殊矩阵中那么有规律可循，因此必须为其设计一些特殊的存储结构。
 */

/**
 * 三元组表示法
 * int trimat[maxterms+1][3]
 * +1是为表单首行，数据和行标为三个元素:0,1,2
 */
typedef struct
{
    int val;  // 数据
    int i, j; // 行下标和列下标
} Trimat;

/**
 * 伪地址表示法
 * 即元素在矩阵中按照行优先或者列优先存储的相对位置。和三元组方法想死，只是三元组每行中有两个存储单元存放地址，而伪地址法只需要一个，因此伪地址法每一行只有两个存储单元，一个用来存放矩阵元素值，另一个用来存放伪地址，这种方法需要2N个存储单元，N为非零元素个数，对于一个mxn的系数矩阵A，元素A[i][j]的伪地址计算方法为n(i-1)+j。根据这个公式，不仅可以计算矩阵中一个给定元素的伪地址，还可以反推出给定元素在原矩阵中的真实地址。
 */

/**
 * 稀疏矩阵的链式存储及其相关操作
 * 1. 邻接表表示法：将矩阵中每一行的非零元素串成一个链表，链表节点中有两个分量，分别表示该结点对应的元素值及其列号。
 * 2. 十字链表表示法：矩阵的每一行和每一列分别用一个带头结点的链表表示，链表结点有5个分量：行分量、列分量、数据域分量、指向下方结点的指针、指向右方结点的指针。
 */

/* 十字链表的两种结点的结构定义*/

// 普通结点

typedef struct OLNode
{
    int row, col;                // 行号和列号
    struct OLNode *right, *down; // 指向右边结点和下方结点的指针
    float val;
} OLNode;

// 头结点
typedef struct
{
    OLNode *rhead, *chead; // 指向两头结点数组的指针
    int m, n, k;           // 矩阵行数、列数以及非零结点总数
} CrossList;

int createcrossListmat(float A[][maxSize], int m, int n, int k, CrossList &M)
{
    if (M.rhead)
    {
        free(M.rhead);
    }
    if (M.chead)
    {
        free(M.chead);
    }
    M.m = m;
    M.n = n;
    M.k = k;

    if (!(M.chead = OLNode *)malloc(sizeof(OLNode) * m))
    {
        return 0;
    }
    if (!(M.rhead = OLNode *)malloc(sizeof(OLNode) * n))
    {
        return 0;
    }
    for (int i = 0; i < M; ++i)
    {
        M.chead[i].right = NULL;
        M.chead[i].down = NULL;
    }
    for (int i = 0; i < n; ++i)
    {
        M.rhead[i].right = NULL;
        M.rhead[i].down = NULL;
    }
    OLNode *temps[maxSize];
    for (int j = 0; j < n; ++j)
    {
        temps[j] = &(M.rhead[j]);
    }
    for (int i = 0; i < m; ++i)
    {
        OLNode *r = &(M.chead[i]);
        for (int j = 0; j < n; ++j)
        {
            if (A[i][j] != 0)
            {
                OLNode *p = (OLNode *)malloc(sizeof(OLNode));
                p->row = i;
                p->col = j;
                p->val = A[i][j];
                p->down = NULL;
                p->right = NULL;
                r = p;
                temps[j]->down = p;
                temps[j] = p;
            }
        }
    }
    return 1;
}
