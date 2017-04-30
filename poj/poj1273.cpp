#include<iostream>
//#include<windows.h>
#include<cstdio>
#include<climits>
#include<queue>
using namespace std;
//using void unsigned static extern friend public protected private virtual short long int struct class default false true template typedef explicit namespace this operator signed bool char sizeof static_cast const const_cast volatile float double if else for while do goto inline reinterpret_cast return try catch throw new delete typename wchar_t char16_t char32_t __cdecl __int64 __int32
struct node
{
	int v,f;
	node *next,*rev;
}pool[100010],*h[50010];
int V,E,top,level[50010];
bool vis[50010];
queue<int> q;
inline bool init()
{
	memset(pool,0,sizeof(pool));
	memset(h,0,sizeof(h));
	if(!(cin>>E>>V))return false;
	for(int i=1;i<=E;i++)
	{
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		node *p=&pool[top++];
		node *q=&pool[top++];
		p->v=y;p->f=c;p->next=h[x];h[x]=p;p->rev=q;
		q->v=x;q->f=0;q->next=h[y];h[y]=q;q->rev=p;
		/*debug*///printf("init--(%d,%d)\n",x,y);
	}
	return true;
}
inline bool suanlevel()
{
	/*debug*///printf("suanlevelbegin\n");
	for(int i=2;i<=V;i++)level[i]=-1;
	level[1]=0;
	while(!q.empty())q.pop();
	q.push(1);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(node *tmp=h[u];tmp;tmp=tmp->next)
		{
			if(level[tmp->v]==-1&&tmp->f>0)
			{
				level[tmp->v]=level[u]+1;
				q.push(tmp->v);
			}
		}
	}
	/*debug*///printf("suanlevelend\n");
	if(level[V]!=-1)return true;
	return false;
}
int Find(int u,int Min)
{
	/*debug*///printf("Findbegin%d \n",u);
	if(u==V)
	{
		/*debug*///printf("%dMin in%d\n",Min,u);
		return Min;
	}
	int s=0,t;
	for(node *tmp=h[u];tmp && s <= Min;tmp=tmp->next)
	{
		if(!vis[tmp->v] && level[tmp->v] == level[u] + 1 && tmp->f > 0)
		{
			vis[tmp->v]=true;
			t=Find(tmp->v,min(Min-s,tmp->f));
			vis[tmp->v]=false;
			/*debug*///printf("Find%din%d\n",t,u);
			s+=t;
			tmp->f-=t;
			tmp->rev->f+=t;
		}
	}
	/*debug*///printf("Findend%d\n",u);
	return s;
}
inline void dinic()
{
	while(init())
	{
		int flow=0,t;
		while(suanlevel())
		{
			memset(vis,0,sizeof(vis));
			while(t=Find(1,INT_MAX))
				flow+=t;
		}
		printf("%d\n",flow);
	}
	
}
int main()
{
	//freopen("1.txt","w",stdout);
	dinic();
	//system("pause");
	return 0;
}
