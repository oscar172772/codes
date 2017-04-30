#include<iostream>
#include<cstdio>
#include<stack>
#include<cstring>
using namespace std;
struct edge
{
	int v;
	edge *next;
}*h[20100],pool[100100];
int top;
int n,m;
int dfn[20100],low[20100];
int vis[20100],bel[20100],indeg[20100],outdeg[20100],cnt[20100];
int ind,gri;
stack<int> s;
void addedge(int u,int v)
{
	edge *tmp=&pool[top++];
	tmp->v=v;
	tmp->next=h[u];
	h[u]=tmp;
	indeg[v]++;
}
void trajan(int u)
{
	s.push(u);
	//cout<<"tarjan "<<u<<endl;
	dfn[u]=low[u]=++ind;
	for(edge *tmp=h[u];tmp;tmp=tmp->next)
	{
		if(!dfn[tmp->v])
		{
			trajan(tmp->v);
			low[u]=min(low[u],low[tmp->v]);
		}
		else if(!vis[tmp->v])
		{
			low[u]=min(low[u],dfn[tmp->v]);
		}
	}
	int v;
	if(dfn[u]==low[u])
	{
		gri++;
		do
		{
			v=s.top();
			s.pop();
			vis[v]=1;
			bel[v]=gri;
			cnt[gri]++;
			//cout<<"pop "<<v<<endl;/
		}while(u!=v);
	}
	//cout<<"trajan "<<u<<endl;
}
int u,v;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		addedge(u,v);
	}
	int c=0,cc=-1;
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])trajan(i);
	}
	memset(indeg,0,sizeof(indeg));
	for(int i=1;i<=n;i++)
	{
		for(edge *tmp=h[i];tmp;tmp=tmp->next)
		{
			if(bel[i]!=bel[tmp->v])
			{
				outdeg[bel[i]]++;
				indeg[bel[tmp->v]]++;
			}
		}
		//cout<<bel[i]<<' '<<cnt[bel[i]]<<endl;
	}
	for(int i=1;i<=gri;i++)
	{
		if(!outdeg[i])
		{
			c++;
			cc=i;
		}
	}
	if(c>1)cout<<0<<endl;
	else cout<<cnt[cc]<<endl;
	return 0;
}

