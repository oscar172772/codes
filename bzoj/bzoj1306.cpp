#include<iostream>
#include<cstdio>
using namespace std;
#ifndef ONLINE_JUDGE
#define $(format,...) printf("%s("format") @ line %d\n",__FUNCTION__,##__VA_ARGS__,__LINE__);
#else
#define $(...) 
#endif
int match[10][10],score[10],curs[10],sum,ans;
int n;
bool check()
{
	int tmp;
	for(int i=1;i<=n;i++)
	{
		tmp=0;
		for(int j=1;j<=n;j++)
		{
			tmp+=match[i][j];
			//cout<<match[i][j]<<' ';
		}
		//cout<<endl;
		if(curs[i]!=score[i])return false;
	}
	return true;
}
void search(int i,int j,int pcnt)
{
	//$("%d,%d,%d",i,j,pcnt)
	if(i==n){if(check())ans++;return;}
	match[i][j]=3;match[j][i]=0;curs[i]+=3;
	if(curs[i]<=score[i])
	{
		//if(j==n)cout<<curs[i]<<' '<<score[i]<<endl;
		if(j==n)
		{
			if(curs[i]==score[i])
				search(i+1,i+2,pcnt);
		}
		else
			search(i,j+1,pcnt);
	}
	if(pcnt)
	{
		match[i][j]=1;match[j][i]=1;curs[i]-=2;curs[j]+=1;
		if(curs[i]<=score[i]&&curs[j]<=score[j])
		{
			if(j==n)
			{
				if(curs[i]==score[i])
					search(i+1,i+2,pcnt-1);
			}
			else
				search(i,j+1,pcnt-1);
		}
	}
	else{curs[i]-=2;curs[j]+=1;}
	match[i][j]=0;match[j][i]=3;curs[i]-=1;curs[j]+=2;
	if(curs[j]<=score[j])
	{
		//if(j==n)cout<<curs[i]<<' '<<score[i]<<endl;
		if(j==n)
		{
			if(curs[i]==score[i])
				search(i+1,i+2,pcnt);
		}
		else
			search(i,j+1,pcnt);
	}
	match[j][i]=0;
	curs[j]-=3;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&score[i]);
		sum+=score[i];
	}
	int pcnt=(n*(n-1)/2*3)-sum;
	search(1,2,pcnt);
	printf("%d\n",ans);
	return 0;
}
