#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=233333;
int top;
#define int unsigned long long
char ch;int num;
inline int readnum()
{
	ch=getchar();
	num=0;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')
	{
		num=num*10+ch-'0';
		ch=getchar();
	}
	return num;
}
struct node
{
	int siz,csiz,maxx[4][4],a,b,c;
	node *lson,*rson,*pa;
}*root,*rf,pool[MAXN];
inline int siz(node *tmp){return tmp?tmp->siz:0;}
inline int maxx(node *tmp,int i,int j){return tmp?tmp->maxx[i][j]:0;}

void debug(string str,int x){cout<<str<<'('<<x<<")\n";}
void debug(string str,node* x){if(!x)return;cout<<str<<'('<<siz(x->lson)<<','<<x->csiz<<','<<x->siz<<',';
for(int i=0;i<4;i++)for(int j=i;j<4;j++)
cout<<x->maxx[i][j]<<',';cout<<")\n";}

void pntree(node *x)
{
	if(x->lson){pntree(x->lson);if(x->lson->pa!=x)cout<<"warning\n";}
	debug("node",x);
	if(x->rson){pntree(x->rson);if(x->rson->pa!=x)cout<<"warning\n";}
}

inline void update(node *cur)
{
	int a[4]={cur->a*cur->csiz,cur->b*cur->csiz,cur->c*cur->csiz,cur->a*cur->csiz};
	memset(cur->maxx,0,sizeof(cur->maxx));
	cur->siz=cur->csiz;
	if(cur->lson)
	{
		cur->siz+=cur->lson->siz;
	}
	if(cur->rson)
	{
		cur->siz+=cur->rson->siz;
	}
	for(int i=0;i<4;i++)
	{
		for(int j=i;j<4;j++)
		{
			for(int k=i;k<=j;k++)
			{
				cur->maxx[i][j]=max(cur->maxx[i][j],maxx(cur->lson,i,k)+a[k]+maxx(cur->rson,k,j));
			}
		}
	}
	//debug("update",cur);
}
inline void rot(node *cur)
{
	//debug("rotate",cur);
	if(cur==root)return;
	node *p=cur->pa,*gp=p->pa;
	if(p->rson==cur)
	{
		p->rson=cur->lson;
		if(cur->lson)cur->lson->pa=p;
		cur->lson=p;
	}
	else
	{
		p->lson=cur->rson;
		if(cur->rson)cur->rson->pa=p;
		cur->rson=p;
	}
	p->pa=cur;
	cur->pa=gp;
	if(gp->lson==p)gp->lson=cur;
	else gp->rson=cur;
	if(root==p)root=cur;
	update(p);
	update(cur);
}
inline void spaly(node *cur,node *t)
{
	while(cur->pa!=t)
	{
		//debug("spaly",cur);
		if(cur->pa->pa==t)rot(cur);
		else if((cur->pa->lson==cur)^(cur->pa->pa->lson==cur->pa))
		{
			rot(cur);rot(cur);
		}
		else
		{
			rot(cur->pa);rot(cur);
		}
	}
}
inline node* Find(int pos)
{
	node *cur=root;
	while(1)
	{
		//debug("find(node)",cur);
		//debug("find(pos)",pos);
		if(pos<=siz(cur->lson))cur=cur->lson;
		else if(pos>siz(cur->lson)+cur->csiz)
		{
			pos-=siz(cur->lson)+cur->csiz;
			cur=cur->rson;
		}
		else return cur;
		if(!cur)return 0;
	}
}
inline void split(int pos,int a,int b,int c,int len)//root, *AFTER* pos
{
	node *tmp=&pool[top++],*tmpl=root,*tmpr=&pool[top++];
	tmp->lson=tmpl;tmp->rson=tmpr;
	tmpr->rson=tmpl->rson;
	if(tmpr->rson)tmpr->rson->pa=tmpr;
	tmpl->rson=0;
	tmpl->pa=tmp;tmpr->pa=tmp;
	root=tmp;
	tmp->pa=rf;
	rf->lson=tmp;
	tmpr->a=tmpl->a;tmpr->b=tmpl->b;tmpr->c=tmpl->c;
	tmpr->csiz=tmpl->csiz-pos;
	tmpl->csiz=pos;
	tmp->csiz=len;
	tmp->a=a;tmp->b=b;tmp->c=c;
	update(tmpl);
	update(tmpr);
	update(tmp);
}
inline void ins(int pos,int a,int b,int c,int len)
{
	//debug("ins",pos);
	if(!root)
	{
		rf=&pool[top++];root=&pool[top++];
		root->pa=rf;rf->lson=root;
		root->a=a;root->b=b;root->c=c;root->csiz=len;
		update(root);
		return;
	}
	if(!pos)
	{
		node *n=Find(pos+1);
		spaly(n,rf);
		split(pos,a,b,c,len);
		return;
	}
	node *n=Find(pos);
	//debug("found",n);
	spaly(n,rf);
	pos-=siz(n->lson);
	split(pos,a,b,c,len);
}
inline int query()
{
	/*int ret=0;
	for(int i=0;i<4;i++)
	{
		ret=max(ret,root->maxx[i]);
	}
	return ret;*/
	return root->maxx[0][3];
}
int tot;
#undef int
int main()
{
	int n;
	scanf("%d",&n);
	unsigned long long a,b,c,x,p,tmp;
	for(int i=1;i<=n;i++)
	{
		//scanf("%llu%llu%llu%llu%llu",&p,&a,&b,&c,&x);
		p=readnum();a=readnum();b=readnum();c=readnum();x=readnum();
		ins(p,a,b,c,x);
		tmp=tot;
		tot=query();
		printf("%llu\n",tot-tmp);
		//pntree(root);
	}
	return 0;
}
