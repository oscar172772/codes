#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<deque>
using namespace std;
struct edge
{
	int v,len;
	edge *next;
}*h[2000010],pool[6000000];
int top;
void addedge(int u,int v,int len)
{
	edge *tmp=&pool[top++];tmp->v=v;tmp->len=len;tmp->next=h[u];h[u]=tmp;
	edge *pmt=&pool[top++];pmt->v=u;pmt->len=len;pmt->next=h[v];h[v]=pmt;
}
const int S=2000000,T=2000001,Inf=0x3f3f3f3f;
int n,m,len;
int dis[2000010];
bool vis[2000010];
deque<int> D;
int main()
{
	scanf("%d%d",&n,&m);
	if(n==1&&m==1){printf("0\n");return 0;}
	else if(n==1||m==1)
	{
		int minn=Inf;
		for(int i=1;i<=n+m-1;i++)
		{
			scanf("%d",&len);
			if(len<minn)minn=len;
		}
		printf("%d\n",minn);
		return 0;
	}
	for(int i=0;i<2000010;i++){dis[i]=Inf;}
	dis[S]=0;
	for(int j=1;j<=m-1;j++)
	{
		scanf("%d",&len);
		addedge(T,j*2-1,len);
		//cout<<"added "<<T<<" to "<<j*2-1<<endl;
	}
	for(int i=2;i<=n-1;i++)
	{
		for(int j=1;j<=m-1;j++)
		{
			scanf("%d",&len);
			addedge(((i-2)*(m-1)+(j-1))*2,((i-1)*(m-1)+(j-1))*2+1,len);
			//cout<<"added "<<((i-2)*(m-1)+(j-1))*2<<" to "<<((i-1)*(m-1)+(j-1))*2+1<<endl;
		}
	}
	for(int j=1;j<=m-1;j++)
	{
		scanf("%d",&len);
		addedge(S,((n-2)*(m-1)+(j-1))*2,len);
		//cout<<"added "<<S<<" to "<<((n-2)*(m-1)+(j-1))*2<<endl;
	}
	for(int i=1;i<=n-1;i++)
	{
		scanf("%d",&len);
		addedge(S,(i-1)*(m-1)*2,len);
		//cout<<"added "<<S<<" to "<<(i-1)*(m-1)*2<<endl;
		for(int j=2;j<=m-1;j++)
		{
			scanf("%d",&len);
			addedge(((i-1)*(m-1)+(j-2))*2+1,((i-1)*(m-1)+(j-1))*2,len);
			//cout<<"added "<<((i-1)*(m-1)+(j-2))*2+1<<" to "<<((i-1)*(m-1)+(j-1))*2<<endl;
		}
		scanf("%d",&len);
		addedge(T,(i*(m-1)-1)*2+1,len);
		//cout<<"added "<<T<<" to "<<(i*(m-1)-1)*2+1<<endl;
	}
	for(int i=1;i<=n-1;i++)
	{
		for(int j=1;j<=m-1;j++)
		{
			scanf("%d",&len);
			addedge(2*((i-1)*(m-1)+(j-1)),2*((i-1)*(m-1)+(j-1))+1,len);
			//cout<<"added "<<2*((i-1)*(m-1)+(j-1))<<" to "<<2*((i-1)*(m-1)+(j-1))+1<<endl;
		}
	}
	//S->T
	D.push_back(S);
	vis[S]=true;
	while(!D.empty())
	{
		int cur=D.front();
		D.pop_front();
		vis[cur]=false;
		for(edge *tmp=h[cur];tmp;tmp=tmp->next)
		{
			if(dis[tmp->v]>dis[cur]+tmp->len)
			{
				dis[tmp->v]=dis[cur]+tmp->len;
				if(!vis[tmp->v])
				{
					if(D.empty()||dis[D.front()]>dis[tmp->v])D.push_front(tmp->v);
					else D.push_back(tmp->v);
				}
				vis[tmp->v]=true;
			}
		}
	}
	printf("%d\n",dis[T]);
	//for(int i=0;i<12;i++)printf("dis[%d]=%d\n",i,dis[i]);
	//system("pause");
	return 0;
}
