#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
#define int long long
const int MAXN=15500,MAXM=500510,S=15450,T=15451;
struct edge
{
    int v,f;
    edge *next,*rev;
}*h[MAXN],pool[MAXM*2];
int top;
int level[MAXN];
inline void addedge(int u,int v,int c)
{
    edge *tmp=&pool[top++];tmp->v=v;tmp->f=c;tmp->next=h[u];h[u]=tmp;
    edge *pmt=&pool[top++];pmt->v=u;pmt->f=0;pmt->next=h[v];h[v]=pmt;
    tmp->rev=pmt;pmt->rev=tmp;
}
inline int Hash(int r,int c){return (r-1)*101+c-1;}
queue<int> q;
inline bool mklevel()
{
    while(!q.empty())q.pop();
    memset(level,-1,sizeof(level));
    level[S]=0;
    q.push(S);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(edge *tmp=h[u];tmp;tmp=tmp->next)
        {
            if(tmp->f&&level[tmp->v]==-1)
            {
                level[tmp->v]=level[u]+1;
                q.push(tmp->v);
            }
        }
        if(level[T]!=-1)return true;
    }
    return false;
}
int dinic(int u,int minf)
{
    if(u==T)return minf;
    int curf=0;
    for(edge *tmp=h[u];tmp&&minf-curf;tmp=tmp->next)
    {
        if(tmp->f&&level[tmp->v]==level[u]+1)
        {
            int f=dinic(tmp->v,min(tmp->f,minf-curf));
            tmp->f-=f;
            tmp->rev->f+=f;
            curf+=f;
        }
    }
    if(!curf)level[u]=-1;
    return curf;
}
int n,m,v;
#undef int
int main()
{
    scanf("%lld%lld",&n,&m);
    long long sum=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%lld",&v);
            addedge(S,Hash(i,j),2*v);//choose L
            sum+=v;
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%lld",&v);
            addedge(Hash(i,j),T,2*v);//choose W
            sum+=v;
        }
    for(int i=1;i<=n-1;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%lld",&v);
            addedge(Hash(i,j),Hash(i+1,j),v);
            addedge(Hash(i+1,j),Hash(i,j),v);
            addedge(S,Hash(i,j),v);
            addedge(S,Hash(i+1,j),v);
            sum+=v;
        }
    for(int i=1;i<=n-1;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%lld",&v);
            addedge(Hash(i,j),Hash(i+1,j),v);
            addedge(Hash(i+1,j),Hash(i,j),v);
            addedge(Hash(i,j),T,v);
            addedge(Hash(i+1,j),T,v);
            sum+=v;
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m-1;j++)
        {
            scanf("%lld",&v);
            addedge(Hash(i,j),Hash(i,j+1),v);
            addedge(Hash(i,j+1),Hash(i,j),v);
            addedge(S,Hash(i,j),v);
            addedge(S,Hash(i,j+1),v);
            sum+=v;
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m-1;j++)
        {
            scanf("%lld",&v);
            addedge(Hash(i,j),Hash(i,j+1),v);
            addedge(Hash(i,j+1),Hash(i,j),v);
            addedge(Hash(i,j),T,v);
            addedge(Hash(i,j+1),T,v);
            sum+=v;
        }
    long long ans=sum*2;
    while(mklevel())ans-=dinic(S,0x3f3f3f3f);
    printf("%lld\n",ans/2);
    return 0;
}
