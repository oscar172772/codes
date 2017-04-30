#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN=100000;
struct aa
{
	int a,b,id,ans;
}sz[MAXN+100];
inline bool cmp1(const aa t1,const aa t2)
{
	if(t1.b>t2.b)return true;
	if(t1.b<t2.b)return false;
	if(t1.a<t2.a)return true;
	if(t1.a>t2.a)return false;
	if(t1.id<t2.id)return true;
	return false;
}
inline bool cmp2(const aa t1,const aa t2)
{
	return t1.id<t2.id;
}
int c[MAXN+100],n;
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
	scanf("%d",&n);
	while(n)
	{
		memset(sz,0,sizeof(sz));
		memset(c,0,sizeof(c));
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&sz[i].a,&sz[i].b);
			sz[i].id=i;
			sz[i].a++;
			sz[i].b++;
		}
		sort(sz+1,sz+n+1,cmp1);
		/*for(int i=1;i<=n;i++)
		{
			cout<<sz[i].id<<' '<<sz[i].a<<' '<<sz[i].b<<' '<<sz[i].ans<<endl;
		}*/
		for(int i=1;i<=n;i++)
		{
			if(sz[i].a==sz[i-1].a&&sz[i].b==sz[i-1].b)
			{
				sz[i].ans=sz[i-1].ans;
				change(sz[i-1].a,1);
			}
			else
			{
				sz[i].ans=query(sz[i].a);
				change(sz[i].a,1);
			}
		}
		sort(sz+1,sz+n+1,cmp2);
		for(int i=1;i<=n;i++)
			printf("%d ",sz[i].ans);
		printf("\n");
		/*for(int i=1;i<=n;i++)
		{
			cout<<sz[i].id<<' '<<sz[i].a<<' '<<sz[i].b<<' '<<sz[i].ans<<endl;
		}*/
		scanf("%d",&n);
	}
	return 0;
}

