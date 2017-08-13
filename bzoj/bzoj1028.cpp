#include<iostream>
#include<cstdio>
using namespace std;
int cnt[1010],tmp[1010],n,m;
inline bool check()
{
	for(int i=1;i<=m;i++)
	{
		tmp[i]=cnt[i];
	}
	for(int i=1;i<=m;i++)
	{
		tmp[i]%=3;
		int minn=tmp[i];
		if(minn>tmp[i+1])minn=tmp[i+1];
		if(minn>tmp[i+2])minn=tmp[i+2];
		tmp[i]-=minn,tmp[i+1]-=minn,tmp[i+2]-=minn;
		if(tmp[i])return false;
	}
	return true;
}
int main()
{
	scanf("%d%d",&m,&n);
	int t,first=0;
	for(int i=1;i<=3*n+1;i++)
	{
		scanf("%d",&t);
		cnt[t]++;
	}
	for(int i=1;i<=m;i++)
	{
		cnt[i]++;
		for(int j=1;j<=m;j++)
		{
			if(cnt[j]>=2)
			{
				cnt[j]-=2;
				if(check())
				{
					if(!first)printf("%d",i);
					else printf(" %d",i);
					first=1;
					cnt[j]+=2;
					break;
				}
				cnt[j]+=2;
			}
		}
		cnt[i]--;
	}
	if(!first)printf("NO");
	printf("\n");
	return 0;
}
