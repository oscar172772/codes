#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
#define int unsigned
const int Inf=0x7f7f7f7f;
int maxd=0,curmax=-1;
int table1[5000];
int primes[13]={0,2,3,5,7,11,13,17,19,23,29,31};
int primecnt[13];
int d()
{
	//cout<<"DDD";
	int ans=1;
	for(int i=1;i<=13;i++)
	{
		ans*=primecnt[i]+1;
	}
	//cout<<ans;
	return ans;
}
int cnt;
void search(int dep)
{
	//cout<<dep<<' ';
	/*cnt++;
	if(cnt>10000)
	{
		cnt=0;
	}*///I don't know why this fragment will cause RE
	if(dep==12)
	{
		long long ans=1;
		for(int i=1;i<=11;i++)
		{
			for(int j=1;j<=primecnt[i];j++)
			{
				ans*=primes[i];
				if(ans>Inf)return;
			}
		}
		int dd=d();
		if(dd>maxd)maxd=dd;
		//cout<<",num="<<ans<<endl;
		table1[dd]=min(table1[dd],(int)ans);
	}
	else if(dep<=5)
	{
		//cout<<"WWW\n";
		for(int i=0;i<=primecnt[dep-1];i++)
		{
			primecnt[dep]=i;
			search(dep+1);
		}
	}
	else
	{
		for(int i=0;i<=min(2u,primecnt[dep-1]);i++)
		{
			primecnt[dep]=i;
			search(dep+1);
		}
	}
}
#undef int
int main()
{
	memset(table1,0x7f,sizeof(table1));
	primecnt[0]=18;
	search(1);
	system("pause");
	for(unsigned i=maxd;i>=1;i--)
	{
		if(table1[i]!=Inf&&table1[i]<curmax)
		{
			curmax=table1[i];
		}
		else table1[i]=Inf;
	}
	for(unsigned i=1;i<=maxd;i++)
	{
		if(table1[i]!=Inf/*&&table1[i]>curmax*/)
		{
			cout<<table1[i]<<',';
			cnt++;
			curmax=table1[i];
		}
	}
	cout<<cnt<<endl;
	return 0;
}
