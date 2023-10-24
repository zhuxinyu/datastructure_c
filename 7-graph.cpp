#include <iostream>
#include <vector>

/*图*/
#define N 50
#define maxSize 100
#define INF MAX_INT

/**
 * 图的存储结构
 * 1. 邻接矩阵
 * 2. 邻接表
 */

// 1
typedef struct
{
    int no;    // 顶点编号
    char info; // 顶点其他信息，很少用到，不做要求可不写
} VertexType;

typedef struct
{
    int edges[maxSize][maxSize]; // 邻接矩阵定义没如果是有权图，则将int改为float
    int n, e;                    // 分别为定点数和边数
    VertexType vex[maxSize];     // 存放结点信息
} MGraph;                        // 图的邻接矩阵类型

// 2
typedef struct ArcNode
{
    int adjvex;              // 该边所指向的结点的位置
    struct ArcNode *nextarc; // 指向下一条边的指针
    int info;                // 该边的相关信息
} ArcNode;

typedef struct
{
    char data;         // 顶点信息
    int count;         // 统计当前顶点的入度 （可选）
    ArcNode *firstarc; // 指向第一条边的指针
} VNode;

typedef struct
{
    VNode adjlist[maxSize]; // 邻接表
    int n, e;               // 顶点数和边数
} AGraph;                   // 图的邻接表类型

/*图的遍历算法操作*/

/**
 * 1.深度优先搜索遍历(DFS)
 * 2.广度优先搜索遍历(BFS)(辅助队列)
 */

int visited[maxSize];
void Visit(int v){};

// 1
void DFS(AGraph *G, int v)
{
    ArcNode *p;
    visited[v] = 1;
    Visit(v);
    p = G->adjlist[v].firstarc;
    while (p != NULL)
    {
        if (visited[p->adjvex] == 0)
        {
            DFS(G, p->adjvex);
        }
        p = p->nextarc;
    }
}

// 2
void BFS(AGraph *G, int v, int visit[maxSize])
{
    ArcNode *p;
    int que[maxSize], front = 0, rear = 0;
    int j;
    Visit(v);
    visited[v] = 1;
    rear = (rear + 1) % maxSize;
    que[rear] = v;
    while (front != rear)
    {
        front = (front + 1) % maxSize;
        j = que[front];
        p = G->adjlist[j].firstarc;
        while (p != NULL)
        {
            if (visited[p->adjvex] == 0)
            {
                Visit(p->adjvex);
                visited[p->adjvex] = 1;
                rear = (rear + 1) % maxSize;
                que[rear] = p->adjvex;
            }
            p = p->nextarc;
        }
    }
}

/*最小生成树*/

/**
 * 无向图
 * 1. prim算法 O(n^2)
 * 2. kruskal算法(并查集) 复杂度由排序决定
 */

// 1
void Prim(MGraph g, int v0, int &sum)
{
    int lowcost[maxSize], vset[maxSize], v;
    int i, j, k, min;
    v = v0;
    for (i = 0; i < g.n; ++i)
    {
        lowcost[i] = g.edges[v0][i];
        vset[i] = 0;
    }
    vset[v0] = 1; // 将v0并入树中
    sum = 0;      // sum清零用来累计树的权值
    for (i = 0; i < g.n - 1; ++i)
    {
        min = INF;
        for (j = 0; j < g.n; ++j) // 选出候选边中的最小者
        {
            if (vset[j] == 0 && lowcost[j] < min) // 选出当前生成树到其余顶点最短边中的最短的一条
            {
                min = lowcost[j];
                k = j;
            }
        }
        vset[k] = 1;
        v = k;
        sum += min;               // 用sum记录了最小生成树的权值
        for (j = 0; j < g.n; ++j) // 以刚并入的顶点v为媒介更新候选边
        {
            if (vset[j] == 0 && g.edges[v][j] < lowcost[j])
            {
                lowcost[j] = g.edges[v][j];
            }
        }
    }
}

// 2
void sort(Road road[], int e);

typedef struct
{
    int a, b; // a和b为一条边所连的两个顶点
    int w;    // 边的权值
} Road;

Road road[maxSize];
int v[maxSize];    // 定义并查集数组
int getRoot(int a) // 在并查集中查找根节点的函数
{
    while (a != v[a])
    {
        a = v[a];
    }
    return a;
}

void kruskal(MGraph g, int &sum, Road road[])
{
    int a, b, i;
    sum = 0;
    for (i = 0; i < g.n; ++i)
    {
        v[i] = i;
    }
    sort(road, g.e); //  对road数组中的E条边按其权值从小到大排序
    for (i = 0; i < g.e; ++i)
    {
        a = getRoot(road[i].a);
        b = getRoot(road[i].b);
        if (a != b)
        {
            v[a] = b;         // 并查集合并
            sum += road[i].w; // 求生成树的权值，若无要求可不写
        }
    }
}

/*最短路径*/

/**
 * 有向图
 * 1. dijsktra算法 O(n^2)
 * 2. Floyd算法 O(n^3)
 */

// 1
void printfPath(int path[], int a)
{
    int stack[maxSize], top = -1;
    while (path[a] != -1)
    {
        stack[++top] = a;
        a = path[a];
    }
    stack[++top] = a;
    while (top != -1)
    {
        std::cout << stack[top--] << std::endl;
    }
}

void Dijkstra(MGraph g, int v, int dist[], int path[])
{
    int set[maxSize];
    int min, i, j, u;
    /*开始初始化*/
    for (i = 0; i < g.n; ++i)
    {
        dist[i] = g.edges[v][i];
        set[i] = 0;
        if (g.edges[v][i] < INF)
        {
            path[i] = v;
        }
        else
        {
            path[i] = -1;
        }
    }
    set[v] = 1;
    path[v] = -1;
    /*结束初始化*/
    /*关键操作开始*/
    for (i = 0; i < g.n - 1; ++i)
    {
        min = INF;
        /*这个循环每次从剩余顶点中选出一个顶点，通往这个顶点的路径在通往所有剩余顶点的路径中是长度最短的*/
        for (j = 0; j < g.n; ++j)
        {
            if (set[j] == 0 && dist[j] < min)
            {
                min = dist[j];
                u = j;
            }
        }
        set[u] = 1; // 将选出的顶点并入最短路径中
        /*这个循环以刚并入的顶点作为中间点，对所有通往剩余顶点的路径进行检测*/
        for (j = 0; j < g.n; ++j)
        {
            /*这个if语句判断顶点u的加入是否会出现通往顶点j的更短路径，如果出现则改变原来路径及其长度，否则什么都不做*/
            if (set[j] == 0 && dist[u] + g.edges[u][j] < dist[j])
            {
                dist[j] = dist[u] + g.edges[u][j];
                path[j] = u;
            }
        }
    }
    /*关键操作结束*/
}
/*函数结束时，dist[]数组中存放了v点到其余顶点的最短路径长度，path[]中存放v点到其余各顶点的最短路径*/

// 2
void printPath(int u, int v, int path[][maxSize], int A[][maxSize]) // 输出从u到v的最短路径上顶点序列

{
    if (A[u][v] == INF) // INF是已定义的常量，数值很大不可能小于图中边的权值，代表无穷输出无路径提示
    {
    }
    else
    {
        if (path[u][v] == -1)
        {
            /* 直接输出边<u,v> */
        }
        else
        {
            int mid = path[u][v];
            printPath(u, mid, path);   // 处理mid前半段路径
            printPath(mid, v, path[]); // 处理mid后半段路径
        }
    }
}

void Floyd(MGraph *g, int path[][maxSize], int A[][maxSize])
{
    int i, j, k;
    for (i = 0; i < g->n; ++i)
    {
        for (j = 0; j < g->n; ++j)
        {
            A[i][j] = g->edges[i][j];
            path[i][j] = -1;
        }
    }
    for (k = 0; k < g->n; ++k)
    {
        for (i = 0; i < g->n; ++i)
        {
            for (j = 0; j < g->n; ++j)
            {
                if (A[i][j] > A[i][k] + A[k][j])
                {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
}

/*拓扑排序*/

/**
 * 1. AOV 按拓扑入度排序遍历
 * 2. AOE 手工
 */

/*拓扑排序核心算法*/
int TopSort(AGraph *G)
{
    int i, j, n = 0;
    int stack[maxSize], top = -1; // 定义并初始化栈
    ArcNode *p;
    /*这个循环将图中入度为0的顶点入栈*/
    for (i = 0; i < G->n; ++i) // 图中顶点从0开始编号
    {
        if (G->adjlist[i].count == 0)
        {
            stack[++top] = i;
        }
    }
    /*关键操作开始*/
    while (top != -1)
    {
        i = stack[top--];      // 顶点出栈
        ++n;                   // 计数器加1，统计当前顶点
        std::cout << i << " "; // 输出当前顶点
        p = G->adjlist[i].firstarc;
        /*这个循环实现了将所有由此顶点引出的边所指向的顶戴你的入度都减少1，并将这个过程中入度变为0的顶点入栈*/
        while (p != NULL)
        {
            j = p->adjvex;
            --(G->adjlist[j].count);
            if (G->adjlist[j].count == 0)
            {
                stack[++top] = j;
            }
            p = p->nextarc;
        }
    }
    /*关键操作结束*/
    if (n == G->n)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
