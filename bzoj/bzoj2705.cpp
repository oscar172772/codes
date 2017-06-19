#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
using namespace std;
#define int unsigned long long
int ans=0,n;
int phi(int x)
{
	int sx=sqrt(x),ret=1,tmp;
	for(int i=2;i<=sx;i++)
	{
		if(x%i==0)
		{
			tmp=i-1;
			x/=i;
			while(x%i==0)
			{
				tmp*=i;
				x/=i;
			}
			ret*=tmp;
			sx=sqrt(x);
		}
	}
	if(x>1)ret*=x-1;
	return ret;
}
void fact(int x)
{
	int sx=sqrt(x);
	for(int i=1;i<=sx;i++)
	{
		if(x%i==0)
		{
			if(i!=x/i)
			{
				ans+=i*phi(x/i);
				ans+=(x/i)*phi(i);
			}
			else ans+=i*phi(i);
		}
	}
}
#undef int
int main()
{
	//for(int i=1;i<=10;i++)cout<<phi(i)<<endl;
	scanf("%llu",&n);
	fact(n);
	printf("%llu\n",ans);
	return 0;
}
