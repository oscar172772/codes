#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=50000,Inf=0x3f3f3f3f;
//HLD
struct edge
{
	int v;
	edge *next;
}*h[MAXN],epool[2*MAXN];
int etop;
int w[MAXN],ntt[MAXN],ttn[MAXN];
void addedge(int u,int v)
{
	edge *tmp=&epool[etop++];tmp->v=v;tmp->next=h[u];h[u]=tmp;
	edge *pmt=&epool[etop++];pmt->v=u;pmt->next=h[v];h[v]=pmt;
}
int dep[MAXN],siz[MAXN],maxson[MAXN],pa[MAXN],pathtop[MAXN],currenttop;
int ltop;
void dfs1(int cur)
{
	//cout<<"dfs1 "<<cur<<endl;
	siz[cur]=1;
	maxson[cur]=0;
	for(edge *tmp=h[cur];tmp;tmp=tmp->next)
	{
		//cout<<cur<<"->"<<tmp->v<<endl;
		if(dep[tmp->v]==-1)
		{
			dep[tmp->v]=dep[cur]+1;
			dfs1(tmp->v);
			siz[cur]+=siz[tmp->v];
			if(siz[maxson[cur]]<siz[tmp->v])maxson[cur]=tmp->v;
			pa[tmp->v]=cur;
		}
	}
}
void dfs2(int cur)
{
	//cout<<cur<<endl;
	pathtop[cur]=currenttop;
	ltop++;
	ntt[ltop]=cur;
	ttn[cur]=ltop;
	int ms=maxson[cur];
	if(ms)
	{
		dfs2(ms);
	}
	for(edge *tmp=h[cur];tmp;tmp=tmp->next)
	{
		if(dep[tmp->v]==dep[cur]+1&&tmp->v!=ms)
		{
			currenttop=tmp->v;
			dfs2(tmp->v);
		}
	}
}
//SGT
struct node
{
	int l,r,sum,maxx;
	node *lson,*rson;
}*root,pool[3*MAXN];
int top;
node* bt(int l,int r)
{
	node *tmp=&pool[top++];
	tmp->l=l;tmp->r=r;
	if(l==r)
	{
		tmp->sum=tmp->maxx=w[ntt[l]];
	}
	else
	{
		int m=l+r>>1;
		tmp->lson=bt(l,m);
		tmp->rson=bt(m+1,r);
		tmp->sum=tmp->lson->sum+tmp->rson->sum;
		tmp->maxx=max(tmp->lson->maxx,tmp->rson->maxx);
	}
	return tmp;
}
void change(node *cur,int pos,int val)
{
	if(cur->l==cur->r)
	{
		cur->sum=cur->maxx=val;
		return;
	}
	if(pos<=cur->lson->r)change(cur->lson,pos,val);
	else change(cur->rson,pos,val);
	cur->sum=cur->lson->sum+cur->rson->sum;
	cur->maxx=max(cur->lson->maxx,cur->rson->maxx);
}
int qsum(node *cur,int l,int r)
{
	if(cur->l==l&&cur->r==r)return cur->sum;
	if(cur->lson->r>=r)return qsum(cur->lson,l,r);
	else if(cur->rson->l<=l)return qsum(cur->rson,l,r);
	else return qsum(cur->lson,l,cur->lson->r)+qsum(cur->rson,cur->rson->l,r);
}
int qmax(node *cur,int l,int r)
{
	//cout<<"qmax "<<cur->l<<' '<<cur->r<<' '<<l<<' '<<r<<endl;
	if(cur->l==l&&cur->r==r)return cur->maxx;
	if(cur->lson->r>=r)return qmax(cur->lson,l,r);
	else if(cur->rson->l<=l)return qmax(cur->rson,l,r);
	else return max(qmax(cur->lson,l,cur->lson->r),qmax(cur->rson,cur->rson->l,r));
}
//OPERATION
void ctree(int pos,int val)
{
	change(root,ttn[pos],val);
}
int qtreesum(int a,int b)
{
	int ans=0;
	while(pathtop[a]!=pathtop[b])
	{
		if(dep[pathtop[a]]<dep[pathtop[b]])
		{
			ans+=qsum(root,ttn[pathtop[b]],ttn[b]);
			b=pa[pathtop[b]];
		}
		else
		{
			ans+=qsum(root,ttn[pathtop[a]],ttn[a]);
			a=pa[pathtop[a]];
		}
	}
	if(dep[a]<dep[b])ans+=qsum(root,ttn[a],ttn[b]);
	else ans+=qsum(root,ttn[b],ttn[a]);
	return ans;
}
int qtreemax(int a,int b)
{
	int ans=-Inf;
	while(pathtop[a]!=pathtop[b])
	{
		//cout<<"qtreemax_jump "<<a<<' '<<b<<endl;
		if(dep[pathtop[a]]<dep[pathtop[b]])
		{
			ans=max(ans,qmax(root,ttn[pathtop[b]],ttn[b]));
			b=pa[pathtop[b]];
		}
		else
		{
			ans=max(ans,qmax(root,ttn[pathtop[a]],ttn[a]));
			a=pa[pathtop[a]];
		}
	}
	//cout<<"qtreemax_same_chain "<<a<<' '<<b<<endl;
	if(dep[a]<dep[b])ans=max(ans,qmax(root,ttn[a],ttn[b]));
	else ans=max(ans,qmax(root,ttn[b],ttn[a]));
	return ans;
}
//MAIN
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int n,q,u,v;
	char buf[30];
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		addedge(u,v);
	}
	for(int i=1;i<=n;i++)scanf("%d",&w[i]);
	memset(dep,-1,sizeof(dep));
	dep[1]=0;
	dfs1(1);
	currenttop=1;
	dfs2(1);
	root=bt(1,n);
	scanf("%d",&q);
	while(q--)
	{
		scanf("%s %d %d",buf,&u,&v);
		switch(buf[1])
		{
			case 'H':
				ctree(u,v);
				break;
			case 'S':
				printf("%d\n",qtreesum(u,v));
				break;
			case 'M':
				printf("%d\n",qtreemax(u,v));
				break;
		}
	}
	return 0;
}
