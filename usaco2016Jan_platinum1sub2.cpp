#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100100;
struct pp
{
    int p,o,id;
    bool operator<(const pp &c)const{return p<c.p;}
}p[MAXN];
bool cmp(const pp &a,const pp &b){return a.o<b.o;}
struct node
{
    int s,l,r;
    node *ls,*rs;
}*root[MAXN],pool[MAXN*30];
int pa[MAXN],ans[MAXN];
vector<int> son[MAXN];
int n,top;
node* bt(int l,int r)
{
    node *tmp=&pool[top++];
    tmp->l=l;
    tmp->r=r;
    if(l!=r)
    {
        int m=(l+r)/2;
        tmp->ls=bt(l,m);
        tmp->rs=bt(m+1,r);
    }
    return tmp;
}
node* change(node *orig,int x)
{
    node *cur=&pool[top++];
    cur->s=orig->s+1;
    cur->l=orig->l;
    cur->r=orig->r;
    if(cur->l!=cur->r)
    {
        if(x<=orig->ls->r)
        {
            cur->ls=change(orig->ls,x);
            cur->rs=orig->rs;
        }
        else
        {
            cur->ls=orig->ls;
            cur->rs=change(orig->rs,x);
        }
    }
    return cur;
}
int query(node *cur,int x)
{
    if(cur->l==cur->r)return 0;
    if(x>=cur->rs->l)return query(cur->rs,x);
    else return cur->rs->s+query(cur->ls,x);
}
void pt(node *cur)
{
    cout<<"{";
    if(cur->ls)pt(cur->ls);
    cout<<"("<<cur->s<<' '<<cur->l<<' '<<cur->r<<")";
    if(cur->rs)pt(cur->rs);
    cout<<"}";
}
int dfs(int cur,int l)
{
    root[l]=change(root[l-1],p[cur].id);//arr[l++]=p[cur];
    //l++;
    //if(son[cur].empty())return l;
    int r=l+1;
    for(int i=0;i<son[cur].size();i++)
    {
        r=dfs(son[cur][i],r);
    }
    /*for(int i=l;i<r;i++)
    {
        if(arr[i]>p[cur])ans[cur]++;
    }*/
    ans[cur]=query(root[r-1],p[cur].id)-query(root[l-1],p[cur].id);
    return r;
}
int main()
{
    freopen("promote.in","r",stdin);
    freopen("promote.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&p[i].p);
        p[i].o=i;
    }
    sort(p+1,p+n+1);
    for(int i=1;i<=n;i++)p[i].id=i;
    sort(p+1,p+n+1,cmp);
    for(int i=2;i<=n;i++)
    {
        scanf("%d",&pa[i]);
        son[pa[i]].push_back(i);
    }
    root[0]=bt(1,n);
    dfs(1,1);
    for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
    return 0;
}
