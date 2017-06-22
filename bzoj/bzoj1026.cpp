#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
int a,b;
int dp[10][10];//digits,last
int sep[10];
int getcount(int hb,int digit)
{
	int res=0;
	if(hb==-1)
	{
		if(digit==1)return 1;
		res+=getcount(-1,digit-1);
		for(int i=1;i<=9;i++)
			res+=getcount(i,digit-1);
		return res;
	}
	memset(dp,0,sizeof(dp));
	dp[digit][hb]=1;
	for(int i=digit-1;i>=1;i--)
		for(int j=0;j<=9;j++)
			for(int k=0;k<=9;k++)
				if(abs(j-k)>=2)
					dp[i][j]+=dp[i+1][k];
	for(int i=0;i<=9;i++)
		res+=dp[1][i];
	//cout<<"getcount("<<hb<<","<<digit<<")="<<res<<endl;
	return res;
}
int getcount(int x)
{
	if(x<0)return x+2;
	else if(x==0)return 1;
	int tmp=x;
	int res=0,top=0;
	while(x)
	{
		sep[++top]=x%10;
		x/=10;
	}
	bool flag=true;
	for(int i=top;i>=1;i--)
	{
		for(int j=0;j<=sep[i]-(i!=1);j++)
		{
			if(i==top&&j==0)
				res+=getcount(-1,i);
			else if(i==top||abs(sep[i+1]-(j))>=2)
				res+=getcount(j,i);
		}
		if(i!=top&&abs(sep[i]-sep[i+1])<2)
		{
			//cout<<"getcount("<<tmp<<")="<<res<<endl;
			return res;
		}
	}
	return res;
}
int main()
{
	/*
	for(int i=1;i<=210;i++)
		cout<<i<<": "<<getcount(i)-1<<endl;
	//*/
	scanf("%d%d",&a,&b);
	printf("%d\n",getcount(b)-getcount(a-1));
	return 0;
}
