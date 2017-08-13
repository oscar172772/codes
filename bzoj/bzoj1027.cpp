#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int MAXN=501;
const double eps=1e-10;
struct P
{
	double x,y;
}a[MAXN],b[MAXN];
int n,m;
int dis[MAXN][MAXN];
inline double cross(const P &a,const P &b,const P &c,const P &d)
{
	//cout<<"cross ";
	double x1=b.x-a.x,y1=b.y-a.y,x2=d.x-c.x,y2=d.y-c.y;
	//cout<<x1<<' '<<x2<<' '<<y1<<' '<<y2<<' '<<x1*y2-x2*y1<<endl;
	return x1*y2-x2*y1;
}
inline double sqr(double x){return x*x;}
inline double len(const P &a,const P &b)
{
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}
int main()
{
	scanf("%d%d",&n,&m);
	if(m==0)return printf("0\n"),0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			dis[i][j]=2333;
	double x,y,z;
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf%lf",&x,&y,&z);
		a[i].x=x,a[i].y=y;
	}
	int allsame=1;
	for(int i=1;i<=m;i++)
	{
		scanf("%lf%lf%lf",&x,&y,&z);
		b[i].x=x,b[i].y=y;
		if(allsame&&i>1&&(b[i].x!=b[i-1].x||b[i].y!=b[i-1].y))allsame=0;
	}
	if(allsame)
	{
		for(int i=1;i<=n;i++)
			if(a[i].x==b[1].x&&a[i].y==b[1].y)
				return printf("1\n"),0;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i==j)continue;
			//cout<<i<<' '<<j<<' ';
			int havep=0,haven=0;
			double r;
			for(int k=1;k<=m;k++)
			{
				r=cross(a[i],a[j],a[i],b[k]);
				havep+=(r>eps),haven+=(r<-eps);
			}
			if(havep&&haven);
			else if(havep)dis[i][j]=1;
			else if(haven)dis[j][i]=1;
			else
			{
				for(int k=1;k<=m;k++)
				{
					double tmp=len(a[i],b[k])+len(b[k],a[j])-len(a[i],a[j]);
					//cout<<len(a[i],b[k])<<' '<<len(b[k],a[j])<<' '<<len(a[i],a[j])<<' '<<tmp<<endl;
					if(tmp<eps&&tmp>-eps)
						return printf("2\n"),0;
				}
				//dis[i][j]=dis[j][i]=1;
			}
			//cout<<dis[i][j]<<' '<<dis[j][i]<<endl;
		}
	}
	int ans=2333,tmp;
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				tmp=dis[i][k]+dis[k][j];
				int &tmp2=dis[i][j];
				if(tmp<tmp2)tmp2=tmp;
			}
	}
	for(int i=1;i<=n;i++)
	{
		tmp=dis[i][i];
		if(tmp<ans)ans=tmp;
	}
	if(ans==2333)printf("-1\n");
	else printf("%d",ans);
	return 0;
}
