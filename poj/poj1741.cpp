#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=10100;
struct edge
{
    int v,len;
    edge *next;
}*h[MAXN],pool[2*MAXN];
int dep[MAXN],siz[MAXN],top;
bool vis[MAXN];
vector<int> insubtree[MAXN];
int n,k,u,v,w,ans;
int tmpdep[MAXN],tot,allsubtrees[MAXN],top_;
void addedge(int u,int v,int len)
{
    edge *tmp=&pool[top++];tmp->v=v;tmp->len=len;tmp->next=h[u];h[u]=tmp;
    edge *pmt=&pool[top++];pmt->v=u;pmt->len=len;pmt->next=h[v];h[v]=pmt;
}
void dfs1(int root)
{
    siz[root]=1;
    vis[root]=1;
    for(edge *tmp=h[root];tmp;tmp=tmp->next)
    {
        if(!vis[tmp->v])
        {
            dfs1(tmp->v);
            siz[root]+=siz[tmp->v];
        }
    }
}
int G_point(int nod)
{
    memset(vis,0,sizeof(vis));
    dfs1(nod);
    int cur=nod,max_son,tot_size=0;
    do
    {
        max_son=-1;tot_size=0;
        for(edge *tmp=h[cur];tmp;tmp=tmp->next)
        {
            if(siz[tmp->v]*2>siz[cur])
                max_son=tmp->v;
            else
                tot_size+=siz[tmp->v];
        }
        if(max_son!=-1)
        {
            siz[cur]=tot_size+1;
            siz[max_son]+=siz[cur];
            cur=max_son;
        }
    }while(max_son!=-1);
    return cur;
}
void cut(int u,int v)//需保证(u,v)存在 
{
    if(h[u]->v==v)
        h[u]=h[u]->next;
    else
        for(edge *tmp=h[u];tmp&&tmp->next;tmp=tmp->next)
            if(tmp->next->v==v)
                tmp->next=tmp->next->next;
    if(h[v]->v==u)
        h[v]=h[v]->next;
    else
        for(edge *tmp=h[v];tmp&&tmp->next;tmp=tmp->next)
            if(tmp->next->v==u)
                tmp->next=tmp->next->next;
}
int cursubtree;
void dfs2(int root,int cur)//在这次dfs中把上面说的那些数据求出来 
{
    vis[cur]=1;
    //bwc[cur]=allsubtrees[top_];
    if(top_)insubtree[allsubtrees[top_]].push_back(cur);
    for(edge *tmp=h[cur];tmp;tmp=tmp->next)
    {
        if(!vis[tmp->v])
        {
            if(root==cur)
            {
                allsubtrees[++top_]=tmp->v;
                insubtree[allsubtrees[top_]].clear();
            }
            dep[tmp->v]=dep[cur]+tmp->len;
            if(dep[tmp->v]<=k)tmpdep[++tot]=dep[tmp->v];
            dfs2(root,tmp->v);
        }
    }
}
void process_tree(int cur)
{//对于每棵subtree找到距离<=k总节点对数量再求和 
    //这个代码block估计要循环，until每一个tree的size都变成1 
    int G=G_point(cur);
    //cout<<"G="<<G<<endl;
    memset(vis,0,sizeof(vis));
    //for(int i=1;i<=n;i++)insubtree[i].clear();
    //memset(bwc,0,sizeof(bwc));
    top_=0;
    cursubtree=0;
    tmpdep[1]=dep[G]=0;
    tot=1;
    dfs2(G,G);
    //统计 
    /*tot=0;
    for(int i=1;i<=n;i++)
    {
        if(vis[i]&&dep[i]<=k)
        {
            tmpdep[++tot]=dep[i];
        }
    }*/
    sort(tmpdep+1,tmpdep+tot+1);
    int sptr=1,eptr=tot;
    while(sptr<eptr)
    {
        while(eptr>=1&&tmpdep[sptr]+tmpdep[eptr]>k)eptr--;
        if(sptr<eptr&&tmpdep[sptr]+tmpdep[eptr]<=k)ans+=eptr-sptr;
        sptr++;
    }
    //cout<<G<<' '<<ans<<endl;
    //排除 
    for(int i=1;i<=top_;i++)
    {
        if(siz[allsubtrees[i]]==1)continue;
        tot=insubtree[allsubtrees[i]].size();//需要重新dfs，否则这部分的复杂度将从siz[allsubtrees[i]]变为siz[cur] 
        for(int j=0;j<tot;j++)tmpdep[j+1]=dep[insubtree[allsubtrees[i]][j]];
        sort(tmpdep+1,tmpdep+tot+1);
        int sptr=1;eptr=tot;
        while(sptr<eptr)
        {
            while(eptr>=1&&tmpdep[sptr]+tmpdep[eptr]>k)eptr--;
            if(sptr<eptr&&tmpdep[sptr]+tmpdep[eptr]<=k)ans-=eptr-sptr;
            sptr++;
        }
    }
    //把root连接的所有边cut掉然后递归 
    for(edge *tmp=h[G];tmp;tmp=tmp->next)
    {
        cut(G,tmp->v);
        if(siz[tmp->v]>1)process_tree(tmp->v);
    }
}//那我为什么不把这个block变成一个function啊 好了已经变了 
int main()
{
    while(scanf("%d%d",&n,&k)&&(n!=0||k!=0))
    {
        top=ans=0;
        for(int i=1;i<n;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            addedge(u,v,w);
        }
        //int t1=clock();
        process_tree(1);
        printf("%d\n",ans);
        //cout<<"time:"<<clock()-t1<<endl;
    }
    return 0;
}
