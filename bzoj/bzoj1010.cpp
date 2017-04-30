#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll Inf=0x3f3f3f3f3f3f3f3fll;
struct point
{
	ll x,y;
	inline point operator=(const point &p)
	{
		x=p.x;y=p.y;
		return *this;
	}
}pt[50050];
int low,hi;
ll n,l,c,s[50050],q[50050],dp[50050];
double nextslope;
inline ll sqr(const ll x){return x*x;}
inline double slope(const int a,const int b)
{
	//if(pt[a].x<pt[b].x)swap(a,b);
	return (pt[a].y-pt[b].y)/(pt[a].x-pt[b].x);
}
int main()
{
	scanf("%lld%lld",&n,&l);l++;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&c);
		s[i]=s[i-1]+c+1;
	}
	low=1,hi=0;
	pt[0].y=sqr(l);
	q[++hi]=0;
	for(int i=1;i<=n;i++)
	{
		while(hi>low&&slope(q[low],q[low+1])<=s[i])low++;
		int k=q[low];
		
		//cout<<"k="<<k<<", next_slope="<<nextslope<<endl;
		dp[i]=dp[k]+sqr(s[i]-s[k]-l);
		pt[i].x=2*s[i];
		pt[i].y=dp[i]+sqr(s[i]+l);
		while(hi>low&&slope(q[hi],i)<slope(q[hi-1],q[hi]))hi--;
		q[++hi]=i;
	}
	//for(int i=0;i<=n;i++)cout<<dp[i]<<' ';cout<<endl;
	printf("%lld\n",dp[n]);
	//system("pause");
	return 0;
}
