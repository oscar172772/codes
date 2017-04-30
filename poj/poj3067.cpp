#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN=1000000;
struct aa
{
	int a,b;
}sz[MAXN+100];
inline bool cmp(const aa t1,const aa t2)
{
	if(t1.b<t2.b)return true;
	if(t1.b>t2.b)return false;
	if(t1.a<t2.a)return true;
	return false;
}
int cass,c[MAXN+100],n,m,k;
unsigned long long ans;
int lowbit(int x)
{
	return x&(x^(x-1));
}
void change(int id,int x)
{
	if(!id)return;
	for(id;id<=n;id+=lowbit(id))
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
	scanf("%d",&cass);
	for(int kase=1;kase<=cass;kase++)
	{
		memset(sz,0,sizeof(sz));
		memset(c,0,sizeof(c));
		ans=0;
		scanf("%d%d%d",&n,&m,&k);
		for(int i=1;i<=k;i++)
		{
			scanf("%d%d",&sz[i].a,&sz[i].b);
		}
		sort(sz+1,sz+k+1,cmp);
		/*for(int i=1;i<=k;i++)
		{
			cout<<sz[i].a<<' '<<sz[i].b<<endl;
		}
		cout<<endl;*/
		for(int i=1;i<=k;i++)
		{
			ans+=i-(query(sz[i].a))-1;
			change(sz[i].a,1);
		}
		printf("Test case %d: %lld\n",kase,ans);
	}
	return 0;
}
