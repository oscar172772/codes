#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
	int n,ans=1;
	scanf("%d",&n);
	if(n==0)return printf("1\n"),0;
	while(n%2==0)n/=2;
	int sn=sqrt(n);
	for(int i=3;i<=sn;i++)
	{
		if(n%i==0)
		{
			int cnt=0;
			while(n%i==0)
			{
				cnt++;
				n/=i;
			}
			if(i%4==1)ans*=cnt*2+1;
			sn=sqrt(n);
		}
	}
	if(n!=1&&n%4==1)ans*=3;
	printf("%d\n",ans*4);
	return 0;
}
