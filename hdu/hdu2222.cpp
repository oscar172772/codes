#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=501000;
struct node
{
    short isend;
    //int id;//temporary
    node *next[26],*fail;
}*root,pool[MAXN];
int top;
void bt(){root=&pool[top++];}
inline void insert(char str[])
{
    node *cur=root;
    int index,len=strlen(str);
    for(int i=0;i<len;i++)
    {
        index=str[i]-'a';
        if(!cur->next[index])
        {
            cur->next[index]=&pool[top++];
            //cur->next[tolower(str[i])-'a']->id=top-1;
        }
        cur=cur->next[index];
    }
    cur->isend++;
}
queue<node*> q;
void get_fail()
{
    node *tmp,*tmp2;
    q.push(root);
    while(!q.empty())
    {
        tmp=q.front();
        q.pop();
        for(int i=0;i<26;i++)
        {
            if(tmp->next[i])
            {
                q.push(tmp->next[i]);
                tmp2=tmp->fail;
                if(!tmp2)
                {
                    tmp->next[i]->fail=root;
                    continue;
                }
                while(!tmp2->next[i]&&tmp2->fail)
                {
                    tmp2=tmp2->fail;
                }
                if(tmp2->next[i])tmp->next[i]->fail=tmp2->next[i];
                else tmp->next[i]->fail=root;
            }
        }
    }
}
inline int pipei(char str[])//·µ»ØÆ¥Åä³É¹¦´ÎÊý 
{
    node *cur=root;
    int cnt=0,index,len=strlen(str);
    for(int i=0;i<len;i++)
    {
        index=str[i]-'a';
        while(!cur->next[index]&&cur->fail)
        {
            cur=cur->fail;
        }
        if(cur->next[index])cur=cur->next[index];
        node *tmp=cur;
        while(cur->fail&&cur->isend!=-1)
        {
            cnt+=cur->isend;
            cur->isend=-1;
            //if(cur->isend)cnt++;
            cur=cur->fail;
        }
        cur=tmp;
    }
    return cnt;
}
/*void pntree(node *cur=root)
{
    cout<<'{';
    cout<<"id="<<cur->id;
    if(cur->fail)
    {
        cout<<",fail-id="<<cur->fail->id;
    }
    if(cur->isend)cout<<",is_end";
    for(int i=0;i<26;i++)
        if(cur->next[i])
            pntree(cur->next[i]);
    cout<<'}';
}*/
char buf[50],buf2[1000100];
int main()
{
    int n,t;
    scanf("%d",&t);
    for(int tt=1;tt<=t;tt++)
    {
        top=0;
        memset(pool,0,sizeof(pool));
        scanf("%d",&n);
        bt();
        for(int i=1;i<=n;i++)
        {
            scanf("%s",buf);
            insert(buf);
        }
        get_fail();
        //pntree();cout<<endl;
        scanf("%s",buf2);
        try{
        printf("%d\n",pipei(buf2));}catch(...){printf("%d\n",n);}
    }
    //system("pause");
    return 0;
}
/*
5
abcd
abcde
bcd
cda
d
abcde
*/
