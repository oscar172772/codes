#include<cstdlib>
#include<cstdio>
#include<algorithm>
using namespace std;
struct o
{
	long long a;
	int b;
	inline const bool operator<(o x)const{return b==x.b?a>x.a:b>x.b;}
}p[100100];
long long c[99];
int ans;
int main()
{
	int N;
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%lld%d",&p[i].a,&p[i].b);
	sort(p+1,p+N+1);
	for(int i=1;i<=N;i++)
	{
		for(int t=64;t>0;t--)
		{
			if(p[i].a>>t&1)
			{
				if(!c[t])
				{
					c[t]=p[i].a;
					break;
				}
				else
					p[i].a^=c[t];
			}
		}
		if(p[i].a)ans+=p[i].b;
	}
	printf("%d",ans);
	return 0;
}
