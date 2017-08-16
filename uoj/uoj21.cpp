#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=1000010;
int cnt[MAXN];
int n,num;
long long sum,ans=0x3f3f3f3f3f3f3f3fll;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&num);
		cnt[num]++;
		sum+=num;
	}
	for(int i=1000000;i>=1;i--)
	{
		cnt[i]+=cnt[i+1];
	}
	for(int x=1;x<=1000000;x++)
	{
		long long tmp=0;
		for(int i=x;i<=1000000;i+=x)
		{
			tmp+=cnt[i];
		}
		tmp=tmp*(x-1);
		if(sum-tmp<ans)ans=sum-tmp;
	}
	printf("%lld\n",ans);
	return 0;
}
