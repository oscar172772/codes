#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
int read()
{
	int tmp=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c<='9'&&c>='0')
	{
		tmp=tmp*10+c-'0';
		c=getchar();
	}
	return tmp;
}
int dis[31][31];
int n,m;
char buf1[233],buf2[233];
int main()
{
	scanf("%d%d",&m,&n);
	char a,b;
	for(int i=1;i<=m;i++)
	{
		scanf(" %c %c",&a,&b);
		dis[a-'a'][b-'a']=1;
	}
	for(int i=0;i<26;i++)dis[i][i]=1;
	for(int k=0;k<26;k++)
		for(int i=0;i<26;i++)
			for(int j=0;j<26;j++)
				if(dis[i][k]&&dis[k][j])
					dis[i][j]=1;
	for(int i=1;i<=n;i++)
	{
		scanf(" %s %s",buf1,buf2);
		if(strlen(buf1)!=strlen(buf2))
		{
			printf("no\n");
		}
		else
		{
			int len=strlen(buf1),ok=1;
			for(int t=0;t<len;t++)
			{
				if(dis[buf1[t]-'a'][buf2[t]-'a']==0)ok=0;
			}
			if(ok)printf("yes\n");
			else printf("no\n");
		}
	}
	return 0;
}
