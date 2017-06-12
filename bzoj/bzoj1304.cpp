#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
#define DEBUG printf("%s @ line %d\n",__FUNCTION__,__LINE__);
struct edge
{
	int v;
	edge *next;
}*h[10010],pool[20020];
int top;
void addedge(int u,int v)
{
	edge *tmp=&pool[top++];tmp->v=v;tmp->next=h[u];h[u]=tmp;
	edge *pmt=&pool[top++];pmt->v=u;pmt->next=h[v];h[v]=pmt;
}
int n,m,a,b,ans=99999;
int dp[10010][2],c[10010],pa[10010],vis[10010],ord[10010];
queue<int> q;
void bfs(int root)
{
	int end=m;
	q.push(root);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		ord[end--]=u;
		vis[u]=1;
		for(edge *tmp=h[u];tmp;tmp=tmp->next)
		{
			if(!vis[tmp->v])
			{
				pa[tmp->v]=u;
				q.push(tmp->v);
			}
		}
	}
}
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	for(int i=1;i<m;i++)
	{
		scanf("%d%d",&a,&b);
		addedge(a,b);
	}
	/*
	for(int root=n+1;root<=m;root++)
	/*/
	int root=m;
	//*/
	{
		memset(vis,0,sizeof(vis));
		pa[root]=0;
		bfs(root);
		for(int i=1;i<=m;i++)
		{
			int u=ord[i];
			if(u<=n){dp[u][c[u]]=1;dp[u][1-c[u]]=99999;}
			else
			{
				/*do some evil tricks*/
				dp[u][0]=dp[u][1]=1;
				for(edge *tmp=h[u];tmp;tmp=tmp->next)
				{
					if(tmp->v!=pa[u])
					{
						dp[u][0]+=min(dp[tmp->v][0]-1,dp[tmp->v][1]);
						dp[u][1]+=min(dp[tmp->v][0],dp[tmp->v][1]-1);
					}
				}
				//cout<<root<<":"<<u<<','<<dp[u][0]<<','<<dp[u][1]<<endl;
			}
		}
		//for(int i=1;i<=m;i++)cout<<pa[i]<<' ';cout<<endl;
		//cout<<root<<' '<<dp[root][0]<<' '<<dp[root][1]<<endl;
		ans=min(ans,dp[root][0]);
		ans=min(ans,dp[root][1]);
	}
	printf("%d\n",ans);
	return 0;
}
