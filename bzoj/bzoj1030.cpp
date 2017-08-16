#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int MAXN=23333;
struct node
{
	int id,isend;
	node *next[26],*fail;
}*root,pool[MAXN];
char buf[233];
int len,top;
void add(node *cur,int pos)
{
	if(pos==len)cur->isend++;
	else
	{
		if(!cur->next[buf[pos]-'A'])cur->next[buf[pos]-'A']=&pool[++top];
		add(cur->next[buf[pos]-'A'],pos+1);
	}
}
queue<node*> q;
void build()
{
	q.push(root);
	root->fail=root;
	while(!q.empty())
	{
		node *tmp=q.front();
		q.pop();
		for(int i=0; i<26; i++)
		{
			if(tmp->next[i])
			{
				node *tmp2=tmp->fail;
				while(tmp2!=root&&!tmp2->next[i])tmp2=tmp2->fail;
				if(tmp!=root&&tmp2->next[i])tmp->next[i]->fail=tmp2->next[i];
				else tmp->next[i]->fail=tmp2;
				tmp->next[i]->isend+=tmp->next[i]->fail->isend;
				q.push(tmp->next[i]);
			}
		}
	}
}
node* match(node *cur,char ch)
{
	while(cur!=root&&!cur->next[ch-'A'])cur=cur->fail;
	if(cur->next[ch-'A'])return cur->next[ch-'A'];
	else return cur;
}
int n,m,ans;
int dp[233][MAXN][2];
int main()
{
	for(int i=1; i<MAXN; i++)pool[i].id=i;
	scanf("%d%d",&n,&m);
	root=&pool[++top];
	for(int i=1; i<=n; i++)
	{
		scanf("%s",buf);
		len=strlen(buf);
		add(root,0);
	}
	build();
	/*
	while(1)
	{
		int num;
		char tmp;
		scanf("%d %c",&num,&tmp);
		printf("%d\n",match(&pool[num],tmp)->id);
	}
	*/
	dp[0][1][0]=1;
	for(int i=0; i<m; i++)
	{
		for(int j=1; j<=top; j++)
		{
			for(char ch='A'; ch<='Z'; ch++)
			{
				node *tmp=match(&pool[j],ch);
				if(tmp->isend)
				{
					dp[i+1][tmp->id][1]=(dp[i+1][tmp->id][1]+dp[i][j][0]+dp[i][j][1])%10007;
				}
				else
				{
					dp[i+1][tmp->id][0]=(dp[i+1][tmp->id][0]+dp[i][j][0])%10007;
					dp[i+1][tmp->id][1]=(dp[i+1][tmp->id][1]+dp[i][j][1])%10007;
				}
			}
		}
	}
	for(int i=1; i<=top; i++)ans=(ans+dp[m][i][1])%10007;
	printf("%d\n",ans);
	return 0;
}
