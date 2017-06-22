#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
double search(double x,double y,int n)
{
	if(n==1)return x/y>1?x/y:y/x;
	double ans=2333333.0;
	for(int i=1;i<=n/2;i++)
	{
		ans=min(ans,max(search(x/n*i,y,i),search(x/n*(n-i),y,n-i)));
		ans=min(ans,max(search(x,y/n*i,i),search(x,y/n*(n-i),n-i)));
	}
	return ans;
}
int main()
{
	int n;
	double x,y;
	scanf("%lf%lf%d",&x,&y,&n);
	printf("%.6lf\n",search(x,y,n));
	return 0;
}

