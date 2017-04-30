#include<iostream>
#include<cstdio>
#include<deque>
#include<cstring>
using namespace std;
const int MAXN=31,Inf=0x3f3f3f3f;
struct edge
{
    int v,len;
    edge *next;
}*h[MAXN],pool[MAXN*MAXN*2];
int top;
void addedge(int u,int v,int len)
{
    edge *tmp=&pool[top++];tmp->v=v;tmp->len=len;tmp->next=h[u];h[u]=tmp;
    edge *pmt=&pool[top++];pmt->v=u;pmt->len=len;pmt->next=h[v];h[v]=pmt;
}
int A,B,open[111][MAXN],open2[111][111][MAXN],f[111][111],dp[111],dis[MAXN];
deque<int> q;
inline int spfa(int s,int t)
{
    while(!q.empty())q.pop_front();
    memset(dis,Inf,sizeof(dis));
    dis[A]=0;
    q.push_back(A);
    while(!q.empty())
    {
        int u=q.front();q.pop_front();
        for(edge *tmp=h[u];tmp;tmp=tmp->next)
        {
            if(open2[s][t][tmp->v]&&dis[tmp->v]>dis[u]+tmp->len)
            {
                dis[tmp->v]=dis[u]+tmp->len;
                if((!q.empty())&&dis[tmp->v]<dis[q.front()])q.push_front(tmp->v);
                else q.push_back(tmp->v);
            }
        }
    }
    if(dis[B]!=Inf)return dis[B]*(t-s+1);
    return dis[B];
}
int main()
{
    int n,m,K,e,u,v,w,d,p,a,b;
    scanf("%d%d%d%d",&n,&m,&K,&e);
    A=1;B=m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            open[i][j]=1;
        }
    }
    for(int i=1;i<=e;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        addedge(u,v,w);
    }
    scanf("%d",&d);
    for(int i=1;i<=d;i++)
    {
        scanf("%d%d%d",&p,&a,&b);
        for(int t=a;t<=b;t++)open[t][p]=0;
    }
    for(int k=1;k<=m;k++)
    {
        for(int i=1;i<=n;i++)
        {
            if(!open[i][k])continue;
            open2[i][i][k]=1;
            for(int j=i+1;j<=n;j++)
            {
                if(open[j][k]==1)
                    open2[i][j][k]=1;
                else break;
            }
        }
    }
    for(int s=1;s<=n;s++)
    {
        for(int t=s;t<=n;t++)
        {
            f[s][t]=spfa(s,t);
            //cout<<f[s][t]<<' ';
        }
        //cout<<endl;
    }
    for(int i=1;i<=n;i++)
    {
        dp[i]=Inf;
        for(int k=0;k<i;k++)
        {
            dp[i]=min(dp[i],dp[k]+f[k+1][i]+K);
        }
        //cout<<dp[i]<<' ';
    }//cout<<endl;
    printf("%d\n",dp[n]-K);
    return 0;
}
