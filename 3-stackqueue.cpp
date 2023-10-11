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

/*顺序栈应用*/

/**
 * 例3-1
 * C语言里算法表达式中的括号只有小括号。编写算法，判断一个表达式中的括号是否正确配对，表达式已经存入字符数组exp[]中，表达式中的字符个数为n。
 */

int match(char exp[], int n)
{
    char stack[maxSize]; // 两句话完成栈的定义和初始化，考试中用这种简写方法可以节省时间
    int top = -1;

    int i;
    for (i = 0; i < n; ++i)
    {
        if (exp[i] == '(')      // 如果遇到"("则入栈等待以后处理
            stack[++top] = '('; // 一句话完成入栈操作
        if (exp[i] == ')')
        {
            if (top == -1) // 如果遇到")"并且栈一空，则不匹配，返回0
            {
                return 0;
            }
            else // 如果栈不空，则出栈，相当于完成了一对匹配
            {
                --top;
            }
        }
    }
    if (top == -1) // 栈空则所有括号都被处理掉，说明括号是匹配的
    {
        return 1;
    }
    else // 否则括号不匹配
    {
        return 0;
    }
}

/**
 * 例3-2
 * 编写一个函数，求后缀式的数值，其中后缀式存于一个字符数组exp中，exp中最后一个字符为”\0“，作为结束符，并且假设后缀式中的数字都只有一位。本题中所出现的除法运算，皆为整除运算，如2/3结果为0，3/2结果为1。
 */

int op(int a, char Op, int b) // 本函数是运算函数，用来完成算是”a op b“的运算
{
    if (Op == '+')
        return a + b;
    if (Op == '-')
        return a - b;
    if (Op == '*')
        return a * b;
    if (Op == '/')
    {
        if (b == 0) // 这里需要判断，如果除数为0，则输出错误标记
        {
            std::cout << "Error" << std::endl;
            return 0;
        }
        else
        {
            return a / b;
        }
    }
    return 0; // op无效时返回0
}

int com(char exp[]) // 后缀式计算函数
{
    int i, a, b, r;     // a,b 为操作数，r来保存结果
    int stack[maxSize]; // 栈的初始化和定义，操作数可能出现多为避免计算错误使用int型
    int top = -1;

    char op; // 操作符
    for (i = 0; exp[i] != '\0'; ++i)
    {
        if (exp[i] >= '0' && exp[i] <= '9') // 如遇操作数入栈处理
        {
            stack[++top] = exp[i] - '0'; // 字符型转成整型
        }
        else // 如遇运算符，开始运算
        {
            op = exp[i];      // 取运算符
            b = stack[top--]; // 取第二个操作数
            a = stack[top--]; // 取第一个操作数
            r = op(a, op, b); // 运算结果保存在r中
            stack[++top] = r; // 运算结果入栈
        }
    }
    return stack[top];
}

/*链栈应用*/

/**
 * 例3-3
 * 用不带头结点的单链表储存链栈，设计初始化栈，判断栈是否为空，进栈和出栈等响应的算法。
 */

// 初始化
void initStackl(LNode *&lst)
{
    lst = NULL
}

// 判空
int isEmptyl(LNode *lst)
{
    if (lst == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// 进栈
void pushl(LNode *&lst, int x)
{
    LNode *p;
    p = (LNode *)malloc(sizeof(LNode));
    p->next = NULL;
    p->data = x;
    p->next = lst;
    lst = p;
}

// 出栈
int popl(LNode *&lst, int &x)
{
    LNode *p;
    if (lst == NULL) // 栈空情况
    {
        return 0;
    }
    p = lst;
    x = p->data;
    lst = p->next;
    free(p);
    return 1;
}

/*顺序队*/

/*循环队列的状态和操作*/

/**
 * 两个状态
 * 1. 队空状态：qu.rear == qu.front;
 * 2. 队满状态：(qu.rear+1)%maxSize == qu.front;
 */

/**
 * 两个操作
 * 1. x进队（移动队尾指针）：qu.rear = (qu.rear+1)%maxSize; qu.data[qu.rear] = x;
 * 2. x出队（移动队首指针）：qu.front = (qu.front + 1)%maxSize; x = qu.data[qu.front];
 */

// 初始化
void initQueue(SqQueue &qu)
{
    qu.front = qu.rear = 0; // 队首和队尾指针重合，并且指向0
}

// 队空
int isQueueEmpty(SqQueue qu)
{
    if (qu.front == qu.rear)
    {
        return 1; // 不论队首、队尾指针指向数组的那个位置，只要两者重合，即为队空
    }
    else
    {
        return 0;
    }
}

// 入队
int enQueue(SqQueue &qu, int x)
{
    if ((qu.rear + 1) % maxSize == qu.front) // 队满的判断条件，队满则不能入队
    {
        reutrn 0;
    }
    qu.rear = (qu.rear + 1) % maxSize; // 若队未满，则先移动指针
    qu.data[qu.rear] = x;              // 再存入元素
    return 1;
}

// 出队
int deQueue(SqQueue &qu, int &x)
{
    if (qu.front == qu.rear) // 若队空，则不能出队
    {
        return 0;
    }
    qu.front = (qu.front + 1) % maxSize; // 若队不空，则先移动指针
    x = qu.data[qu.front];               // 再取出元素
    return 1;
}

/*链队*/

/*链队的状态和操作*/

/**
 * 两个状态
 * 1. 队空状态： lqu->rear == NULL 或者 lqu->front == NULL (为何有两种情况，因为队列为空时，新结点会同时赋给首尾)
 * 2. 队满状态： 假设内存无限大的情况下，不存在队列满的情况
 */

/**
 * 两个操作
 * 1. 进队：lqu->rear->next = p; lqu->rear = p;
 * 2. 出队：p = lqu->front; lqu->front = p.next; x = p->data; free(p);
 */

// 初始化
void initLQueue(LiQueue *&lqu)
{
    lqu = (LiQueue *)malloc(sizeof(LiQueue));
    lqu->front = lqu->rear = NULL;
}

// 队空
int isLQueueEmpty(LiQueue *lqu)
{
    if (lqu->rear == NULL || lqu->front == NULL) // 队首或队尾为空即为空队
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// 入队
void enLQueue(LiQueue *lqu, int x)
{
    QNode *p;
    p = (QNode *)malloc(sizeof(QNode));
    p->data = x;
    p->next = NULL;

    if (lqu->rear == NULL) // 若队列为空，则新结点是队首结点，也是队尾结点
    {
        lqu->front = lqu->rear = p;
    }
    else
    {
        lqu->rear->next = p; // 将新结点链接到队尾，rear指向它
        lqu->rear = p;
    }
}

// 出队
int deLQueue(LiQueue *lqu, int &x)
{
    QNode *p;
    if (lqu->rear == NULL) // 队空不能出队
    {
        return 0;
    }
    else
    {
        p = lqu->front;
    }
    if (lqu->front == lqu->rear) // 队列中只有一个结点时的出队操作需特殊处理
    {
        lqu->front = lqu->rear = NULL
    }
    else
    {
        lqu->front = lqu->front->next;
    }
    x = p->data;
    free(p);
    return 1;
}

/*共享栈和双端队列*/

/**
 * 共享栈：相比于普通的顺序栈，共享栈主要是为了提高内存的利用率和减少溢出的可能性儿设计的。当两个栈共享一片连续的内存空间时，应将两栈的栈底分别设在这篇内存空间的两端，这样当两个栈的栈顶在栈空间的某一位置相遇时，才产生上溢。
 * 双端队列：是一个插入和删除操作在两端均可进行的线性表。可以把双端队列看成栈底连载一起的两个栈。他们与共享栈不同之处在与两个栈的栈顶指针是向两端延伸的。
 * 受限的双端队列：允许在一端进行插入和删除，另一端只允许删除/插入的双端队列。
 */

