#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define int long long
struct node
{
    int l,r,s,lazy;
    node *lson,*rson;
}*root,pool[1000000];
int top;
inline node* bt(int l,int r)
{
    node *tmp=&pool[top++];
    tmp->l=l;tmp->r=r;tmp->lazy=0;
    if(l==r)
    {
        scanf("%lld",&tmp->s);
    }
    else
    {
        int m=(l+r)>>1;
        tmp->lson=bt(l,m);
        tmp->rson=bt(m+1,r);
        tmp->s=tmp->lson->s+tmp->rson->s;
    }
    return tmp;
}
inline void change(node *cur,int l,int r,int d)
{
    if(cur->l==l&&cur->r==r)
    {
        cur->lazy+=d;
    }
    else
    {
        if(cur->lazy)
        {
            cur->s+=cur->lazy*(cur->r-cur->l+1);
            if(cur->lson)
            {
                cur->lson->lazy+=cur->lazy;
                cur->rson->lazy+=cur->lazy;
            }
            cur->lazy=0;
        }
        cur->s+=d*(r-l+1);
        if(r<cur->rson->l)
        {
            change(cur->lson,l,r,d);
        }
        else if(l>cur->lson->r)
        {
            change(cur->rson,l,r,d);
        }
        else
        {
            change(cur->lson,l,cur->lson->r,d);
            change(cur->rson,cur->rson->l,r,d);
        }
    }
}
int query(node *cur,int l,int r)
{
    if(cur->l==l&&cur->r==r)
    {
        return cur->s+cur->lazy*(cur->r-cur->l+1);
    }
    else
    {
        if(cur->lazy)
        {
            cur->s+=cur->lazy*(cur->r-cur->l+1);
            if(cur->lson)
            {
                cur->lson->lazy+=cur->lazy;
                cur->rson->lazy+=cur->lazy;
            }
            cur->lazy=0;
        }
        if(r<cur->rson->l)
        {
            return query(cur->lson,l,r);
        }
        else if(l>cur->lson->r)
        {
            return query(cur->rson,l,r);
        }
        else
        {
            return query(cur->lson,l,cur->lson->r)+
                   query(cur->rson,cur->rson->l,r);
        }
    }
}
#undef int
int main()
{
    int n,q,l,r,d;
    char c;
    scanf("%d%d",&n,&q);
    root=bt(1,n);
    while(q--)
    {
        scanf(" %c",&c);
        switch(c)
        {
            case 'Q':
                 scanf(" %d %d",&l,&r);
                 printf("%lld\n",query(root,l,r));
                 break;
            case 'C':
                 scanf(" %d %d %d",&l,&r,&d);
                 change(root,l,r,d);
                 break;
        }
    }
    return 0;
}
