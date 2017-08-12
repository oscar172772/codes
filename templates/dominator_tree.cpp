#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=100010;
struct edge
{
	int v;
	edge *next;
}*h[MAXN],pool[MAXN*10];
int top,deg[MAXN];
vector<int> pa[MAXN];
inline void addedge(int u,int v)
{
	edge *tmp=&pool[top++];tmp->v=v;tmp->next=h[u];h[u]=tmp;deg[v]++;
}
int n;
int seq[MAXN],end;
queue<int> q;
void topo_sort()
{
	while(!q.empty())
	{
		int x=q.front();q.pop();
		seq[++end]=x;
		for(edge *tmp=h[x];tmp;tmp=tmp->next)
		{
			deg[tmp->v]--;
			if(deg[tmp->v]==0)q.push(tmp->v);
		}
	}
}
int pa2[MAXN],jump[MAXN][18],dep[MAXN],siz[MAXN];
inline void update(int x)
{
	jump[x][0]=pa2[x];
	for(int i=1;i<=17;i++)
	{
		jump[x][i]=jump[jump[x][i-1]][i-1];
	}
}
inline int LCA(int a,int b)
{
	if(dep[a]<dep[b])swap(a,b);
	for(int i=17;i>=0;i--)
	{
		if(dep[jump[a][i]]>=dep[b])
			a=jump[a][i];
	}
	for(int i=17;i>=0;i--)
	{
		if(jump[a][i]!=jump[b][i])
		{
			a=jump[a][i];
			b=jump[b][i];
		}
	}
	while(a!=b)a=pa2[a],b=pa2[b];
	return a;
}
int main()
{
	scanf("%d",&n);
	int a;
	for(int i=1;i<=n;i++)
	{
		int cnt=0;
		while(scanf("%d",&a)&&a!=0)
		{
			addedge(a,i);
			pa[i].push_back(a);
			cnt++;
		}
		if(cnt==0)q.push(i);
	}
	topo_sort();
	//for(int i=1;i<=n;i++)cout<<seq[i]<<' ';cout<<endl;
	for(int t=1;t<=n;t++)
	{
		int i=seq[t];
		if(pa[i].size()==0)
		{
			dep[i]=1;
			continue;
		}
		int lca=pa[i][0];
		for(int j=1;j<pa[i].size();j++)
		{
			lca=LCA(lca,pa[i][j]);
		}
		pa2[i]=lca;
		dep[i]=dep[lca]+1;
		update(i);
		deg[pa2[i]]++;
	}
	for(int i=1;i<=n;i++)
	{
		siz[i]=1;
		if(!deg[i])q.push(i);
	}
	while(!q.empty())
	{
		int u=q.front();q.pop();
		if(!pa2[u])continue;
		siz[pa2[u]]+=siz[u];
		deg[pa2[u]]--;
		if(deg[pa2[u]]==0)q.push(pa2[u]);
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",siz[i]-1);
	return 0;
}
