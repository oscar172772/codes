#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#define INF 1073741823
using namespace std;
struct node
{
	int v,f,len;
	node *rev,*next;
}pool[100100],*h[1100];
vector<node*> route[1100];
queue<int> q;
int N,M,top,SP[1100],in[1100],len;
inline void addedge(int x,int y,int f,int l)
{
	node *p=&pool[top++],*rp=&pool[top++],*q=&pool[top++],*rq=&pool[top++];
	p->v=y;p->f=f;p->len=l;p->next=h[x];p->rev=rp;h[x]=p;
	rp->v=x;rp->f=0;rp->len=-l;rp->next=h[y];rp->rev=p;h[y]=rp;
	q->v=x;q->f=f;q->len=l;q->next=h[y];q->rev=rq;h[y]=q;
	rq->v=y;rq->f=0;rq->len=-l;rq->next=h[x];rq->rev=q;h[x]=rq;
}
inline bool SPFA(int a,int b)
{
	for(int i=0;i<=1009;i++)SP[i]=INF;
	memset(in,0,sizeof(in));
	memset(route,0,sizeof(route));
	in[a]++;
	SP[a]=0;
	q.push(a);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(node *tmp=h[u];tmp;tmp=tmp->next)
		{
			if(tmp->f&&SP[tmp->v]>SP[u]+tmp->len)
			{
				SP[tmp->v]=SP[u]+tmp->len;
				q.push(tmp->v);
				in[tmp->v]++;
				if(in[tmp->v]>N-1)return false;
				route[tmp->v]=route[u];
				route[tmp->v].push_back(tmp);
			}
		}
	}
	if(SP[b]==INF)return false;
	return true;
}
inline void Find(int u)
{
	for(int i=0;i<route[u].size();i++)
	{
		/*debug*///printf("%d ",route[u][i]->v);
		node *tmp=route[u][i];
		tmp->f--;
		tmp->rev->f++;
	}
	/*debug*///printf("\n");
}
int main()
{
	scanf("%d%d",&N,&M);
	int s,e,l,S=0,T=N+1;
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d%d",&s,&e,&l);
		addedge(s,e,1,l);
	}
	addedge(S,1,2,0);
	addedge(N,T,2,0);
	if(SPFA(S,T))
	{
		len+=SP[T];
		Find(T);
	}
	else return 3242097;
	if(SPFA(S,T))
	{
		len+=SP[T];
		Find(T);
		printf("%d",len);
	}
	else return 3242097;
	//system("pause");
	return 0;
}
