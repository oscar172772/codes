#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int sigma=26,MAXN=233333;
struct node
{
	int maxlen,fastlen;
	bool isend;
	node *next[sigma],*link,*fast;
}*root,pool[MAXN],*last;
int top,totlen;
char buf[MAXN],str[MAXN];
void add(int ch)
{
	node *p=last,*cur=&pool[++top];
	cur->maxlen=p->maxlen+1;
	while(p&&!p->next[ch])
	{
		p->next[ch]=cur;
		p=p->link;
	}
	if(!p)
		cur->link=root;
	else
	{
		node *q=p->next[ch];
		if(p->maxlen+1==q->maxlen)cur->link=q;
		else
		{
			node *sq=&pool[++top];
			sq->maxlen=p->maxlen+1;
			for(int i=0;i<sigma;i++)
				sq->next[i]=q->next[i];
			while(p&&p->next[ch]==q)
			{
				p->next[ch]=sq;
				p=p->link;
			}
			sq->link=q->link;
			q->link=sq;
			cur->link=sq;
		}
	}
	last=cur;
}
inline void update()
{
	node *p=last;
	while(p!=root)
	{
		p->isend=1;
		p=p->link;
	}
	for(int i=1;i<=top;i++)
	{
		node *t=&pool[i],*q=0;
		if(t->isend)continue;
		int c=0;
		for(int ch=0;ch<sigma;ch++)
		{
			if(t->next[ch])
				++c,q=t->next[ch];
		}
		if(c==1)
		{
			t->fast=q;
			t->fastlen=1;
		}
	}
}
typedef pair<node*,int> pni;
#define mp make_pair
pni find(node *u)
{
	if(!u->fast)return mp(u,0);
	pni _=find(u->fast);
	u->fast=_.first;
	u->fastlen+=_.second;
	return mp(u->fast,u->fastlen);
}
int lcp[MAXN],minn,cnt;
void dfs(node *u,int len=0)
{
	//cout<<"dfs "<<len<<endl;
	if(u->isend)
	{
		printf("%d ",totlen-len+1);
		//printf("%s\n",str);
		lcp[++cnt]=minn;
		minn=len;
	}
	if(u->fast)
	{
		find(u);
		dfs(u->fast,len+u->fastlen);
	}
	else
		for(int x=0;x<sigma;x++)
		{
			if(u->next[x])
			{
				//str[len]=x+'a';
				if(len<minn)minn=len;
				dfs(u->next[x],len+1);
			}
		}
	//str[len]=0;
}
int main()
{
	//freopen("data.in","r",stdin);
	//freopen("dump.txt","w",stdout);
	scanf("%s",buf);
	totlen=strlen(buf);
	last=root=&pool[++top];
	for(int i=0;i<totlen;++i)
	{
		add(buf[i]-'a');
	}
	update();
	dfs(root);
	printf("\n");
	for(int i=2;i<=totlen;i++)
		printf("%d ",lcp[i]);
	printf("\n");
	return 0;
}
