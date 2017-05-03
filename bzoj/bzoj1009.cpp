#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int fail[25];
int n,m,p;int siz,mod;
struct matrix
{
	int mat[210][210];
	matrix()
	{
		memset(mat,0,sizeof(mat));
	}
	matrix operator=(const matrix &m)
	{
		for(int i=0;i<siz;i++)
		{
			for(int j=0;j<siz;j++)
			{
				mat[i][j]=m.mat[i][j];
			}
		}
		return *this;
	}
	matrix operator*(const matrix &m)const
	{
		matrix tmp;
		for(int i=0;i<siz;i++)
		{
			for(int j=0;j<siz;j++)
			{
				for(int k=0;k<siz;k++)
				{
					tmp.mat[i][j]+=mat[i][k]*m.mat[k][j];
					tmp.mat[i][j]%=mod;
				}
			}
		}
		return tmp;
	}
	matrix operator *=(const matrix &m)
	{
		return *this=(*this)*m;
	}
}mult;
char buf[30];
inline void getfail()
{
	int j=0;
	for(int i=2;i<=m;i++)
	{
		while(j!=0&&buf[j+1]!=buf[i])j=fail[j];
		if(buf[j+1]==buf[i])fail[i]=++j;
		else fail[i]=j;
	}
}
inline int match(int pos,char num)
{
	while(pos!=0&&buf[pos+1]!=num)
	{
		pos=fail[pos];
	}
	if(buf[pos+1]==num)return pos+1;
	return pos;
}
inline matrix f_exp(const matrix &m,const int x)
{
	matrix tmp;
	for(int i=0;i<siz;i++)tmp.mat[i][i]=1;
	int bit=1<<30;
	while(bit)
	{
		tmp*=tmp;
		if(bit&x)tmp*=m;
		bit>>=1;
	}
	return tmp;
}
int main()
{
	scanf("%d%d%d",&n,&m,&p);
	mod=p;siz=m;
	scanf("%c",&buf[0]);
	scanf("%s",buf+1);
	getfail();
	/*for(int i=1;i<=m;i++)
	{
		cout<<fail[i]<<' ';
	}*/
	for(int i=0;i<m;i++)
	{
		for(char ch='0';ch<='9';ch++)
		{
			int tmp=match(i,ch);
			if(tmp!=m)
			{
				mult.mat[i][tmp]++;
			}
		}
	}
	/*
	for(int i=0;i<siz;i++)
	{
		for(int j=0;j<siz;j++)
		{
			cout<<mult.mat[i][j]<<' ';
		}
		cout<<endl;
	}*/
	matrix result=f_exp(mult,n);
	/*
	for(int i=0;i<siz;i++)
	{
		for(int j=0;j<siz;j++)
		{
			cout<<result.mat[i][j]<<' ';
		}
		cout<<endl;
	}*/
	int ans=0;
	for(int i=0;i<siz;i++)
	{
		ans=(ans+result.mat[0][i])%p;
	}
	printf("%d\n",ans);
	return 0;
}
