#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
int primes[233],top;
long long ans;
inline bool Isprime(int x)
{
	for(int j=2;j<=sqrt(x);j++)
	{
		if(x%j==0)
			return false;
	}
	return true;
}
long long dp[233][1001];//primeID,leftsum
int main()
{
	for(int i=2;i<=1000;i++)
		if(Isprime(i))
			primes[++top]=i;
	int n;
	scanf("%d",&n);
	dp[0][n]=1;
	for(int i=1;i<=top;i++)
		for(int left=n;left>=0;left--)
		{
			dp[i][left]+=dp[i-1][left];
			for(int j=1;pow(primes[i],j)<=left;j++)
			{
				dp[i][(long long)(left-pow(primes[i],j))]+=dp[i-1][left];
			}
		}
			
	for(int i=0;i<=n;i++)
	{
		ans+=dp[top][i];
	}
	printf("%lld\n",ans);
	return 0;
}

