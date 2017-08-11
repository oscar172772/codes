#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int MAXN=1000010,MAXM=5000010;
struct edge
{
	int v;
	int f;
	edge *next,*rev;
}*h[MAXN],pool[MAXM*2];
int top;
inline void addedge(int u,int v,int c)
{
	edge *tmp=&pool[top++];tmp->v=v;tmp->next=h[u];h[u]=tmp;tmp->f=c;
	edge *pmt=&pool[top++];pmt->v=u;pmt->next=h[v];h[v]=pmt;pmt->f=0;
	tmp->rev=pmt;pmt->rev=tmp;
}
queue<int> q;
int level[MAXN];
int S,T;
inline bool mklevel()
{
	while(!q.empty())q.pop();
	memset(level,-1,sizeof(level));
	q.push(S);
	level[S]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(edge *tmp=h[u];tmp;tmp=tmp->next)
		{
			if(level[tmp->v]==-1&&tmp->f)
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
	//cout<<"dinic("<<u<<','<<minf<<")\n";
	if(u==T)return minf;
	int totf=0;
	for(edge *tmp=h[u];tmp;tmp=tmp->next)
	{
		if(tmp->f&&level[tmp->v]==level[u]+1)
		{
			int f=dinic(tmp->v,min(minf-totf,tmp->f));
			tmp->f-=f;
			tmp->rev->f+=f;
			totf+=f;
			if(totf==minf)break;
		}
	}
	if(totf==0)level[u]=-1;
	return totf;
}
int n,m;
int main()
{
	scanf("%d%d%d%d",&n,&m,&S,&T);
	int a,b,c;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		addedge(a,b,c);
	}
	long long totf=0;
	while(mklevel())totf+=dinic(S,0x7fffffff);
	printf("%lld\n",totf);
	return 0;
}
