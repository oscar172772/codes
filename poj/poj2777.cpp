#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;
const int MAXN=200000;
int Q,n,top;

struct Tree
{
    Tree *lson,*rson;
    int l,r;
    int s,lazy;
}pool[MAXN*4+300],*root;
void pntsubtree(Tree *node)
{
    cout<<'('<<node->s<<','<<node->l<<','<<node->r<<','<<node->lazy<<')';
    if(node->l==node->r)return;
    cout<<'{';
    pntsubtree(node->lson);
    pntsubtree(node->rson);
    cout<<'}';
}
void ud(Tree *node)
{
    node->s=0;
    if(node->lson->lazy)node->s|=node->lson->lazy;
    else node->s|=node->lson->s;
    if(node->rson->lazy)node->s|=node->rson->lazy;
    else node->s|=node->rson->s;
}
void fa_lazy(Tree *node)
{
    if(!node->lazy)return;
    node->lson->lazy=node->lazy;
    node->rson->lazy=node->lazy;
    node->s=node->lazy;
    node->lazy=0;
}
void build(Tree *node,int l,int r)
{
    //cout<<"build("<<len<<")\n";
    Tree *tmp1=&pool[++top];
    Tree *tmp2=&pool[++top];
    node->lson=tmp1;
    node->rson=tmp2;
    node->l=l;
    node->r=r;
    if(l==r)
    {
        node->s=1;
        return;
    }
    int m=(l+r)/2;
    build(tmp1,l,m);
    build(tmp2,m+1,r);
    ud(node);
    //node->sum=node->lson->sum+node->rson->sum;
}
void change(Tree *node,int l,int r,int num)
{
    if(l>r)l^=r^=l^=r;
    if(l==node->l&&r==node->r){node->lazy=1<<(num-1);return;}//return node->sum+node->lazy*(node->r-node->l+1);
    fa_lazy(node);
    if(node->lson->r>=r)change(node->lson,l,r,num);
    else if(node->rson->l<=l)change(node->rson,l,r,num);
    else
    {
        change(node->lson,l,node->lson->r,num);
        change(node->rson,node->rson->l,r,num);
    }
    ud(node);
}
int query(Tree *node,int l,int r)
{
    if(l>r)l^=r^=l^=r;
    /*cout<<"querying ";
    pntsubtree(node);
    cout<<node->sum+node->lazy*(node->r-node->l+1)<<endl;*/
    if(l==node->l&&r==node->r)
    {
        if(node->lazy)return node->lazy;
        return node->s;
    }
    fa_lazy(node);
    int ans;
    if(node->lson->r>=r)ans=query(node->lson,l,r);
    else if(node->rson->l<=l)ans=query(node->rson,l,r);
    else
    {
        ans=query(node->lson,l,node->lson->r)|
            query(node->rson,node->rson->l,r);
    }
    return ans;
}
int main()
{
    scanf("%d%d%d",&n,&Q,&Q);
    root=&pool[0];
    build(root,1,n);
    char a;
    int b,c;
    int d;
    while(Q--)
    {
        //pntsubtree(root);
        //cout<<endl;
        cin>>a;
        if(a=='P')
        {
            cin>>b>>c;
            int t1=query(root,b,c),t2=0;
            while(t1)
            {
                t2+=t1%2;
                t1>>=1;
            }
            cout<<t2<<endl;
        }
        else
        {
            cin>>b>>c>>d;
            change(root,b,c,d);
        }
    }
    system("pause");
    return 0;
}
