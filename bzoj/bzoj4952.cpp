#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
int read()
{
	int tmp=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c<='9'&&c>='0')
	{
		tmp=tmp*10+c-'0';
		c=getchar();
	}
	return tmp;
}
double d[1010],s[1010];
int n,t;
const double eps=1e-11;
inline double check(double c)
{
	double ret=0;
	for(int i=1;i<=n;i++)
	{
		if(s[i]+c<=0)return 123456789098765432123456789.0;
		ret+=d[i]/(s[i]+c);
	}
	return ret;
}
int main()
{
	scanf("%d%d",&n,&t);
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf",&d[i],&s[i]);
	}
	double l=-1000000000.0,r=1000000000.0;
	while(r-l>eps)
	{
		double mid=(l+r)/2;
		if(check(mid)>t)l=mid;
		else r=mid;
	}
	printf("%.9lf\n",r);
	while(r>=999999999||r<-999999999);
	return 0;
}
