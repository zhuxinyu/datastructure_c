#include <iostream>
#include <vector>

/*树与二叉树*/
#define N 50
#define maxSize 100

/**
 * 树的存储结构
 * 1. 顺序存储（双亲存储）
 * 2. 链式存储：
 * ① 孩子存储结构（图的邻接表存储）
 * ② 孩子兄弟存储结构 （与树和森林与二叉树的相互转换关系密切）
 */

/**
 * 顺序存储 BTree[]
 * 链式存储 BTNode
 * 线索结点 TBTNode
 */

typedef struct BTNode
{
    char data; // 数据类型可自定义
    struct BTNode *lchild;
    struct BTNode *rchild;
} BTNode;

typedef struct TBTNode
{
    char data;
    int ltag, rtag;
    struct TBTNode *lchild;
    struct TBTNode *rchild;
} TBTNode;

/**
 * 二叉树的性质
 * ① 非空二叉树上的叶子结点数等于双分支结点数+1
 * ② 二叉树的第i层上最多有2^(i-1)个结点
 * ③ 高度为h的二叉树最多（满二叉树中前k层）有(2^k)-1个结点
 * ④ 有n个结点的完全二叉树，对各节点从上到下，从左到右依次编号（编号范围为1~n），则结点之间有如下关系：
 *      若i为某结点a的编号，则：
 *      如果i≠1，则a双亲结点的编号为⌊i/2⌋。
 *      如果2i≤n，则a左孩子的编号为2i；如果2i＞n，则a无左孩子。
 *      如果2i+1≤n，则a右孩子的编号为2i+1；如果2i+1＞n，则a无右孩子。
 * ⑤ 函数Catalan(): 给定n个结点，能构成h(n)种不同的二叉树，h(n) = C(n,2n) / (n+1)。
 * ⑥ 具有n(n≥1)个结点的完全二叉树的高度为⌊log2n⌋+1
 */

/**
 * 二叉树的遍历算法 （递归
 * 1. 先序遍历
 * 2. 中序遍历
 * 3. 后序遍历 （⭐️⭐️⭐️先序交换左右子树遍历得逆后序遍历，逆后序逆序遍历得后序遍历，因此需要两个辅助栈）
 * 4. 层次遍历 （辅助队列,BFS）
 */

void Visit(BTNode *q) {} // 访问操作

// 1
void preorderRecursion(BTNode *p)
{
    if (p != NULL)
    {
        Visit(p);                     // 假设访问函数Visit()已经定义过，其中包含了对结点p的各种访问操作
        preorderRecursion(p->lchild); // 先序遍历左子树
        preorderRecursion(p->rchild); // 先序遍历右子树
    }
}

// 2
void inorderRecursion(BTNode *p)
{
    if (p != NULL)
    {
        inorderRecursion(p->lchild);
        Visit(p);
        inorderRecursion(p->rchild);
    }
}

// 3
void postorderRecursion(BTNode *p)
{
    if (p != NULL)
    {
        postorderRecursion(p->lchild);
        postorderRecursion(p->rchild);
        Visit(p);
    }
}

// 4
void level(BTNode *p)
{
    int front, rear;
    BTNode *que[maxSize];
    fornt = rear = 0;
    BTNode *q;
    while (p != NULL)
    {
        rear = (rear + 1) % maxSize;
        que[rear] = p;        // 根节点入队
        while (front != rear) // 当队列不空的时候进行循环
        {
            front = (front + 1) % maxSize;
            q = que[front];        // 队头结点出队
            Visit(q);              // 访问队头结点
            if (q->lchild != NULL) // 如果左子树不空，则左子树的根节点入队
            {
                rear = (rear + 1) % maxSize;
                que[rear] = q->lchild;
            }
            if (q->rchild != NULL) // 如果右子树不空，则右子树的根节点入队
            {
                rear = (rear + 1) % maxSize;
                que[rear] = q->rchild;
            }
        }
    }
}

/**
 * 二叉树遍历算法的改进
 * 1. DFS: 用辅助栈实现非递归遍历
 *      ① 先序遍历非递归算法
 *      ② 中序遍历非递归算法
 *      ③ 后序遍历非递归算法
 * 2. 线索二叉树: 线索化目的是减少对系统栈的依赖，大幅度降低系统栈的深度
 *      ① 中序线索二叉树的改造（高频）
 *      ② 遍历中序线索二叉树
 *      ③ 前序线索二叉树
 *      ④ 遍历前序线索二叉树
 *      ⑤ 后序线索二叉树
 */

// 1-①
void preorderNonrecursion(BTNode *bt)
{
    if (bt != NULL)
    {
        BTNode *stack[maxSize]; // 定义一个栈
        int top = -1;           // 初始化栈
        BTNode *p;
        stack[++top] = bt; // 根节点入栈
        while (top != -1)  // 栈空循环退出，遍历结束
        {
            p = stack[top--]; // 出栈并输出栈顶结点
            Visit(p);
            /*重点⭐️⭐️⭐️⭐️⭐️ 为保证出栈顺序符合先序，右子树先入栈，左子树后入栈*/
            if (p->rchild != NULL) // 栈顶结点的右孩子存在，则右孩子入栈
            {
                stack[++top] = p->rchild;
            }
            if (p->lchild != NULL) // 栈顶结点的左孩子存在，则左孩子入栈
            {
                stack[++top] = p->lchild;
            }
        }
    }
}

// 1-②
void inorderNonrecursion(BTNode *bt)
{
    if (bt != NULL)
    {
        BTNode *stack[maxSize];
        int top = -1;
        BTNode *p;
        p = bt;
        /*重点⭐️⭐️⭐️⭐️⭐️ 有栈空但未遍历结束的情况，此时p非空*/
        while (top != -1 || p != NULL)
        {
            while (p != NULL) // 左孩子存在，则左孩子入栈
            {
                stack[++top] = p;
                p = p->lchild;
            }
            if (top != -1) // 在栈不空的情况下出栈并输出结点
            {
                p = stack[top--];
                Visit(p);
                p = p->rchild;
            }
        }
    }
}

// 1-③
void postorderNonrecursion(BTNode *bt)
{
    if (bt != NULL)
    {
        /*定义两个栈*/
        BTNode *stack1[maxSize];
        BTNode *stack2[maxSize];
        int top1 = -1;
        int top2 = -1;
        BTNode *p = NULL;
        stack1[++top1] = bt;
        while (top1 != -1)
        {
            p = stack1[top1--];
            stack2[++top2] = p;
            /*重点⭐️⭐️⭐️⭐️⭐️ 注意和先序遍历得区别，左、右孩子的入栈顺序相反*/
            if (p->lchild != NULL)
            {
                stack1[++top1] = p->lchild;
            }
            if (p->rchild != NULL)
            {
                stack2[++top2] = p->rchild;
            }
        }
        while (top2 != -1)
        {
            p = stack2[top2--];
            Visit(p);
        }
    }
}

// 2-①
void InThread(TBTNode *p, TBTNode *&pre)
{
    if (p != NULL)
    {
        InThread(p->lchild, pre); // 递归，左子树线索化
        if (p->lchild == NULL)
        {
            p->lchild = pre; // 建立当前结点的前驱线索
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL)
        {
            pre->rchild = p; // 建立前驱结点的后继线索
            pre->rtag = 1;
        }
        pre = p;          // pre指向当前p，作为p将要指向的下一个节点的前驱结点指针
        p = p->rchild;    // p指向一个新结点，此时pre和p分别指向的结点形成了一个前驱后继对，为下一次线索的连接做准备
        InThread(p, pre); // 递归，右子树线索化
    }
}

// 2-②
void createInThread(TBTNode *root)
{
    TBTNode *pre = NULL; // 前驱结点指针
    if (root != NULL)
    {
        InThread(root, pre);
        pre->rchild = NULL; // 非空二叉树，线索化后处理中序最后一个结点
        pre->rtag = 1;
    }
}

// 2-③
void preThread(TBTNode *p, TBTNode *&pre)
{
    if (p != NULL)
    {
        if (p->lchild == NULL)
        {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL)
        {
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;
        /*注意，这里在递归入口处有限制条件，左右指针不是线索才继续递归*/
        if (p.ltag == 0)
        {
            preThread(p->lchild, pre);
        }
        if (p->rtag == 0)
        {
            preThread(p->rchild, pre);
        }
    }
}

// 2-④
void preorder(TBTNode *root)
{
    if (root != NULL)
    {
        TBTNode *p = root;
        while (p != NULL)
        {
            while (p->ltag == 0)
            {
                Visit(p);
                p = p->lchild;
            }
            Visit(p);
            p = p->rchild;
        }
    }
}

// 2-⑤
void postThread(TBTNode *p, TBTNode *&pre)
{
    if (p != NULL)
    {
        postThread(p->lchild, pre);
        postThread(p->rchild, pre);
        if (p->lchild == NULL)
        {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre.rchild == NULL)
        {
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;
    }
}

/*赫夫曼树和赫夫曼编码*/

/**
 * 1. 赫夫曼树的特点
 *      ① 权值越大的结点，距离根节点越近
 *      ② 树中没有度为1的结点，这类树又叫做正则（严格）二叉树
 *      ③ 树的带权路径长度最短
 * 2. 赫夫曼编码产生的是最短前缀编码（在前缀码中，任一字符的编码串都不是另一字符编码串的前缀）
 * 3. 对于同一组结点，构造出的赫夫曼树可能不是唯一的
 */