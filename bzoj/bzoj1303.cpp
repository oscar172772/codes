#include<cstdio>
long long ans;
int n,k,a,cnt,cntbp[100100],cntap[100100],cntbn[100100],cntan[100100];//b4,after
bool flag;
int main()
{
	scanf("%d%d",&n,&k);
	cntbp[0]++;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		if(a>k)
			cnt++;
		else if(a<k)
			cnt--;
		else flag=true;
		if(!flag)
			if(cnt>=0)cntbp[cnt]++;
			else cntbn[-cnt]++;
		else
			if(cnt>=0)cntap[cnt]++;
			else cntan[-cnt]++;
	}
	for(int i=0;i<=n;i++)
	{
		ans+=cntbn[i]*cntan[i]+cntbp[i]*cntap[i];
	}
	printf("%lld\n",ans);
	return 0;
}
