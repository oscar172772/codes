#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
struct edge
{
	int v;
	edge *next;
}*h[1010],pool[2010];
int top;
int next[1010][1010],deg[1010],dis[1010];
bool vis[1010];
void addedge(int u,int v)
{
	edge *tmp=&pool[top++];tmp->v=v;tmp->next=h[u];h[u]=tmp;
	edge *pmt=&pool[top++];pmt->v=u;pmt->next=h[v];h[v]=pmt;
	deg[u]++;deg[v]++;
}
int n,e,c,m,a,b;
double dp[1010][1010];
queue<int> q;
double search(int s,int t)
{
	if(dp[s][t])return dp[s][t];
	if(s==t)
	{
		dp[s][t]=0;
		return 0.0;
	}
	double ans=0.0;
	if(next[s][t]!=t&&next[next[s][t]][t]!=t)
	{
		ans+=search(next[next[s][t]][t],t)/(deg[t]+1);
		for(edge *tmp=h[t];tmp;tmp=tmp->next)
		{
			if(tmp->v!=next[next[s][t]][t])
				ans+=search(next[next[s][t]][t],tmp->v)/(deg[t]+1);
		}
	}
	dp[s][t]=ans+1;
	return ans+1;
}
int main()
{
	scanf("%d%d%d%d",&n,&e,&c,&m);
	for(int i=1;i<=e;i++)
	{
		scanf("%d%d",&a,&b);
		addedge(a,b);
	}
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		memset(dis,0,sizeof(dis));
		q.push(i);
		vis[i]=true;
		next[i][i]=0;
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(edge *tmp=h[u];tmp;tmp=tmp->next)
			{
				if(!vis[tmp->v]||(dis[tmp->v]==dis[u]+1&&next[i][u]<next[i][tmp->v]))
				{
					if(next[i][u])next[i][tmp->v]=next[i][u];
					else next[i][tmp->v]=tmp->v;
					dis[tmp->v]=dis[u]+1;
					if(!vis[tmp->v])q.push(tmp->v);
					vis[tmp->v]=true;
				}
			}
		}
	}
	/*for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cout<<next[i][j]<<' ';
		}
		cout<<endl;
	}*/
	printf("%.3lf\n",search(c,m));
	return 0;
}
