#include <iostream>
#include <vector>
#include <string>

/*栈和队列*/
#define N 50
#define maxSize 100

/*栈和队列的定义*/

/*顺序栈*/
typedef struct
{
    int data[maxSize]; // 存放栈中元素
    int top;           // 栈顶指针
} SqStack;             //  顺序栈类型定义

/*链栈结点*/
typedef struct LNode
{
    int data;           // 数据域
    struct LNode *next; // 指针域
} LNode;                // 链栈结点定义

/*顺序队列*/
typedef struct
{
    int data[maxSize];
    int front; // 队首指针
    int rear;  // 队尾指针
} SqQueue;     // 顺序队列类型定义

/*链队*/
typedef struct QNode
{
    int data;
    struct QNode *next;
} QNode;

typedef struct
{
    QNode *front;
    QNode *rear;
} LiQueue;

/*顺序栈的状态和操作*/

/**
 * 三个状态
 * 1. 栈空：st.top == -1;
 * 2. 栈满：st.top == maxSize - 1;
 * 3. 非法：上溢和下溢
 */

/**
 * 两个操作
 * 1. x进栈：++(st.top); st.data[st.top] = x;
 * 2. x出栈：x = st.data[st.top]; -- (st.top);
 */

// 初始化
void initStatck(SqStack &st) // 初始化栈
{
    st.top = -1; // 只需将栈顶指针设置为-1
}

// 判断栈空
int isEmpty(SqStack st)
{
    if (st.top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// 进栈
int push(SqStack &st, int x)
{
    if (st.top == maxSize - 1)
    {
        return 0;
    }
    ++(st.top);
    st.data[st.top] = x;
    return 1;
}

// 出栈
int pop(SqStack &st, int &x)
{
    if (st.top == -1)
    {
        return 0;
    }
    x = st.data[st.top];
    --(st.top);
    return 1;
}

/*链栈的状态和操作*/

/**
 * 两个状态
 * 1. 栈空：lst->next = NULL;
 * 2. 栈满：假设内存无限大则不存在栈满情况;
 */

/**
 * 两个操作
 * 1. 进栈：p->next = lst->next; lst->next = p; 其实是头插法建立链表中的插入操作
 * 2. 出栈：p = lst->next; x = p->data; lst->next = p->next; free(p); 其实就是单链表的删除操作
 */

// 初始化
void initLStack(LNode *&lst) // lst要改变，用引用型
{
    lst = (LNode *)malloc(sizeof(LNode)); // 制造一个头结点
    lst->next = NULL;
}

// 栈空
int isEmptylst(LNode *lst)
{
    if (lst->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// 进栈
void pushlst(LNode *lst, int x)
{
    LNode *p;
    p = (LNode *)malloc(sizeof(LNode));
    p->next = NULL;

    p->data = x;
    p->next = lst->next;
    lst->next = p;
}

// 出栈
int poplst(LNode *lst, int &x)
{
    LNode *p;
    if (lst->next == NULL)
    {
        return 0;
    }
    p = lst->next;
    x = p->data;
    lst->next = p->next;
    free(p);
    return 1;
}

int main(int argc, char const *argv[])
{
    /*顺序栈*/
    int stack[maxSize];
    int top = -1;
    int x = 1;
    stack[++top] = x;
    x = stack[top--];
    return 0;
}
