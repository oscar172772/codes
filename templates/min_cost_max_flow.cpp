#include<iostream>
#include<cstdio>
#include<cstring>
#include<deque>
using namespace std;
const int MAXN=411,MAXM=23333;
struct edge
{
	int v,f,w;
	edge *next,*rev;
}*h[MAXN],pool[MAXM*2];
int top;
inline void addedge(int u,int v,int c,int w)
{
	edge *tmp=&pool[top++];tmp->v=v;tmp->f=c;tmp->w=w;tmp->next=h[u];h[u]=tmp;
	edge *pmt=&pool[top++];pmt->v=u;pmt->f=0;pmt->w=-w;pmt->next=h[v];h[v]=pmt;
	tmp->rev=pmt;pmt->rev=tmp;
}
deque<int> q;
int S,T;
int last[MAXN],inq[MAXN];
long long dis[MAXN],maxf[MAXN];
edge *laste[MAXN];
int totcost,totflow;
bool SPFA()
{
	memset(dis,0x3f,sizeof(dis));
	memset(last,0,sizeof(last));
	memset(maxf,0,sizeof(maxf));
	memset(inq,0,sizeof(inq));
	while(!q.empty())q.pop_front();
	q.push_front(S);
	maxf[S]=0x3f3f3f3f3f3f3f3fll;
	inq[S]=1;
	dis[S]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop_front();
		inq[u]=0;
		//cout<<"SPFA("<<u<<",dis = "<<dis[u]<<",maxFlow = "<<maxf[u]<<",last = "<<last[u]<<")\n";
		for(edge *tmp=h[u];tmp;tmp=tmp->next)
		{
			if(tmp->f&&dis[tmp->v]>dis[u]+tmp->w)
			{
				dis[tmp->v]=dis[u]+tmp->w;
				last[tmp->v]=u;
				maxf[tmp->v]=max(maxf[tmp->v],min(maxf[u],(long long)tmp->f));
				laste[tmp->v]=tmp;
				if(!inq[tmp->v])
				{
					if(q.empty()||dis[q.front()]>tmp->v)q.push_front(tmp->v);
					else q.push_back(tmp->v);
					inq[tmp->v]=1;
				}
			}
		}
	}
	if(dis[T]>=0x3f3f3f3f3f3f3f3fll)return false;
	int u=T;
	while(last[u])
	{
		//cout<<u<<endl;
		laste[u]->f-=maxf[T];
		laste[u]->rev->f+=maxf[T];
		u=last[u];
	}
	totcost+=dis[T]*maxf[T];
	totflow+=maxf[T];
	return true;
}
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	S=1,T=n;
	int a,b,c,d;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		addedge(a,b,c,d);
	}
	while(SPFA());
	printf("%lld %lld\n",totflow,totcost);
	return 0;
}
