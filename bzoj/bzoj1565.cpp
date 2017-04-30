#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
#include<stack>
using namespace std;
struct edge
{
	int v,f,mark;
	edge *next,*rev;
}*h[750],pool[455000];
int top;
int n,m,score[750],sum;
const int Inf=0x3f3f3f3f,S=700,T=701;
inline int hash(int r,int c){return r*m+c;}
//inline int hr(int h){return h/m;}inline int hc(int h){return h%m;}
//inline void //debug(string str,int h){cout<<str<<' ';if(h==S)cout<<'S';else if(h==T)cout<<'T';else cout<<hr(h)<<','<<hc(h);cout<<endl;}
//inline void //debug(string str,int h,int h2){cout<<str<<' ';if(h==S)cout<<'S';else if(h==T)cout<<'T';else cout<<hr(h)<<','<<hc(h);cout<<' ';if(h2==S)cout<<'S';else if(h2==T)cout<<'T';else cout<<hr(h2)<<','<<hc(h2);cout<<endl;}
//inline void //debug(string str,int h,int h2,int len){cout<<str<<' ';if(h==S)cout<<'S';else if(h==T)cout<<'T';else cout<<hr(h)<<','<<hc(h);cout<<' ';if(h2==S)cout<<'S';else if(h2==T)cout<<'T';else cout<<hr(h2)<<','<<hc(h2);cout<<' '<<len<<endl;}
inline void addedge(int u,int v,int c)
{
	//debug("addedge",u,v,c);
	edge *tmp=&pool[top++],*pmt=&pool[top++];
	tmp->v=v;pmt->v=u;
	tmp->f=c;pmt->f=0;
	tmp->next=h[u];pmt->next=h[v];
	h[u]=tmp;h[v]=pmt;
	tmp->rev=pmt;pmt->rev=tmp;
}
//tarjan
int dfn[750],low[750];
int vis[750],bel[750],cnt[750];
int ind,gri;
stack<int> s;
void trajan(int u)
{
	s.push(u);
	//debug("tarjan",u);//cout<<"tarjan "<<u<<endl;
	dfn[u]=low[u]=++ind;
	for(edge *tmp=h[u];tmp;tmp=tmp->next)
	{
		if((!tmp->f)&&tmp->v!=S&&tmp->v!=T)
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
			//debug("pop",v);//cout<<"pop "<<v<<endl;/
		}while(u!=v);
	}
	//debug("trajan",u);//cout<<"trajan "<<u<<endl;
}
//mklevel
queue<int> q;
int level[750];
inline bool mklevel()
{
	sum=0;
	memset(level,-1,sizeof(level));
	level[S]=0;
	while(!q.empty())q.pop();
	q.push(S);
	while(!q.empty())
	{
		//debug("mklevel",q.front());
		int u=q.front();q.pop();
		sum+=score[u];
		for(edge *tmp=h[u];tmp;tmp=tmp->next)
		{
			if((!tmp->mark)&&level[tmp->v]==-1&&tmp->f)
			{
				level[tmp->v]=level[u]+1;
				q.push(tmp->v);
			}
		}
		if(level[T]!=-1)return true;
	}
	return false;
}
//dinic
int dinic(int u,int minn)
{
	//debug("dinic",u);
	if(u==T)return minn;
	int curf=0;
	for(edge *tmp=h[u];tmp&&(minn-curf);tmp=tmp->next)
	{
		if((!tmp->mark)&&level[tmp->v]==level[u]+1&&tmp->f)
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
//del
void del(int u)
{
	if(u==S||u==T)return;
	for(edge *tmp=h[u];tmp;tmp=tmp->next)
	{
		if(tmp->f==0&&!tmp->mark/*&&tmp->v!=S&&tmp->v!=T*/)
		{
			//debug("delete",u,tmp->v);
			tmp->mark=1;
			tmp->rev->mark=1;
			del(tmp->v);
		}
	}
}
//main
int main()
{
	int w,x,y;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d%d",&score[hash(i,j)],&w);
			if(score[hash(i,j)]>0)addedge(S,hash(i,j),score[hash(i,j)]);
			else if(score[hash(i,j)]<0)addedge(hash(i,j),T,-score[hash(i,j)]);
			for(int k=1;k<=w;k++)
			{
				scanf("%d%d",&x,&y);
				addedge(hash(x,y),hash(i,j),Inf);
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m-1;j++)
		{
			addedge(hash(i,j),hash(i,j+1),Inf);
        }
    }
	//tarjan
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(!vis[hash(i,j)])
				trajan(hash(i,j));
        }
    }
	//memset(indeg,0,sizeof(indeg));
	for(int i=0;i<n*m;i++)
	{
		//cout<<"bel["<<i<<"]="<<bel[i]<<",cnt[bel["<<i<<"]]="<<cnt[bel[i]]<<endl;
		if(cnt[bel[i]]>1)del(i);
		//cout<<bel[i]<<' '<<cnt[bel[i]]<<endl;
	}
	//dinic
	int flow=0;
	while(mklevel())flow+=dinic(S,Inf);
	printf("%d\n",sum);
	return 0;
}
