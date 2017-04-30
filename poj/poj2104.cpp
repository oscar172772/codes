#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100100;
struct node
{
    int t;
    node *ls,*rs;
}pool[20*MAXN],*root[MAXN];
struct _
{
    int id,num;
    bool operator<(const _ &b)const{return num<b.num;}
}a[MAXN];
int top;
int curt=0;
int n,m,x,y,z,rank[MAXN];
node* bt(int l,int r)
{
    node *tmp=&pool[top++];
    tmp->t=0;
    if(l!=r)
    {
        int m=(l+r)/2;
        tmp->ls=bt(l,m);
        tmp->rs=bt(m+1,r);
    }
    return tmp;
}
void change(node *cur,node *rgn,int l,int r,int x)
{
    if(rgn->ls)
    {
        int m=(l+r)/2;
        if(m>=x)//left
        {
            node *tmp=&pool[top++];
            tmp->t=rgn->ls->t+1;
            cur->ls=tmp;
            cur->rs=rgn->rs;
            change(tmp,rgn->ls,l,m,x);
        }
        else
        {
            node *tmp=&pool[top++];
            tmp->t=rgn->rs->t+1;
            cur->rs=tmp;
            cur->ls=rgn->ls;
            change(tmp,rgn->rs,m+1,r,x);
        }
    }
}
void Change(int x,int dt)
{
    if(dt)
    {
        for(int i=1;i<=dt;i++)
        {
            root[curt+i]=&pool[top++];
            root[curt+i]->t=root[curt]->t;
            root[curt+i]->ls=root[curt]->ls;
            root[curt+i]->rs=root[curt]->rs;
        }
    }
    root[curt+dt]->t++;
    change(root[curt+dt],root[curt],1,n,x);
    curt+=dt;
}
int query(node *cur,node *rgn,int l,int r,int k)
{
    if(l==r)return a[l].num;
    int m=(l+r)/2;
    if(cur->ls->t-rgn->ls->t>=k)return query(cur->ls,rgn->ls,l,m,k);
    else return query(cur->rs,rgn->rs,m+1,r,k-cur->ls->t+rgn->ls->t);
}
int Query(int i,int j,int k)
{
    return query(root[j],root[i-1],1,n,k);
}
int main()
{
    scanf("%d%d",&n,&m);
    root[0]=bt(1,n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&(a[i].num));
        a[i].id=i;
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
    {
        rank[a[i].id]=i;
    }
    for(int i=1;i<=n;i++)Change(rank[i],1);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        printf("%d\n",Query(x,y,z));
    }
    system("pause");
    return 0;
}
