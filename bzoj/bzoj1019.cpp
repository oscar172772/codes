#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;
char buf[10];
int a[10];
int n,last;
long long ans;
stack<int> cur[3];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=6;i++)
	{
		scanf(" %s",buf);
		if(buf[0]=='A')
		{
			if(buf[1]=='B')a[i]=1;
			else a[i]=2;
		}
		else if(buf[0]=='B')
		{
			if(buf[1]=='A')a[i]=3;
			else a[i]=4;
		}
		else
		{
			if(buf[1]=='A')a[i]=5;
			else a[i]=6;
		}
	}
	for(int i=3;i>=1;i--)cur[0].push(i);
	while((!cur[0].empty())||((!cur[1].empty())&&(!cur[2].empty())))
	{
		int flag=0;
		for(int i=1;i<=6;i++)
		{
			switch(a[i])
			{
				case 1:
					if((!cur[0].empty())&&cur[0].top()!=last&&(cur[1].empty()||cur[0].top()<cur[1].top()))
					{
						cur[1].push(cur[0].top());
						last=cur[0].top();
						cur[0].pop();
						flag=1;
					}
					break;
				case 2:
					if((!cur[0].empty())&&cur[0].top()!=last&&(cur[2].empty()||cur[0].top()<cur[2].top()))
					{
						cur[2].push(cur[0].top());
						last=cur[0].top();
						cur[0].pop();
						flag=1;
					}
					break;
				case 3:
					if((!cur[1].empty())&&cur[1].top()!=last&&(cur[0].empty()||cur[1].top()<cur[0].top()))
					{
						cur[0].push(cur[1].top());
						last=cur[1].top();
						cur[1].pop();
						flag=1;
					}
					break;
				case 4:
					if((!cur[1].empty())&&cur[1].top()!=last&&(cur[2].empty()||cur[1].top()<cur[2].top()))
					{
						cur[2].push(cur[1].top());
						last=cur[1].top();
						cur[1].pop();
						flag=1;
					}
					break;
				case 5:
					if((!cur[2].empty())&&cur[2].top()!=last&&(cur[0].empty()||cur[2].top()<cur[0].top()))
					{
						cur[0].push(cur[2].top());
						last=cur[2].top();
						cur[2].pop();
						flag=1;
					}
					break;
				case 6:
					if((!cur[2].empty())&&cur[2].top()!=last&&(cur[1].empty()||cur[2].top()<cur[1].top()))
					{
						cur[1].push(cur[2].top());
						last=cur[2].top();
						cur[2].pop();
						flag=1;
					}
					break;
			}
			if(flag)break;
		}
		ans++;
		//cout<<cur[0].size()<<' '<<cur[1].size()<<' '<<cur[2].size()<<endl;
	}
	//cout<<ans<<endl;
	int k,b,m;
	if(ans==7)k=2,b=-1,m=2;
	else if(ans==17)k=3,b=-1,m=2;
	else if(ans==9)k=3,b=0,m=1;
	else throw;
	ans=1;
	for(int i=1;i<n;i++)ans*=k;
	printf("%lld\n",ans*m+b);
	return 0;
}
