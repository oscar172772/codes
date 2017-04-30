#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
struct node
{
	int id,end;
	node *next[26],*fail;
}*root,pool[30001];
int top;
string bas[55],ban[55];
int n,m,l,len[111],N;long long ans;
int dp[111][111];//[len][id]
/*
void debug(string name){cout<<name<<"()\n";}
void debug(string name,string str){cout<<name<<'('<<str<<")\n";}
void debug(string name,int x){cout<<name<<'('<<x<<")\n";}
void debug(string name,string str,int x){cout<<name<<'('<<str<<','<<x<<")\n";}
//*/
const long long mod=1000000007ll;
struct matrix
{
	int siz;
	int mat[233][233];
#define int long long
	matrix(int x=0)
	{
		siz=N;
		for(int i=1;i<=siz;i++)
			for(int j=1;j<=siz;j++)
			{
				mat[i][j]=x*(int)(i==j);
			}
	}
	matrix operator=(const matrix& m)
	{
		siz=N;
		for(int i=1;i<=siz;i++)
		{
			for(int j=1;j<=siz;j++)
			{
				mat[i][j]=m.mat[i][j];
			}
		}
		return *this;
	}
	matrix operator=(const int x)
	{
		siz=N;
		for(int i=1;i<=siz;i++)
			for(int j=1;j<=siz;j++)
			{
				mat[i][j]=x*(int)(i==j);
			}
		return *this;
	}
	matrix operator*=(const matrix &m)
	{
		matrix tmp;
		for(int i=1;i<=siz;i++)
		{
			for(int j=1;j<=siz;j++)
			{
				long long o=0;
				for(int k=1;k<=siz;k++)
				{
					o+=((long long)mat[i][k]*m.mat[k][j])%mod;
				}
				o%=mod;
				tmp.mat[i][j]=o;
			}
		}
		return *this=tmp;
	}
};
inline matrix fexp(matrix &x,int y)
{
	int bit=1<<30;
	matrix cur=1;
	while(bit)
	{
		cur*=cur;
		if(y&bit)cur*=x;
		bit>>=1;
	}
	return cur;
}
#undef int
void addword(string str)
{
	//debug("addword",str);
	int len=str.length();
	node *tmp=root;
	for(int i=0;i<len;i++)
	{
		int cur=str[i]-'a';
		if(!tmp->next[cur])
		{
			tmp->next[cur]=&pool[++top];
			tmp->next[cur]->id=top;
		}
		tmp=tmp->next[cur];
	}
	tmp->end=1;
}
queue<node*> q;
void build()
{
	while(!q.empty())q.pop();
	q.push(root);
	while(!q.empty())
	{
		node *cur=q.front();q.pop();
		//debug("build",cur->id);
		for(int i=0;i<26;i++)
		{
			node *nex=cur->next[i],*tmp=cur->fail;
			//cout<<(char)(i+'a')<<endl;
			if(!nex)continue;
			while(tmp!=root&&!(tmp->next[i]))tmp=tmp->fail;
			if(cur==root||!(tmp->next[i]))
				nex->fail=tmp;
			else
				nex->fail=tmp->next[i];
			//cout<<nex->id<<"->fail="<<nex->fail->id<<endl;
			q.push(nex);
		}
	}
}
int match(string str,int len,int start)
{
	//debug("match",str,start);
	node *cur=&pool[start],*tmp;
	for(int i=0;i<len;i++)
	{
		int e=str[i]-'a';
		while(cur!=root&&!(cur->next[e]))cur=cur->fail;
		if(cur->next[e])
			cur=cur->next[e];
		tmp=cur;
		while(tmp!=root)
		{
			//debug("test_fail",tmp->id);
			if(tmp->end)return 0;
			tmp=tmp->fail;
		}
	}
	return cur->id;
}
int main()
{
	char buf[110];
	root=&pool[++top];root->id=1;root->fail=root;
//#ifndef DDDDBUG
//	freopen("sorcery.in","r",stdin);
//	freopen("sorcery.out","w",stdout);
//#endif  //DDDDBUG
	scanf("%d%d%d",&n,&m,&l);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",buf);
		bas[i]=buf;
		len[i]=bas[i].length();
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%s",buf);
		ban[i]=buf;
		addword(ban[i]);
	}
	build();
	//*
	if(l<=100)
	{
		dp[0][1]=1;
		for(int i=0;i<l;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(i+len[j]<=l)
					for(int id=1;id<=top;id++)
					{
						int tmp=match(bas[j],len[j],id);
						if(tmp)
							dp[i+len[j]][tmp]=(dp[i][id]+dp[i+len[j]][tmp])%mod;
					}
			}
		}
		for(int id=1;id<=top;id++)
		{
			ans=(ans+dp[l][id])%mod;
		}
		printf("%lld\n",ans);
	}
	else
	//*/
	{
		int notwo=1;
		N=2*top;
		matrix mult=0;
		for(int i=1;i<=top;i++)
		{
			mult.mat[i+top][i]=1;
		}
		for(int pos=1;pos<=top;pos++)
		{
			for(int i=1;i<=n;i++)
			{
				if(len[i]==1)
				{
					int x=pos,y=match(bas[i],1,pos);
					if(y)
					{
						mult.mat[x][y]++;
						//mult.mat[x+top][y+top]++;
					}
				}
				else
				{
					int x=pos,y=match(bas[i],2,pos);
					if(y)
						mult.mat[x][y+top]++;
					notwo=0;
				}
			}
		}
		if(notwo)N>>=1;
		matrix tmp=fexp(mult,l);
		matrix orig=0;
		orig.mat[1][1]=1;
		orig*=tmp;
		for(int pos=1;pos<=top;pos++)
		{
			ans+=orig.mat[1][pos];
			ans%=mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
