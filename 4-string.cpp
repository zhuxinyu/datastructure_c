#include <iostream>
#include <vector>
#include <string>

/*串*/
#define N 50
#define maxSize 100

/**
 * 串的存储结构
 * 1. 定长顺序存储
 * 2. 变长分配存储
 */

typedef struct
{
    char str[maxSize + 1]; // +1为储存结束标记
    int length;
} Str;

typedef struct
{
    char *ch;   // 指向动态分配存储区首地址的字符指针
    int length; // 串长度
} VStr;

/**
 * 串的基本操作
 * 1. 赋值操作
 * 2. 取串长度操作
 * 3. 串比较操作（核心）
 * 4. 串链接操作
 * 5. 求子串操作
 * 6. 串清空操作
 */

// 1
int strassign(VStr &str, char *ch)
{
    if (str.ch) // 释放原串空间
    {
        free(str.ch);
    }
    int len = 0;
    char *c = ch;
    while (*c) //  求ch串的长度
    {
        ++len;
        ++c;
    }
    if (len == 0) // 如果ch为空串，则直接返回空串
    {
        str.ch = NULL;
        str.length = 0;
        return 1;
    }
    else
    {
        str.ch = (char *)malloc(sizeof(char) * (len + 1));
        // 取len+1是为了多分配一个空间存放"\0"字符
        if (str.ch == NULL) // 分配空间失败的情况
        {
            return 0;
        }
        else
        {
            c = ch;
            /*注意：循环条件之所以用<=是为了将cn最后的结束符复制到新串中作为结束标记*/
            for (int i = 0; i <= len; ++i, ++c)
            {
                str.ch[i] = *c;
            }
            str.length = len;
            return 1;
        }
    }
}

// 2
int vstrlength(VStr str)
{
    return str.length;
}

// 3
int strcompare(Str s1, Str s2)
{
    for (int i = 0; i < s1.length && i < s2.length; ++i)
    {
        if (s1.ch[i] != s2.ch[i])
        {
            return s1.ch[i] - s2.ch[i];
        }
    }
    return s1.length - s2.length;
}

// 4
int concat(Str &str, Str str1, Str str2)
{
    if (str.str)
    {
        free(str.str); // 释放原串空间
        str.str = NULL;
    }
    str.str = (char *)malloc(sizeof(char) * (str1.length + str2.length + 1));
    if (str.str == NULL)
    {
        return 0;
    }
    int i = 0;
    while (i < str1.length)
    {
        str.str[i] = str1.str[i];
        ++i;
    }
    int j = 0;
    /*注意，之所以使用 <= 是为了连通str2的结束符一起复制*/
    while (j <= str2.length)
    {
        str.str[i + j] = str2.str[j];
        ++j;
    }

    str.length = str1.length + str2.length;
    return 1;
}

// 5 求str串中从pos位置开始，长度为len的子串，子串由substr返回给用户
int substring(Str &substr, Str str, int pos, int len)
{
    if (pos < 0 || len >= substr.length || len < 0 || len > substr.length - pos)
    {
        return 0;
    }
    if (substr.str)
    {
        free(substr.str);
        substr.str = NULL;
    }
    if (len == 0)
    {
        substr.str = NULL;
        substr.length = 0;
        return 1;
    }
    else
    {
        substr.str = (char *)malloc(sizeof(char) * (len + 1));
        int i = pos, j = 0;
        while (i < pos + len)
        {
            substr.str[j] = str[i];
            ++i;
            ++j;
        }
    }
    substr.str[j] = '\0';
    substr.length = len;
    return 1;
}

// 6
int clearstring(Str &str)
{
    if (str.str)
    {
        free(str.str);
        str.str = NULL;
    }
    str.length = 0;
    return 1;
}

/**
 * 串的匹配模式
 * 1. 简单匹配模式
 * 2. KMP算法
 * 3. KMP算法的改进
 */

// 1
int index(Str str, Str substr)
{
    int i = 1, j = 1, k = i; // 串从数组下标1位置开始储存，因此初值为1
    while (i <= str.length && j <= substr.length)
    {
        if (str.str[i] == substr.str[j])
        {
            ++i;
            ++j;
        }
        else
        {
            j = 1;   // 匹配失败重置子串指针
            i = ++k; // i从主串的下一位置开始，k中记录了上一次的起始位置
        }
    }
    if (j > substr.length)
    {
        return k;
    }
    else
    {
        return 0;
    }
}

// 2
void getnext(Str substr, int next[])
{
    int i = 1, j = 0; // 串从个数组下标1位置开始存储，因此i初值为1
    next[1] = 0;
    while (i < substr.length)
    {
        if (j == 0 || substr.str[i] == substr.str[j])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
}

int KMP(Str str, Str substr, int next[])
{
    int i = 1, j = 1; // 串从数组下标1位置开始存储，因此处置为1
    while (i <= str.length && j <= substr.length)
    {
        if (j == 0 || str.str[i] == substr.str[j])
        {
            ++i;
            ++j;
        }
        else
        {
            j = next[j];
        }
    }
    if (j > substr.length)
    {
        return i - substr.length;
    }
    else
    {
        return 0;
    }
}

// 3
void getnextval(Str substr, int nextval[])
{
    int i = 1, j = 0; // 串从数组下标1位置开始存储，因此i初值为1
    nextval[1] = 0;
    while (i < substr.length)
    {
        if (j == 0 || substr.str[i] == substr.str[j])
        {
            ++i;
            ++j;
            if (substr.str[i] != substr.str[j])
            {
                nextval[i] = j;
            }
            else
            {
                nextval[i] = nextval[j];
            }
        }
        else
        {
            j = nextval[j];
        }
    }
}