#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#ifndef ONLINE_JUDGE
#define $(format,...) printf("%s("format") @ line %d\n",__FUNCTION__,##__VA_ARGS__,__LINE__);
#else
#define $(...) 
#endif
const int MAXN=210,S=204,T=206,ADD=100,G=50,Inf=0x3f3f3f3f;
struct edge
{
	int v,f;
	edge *next,*rev;
}*h[MAXN],pool[MAXN*MAXN*2];
int top;
void addedge(int u,int v,int w)
{
	edge *tmp=&pool[top++];tmp->v=v;tmp->f=w;tmp->next=h[u];h[u]=tmp;
	edge *pmt=&pool[top++];pmt->v=u;pmt->f=0;pmt->next=h[v];h[v]=pmt;
	tmp->rev=pmt;pmt->rev=tmp;
}
int level[MAXN];
queue<int> q;
bool mklevel()
{
	$("")
	memset(level,-1,sizeof(level));
	while(!q.empty())q.pop();
	level[S]=0;
	q.push(S);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(edge *tmp=h[u];tmp;tmp=tmp->next)
		{
			if(tmp->f && level[tmp->v]==-1)
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
	$("%d,%d",u,minf)
	if(u==T)return minf;
	int totf=0,f;
	for(edge *tmp=h[u];tmp&&minf-totf;tmp=tmp->next)
	{
		if(tmp->f && level[tmp->v]==level[u]+1)
		{
			f=dinic(tmp->v,min(minf-totf,tmp->f));
			totf+=f;
			tmp->f-=f;
			tmp->rev->f+=f;
		}
	}
	if(totf==0)level[u]=0;
	$("%s=%d","ret",totf)
	return totf;
}
int ans;
int main()
{
	int n,k;
	char ch[55][55];
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		for(int j=G+1;j<=G+n;j++)
		{
			scanf(" %c",&ch[i][j]);
		}
	}
	int l=0,r=n;
	while(l<r)
	{
		int m=((l+r)>>1)+1;
		ans=top=0;memset(h,0,sizeof(h));
		for(int i=1;i<=n;i++)
		{
			for(int j=G+1;j<=G+n;j++)
			{
				if(ch[i][j]=='N')
					addedge(i+ADD,j+ADD,1);
				else
					addedge(i,j,1);
			}
			addedge(i,i+ADD,k);
			addedge(G+i+ADD,G+i,k);
			addedge(S,i,m);
			addedge(G+i,T,m);
		}
		while(mklevel())
		{
			ans+=dinic(S,Inf);
		}
		if(ans==n*m)l=m;
		else r=m-1;
	}
	printf("%d\n",l);
	return 0;
}
