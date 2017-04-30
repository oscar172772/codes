#include<cstdlib>
#include<cstdio>
#include<iostream>
using namespace std;
const int MAXN=150000;
struct splay
{
    splay *pa,*son[2];
    int d,size,lazy,rev,Min;
}pool[MAXN+100],*root,*rf;
int n,m,top;
void fa_lazy(splay *node)
{
    if(node->rev)
    {
        swap(node->son[0],node->son[1]);
        if(node->son[0])node->son[0]->rev^=1;
        if(node->son[1])node->son[1]->rev^=1;
        node->rev=0;
    }
    if(node->lazy)
    {
        node->Min+=node->lazy;
        node->d+=node->lazy;
        if(node->son[0])node->son[0]->lazy+=node->lazy;
        if(node->son[1])node->son[1]->lazy+=node->lazy;
        node->lazy=0;
    }
}
void ud(splay *node)
{
    node->Min=node->d;
    node->size=1;
    if(node->son[0])
    {
        fa_lazy(node->son[0]);
        node->Min=min(node->Min,node->son[0]->Min);
        node->size+=node->son[0]->size;
    }
    if(node->son[1])
    {
        fa_lazy(node->son[1]);
        node->Min=min(node->Min,node->son[1]->Min);
        node->size+=node->son[1]->size;
    }
}
int size(splay *node){if(node)return node->size;return 0;}
void rot(splay *node)
{
    if(node==root)return;
    int type=node==node->pa->son[0];//lrot:0,rrot:1;
    splay *g=node->pa->pa, *p=node->pa, *s=node->son[type];
    p->son[!type]=s;
    if(s)s->pa=p;
    node->son[type]=p;
    p->pa=node;
    g->son[g->son[1]==p]=node;
    node->pa=g;
    if(root==p)root=node;
    ud(p);
    ud(node);
}
void Splay(splay *node,splay *to)
{
    while(node->pa!=to)
    {
        if(node->pa->pa==to)rot(node);
        else
        {
            splay *p=node->pa;
            if((p->son[0]==node)^(p->pa->son[0]==p)){rot(node);rot(node);}
            else{rot(p);rot(node);}
        }
    }
}
splay *Find(int pos)
{
    if(!pos)return 0;
    splay *cur=root;
    fa_lazy(cur);
    while(size(cur->son[0])!=pos-1)
    {
        ud(cur);
        if(size(cur->son[0])>pos-1)cur=cur->son[0];
        else {pos-=size(cur->son[0])+1;cur=cur->son[1];}
        fa_lazy(cur);
    }
    return cur;
}
void insert(int pos,int i)
{
    splay *tmp=Find(pos),
          *tmp2=Find(pos+1),
          *tmp3=&pool[++top];
    if(tmp)
    {
        Splay(tmp,rf);
        Splay(tmp2,root);
        tmp3->d=tmp3->Min=i;
        tmp3->size=1;
        tmp3->pa=tmp2;
        tmp2->son[0]=tmp3;
        ud(tmp2);
        ud(tmp);
    }
    else
    {
        Splay(tmp2,rf);
        tmp3->d=tmp3->Min=i;
        tmp3->size=1;
        tmp3->pa=tmp2;
        tmp2->son[0]=tmp3;
        ud(tmp2);
    }
}
void del(int pos)
{
    splay *tmp=Find(pos-1),
          *tmp2=Find(pos+1);
    if(tmp)
    {
        Splay(tmp,rf);
        Splay(tmp2,root);
        tmp2->son[0]=0;
        ud(tmp2);
        ud(tmp);
    }
    else
    {
        Splay(tmp2,rf);
        tmp2->son[0]=0;
        ud(tmp2);
    }
}
void add(int l,int r,int i)
{
    splay *tmp=Find(l-1),
          *tmp2=Find(r+1);
    if(tmp)
    {
        Splay(tmp,rf);
        Splay(tmp2,root);
        tmp2->son[0]->lazy+=i;
        ud(tmp2);
        ud(tmp);
    }
    else
    {
        Splay(tmp2,rf);
        tmp2->son[0]->lazy+=i;
        ud(tmp2);
    }
}
void reverse(int l,int r)
{
    splay *tmp=Find(l-1),
          *tmp2=Find(r+1);
    if(tmp)
    {
        Splay(tmp,rf);
        Splay(tmp2,root);
        tmp2->son[0]->rev^=1;
        ud(tmp2);
        ud(tmp);
    }
    else
    {
        Splay(tmp2,rf);
        tmp2->son[0]->rev^=1;
        ud(tmp2);
    }
}
void revolve(int l,int r,int t)
{
    t%=r-l+1;
    if(!t)return;
    reverse(l,r);
    reverse(l,l+t-1);
    reverse(l+t,r);
}
int Min(int l,int r)
{
    splay *tmp=Find(l-1);
    splay *tmp2=Find(r+1);
    int ans;
    if(tmp)
    {
        Splay(tmp,rf);
        Splay(tmp2,root);
        return tmp2->son[0]->Min;
    }
    else
    {
        Splay(tmp2,rf);
        return tmp2->son[0]->Min;
    }
}
int main()
{
    scanf("%d",&n);
    int a;
    rf=&pool[MAXN+99];
    splay *tmp=&pool[++top];
    tmp->d=tmp->Min=INT_MAX;
    tmp->size=1;
    root=tmp;
    tmp->pa=rf;
    rf->son[0]=tmp;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a);
        insert(i-1,a);
    }
    scanf("%d",&m);
    char s[10];
    int x,y,z;
    for(int i=1;i<=m;i++)
    {
        scanf("%s",s);
        if(s[0]=='A')
        {
            scanf("%d%d%d",&x,&y,&z);
            add(x,y,z);
        }
        else if(s[0]=='I')
        {
            scanf("%d%d",&x,&y);
            insert(x,y);
        }
        else if(s[0]=='D')
        {
            scanf("%d",&x);
            del(x);
        }
        else if(s[3]=='E')
        {
            scanf("%d%d",&x,&y);
            reverse(x,y);
        }
        else if(s[3]=='O')
        {
            scanf("%d%d%d",&x,&y,&z);
            revolve(x,y,z);
        }
        else if(s[0]=='M')
        {
            scanf("%d%d",&x,&y);
            printf("%d\n",Min(x,y));
        }
    }
    system("pause");
    return 0;
}
