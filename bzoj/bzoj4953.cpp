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
int d,K,a,b;
long long dp[279][279],s[279];
long long interval[279][279],last[279],minn=0x3f3f3f3f3f3f3f3fll;
int main()
{
	memset(dp,0x3f,sizeof(dp));
	scanf("%d%d",&d,&K);
	for(int i=1;i<=d;i++)
	{
		scanf("%d%d",&a,&b);
		s[a]=b;
	}
	for(int i=0;i<=255;i++)//(i,j]
	{
		for(int j=i+1;j<=255;j++)
		{
			for(int k=i+1;k<j;k++)
			{
				if(k-i<j-k)interval[i][j]+=s[k]*(k-i)*(k-i);
				else interval[i][j]+=s[k]*(j-k)*(j-k);
			}
		}
	}
	for(int i=0;i<=255;i++)
	{
		dp[i][1]=0;
		for(int j=0;j<i;j++)
		{
			dp[i][1]+=s[j]*(i-j)*(i-j);
		}
		for(int j=i+1;j<=255;j++)
		{
			last[i]+=s[j]*(j-i)*(j-i);
		}
	}
	for(int i=0;i<=255;i++)
	{
		for(int j=0;j<i;j++)
		{
			for(int k=2;k<=K;k++)
			{
				dp[i][k]=min(dp[i][k],dp[j][k-1]+interval[j][i]);
			}
		}
	}
	for(int i=0;i<=255;i++)minn=min(minn,dp[i][K]+last[i]);
	/*
	for(int i=0;i<=255;i++)
	{
		for(int j=1;j<=K;j++)
		{
			cout<<dp[i][j]<<' ';
		}
		cout<<endl;
	}
	for(int i=0;i<=255;i++)cout<<last[i]<<endl;*/
	printf("%lld",minn);
	return 0;
}
