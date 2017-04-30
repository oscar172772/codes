#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN=150000;
struct aa
{
	int a,b;
}sz[MAXN+100];
int c[MAXN+100],n;
int ans[MAXN+100];
int lowbit(int x)
{
	return x&(x^(x-1));
}
void change(int id,int x)
{
	if(!id)return;
	for(id;id<=MAXN;id+=lowbit(id))
	{
		c[id]+=x;
	}
}
int query(int id)
{
	int sum=0;
	for(id;id;id-=lowbit(id))
	{
		sum+=c[id];
	}
	return sum;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&sz[i].a,&sz[i].b);
		sz[i].a++;
		sz[i].b++;
	}
	/*for(int i=1;i<=k;i++)
	{
		cout<<sz[i].a<<' '<<sz[i].b<<endl;
	}
	cout<<endl;*/
	for(int i=1;i<=n;i++)
	{
		ans[query(sz[i].a)]++;
		//cout<<query(sz[i].a)<<endl;
		change(sz[i].a,1);
	}
	//cout<<endl;
	for(int i=0;i<=n-1;i++)
	{
		printf("%d\n",ans[i]);
    }
    //system("pause");
	return 0;
}
