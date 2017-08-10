#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int MAXN=100010,MAXM=1000010;
int ht[MAXN];
struct edge
{
    int v,w;
    edge *next;
}*h[MAXN],pool[2*MAXM];
int top;
struct cmp
{
    inline bool operator()(const edge *a,const edge *b){return ht[a->v]==ht[b->v]?a->w>b->w:ht[a->v]<ht[b->v];}
};
inline void addedge(int a,int b,int c)
{
    edge *tmp=&pool[top++];tmp->v=b;tmp->w=c;tmp->next=h[a];h[a]=tmp;
}
priority_queue<edge*,vector<edge*>,cmp> pq;
int n,m;
int vis[MAXN];
int cnt;
long long ans;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&ht[i]);
    int u,v,w;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        if(ht[u]>ht[v])addedge(u,v,w);
        else if(ht[u]<ht[v])addedge(v,u,w);
        else addedge(u,v,w),addedge(v,u,w);
    }
    vis[1]=1;
    cnt++;
    for(edge *tmp=h[1];tmp;tmp=tmp->next)
    {
        //cout<<1<<' '<<tmp->v<<endl;
        pq.push(tmp);
    }
    while(!pq.empty())
    {
        edge *tmp=pq.top();pq.pop();
        int u1=tmp->v;
        //cout<<u1<<endl;
        if(!vis[u1])
        {
            cnt++;
            vis[u1]=1;
            ans+=tmp->w;
            for(edge *tmp1=h[u1];tmp1;tmp1=tmp1->next)
            {
                //cout<<u1<<' '<<tmp1->v<<endl;
                pq.push(tmp1);
            }
        }
    }
    printf("%d %lld\n",cnt,ans);
    return 0;
}
