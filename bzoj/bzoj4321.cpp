#include<iostream>
#include<cstdio>
using namespace std;
long long n,dp[1010][1010][2];
const long long MOD=7777777;
int main()
{
	scanf("%lld",&n);
	dp[1][0][0]=1;
	for(int i=1;i<n;i++)
	{
		for(int j=0;j<=n;j++)
		{
			dp[i+1][j][1]=(dp[i+1][j][1]+dp[i][j][1])%MOD;
			dp[i+1][j+1][1]=(dp[i+1][j+1][1]+dp[i][j][1]+2*dp[i][j][0])%MOD;
			if(j)dp[i+1][j-1][0]=(dp[i+1][j-1][0]+j*dp[i][j][0]+(j-1)*dp[i][j][1])%MOD;
			dp[i+1][j][0]=(dp[i+1][j][0]+max((i-j-1),0)*dp[i][j][0]+(i-j)*dp[i][j][1])%MOD;
		}
	}
	/*
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=n;j++)
		{
			cout<<dp[i][j][0]<<' ';
		}
		cout<<endl;
	}
	cout<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=n;j++)
		{
			cout<<dp[i][j][1]<<' ';
		}
		cout<<endl;
	}
	cout<<endl;
	*/
	printf("%lld\n",dp[n][0][0]);
	return 0;
}
