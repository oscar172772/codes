#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=100010,B=300;
long long a[MAXN],p[MAXN],pp[MAXN],cpos[MAXN],cnum[MAXN];
int n,m;
char buf;
inline long long read()
{
	char ch=getchar();
	long long ret=0;
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
	for(register int i=1;i<=n;i++)
		a[i]=read();
	for(register int i=1;i<=n;i++)
		p[i]=p[i-1]+a[i];
	for(register int i=1;i<=n;i++)
		pp[i]=pp[i-1]+p[i];
	long long x,y;
	for(register int i=1,k=1;i<=m;++i,++k)
	{
		if(k>=B)k-=B;
		if(!k)
		{
			for(register int j=1;j<=n;j++)
				p[j]=p[j-1]+a[j];
			for(register int j=1;j<=n;j++)
				pp[j]=pp[j-1]+p[j];
			for(register int j=0;j<B;j++)
				cpos[j]=cnum[j]=0;
		}
		buf=getchar();
		while(buf!='M'&&buf!='Q')buf=getchar();
		if(buf=='M')
		{
			x=read();y=read();
			y-=a[x];
			a[x]+=y;
			cpos[k]=x;
			cnum[k]=y;
		}
		else
		{
			x=read();
			long long ans=pp[x];
			for(register int j=0;j<k;j++)
			{
				if(cpos[j]<=x)
					ans+=(x-cpos[j]+1)*cnum[j];
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
