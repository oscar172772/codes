#include<iostream>
#include<cstdio>
using namespace std;
const int MOD=10007;
int a[50050];
int n,m;
short dp[50050][1010];
int ll[1010],sum[1010],ans;
int s[50050];
int main()
{
	scanf("%d%d",&n,&m);
	int minn=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		minn=max(minn,a[i]);
		s[i]=s[i-1]+a[i];
	}
	int l=minn,r=s[n];
	while(l<r)
	{
		int mid=(l+r)/2,curlen=0,curcut=0;
		for(int i=1;i<=n;i++)
		{
			if(curlen+a[i]>mid)
			{
				curlen=a[i];
				curcut++;
			}
			else
			{
				curlen+=a[i];
			}
		}
		if(curcut>m)l=mid+1;
		else r=mid;
	}
	printf("%d ",l);
	//*
	sum[0]=dp[0][0]=1;
	//for(int i=0;i<=m;i++)ll[i]=0;
	for(int i=1;i<=n;i++)
	{
		//cout<<"i="<<i<<endl;
		for(int j=m;j>=0;j--)
		{
			//cout<<"sum["<<j<<"]="<<sum[j]<<endl;
			while(s[i]-s[ll[j]]>l)
			{
				sum[j]=(sum[j]-dp[ll[j]][j]+MOD)%MOD;
				ll[j]++;
				//cout<<i<<' '<<sum[i]<<' '<<s[i]<<' '<<ll[j]<<' '<<sum[ll[j]]<<' '<<s[ll[j]]<<endl;
			}
			dp[i][j+1]=sum[j];
			sum[j+1]=(sum[j+1]+dp[i][j+1])%MOD;
		}
	}
	for(int j=0;j<=m+1;j++)
		ans=(ans+dp[n][j])%MOD;
	printf("%d\n",ans);
	/*
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=m+1;j++)
			cout<<dp[i][j]<<' ';
		cout<<endl;
	}
	*/
	/*/
	dp[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			for(int k=0;k<i;k++)
			{
				if(s[i]-s[k]<=l)
				{
					dp[i][j+1]=(dp[i][j+1]+dp[k][j])%MOD;
				}
			}
		}
	}
	for(int j=0;j<=m+1;j++)
		ans=(ans+dp[n][j])%MOD;
	printf("%d\n",ans);
	
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=m+1;j++)
			cout<<dp[i][j]<<' ';
		cout<<endl;
	}
	//*/
	return 0;
}
