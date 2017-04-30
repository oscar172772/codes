#include<iostream>
#include<cstdio>
#include<queue>
#include<cstdlib>
#include<cstring>
using namespace std;
struct edge
{
	int v,f;
	edge *next,*rev;
}*h[900],pool[30000];
int top;
int r,c,d,frogs;
char map[450],frog[450];
inline int hash(int x,int y){return x*c+y;}
inline void addedge(int u,int v,int c)
{
	edge *tmp=&pool[top++],*pmt=&pool[top++];
	tmp->v=v;pmt->v=u;
	tmp->f=c;pmt->f=0;
	tmp->next=h[u];pmt->next=h[v];
	h[u]=tmp;h[v]=pmt;
	tmp->rev=pmt;pmt->rev=tmp;
}
const int S=817,T=836,Inf=0x3f3f3f3f,chai=400;
int level[900];
queue<int> q;
inline bool mklevel()
{
	memset(level,-1,sizeof(level));
	level[S]=0;
	while(!q.empty())q.pop();
	q.push(S);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(edge *tmp=h[u];tmp;tmp=tmp->next)
		{
			if(tmp->f&&level[tmp->v]==-1)
			{
				level[tmp->v]=level[u]+1;
				q.push(tmp->v);
			}
		}
		if(level[T]!=-1)return true;
	}
	return false;
}
int dinic(int u,int minn)
{
	if(u==T)return minn;
	int curf=0;
	for(edge *tmp=h[u];tmp&&(minn-curf>0);tmp=tmp->next)
	{
		if(level[tmp->v]==level[u]+1&&tmp->f)
		{
			int f=dinic(tmp->v,min(tmp->f,minn-curf));
			tmp->f-=f;
			tmp->rev->f+=f;
			curf+=f;
		}
	}
	if(!curf)level[u]=-1;
	return curf;
}
void init(){memset(h,0,sizeof(h));top=0;frogs=0;}
int main()
{
	int cases;
	char buf[200];
	scanf("%d",&cases);
	for(int kase=1;kase<=cases;kase++){
		init();
		scanf("%d%d",&r,&d);
		for(int i=0;i<r;i++)
		{
			scanf(" %s",buf);
			c=strlen(buf);
			for(int j=0;j<c;j++)
			{
				map[hash(i,j)]=buf[j];
				if(map[hash(i,j)]!='0')
				{
					addedge(hash(i,j),hash(i,j)+chai,map[hash(i,j)]-'0');
					if(i<d||j<d||i>=r-d||j>=c-d)
						addedge(hash(i,j)+chai,T,Inf);
				}
			}
		}
		for(int i1=0;i1<r;i1++)
			for(int j1=0;j1<c;j1++)
						if(map[hash(i1,j1)]!='0')
					for(int i2=0;i2<r;i2++)
						for(int j2=0;j2<c;j2++)
							if(map[hash(i2,j2)!='0']&&(i1!=i2||j1!=j2))
								if(abs(i1-i2)+abs(j1-j2)<=d)
								{
									addedge(hash(i1,j1)+chai,hash(i2,j2),Inf);
									//addedge(hash(i2,j2)+chai,hash(i1,j1),Inf);
								}
		for(int i=0;i<r;i++)
		{
			for(int j=0;j<c;j++)
			{
				scanf(" %c",&frog[hash(i,j)]);
				if(frog[hash(i,j)]!='.')
				{
					frogs++;
					addedge(S,hash(i,j),1);
				}
			}
		}
		while(mklevel()){frogs-=dinic(S,Inf);}
		printf("Case #%d: ",kase);
        if(!frogs)printf("no lizard was ");
        else if(frogs==1)printf("1 lizard was ");
        else printf("%d lizards were ",frogs);
        printf("left behind.\n");
	}
	return 0;
}
