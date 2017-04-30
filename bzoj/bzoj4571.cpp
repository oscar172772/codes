#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
const int MAXN=524287;
struct node
{
    int cnt;
    node *ls,*rs;
}pool[6000010],*root[2*MAXN];
int top,curt;
int n,m,a,b,x,l,r;
void inorder(node *cur)
{
    printf("{");
    if(cur->ls){inorder(cur->ls);}
    printf("(%d)",cur->cnt);
    if(cur->rs){inorder(cur->rs);}
    printf("}");
}
node* bt(int l,int r)
{
    node *tmp=&pool[top++];
    tmp->cnt=0;
    if(l!=r)
    {
        int m=(l+r)/2;
        tmp->ls=bt(l,m);
        tmp->rs=bt(m+1,r);
    }
    return tmp;
}
/*void change(node *cur,node *rgn,int l,int r,int x)
{
    if(l!=r)
    {
        node *tmp=&pool[top++];
        int m=(l+r)/2;
        if(x<=m)
        {
            tmp->cnt=(rgn->ls->cnt)+1;
            tmp->ls=rgn->ls->ls;
            tmp->rs=rgn->ls->rs;
            cur->ls=tmp;
            change(tmp,rgn->ls,l,m,x);
        }
        else
        {
            tmp->cnt=(rgn->rs->cnt)+1;
            tmp->ls=rgn->rs->ls;
            tmp->rs=rgn->rs->rs;
            cur->rs=tmp;
            change(tmp,rgn->rs,m+1,r,x);
        }
    }
}
void Change(int x)
{
    node *tmp=&pool[top++];
    tmp->ls=root[curt]->ls;
    tmp->rs=root[curt]->rs;
    tmp->cnt=(root[curt]->cnt)+1;
    root[curt+1]=tmp;
    change(root[curt+1],root[curt],0,MAXN,x);
    curt++;
}*/
node* Change(node *pre,int x,int l,int r)
{
    node *tmp=&pool[top++];
    tmp->cnt=pre->cnt+1;
    if(l==r){return tmp;}
    int m=(l+r)/2;
    if(x<=m){tmp->ls=Change(pre->ls,x,l,m);tmp->rs=pre->rs;}
    else {tmp->ls=pre->ls;tmp->rs=Change(pre->rs,x,m+1,r);}
    return tmp;
}
bool hn(node *cur,node *sub,int l,int r,int lrg,int rrg)
{
    if(l==lrg&&r==rrg)return cur->cnt-sub->cnt;
    int m=(l+r)/2;
    if(rrg<=m)return hn(cur->ls,sub->ls,l,m,lrg,rrg);
    if(lrg>m)return hn(cur->rs,sub->rs,m+1,r,lrg,rrg);
    return hn(cur->ls,sub->ls,l,m,lrg,m)||hn(cur->rs,sub->rs,m+1,r,m+1,rrg);
}
bool HN(int lt,int rt,int lrg,int rrg)
{
    if(rrg<0)return false;
    //if(!root[lt-1])root[lt-1]->cnt=2;
    return hn(root[rt],root[lt-1],0,MAXN,max(0,lrg),rrg);
}
int query(int lt,int rt,int dep,int l,int r,int x,int b)
{
    if(l==r)return l^b;//return (l+x)^b;
    int oi=(b>>dep)&1,m=(l+r)/2;
    if(oi)
    {
        if(HN(lt,rt,l-x,m-x))
            return query(lt,rt,dep-1,l,m,x,b);
        else
            return query(lt,rt,dep-1,m+1,r,x,b);
    }
    else
    {
        if(HN(lt,rt,m+1-x,r-x))
            return query(lt,rt,dep-1,m+1,r,x,b);
        else
            return query(lt,rt,dep-1,l,m,x,b);
    }
    /*if(cur->cnt-sub->cnt)
    {
        if(oi)return query(cur->rs,sub->rs,dep-1,m+1,r,x,b);
        else return query(cur->ls,sub->ls,dep-1,l,m,x,b);
    }
    else
    {
        if(!oi)return query(cur->rs,sub->rs,dep-1,m+1,r,x,b);
        else return query(cur->ls,sub->ls,dep-1,l,m,x,b);
    }*/
}
int Query(int b,int x,int l,int r)
{
    return query(l,r,18,0,MAXN,x,b);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    root[0]=bt(0,MAXN);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a);
        root[curt+1]=Change(root[curt],a,0,MAXN);
        curt++;
    }
    //for(int i=0;i<=n;i++){cout<<root[i]->cnt<<' ';inorder(root[i]->ls->ls->ls->ls->ls->ls->ls->ls->ls->ls->ls->ls->ls->ls->ls->ls);cout<<endl;}
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%d",&b,&x,&l,&r);
        printf("%d\n",Query(b,x,l,r));
    }
    //system("start compare.exe");
    return 0;
}
