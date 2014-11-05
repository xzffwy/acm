#include <iostream>
using namespace std;
const int MAXM = 30,KIND = 26;
int m;
int sign;
typedef struct fun
{
	char s1[25],s2[25];
}rr;
fun a[105];
struct node
{
    char* s;
    int prefix;
    bool isword;
    node* next[KIND];
    node()
    {
        s = NULL;
        prefix = 0;
        isword = false;
        memset(next,0,sizeof(next));
    }
}*root;//根
void insert(node *root,char *s)//插入
{
    node *p = root;
    for (int i = 0;s[i];i++)
    {
        int x = s[i] - 'a';
        p->s = s+i;
        if (p->next[x] == NULL)
            p->next[x] = new node;
        p = p->next[x];
        p->prefix++;
    }
    p->isword = true;
}
bool del(node *root,char *s)//删除
{
    node *p = root;
    for (int i = 0;s[i];i++)
    {
        int x = s[i] - 'a';
        if (p->next[x] == NULL)
            return false;
        p = p->next[x];
    }
    if (p->isword)
        p->isword = false;
    else
        return false;
    return true;
}
bool search(node *root,char* s)//查找
{
    node* p = root;
    for (int i = 0;s[i];i++)
    {
        int x = s[i]-'a';
        if (p->next[x] == NULL)
            return false;
        p = p->next[x];
    }
    return p->isword;
}
int count(node *root,char *s)//统计后缀
{
    node *p = root;
    for (int i = 0;s[i];i++)
    {
        int x = s[i] - 'a';
        if (p->next[x] == NULL)
            return 0;
        p = p->next[x];
    }
    return p->prefix;
}
int main()
{
    m = 0;
    root = new node;
    char s[MAXM];
    while (gets(a[1].s1))
    {
        if (strcmp(a[1].s1,"") == 0)
            break;
        insert(root,a[1].s1);
    }
    while (gets(s))
        printf("%d\n",count(root,s));
}

