#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct edge
{
	int v;
	edge *next;
}*h[55],pool[3000];
int top;
void addedge(int u,int v)
{
	edge *tmp=&pool[top++];tmp->v=v;tmp->next=h[u];h[u]=tmp;
	edge *pmt=&pool[top++];pmt->v=u;pmt->next=h[v];h[v]=pmt;
}
int diss[55][3050];
int topd;
//int dis[55][55];
int n,t,p,m,root;
int pa[55],dep[55];
bool vis[55],flag;
int find(int x){return pa[x]>0?pa[x]=find(pa[x]):x;}
void onion(int x,int y)
{
	int px=find(x),py=find(y);
	//pa[py]+=pa[px];
	pa[px]=py;
}
void tLCA(int cur)
{
	int lca;
	for(int i=1;i<=m;i++)
	{
		if(vis[i])
		{
			lca=find(i);
			//cout<<"lca("<<cur<<','<<i<<")="<<lca<<endl;
			diss[t][topd++]=dep[i]+dep[cur]-2*dep[lca];//dis[i][cur]=dis[cur][i]=dep[i]+dep[cur]-2*dep[lca];
		}
	}
	vis[cur]=true;
	for(edge *tmp=h[cur];tmp;tmp=tmp->next)
	{
		if(!vis[tmp->v])
		{
			dep[tmp->v]=dep[cur]+1;
			tLCA(tmp->v);
			onion(tmp->v,cur);
			//cout<<"union("<<tmp->v<<','<<cur<<");\n";
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(t=1;t<=n;t++)
	{
		memset(h,0,sizeof(h));
		//memset(dis,0,sizeof(dis));
		memset(pa,0,sizeof(pa));
		memset(vis,0,sizeof(vis));
		memset(dep,0,sizeof(dep));
		top=topd=0;
		scanf("%d",&m);
		for(int i=1;i<=m;i++)
		{
			scanf("%d",&p);
			if(!p)root=i;
			else addedge(i,p);
		}
		tLCA(root);
		//for(int i=0;i<topd;i++)cout<<diss[t][i]<<' ';cout<<endl;
		sort(diss[t],diss[t]+topd);
		for(int i=1;i<t;i++)
		{
			flag=true;
			for(int j=0;j<=topd;j++)
			{
				if(diss[t][j]!=diss[i][j])
				{
					flag=false;
					break;
				}
			}
			if(flag)
			{
				printf("%d\n",i);
				break;
			}
		}
		if(!flag)printf("%d\n",t);
	}
	//printf("%d\n",ans);
	return 0;
} 
