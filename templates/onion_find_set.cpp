#include<iostream>
#include<cstdio>
using namespace std;
int n,m,pa[4000010];
int find(int x){return pa[x]==x?x:pa[x]=find(pa[x]);}
inline void onion(int x,int y){int px=find(x),py=find(y);if(px!=py)pa[px]=py;}
inline int read()
{
	char ch=getchar();
	int ret=0;
	while(ch>'9'||ch<'0')ch=getchar();
	while(ch<='9'&&ch>='0')
	{
		ret=ret*10+ch-'0';
		ch=getchar();
	}
	return ret;
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)pa[i]=i;
	int op,u,v,ans=0;
	for(int i=1;i<=m;i++)
	{
		op=read();u=read();v=read();
		if(op)ans=((ans<<1)+(find(u)==find(v)))%998244353;
		else onion(u,v);
	}
	printf("%d\n",ans);
	return 0;
}
