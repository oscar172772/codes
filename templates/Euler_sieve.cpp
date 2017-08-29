#include<iostream>
#include<cstdio>
using namespace std;
string ans[2]={"Yes","No"};
int pr[10040104],list[2333333],top;
int n,m;
inline void shai()
{
	pr[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!pr[i])list[++top]=i;
		for(int j=1;j<=top&&i*list[j]<=n;j++)
		{
			pr[i*list[j]]=1;
			//cout<<i<<' '<<list[j]<<' '<<i*list[j]<<endl;
			if(i%list[j]==0)break;
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	shai();
	while(m--)
	{
		scanf("%d",&n);
		printf("%s\n",ans[pr[n]].c_str());
	}
	return 0;
}
